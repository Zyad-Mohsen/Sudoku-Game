#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
    char sudoku[5][9][9]=   //various levels of sudoku with various difficulties
    {
        {
            {0,0,9,0,8,5,0,6,3},        //easy level
            {0,7,0,9,6,0,0,0,0},
            {5,0,1,0,0,4,0,0,0},
            {0,0,6,7,0,3,0,0,4},
            {0,4,0,2,1,0,3,9,0},
            {8,0,0,0,9,0,0,5,7},
            {9,8,4,5,0,0,6,0,0},
            {0,0,7,6,4,9,0,3,0},
            {6,1,0,0,2,0,0,4,0}
        },
        {
            {4,0,7,0,0,0,0,1,0},        //medium level
            {9,0,0,0,4,2,6,0,7},
            {6,0,3,0,0,7,0,0,0},
            {0,3,2,0,8,0,0,0,0},
            {5,0,0,0,0,0,0,6,2},
            {0,0,4,2,0,0,5,0,8},
            {0,0,6,0,0,3,0,9,0},
            {0,0,0,0,5,1,0,0,0},
            {8,7,1,0,0,0,0,4,0}
        },
        {
            {0,0,0,0,0,0,0,0,3},        //hard level
            {9,0,0,3,0,2,0,0,0},
            {6,8,0,0,0,0,0,5,0},
            {1,0,0,0,0,5,0,0,9},
            {5,0,0,7,0,0,0,6,2},
            {0,0,4,0,1,0,5,3,8},
            {3,4,0,8,0,0,7,0,0},
            {0,0,1,9,0,0,0,0,0},
            {0,5,0,0,7,3,0,0,0}

        },
        {
            {7,0,0,1,0,0,9,0,0},        //expert level
            {0,0,0,0,0,0,4,0,0},
            {9,4,0,0,0,0,0,0,2},
            {0,0,0,0,1,0,8,2,0},
            {0,0,0,0,2,0,0,5,0},
            {0,0,0,7,9,4,0,0,0},
            {0,0,1,0,0,7,0,0,0},
            {0,0,8,0,0,0,0,3,6},
            {0,2,0,6,0,0,0,0,0}
        },
        {
            {1,0,8,5,3,0,6,0,0},        //evil level
            {0,2,0,0,0,1,0,0,0},
            {0,4,0,0,0,0,0,0,8},
            {8,0,5,0,0,3,0,0,9},
            {0,0,4,0,0,0,0,0,0},
            {0,0,0,0,9,0,2,0,0},
            {3,0,9,0,0,5,0,0,2},
            {0,0,0,6,0,0,0,7,0},
            {0,1,0,0,0,0,0,0,0}
        }
    };

    while(sudoku_again())  //while user has not finished all levels and still wants to play
    {
        sudoku_intro();         //welcoming user
        sudoku_copyGame(sudoku[level]);
        startTimer();

        while(!sudoku_isFull()) //while current level isn't solved yet
        {
            sudoku_print(sudoku[level]);
            sudoku_takeNumber(sudoku[level]);
        }
        stopTimer();
        getElapsedTime();
    }
    return 0;
}

/*
this is a 9*9 sudoku game with 5 levels each
level is harder than the previous level
user enters the desired row, column(position) and number
if these inputs are valid the sudoku board gets edited according to
these inputs and new inputs are printed in different color than original
if inputs are not valid the user gets a warning in red and is asked to try again with
valid numbers, user can overwrite any previous input of his as long as it's not repeated
in row or column, user also can delete any previous input by selecting position and entering 0
as long as the user can't enter repeated numbers, this means if the
board has all non-zero values then the board is complete and no number is repeated
thus meaning the current level is solved and user gets a congratulations message in green.
after each level user can either terminate the game or play the next level
of a harder difficulty, if all levels are solved user gets a congratulations message and program
is terminated.
DEVELOPED BY: ZYAD M.ABOZEID
*/
