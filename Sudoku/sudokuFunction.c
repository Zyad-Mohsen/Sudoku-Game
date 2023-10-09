#include <stdio.h>
#include <stdlib.h>

//Define color codes
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"
//to print in color on console

int level=-1;  //difficulty level from 0 to 4 (-1 indicates user hasn't played yet)
char sudoku_game[9][9]= {0};

/*
sudoku_game is an empty array is a combination that stores the original current level array
and all inputs of the user, by comparing the original array with the copy
it benefits in printing new inputs by user only in color
and to check if user is trying to change a number of the
original game not of his inputs
*/

void sudoku_intro(void) //to welcome the user and give him the game rules
{
    printf(COLOR_YELLOW"***** WELCOME TO THE SUDOKU GAME! *****\n\n");
    printf("INSTRUCTIONS: \n\n");
    printf("1- ENTER ROW, COLUMN AND A NUMBER ALL MUST BE IN RANGE (1 TO 9)\n");
    printf("2- YOU CAN OVERWRITE A NUMBER ONLY IF NOT REPEATED IN ROW AND COLUMN OR SUBGRID\n");
    printf("3- TO DELETE A NUMBER SELECT ROW AND COLUMN AND ENTER 0\n");
    printf("4- EACH LEVEL GETS A LITTLE BIT HARDER!\n\n");
    printf("GOOD LUCK ;) \n\n");
    printf("PRESS ENTER KEY TO PLAY\n"COLOR_RESET);
    getchar();     //WAIT FOR ENTER KEY TO BE PUSHED
    fflush(stdin); //CLEAR OR FLUSH INPUT BUFFER
}

void sudoku_copyGame(const char sudoku[][9])  //it copies the current level original array into the empty array
{
    int i,j;
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            sudoku_game[i][j]=sudoku[i][j];
        }
    }
}

void sudoku_print(const char sudoku[][9]) //prints the original game in white and user input in different color
{
    system("cls"); //to clear console
    int i,j;
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            if(!sudoku_game[i][j])  //zero indicates that this position is empty
            {
                printf("  ");
            }
            else    //a number exists in this position
            {
                if(sudoku[i][j])     //check if this number is from user input or in the original game array
                    printf(" %d",sudoku_game[i][j]);   //print number in white
                else
                    printf(COLOR_CYAN" %d"COLOR_RESET,sudoku_game[i][j]); //print user input in cyan color
            }
            if(j==2||j==5)
            {
                printf(" |");   //print game columns borders
            }
        }
        printf("\n");
        if(i==2||i==5)
        {
            printf(" - - - - - - - - - - -\n"); //print game rows borders
        }
    }
    printf("\n");
}

/*
sudoku_isAvailable function checks if:
1- rows, columns and number input itself is from (1 to 9)
2- user entered 0 to clear a position in game
3- desired position is fixed from original game or can be changed
4- input number is repeated in the desired row or column
*/
int sudoku_isAvailable(const char sudoku[][9],int num,int row,int col)
{
    int i;
    int subgrid_RowStart = 3*((row-1)/3);
    int subgrid_ColStart = 3*((col-1)/3);

    //Check if row and column are within bounds
    if(!(row>0&&row<10))
    {
        printf(COLOR_RED"\nInvalid Input!, Row Is Out of Range\n"COLOR_RESET);
        return 0;
    }
    if(!(col>0&&col<10))
    {
        printf(COLOR_RED"\nInvalid Input!, Column Is Out of Range\n"COLOR_RESET);
        return 0;
    }
    if(!(num>0&&num<10))  //num not (0 to 9)
    {
        if(num==0) //zero means user wants to clear a position
        {
            return 1;
        }
        else
        {
            printf(COLOR_RED"\nInvalid Input!, Number Is Out of Range\n"COLOR_RESET);
            return 0;
        }
    }

    if(sudoku[row-1][col-1]!=0)  //number is fixed and part of the original array, can't be changed
    {
        printf(COLOR_RED"\nInvalid Input,This Number Can't Be Changed!\n"COLOR_RESET);
        return 0;
    }

    for(i=0; i<9; i++)
    {
        if(sudoku_game[row-1][i]==num) //number is repeated in row
        {
            printf(COLOR_RED"\n%d Is Repeated in Row (%d)!\n"COLOR_RESET,num,row);
            return 0;
        }
        if(sudoku_game[i][col-1]==num) //number is repeated in column
        {
            printf(COLOR_RED"\n%d Is Repeated in Column (%d)!\n"COLOR_RESET,num,col);
            return 0;
        }
        if(sudoku_game[subgrid_RowStart+i/3][subgrid_ColStart+i%3]==num) //number is repeated in subgrid
        {
            printf(COLOR_RED"\n%d Is Repeated in This Subgrid\n"COLOR_RESET,num);
            return 0;
        }
    }
    return 1;  //inputs by user are valid
}

void sudoku_takeNumber(const char sudoku[][9]) //takes user inputs and edits the sudoku
{
    int num,row,col,valid;
    do
    {
        printf("ENTER ROW: ");
        scanf("%d",&row);
        printf("ENTER COLUMN: ");
        scanf("%d",&col);
        printf("ENTER YOUR NUMBER: ");
        scanf("%d",&num);
        valid=sudoku_isAvailable(sudoku,num,row,col);
        if(valid)
        {
            sudoku_game[row-1][col-1]=num;
        }
        else
        {
            printf(COLOR_RED"Please Try Again.\n\n"COLOR_RESET); //input is not valid
        }
    }
    while(!valid); //take input again if previous is not available
}

int sudoku_isFull(void) //checks if level is complete
{
    int i,j;
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            if(!sudoku_game[i][j]) //if all board is (1 to 9) and not 0, level is compelete
            {
                return 0;
            }
        }
    }
    sudoku_print(sudoku_game);
    printf(COLOR_GREEN"\nCONGRATULATIONS!!\nYOU SOLVED THE PUZZLE.\n"COLOR_RESET);
    return 1;      //level solved
}

/*
sudoku_again function
checks if user wants to end the game or
play next level after finishing each level
also checks if user solved all 5 levels
*/

int sudoku_again(void)
{
    int again=1;
    if(level==-1) // -1 indicates that first level not solved yet
    {
        level++;
        return again;
    }
    else if(level<4)
    {
        printf("\nENTER A NUMBER TO PLAY NEXT LEVEL\nOR ENTER 0 IF YOU WANT TO END GAME.\n");
        scanf("%d",&again);
        level++;
        return again;
    }
    else    //all levels solved
    {
        printf(COLOR_GREEN"YOU'RE A CHAMPION!!\nYOU SOLVED ALL PUZZLES.\n\n"COLOR_RESET);
        return 0;
    }
}

