#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void header();
void credit();
void loadingScreen();
void rule();
void description();
void board(int a);
void resetBoard();
void getDataDuals();
void getDataBot();
void quickPlay();
void duals();
void bot();
int botMove();
int checkWin();
void resetRecord();
void showRecord();
void saveRecord();
void getRecord();

int total;
char game[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

struct dualPlayers
{
    char playerName[25];
    int win;
};
struct dualPlayers p[3];

struct bot
{
    char name[25];
    int win, draw, lose, total;
};
struct bot b;

int dualsTotal, dualsDraw, quickPlayTotal;

int main()
{
    char mode, choice;
    printf("\e[1m");
    system("color c");
    loadingScreen();
    credit();
    system("color 3");
recordChoice:
    header();
    printf(" 1) Load Previous Record \n 2) Take a New Start \n");
    printf("Press your choice: ");
    choice = getche();
    printf("\n");
    switch (choice)
    {
    case '1':
        getRecord();
        loadingScreen();
        if (total == 0)
        {
            printf("Starting a New Game, as no \n");
            printf("previous record found in our Database... \n\a");
        }
        else
        {
            printf("Record Successfully Loaded... \n");
        }
        printf("Press any key to continue...");
        getche();
        break;
    case '2':
    reset:
        resetRecord();
        loadingScreen();
        break;
    default:
        printf("\a");
        goto recordChoice;
        break;
    }
    rule();
    description();
    while (1)
    {
        resetBoard();
        system("color 3");
    mode:
        header();
        printf("Select an mode from the following \n");
        printf(" 1) Quick Play \n 2) Duals \n 3) Vs Computer \n 4) Display Record \n 5) Change Player Names \n 6) Reset Game \n 7) Exit and Save Progress \n");
        printf("Press your choice: ");
        mode = getche();
        printf("\n");
        header();
        switch (mode)
        {
        case '1':
            system("color d");
            quickPlay();
            break;
        case '2':
            system("color e");
            if (p[1].playerName[0] == '\0' || p[2].playerName[0] == '\0' || dualsTotal == 0)
            {
                getDataDuals();
            }
            duals();
            showRecord();
            break;
        case '3':
            system("color a");
            if (b.name[0] == '\0' || b.total == 0)
            {
                getDataBot();
            }
            bot();
            showRecord();
            break;
        case '4':
            showRecord();
            break;
        case '5':
        nameChangeChoice:
            header();
            printf(" 1) Duals Players Name \n 2) Vs Computer Player Name \n 3) Back \n");
            printf("Press your choice: ");
            choice = getche();
            printf("\n");
            switch (choice)
            {
            case '1':
                getDataDuals();
            yesOrNoChoiceDuals:
                header();
                printf("Do you want to keep the record of Duals games played? \n");
                printf(" 1) YES \n 2) NO \n");
                printf("Press your choice: ");
                choice = getche();
                printf("\n");
                switch (choice)
                {
                case '1':
                    break;
                case '2':
                    total -= dualsTotal;
                    dualsTotal = 0;
                    dualsDraw = 0, p[1].win = 0, p[2].win = 0;
                    break;
                default:
                    printf("\a");
                    goto yesOrNoChoiceDuals;
                    break;
                }
                loadingScreen();
                printf("Name change successful \n");
                printf("Press any key to continue...");
                getche();
                break;
            case '2':
                getDataBot();
            yesOrNoChoiceBot:
                header();
                printf("Do you want to keep the record of VS BOT games played? \n");
                printf(" 1) YES \n 2) NO \n");
                printf("Press your choice: ");
                choice = getche();
                printf("\n");
                switch (choice)
                {
                case '1':
                    break;
                case '2':
                    total -= b.total;
                    b.total = 0, b.win = 0, b.draw = 0, b.lose = 0;
                    break;
                default:
                    printf("\a");
                    goto yesOrNoChoiceBot;
                    break;
                }
                loadingScreen();
                printf("Name change successful \n");
                printf("Press any key to continue...");
                getche();
                break;
            case '3':
                goto mode;
                break;
            default:
                printf("\a");
                goto nameChangeChoice;
                break;
            }
            break;
        case '6':
            resetRecord();
            loadingScreen();
            printf("Record cleared \n");
            printf("Press anty key to continue...");
            getche();
            break;
        case '7':
            saveRecord();
            loadingScreen();
            printf("Exiting the game....\n");
            goto end;
            break;
        default:
            printf("\a");
            goto mode;
        }
    }
    printf("\e[m");
end:
    return 0;
}

void getDataDuals()
{
    for (int i = 1; i < 3; i++)
    {
        printf("\nEnter your name (Player %d): ", i);
        scanf(" %[^\n]s", &p[i].playerName);
    }
}

void getDataBot()
{
    printf("\nEnter your name: ");
    scanf(" %[^\n]s", &b.name);
}

void quickPlay()
{
    total++;
    quickPlayTotal++;
    int player, check = 1, chosed;
    char mark, choice;
    player = (total % 2 == 0) ? 1 : 2;
    while (check == 1)
    {
        player++;
        board(1);
        player = (player % 2 == 0) ? 2 : 1;
        mark = (player == 1) ? 'X' : 'O';
        printf("Player %d\'s turn \nEnter the number of box you want to place mark: ", player);
    choice:
        choice = getche();
        printf("\n");
        if (choice == 'Q' || choice == 'q')
        {
            return;
        }
        chosed = (int)(choice - 48);
        if (chosed < 1 || chosed > 9 || game[chosed] != ' ')
        {
            printf("Invalid move! \n\a");
            printf("Please enter the number of box you want to place mark: ");
            goto choice;
        }
        else
        {
            game[chosed] = mark;
        }
        check = checkWin();
    }
    board(1);
    if (check == 0)
    {
        printf("Player %d WINS the Game! \n\a", player);
    }
    else
    {
        printf("Match DRAW ! \n\a");
    }
    printf("\nPress any key to continue...");
    getche();
    board(1);
}

void duals()
{
    total++;
    dualsTotal++;
    int player, check = 1, chosed;
    char mark, choice;
    player = (total % 2 == 0) ? 1 : 2;
    while (check == 1)
    {
        player++;
        board(2);
        player = (player % 2 == 0) ? 2 : 1;
        mark = (player == 1) ? 'X' : 'O';
        printf("%s\'s turn \nEnter the number of box you want to place mark: ", p[player].playerName);
    choice:
        choice = getche();
        printf("\n");
        if (choice == 'Q' || choice == 'q')
        {
            dualsDraw++;
            return;
        }
        chosed = (int)(choice - 48);
        if (chosed < 1 || chosed > 9 || game[chosed] != ' ')
        {
            printf("Invalid move! \n\a");
            printf("Please enter the number of box you want to place mark: ");
            goto choice;
        }
        else
        {
            game[chosed] = mark;
        }
        check = checkWin();
    }
    board(2);
    if (check == 0)
    {
        printf("%s WINS the Game! \n\a", p[player].playerName);
        p[player].win++;
    }
    else
    {
        printf("Match DRAW ! \n\a");
        dualsDraw++;
    }
    printf("\nPress any key to continue...");
    getche();
    board(2);
}

void bot()
{
    total++;
    b.total++;
    int player, check = 1, chosed;
    char mark, choice;
    while (check == 1)
    {
        player++;
        board(3);
        player = (player % 2 == 0) ? 2 : 1;
        mark = (player == 1) ? 'X' : 'O';
        if (player == 1)
        {
            printf("%s\'s turn \nEnter the number of box you want to place mark: ", b.name);
        choice:
            choice = getche();
            printf("\n");
            if (choice == 'Q' || choice == 'q')
            {
                b.draw++;
                return;
            }
            chosed = (int)(choice - 48);
            if (chosed < 1 || chosed > 9 || game[chosed] != ' ')
            {
                printf("Invalid move! \n\a");
                printf("Please enter the number of box you want to place mark: ");
                goto choice;
            }
            else
            {
                game[chosed] = mark;
            }
            check = checkWin();
            if (check == 0)
            {
                break;
            }
        }
        else
        {
            board(3);
            printf("The bot is thinking...");
            Sleep(500);
            game[botMove()] = mark;
            check = checkWin();
        }
    }
    board(3);
    if (check == 0)
    {
        if (player == 1)
        {
            printf("%s WINS the Game! \n\a", b.name);
            b.lose++;
        }
        else
        {
            printf("BOT WINS the Game! \n\a");
            b.win++;
        }
    }
    else
    {
        printf("Match DRAW ! \n\a");
        b.draw++;
    }
    printf("\nPress any key to continue...");
    getche();
    board(3);
}

void saveRecord()
{
    FILE *ptr;
    ptr = fopen("record.bin", "wb");
    if (ptr == NULL)
    {
        printf("Error loading or creating file... \n");
        printf("Exiting the program... \n");
        exit(1);
    }
    fprintf(ptr, "%d\n", total);
    fprintf(ptr, "%d\n", quickPlayTotal);
    fprintf(ptr, "%d\n", dualsTotal);
    fprintf(ptr, "%d\n", dualsDraw);
    fprintf(ptr, "%s\n", p[1].playerName);
    fprintf(ptr, "%d\n", p[1].win);
    fprintf(ptr, "%s\n", p[2].playerName);
    fprintf(ptr, "%d\n", p[2].win);
    fprintf(ptr, "%d\n", b.total);
    fprintf(ptr, "%s\n", b.name);
    fprintf(ptr, "%d\n", b.lose);
    fprintf(ptr, "%d\n", b.win);
    fprintf(ptr, "%d\n", b.draw);
}

void getRecord()
{
    FILE *ptr;
    ptr = fopen("record.bin", "rb");
    if (ptr == NULL)
    {
        saveRecord();
    }
    fscanf(ptr, "%d\n", &total);
    fscanf(ptr, "%d\n", &quickPlayTotal);
    fscanf(ptr, "%d\n", &dualsTotal);
    fscanf(ptr, "%d\n", &dualsDraw);
    fscanf(ptr, "%[^\n]s\n", p[1].playerName);
    fflush(stdin);
    fscanf(ptr, "%d\n", &p[1].win);
    fscanf(ptr, "%[^\n]s\n", p[2].playerName);
    fflush(stdin);
    fscanf(ptr, "%d\n", &p[2].win);
    fscanf(ptr, "%d\n", &b.total);
    fscanf(ptr, "%[^\n]s\n", b.name);
    fflush(stdin);
    fscanf(ptr, "%d\n", &b.lose);
    fscanf(ptr, "%d\n", &b.win);
    fscanf(ptr, "%d\n", &b.draw);
}

void resetRecord()
{
    total = 0;
    quickPlayTotal = 0;
    dualsTotal = 0;
    dualsDraw = 0, p[1].win = 0, p[2].win = 0;
    b.total = 0, b.win = 0, b.draw = 0, b.lose = 0;
}

void showRecord()
{
    printf("\n\t\tTotal Game(s) = %d \n\n\n", total);
    if (quickPlayTotal != 0)
    {
        printf("\t\t === Quick Play === \n\n");
        printf("\t\tGames Played = %d \n\n\n", quickPlayTotal);
    }

    if (dualsTotal != 0)
    {
        printf("\t\t ===== Duals ===== \n\n");
        printf("\t\tGames Played = %d \n", dualsTotal);
        printf("\t\t%s\'s Win(s) = %d \n", p[1].playerName, p[1].win);
        printf("\t\t%s\'s Win(s) = %d \n", p[2].playerName, p[2].win);
        printf("\t\tMatch Draw(s) = %d \n\n\n", dualsDraw);
    }
    if (b.total != 0)
    {
        printf("\t\t ===== VS Bot ===== \n\n");
        printf("\t\tGames Played = %d \n", b.total);
        printf("\t\t%s\'s Win(s) = %d \n", b.name, b.lose);
        printf("\t\tBOT\'s Win(s) = %d \n", b.win);
        printf("\t\tMatch Draw(s) = %d \n\n\n", b.draw);
    }
    printf("\nPress any key to continue...");
    getche();
}

void board(int a)
{
    header();
    if (a == 2)
    {
        printf("Player 1 = %s \n", p[1].playerName);
        printf("Player 2 = %s \n", p[2].playerName);
    }
    else if (a == 3)
    {
        printf("Player 1 = %s \n", b.name);
        printf("Player 2 = BOT \n");
    }
    printf("\n   Player 1 (X)  -  Player 2 (O) \t\t      Board\n\n");
    printf("\t     |     |      \t\t");
    printf("\t     |     |      \n");
    printf("\t  %c  |  %c  |  %c  \t\t", game[1], game[2], game[3]);
    printf("\t  %d  |  %d  |  %d   \n", 1, 2, 3);
    printf("\t_____|_____|_____ \t\t");
    printf("\t_____|_____|_____ \n");
    printf("\t     |     |      \t\t");
    printf("\t     |     |      \n");
    printf("\t  %c  |  %c  |  %c  \t\t", game[4], game[5], game[6]);
    printf("\t  %d  |  %d  |  %d   \n", 4, 5, 6);
    printf("\t_____|_____|_____ \t\t");
    printf("\t_____|_____|_____ \n");
    printf("\t     |     |      \t\t");
    printf("\t     |     |      \n");
    printf("\t  %c  |  %c  |  %c  \t\t", game[7], game[8], game[9]);
    printf("\t  %d  |  %d  |  %d   \n", 7, 8, 9);
    printf("\t     |     |      \t\t");
    printf("\t     |     |      \n\n");
    printf("Game Number = %d \n\n", total);
}

void loadingScreen()
{
    char spinningCursor[] = {'|', '/', '-', '\\'};
    for (int i = 0; i <= 20; i++)
    {
        header();
        printf("\n\n\t");
        printf("Loading [ ");
        for (int j = 0; j < i; j++)
        {
            printf("%c", 254);
        }
        for (int j = 0; j <= 20 - i; j++)
        {
            printf(" ");
        }
        printf("] %c %d%% \n\n", spinningCursor[i % 4], i * 5);
        // Sleep(10);
    }
    // printf("\n\n\n\nLoading completed... \n");
}

void resetBoard()
{
    for (int i = 0; i < 10; i++)
    {
        game[i] = ' ';
    }
}

void description()
{
    system("color e");
    system("cls");
    header();
    printf("\t\t     Description \n");
    printf("\t\t ------------------ \n\n");
    printf("This game has 3 gamemodes \n\n");
    printf("1) Quickplay: In this gamemode 2, player will be able to \n");
    printf("   play the game instantly. (This gamemode doesn\'t keep \n");
    printf("   record of player Wins and Loses, Total number of games still counts) \n\n");
    printf("2) Duals: In this gamemode, 2 player will be able to \n");
    printf("   play the game with each other and the game will maintain \n");
    printf("   a proper record for Wins, Loses, and Draws of the players. \n\n");
    printf("3) Vs Computer: In this gamemode, you will be able to play the \n");
    printf("   game with BOT on the hardest difficulty. \n");
    printf("   (It is impossible to defeat the BOT in this game) \n\n");
    printf("Press any key to continue...");
    getche();
}

void rule()
{
    system("color c");
    system("cls");
    header();
    printf("\t\t     Game Rules \n");
    printf("\t\t ------------------ \n\n");
    printf("1) This game will be played on a 3 x 3 Grid \n");
    printf("2) Two players will place the (X) or (O) Mark alternatively \n");
    printf("   (Mark will be automatically changed for players) \n");
    printf("3) Place the mark by entering the respective number of the box \n");
    printf("4) Enter Q anytime between the game to exit the game with conclusion of Draw \n");
    printf("\nPress any key to continue...");
    getche();
}

void credit()
{
    header();
    printf("\n\n\t------------------------------------\n");
    printf("\t|      PROJECT BY DATA SCIENCE     | \n");
    printf("\t|   ----------------------------   | \n");
    printf("\t|                                  | \n");
    printf("\t|   DT-22039 - Abdul Rafay Khatri  | \n");
    printf("\t|      DT-22006 - Ajiya Anwar      | \n");
    printf("\t|      DT-22010 - Hasan Hayat      | \n");
    printf("\t|                                  | \n");
    printf("\t------------------------------------\n");
    getche();
    printf("\nPress any key to continue...");
    getche();
}

void header()
{
    system("cls");
    printf("\n\t\t==== TIC TAC TOE ====\n\n");
}

int checkWin()
{
    if (game[1] == game[2] && game[2] == game[3] && game[1] != ' ')
    {
        return 0;
    }
    else if (game[4] == game[5] && game[5] == game[6] && game[4] != ' ')
    {
        return 0;
    }
    else if (game[7] == game[8] && game[8] == game[9] && game[7] != ' ')
    {
        return 0;
    }
    else if (game[1] == game[4] && game[4] == game[7] && game[1] != ' ')
    {
        return 0;
    }
    else if (game[2] == game[5] && game[5] == game[8] && game[2] != ' ')
    {
        return 0;
    }
    else if (game[3] == game[6] && game[6] == game[9] && game[3] != ' ')
    {
        return 0;
    }
    else if (game[1] == game[5] && game[5] == game[9] && game[1] != ' ')
    {
        return 0;
    }
    else if (game[3] == game[5] && game[5] == game[7] && game[3] != ' ')
    {
        return 0;
    }
    else
    {
        for (int i = 1; i < 10; i++)
        {
            if (game[i] == ' ')
            {
                return 1;
            }
        }
        return -1;
    }
}

int botMove()
{
    if (game[5] == ' ')
    {
        return 5;
    }
    else if (game[1] == game[2] && game[3] == ' ' && game[1] != ' ' && game[1] == 'O')
    {
        return 3;
    }
    else if (game[2] == game[3] && game[1] == ' ' && game[2] != ' ' && game[2] == 'O')
    {
        return 1;
    }
    else if (game[1] == game[3] && game[2] == ' ' && game[1] != ' ' && game[1] == 'O')
    {
        return 2;
    }
    else if (game[4] == game[5] && game[6] == ' ' && game[4] != ' ' && game[4] == 'O')
    {
        return 6;
    }
    else if (game[5] == game[6] && game[4] == ' ' && game[5] != ' ' && game[5] == 'O')
    {
        return 4;
    }
    else if (game[4] == game[6] && game[5] == ' ' && game[4] != ' ' && game[4] == 'O')
    {
        return 5;
    }
    else if (game[7] == game[8] && game[9] == ' ' && game[7] != ' ' && game[7] == 'O')
    {
        return 9;
    }
    else if (game[8] == game[9] && game[7] == ' ' && game[8] != ' ' && game[8] == 'O')
    {
        return 7;
    }
    else if (game[7] == game[9] && game[8] == ' ' && game[7] != ' ' && game[7] == 'O')
    {
        return 8;
    }
    else if (game[1] == game[4] && game[7] == ' ' && game[1] != ' ' && game[1] == 'O')
    {
        return 7;
    }
    else if (game[4] == game[7] && game[1] == ' ' && game[4] != ' ' && game[4] == 'O')
    {
        return 1;
    }
    else if (game[1] == game[7] && game[4] == ' ' && game[1] != ' ' && game[1] == 'O')
    {
        return 4;
    }
    else if (game[2] == game[5] && game[8] == ' ' && game[2] != ' ' && game[2] == 'O')
    {
        return 8;
    }
    else if (game[5] == game[8] && game[2] == ' ' && game[5] != ' ' && game[5] == 'O')
    {
        return 2;
    }
    else if (game[2] == game[8] && game[5] == ' ' && game[2] != ' ' && game[2] == 'O')
    {
        return 5;
    }
    else if (game[3] == game[6] && game[9] == ' ' && game[3] != ' ' && game[3] == 'O')
    {
        return 9;
    }
    else if (game[6] == game[9] && game[3] == ' ' && game[6] != ' ' && game[6] == 'O')
    {
        return 3;
    }
    else if (game[3] == game[9] && game[6] == ' ' && game[3] != ' ' && game[3] == 'O')
    {
        return 6;
    }
    else if (game[1] == game[5] && game[9] == ' ' && game[1] != ' ' && game[1] == 'O')
    {
        return 9;
    }
    else if (game[5] == game[9] && game[1] == ' ' && game[5] != ' ' && game[5] == 'O')
    {
        return 1;
    }
    else if (game[1] == game[9] && game[5] == ' ' && game[1] != ' ' && game[1] == 'O')
    {
        return 5;
    }
    else if (game[3] == game[5] && game[7] == ' ' && game[3] != ' ' && game[3] == 'O')
    {
        return 7;
    }
    else if (game[5] == game[7] && game[3] == ' ' && game[5] != ' ' && game[5] == 'O')
    {
        return 3;
    }
    else if (game[3] == game[7] && game[5] == ' ' && game[3] != ' ' && game[3] == 'O')
    {
        return 5;
    }
    else if (game[1] == game[2] && game[3] == ' ' && game[1] != ' ')
    {
        return 3;
    }
    else if (game[2] == game[3] && game[1] == ' ' && game[2] != ' ')
    {
        return 1;
    }
    else if (game[1] == game[3] && game[2] == ' ' && game[1] != ' ')
    {
        return 2;
    }
    else if (game[4] == game[5] && game[6] == ' ' && game[4] != ' ')
    {
        return 6;
    }
    else if (game[5] == game[6] && game[4] == ' ' && game[5] != ' ')
    {
        return 4;
    }
    else if (game[4] == game[6] && game[5] == ' ' && game[4] != ' ')
    {
        return 5;
    }
    else if (game[7] == game[8] && game[9] == ' ' && game[7] != ' ')
    {
        return 9;
    }
    else if (game[8] == game[9] && game[7] == ' ' && game[8] != ' ')
    {
        return 7;
    }
    else if (game[7] == game[9] && game[8] == ' ' && game[7] != ' ')
    {
        return 8;
    }
    else if (game[1] == game[4] && game[7] == ' ' && game[1] != ' ')
    {
        return 7;
    }
    else if (game[4] == game[7] && game[1] == ' ' && game[4] != ' ')
    {
        return 1;
    }
    else if (game[1] == game[7] && game[4] == ' ' && game[1] != ' ')
    {
        return 4;
    }
    else if (game[2] == game[5] && game[8] == ' ' && game[2] != ' ')
    {
        return 8;
    }
    else if (game[5] == game[8] && game[2] == ' ' && game[5] != ' ')
    {
        return 2;
    }
    else if (game[2] == game[8] && game[5] == ' ' && game[2] != ' ')
    {
        return 5;
    }
    else if (game[3] == game[6] && game[9] == ' ' && game[3] != ' ')
    {
        return 9;
    }
    else if (game[6] == game[9] && game[3] == ' ' && game[6] != ' ')
    {
        return 3;
    }
    else if (game[3] == game[9] && game[6] == ' ' && game[3] != ' ')
    {
        return 6;
    }
    else if (game[1] == game[5] && game[9] == ' ' && game[1] != ' ')
    {
        return 9;
    }
    else if (game[5] == game[9] && game[1] == ' ' && game[5] != ' ')
    {
        return 1;
    }
    else if (game[1] == game[9] && game[5] == ' ' && game[1] != ' ')
    {
        return 5;
    }
    else if (game[3] == game[5] && game[7] == ' ' && game[3] != ' ')
    {
        return 7;
    }
    else if (game[5] == game[7] && game[3] == ' ' && game[5] != ' ')
    {
        return 3;
    }
    else if (game[3] == game[7] && game[5] == ' ' && game[3] != ' ')
    {
        return 5;
    }
    else if (game[2] == game[4] && game[1] == ' ' && game[2] != ' ')
    {
        return 1;
    }
    else if (game[2] == game[6] && game[3] == ' ' && game[2] != ' ')
    {
        return 3;
    }
    else if (game[4] == game[8] && game[7] == ' ' && game[4] != ' ')
    {
        return 7;
    }
    else if (game[6] == game[8] && game[9] == ' ' && game[6] != ' ')
    {
        return 9;
    }
    else if (game[2] == game[7] && game[1] == ' ' && game[2] != ' ')
    {
        return 1;
    }
    else if (game[2] == game[9] && game[3] == ' ' && game[2] != ' ')
    {
        return 3;
    }
    else if (game[4] == game[3] && game[1] == ' ' && game[4] != ' ')
    {
        return 1;
    }
    else if (game[4] == game[9] && game[7] == ' ' && game[4] != ' ')
    {
        return 7;
    }
    else if (game[6] == game[1] && game[3] == ' ' && game[6] != ' ')
    {
        return 3;
    }
    else if (game[6] == game[7] && game[9] == ' ' && game[6] != ' ')
    {
        return 9;
    }
    else if (game[8] == game[1] && game[7] == ' ' && game[8] != ' ')
    {
        return 7;
    }
    else if (game[8] == game[3] && game[9] == ' ' && game[8] != ' ')
    {
        return 9;
    }
    else if (game[1] == game[9] && game[1] == 'X' && (game[2] == ' ' || game[4] == ' ' || game[6] == ' ' || game[8] == ' '))
    {
        if (game[6] == ' ')
        {
            return 6;
        }
        else if (game[4] == ' ')
        {
            return 4;
        }
        else if (game[2] == ' ')
        {
            return 2;
        }
        else if (game[8] == ' ')
        {
            return 8;
        }
    }
    else if (game[3] == game[7] && game[3] == 'X' && (game[2] == ' ' || game[4] == ' ' || game[6] == ' ' || game[8] == ' '))
    {
        if (game[6] == ' ')
        {
            return 6;
        }
        else if (game[4] == ' ')
        {
            return 4;
        }
        else if (game[2] == ' ')
        {
            return 2;
        }
        else if (game[8] == ' ')
        {
            return 8;
        }
    }
    else if (game[7] == ' ')
    {
        return 7;
    }
    else if (game[3] == ' ')
    {
        return 3;
    }
    else if (game[1] == ' ')
    {
        return 1;
    }
    else if (game[9] == ' ')
    {
        return 9;
    }
    else if (game[6] == ' ')
    {
        return 6;
    }
    else if (game[4] == ' ')
    {
        return 4;
    }
    else if (game[2] == ' ')
    {
        return 2;
    }
    else if (game[8] == ' ')
    {
        return 8;
    }
}