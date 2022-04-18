#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
char cur_player = 'X';
int moves_left = 9;

int main()
{
    void set_up_board();
    void draw(int);
    void player();
    void computer();
    int check_win();
    int check_draw();
   
    char temp;

    initscr();
    noecho();
    curs_set(0);
    srand(time(NULL));
    set_up_board();
    draw(1);
    
    while(1)
    {
        if(cur_player == 'X')
	{
        	player();
		temp = 'O';
	}
	else
	{
		computer();
		temp = 'X';
	}

	clear();
	draw(0);

        if(check_win())
        {
            printw("%c wins!\n\n", cur_player);
            break;
        }
        if(check_draw())
        {
            addstr("Draw!\n\n");
            break;
        }

	cur_player = temp;
    }

    addstr("[Press any key to quit]");
    refresh();
    getch();
    endwin();

    return 0;
}

void set_up_board()
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void draw(int init)
{
    if(init)
    {
    	addstr("     |     |     \n");
	addstr("  1  |  2  |  3  \n");
    	addstr("     |     |     \n");
	addstr("-----------------\n");
	addstr("     |     |     \tPlayer - X\n");
	addstr("  4  |  5  |  6  \tComputer - O\n");
    	addstr("     |     |     \n");
    	addstr("-----------------\n");
    	addstr("     |     |     \n");
    	addstr("  7  |  8  |  9  \n");
	addstr("     |     |     \n\n");
    }
    else
    {
    	addstr("     |     |     \n");
    	printw("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    	addstr("     |     |     \n");
    	addstr("-----------------\n");
    	addstr("     |     |     \tPlayer - X\n");
    	printw("  %c  |  %c  |  %c  \tComputer - O\n", board[1][0], board[1][1], board[1][2]);
    	addstr("     |     |     \n");
    	addstr("-----------------\n");
    	addstr("     |     |     \n");
    	printw("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    	addstr("     |     |     \n\n");
    }

    refresh();
}

void player()
{
    int move, row, col;

    do
    {
    	move = getch() - '1';
    	row = move / 3;
    	col = move % 3;

    } while(board[row][col] != ' ');

    board[row][col] = cur_player;
    --moves_left;
}

void computer()
{
    char row[moves_left], col[moves_left];
    int k = 0, random;
            
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                row[k] = i;
                col[k] = j;
                ++k;
            }
        }
    }
    random = rand() % moves_left;
    board[row[random]][col[random]] = cur_player;
    --moves_left;
}

int check_win()
{
    // CHECK ROWS
    for(int i = 0; i < 3; i++)
        if((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][0] != ' '))
            return 1;
            
    // CHECK COLUMNS
    for(int i = 0; i < 3; i++)
        if((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && (board[0][i] != ' '))
            return 1;
            
    // CHECK DIAGONALS
    if( ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] != ' ')) || ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && (board[0][2] != ' ')) )
        return 1;
        
    return 0;
}

int check_draw()
{
    if(moves_left == 0)
        return 1;

    return 0;
}
