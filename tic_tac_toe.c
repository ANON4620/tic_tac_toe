#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
char cur_player;
int moves_left = 9;

int main()
{
    void set_up_board();
    void draw();
    void player();
    void computer();
    int check_win();
    int check_draw();
    
    initscr();
    curs_set(0);
    srand(time(NULL));
    set_up_board();
    draw();
    
    while(1)
    {
        // PLAYER'S MOVE
        cur_player = 'X';
        player();
	clear();
	draw();
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
        
        // COMPUTER'S MOVE
        cur_player = 'O';
        computer();
	clear();
	draw();
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
    }

    addstr("[Press any key to quit]");
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

void draw()
{
    addstr("     |     |     \n");
    printw("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    addstr("     |     |     \n");
    addstr("-----------------\n");
    addstr("     |     |     \n");
    printw("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    addstr("     |     |     \n");
    addstr("-----------------\n");
    addstr("     |     |     \n");
    printw("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    addstr("     |     |     \n\n");
}

void player()
{
    int move; // to store player's move
    int y, x;

    input:
    getyx(stdscr, y, x);
    move(y, 0); // ncurses function to move the cursor
    clrtoeol();

    move = getch() - '0';
    switch(move)
    {
        case 1:
        if(board[0][0] == ' ')
            board[0][0] = cur_player;
        else
            goto input;
        break;
            
        case 2:
        if(board[0][1] == ' ')
            board[0][1] = cur_player;
        else
            goto input;
        break;
            
        case 3:
        if(board[0][2] == ' ')
            board[0][2] = cur_player;
        else
            goto input;
        break;
            
        case 4:
        if(board[1][0] == ' ')
            board[1][0] = cur_player;
        else
            goto input;
        break;
            
        case 5:
        if(board[1][1] == ' ')
            board[1][1] = cur_player;
        else
            goto input;
        break;
            
        case 6:
        if(board[1][2] == ' ')
            board[1][2] = cur_player;
        else 
            goto input;
        break;
            
        case 7:
        if(board[2][0] == ' ')
            board[2][0] = cur_player;
        else
            goto input;
        break;
            
        case 8:
        if(board[2][1] == ' ')
            board[2][1] = cur_player;
        else
            goto input;
        break;
            
        case 9:
        if(board[2][2] == ' ')
            board[2][2] = cur_player;
        else
            goto input;
        break;

	default:
	goto input;
    }
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
