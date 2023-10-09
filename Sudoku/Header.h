extern int level;       //external global variable indicates level
void sudoku_intro(void);
void sudoku_copyGame(const char sudoku[][9]);
void sudoku_print(const char sudoku[][9]);
int sudoku_isAvailable(const char sudoku[][9],int num,int row,int col);
void sudoku_takeNumber(const char sudoku[][9]);
int sudoku_isFull(void);
int sudoku_again(void);
void startTimer(void);
void stopTimer(void);
void getElapsedTime(void);
