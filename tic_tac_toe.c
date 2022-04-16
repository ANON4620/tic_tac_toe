#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
int moves_left = 9;

int main()
{
    void set_up_board();
    void draw();
    void player();
    void computer();
    int check_win();
    int check_draw();
    
    char cur_player;
    
    initscr();
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
            printw("%c wins!", cur_player);
            break;
        }
        if(check_draw())
        {
            addstr("Draw!");
            break;
        }
        
        // COMPUTER'S MOVE
        cur_player = 'O';
        computer();
	clear();
	draw();
        if(check_win())
        {
            printw("%c wins!", cur_player);
            break;
        }
        if(check_draw())
        {
            addstr("Draw!");
            break;
        }
    }

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
    addstr("     |     |     \n");
    addch('\n');
}

void player()
{
    int move;
    
    input:
    move = getch() - 48;
    switch(move)
    {
        case 1:
        if(board[0][0] == ' ')
            board[0][0] = 'X';
        else
            goto input;
        break;
            
        case 2:
        if(board[0][1] == ' ')
            board[0][1] = 'X';
        else
            goto input;
        break;
            
        case 3:
        if(board[0][2] == ' ')
            board[0][2] = 'X';
        else
            goto input;
        break;
            
        case 4:
        if(board[1][0] == ' ')
            board[1][0] = 'X';
        else
            goto input;
        break;
            
        case 5:
        if(board[1][1] == ' ')
            board[1][1] = 'X';
        else
            goto input;
        break;
            
        case 6:
        if(board[1][2] == ' ')
            board[1][2] = 'X';
        else 
            goto input;
        break;
            
        case 7:
        if(board[2][0] == ' ')
            board[2][0] = 'X';
        else
            goto input;
        break;
            
        case 8:
        if(board[2][1] == ' ')
            board[2][1] = 'X';
        else
            goto input;
        break;
            
        case 9:
        if(board[2][2] == ' ')
            board[2][2] = 'X';
        else
            goto input;
        break;
    }
    --moves_left;
}

void computer()
{
    char row[moves_left], column[moves_left];
    int k = 0, random;
            
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                row[k] = i;
                column[k] = j;
                ++k;
            }
        }
    }
    random = rand() % moves_left;
    board[row[random]][column[random]] = 'O';
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
