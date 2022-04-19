#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER 'X'
#define COMPUTER 'O'

void clear_board();
void draw();
void player();
void computer();
int check_win();
int check_draw();

char board[3][3] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};
int moves_left = 9;
int won = 0;

int main()
{
    char cur_player = PLAYER;
    char next_player;

    initscr();
    noecho();
    curs_set(0);
    srand(time(NULL));
    draw();
    clear_board();
    
    while(1)
    {
        if(cur_player == PLAYER)
	{
        	player();
		next_player = COMPUTER;
	}
	else
	{
		computer();
		next_player = PLAYER;
	}
	moves_left--;

	clear();
	draw();

        if(won || check_win())
        {
            printw("%c wins!\n\n", cur_player);
            break;
        }
        if(check_draw())
        {
            addstr("Draw!\n\n");
            break;
        }

	cur_player = next_player;
    }

    addstr("[Press any key to quit]");
    refresh();
    getch();
    endwin();

    return 0;
}

void clear_board()
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void draw()
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

    refresh();
}

void player()
{
    int move, row, col;

    while(1)
    {
    	move = getch() - '1';
    	row = move / 3;
    	col = move % 3;

	if(move >= 0 && move <= 8 && board[row][col] == ' ')
		break;
    }

    board[row][col] = PLAYER;
}

void computer()
{
    char row[moves_left], col[moves_left];
    int k = 0;

    // Find all possible moves
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                row[k] = i;
                col[k] = j;
                k++;
            }
        }
    }

    // Check which move can make a win
    for(int i = 0; i < moves_left; i++)
    {
	board[row[i]][col[i]] = COMPUTER;
	if(check_win())
	{
		won = 1;
		return;
	}
	board[row[i]][col[i]] = ' ';
    }

    // If no move can make a win, check if computer can block the player
    for(int i = 0; i < moves_left; i++)
    {
	    board[row[i]][col[i]] = PLAYER;
	    if(check_win())
	    {
		    board[row[i]][col[i]] = COMPUTER;
		    return;
	    }
	    board[row[i]][col[i]] = ' ';
    }

    // Check if a move can be made at the center
    if(board[1][1] == ' ')
    {
	    board[1][1] = COMPUTER;
    }
    // Check the corners
    else if(board[0][0] == ' ' && board[0][2] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
    {
	    board[0][0] = COMPUTER;
    }
    else if(board[0][0] == PLAYER && board[2][2] == ' ')
    {
	    board[2][2] = COMPUTER;
    }
    else if(board[2][2] == PLAYER && board[0][0] == ' ')
    {
	    board[0][0] = COMPUTER;
    }
    else if(board[0][2] == PLAYER && board[2][0] == ' ')
    {
	    board[2][0] = COMPUTER;
    }
    else if(board[2][0] == PLAYER && board[0][2] == ' ')
    {
	    board[0][2] = COMPUTER;
    }
    // Check the sides
    else if(board[0][1] == ' ')
    {
	    board[0][1] = COMPUTER;
    }
    else if(board[1][0] == ' ')
    {
	    board[1][0] = COMPUTER;
    }
    else if(board[1][2] == ' ')
    {
	    board[1][2] = COMPUTER;
    }
    else
    {
	    board[2][1] = COMPUTER;
    }
}

int check_win()
{
    // CHECK ROWS
    for(int i = 0; i < 3; i++)
    {
        if((board[i][0] != ' ') && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
	{
            return 1;
	}
    }
            
    // CHECK COLUMNS
    for(int i = 0; i < 3; i++)
    {
        if((board[0][i] != ' ') && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
	{
            return 1;
	}
    }
            
    // CHECK DIAGONALS
    if( ((board[0][0] != ' ') && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) || ((board[0][2] != ' ') && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0])) )
    {
        return 1;
    }
        
    return 0;
}

int check_draw()
{
    if(moves_left == 0)
    {
	    return 1;
    }

    return 0;
}
