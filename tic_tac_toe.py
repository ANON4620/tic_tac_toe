import random

def draw():
    print()
    print()
    print()
    print()
    print("            |             |")
    print("            |             |")
    print("      {}     |      {}      |     {}".format(board[0][0], board[0][1], board[0][2]))
    print("            |             |")
    print("            |             |")
    print("------------|-------------|------------")
    print("            |             |")
    print("            |             |")
    print("      {}     |      {}      |     {}".format(board[1][0], board[1][1], board[1][2]))
    print("            |             |")
    print("            |             |")
    print("------------|-------------|------------")
    print("            |             |")
    print("            |             |")
    print("      {}     |      {}      |     {}".format(board[2][0], board[2][1], board[2][2]))
    print("            |             |")
    print("            |             |")
    print()

def check_rows():
    for i in range(3):
        count = 0
        for j in range(3):
            if board[i][j] == cur_player:
                count += 1
            else:
                break
        if count == 3:
            return True
    return False

def check_columns():
    for i in range(3):
        count = 0
        for j in range(3):
            if board[j][i] == cur_player:
                count += 1
            else:
                break
        if count == 3:
            return True
    return False

def check_diagonals():
    if (board[0][0] == cur_player and board[0][0] == board[1][1] and board[1][1] == board[2][2]) or (board[0][2] == cur_player and board[0][2] == board[1][1] and board[1][1] == board[2][0]):
        return True
    return False

# Setting up variables
player = "X"
computer = "O"
cur_player = player

# Setting up board
board = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
print("PLAYER   -- X")
print("COMPUTER -- O")
draw()

# Clearing the board
for i in range(3):
    for j in range(3):
        board[i][j] = " "    # Space character

# Tracking the available positions
available_pos = []
for i in range(3):
    for j in range(3):
        available_pos.append({"row" : i, "col" : j})
pos_left = len(available_pos)

#######################   Main   #######################

if __name__ == '__main__':
    while pos_left > 0:
        
        # Automatically play last position left
        if pos_left == 1:
            pos = available_pos[0]
            board[pos["row"]][pos["col"]] = cur_player
            
        # If current player is player
        elif cur_player == player:
            pos = int(input(">> ")) - 1
            row = pos // 3
            col = pos % 3
            pos = {"row" : row, "col" : col}
            if pos in available_pos:
                board[row][col] = cur_player
            else:
                print("Invalid position!")
                continue
                
        # If current player is computer
        else:
            played = False
            
            # Check for an immediate win
            for pos in available_pos:
                board[pos["row"]][pos["col"]] = cur_player
                if check_rows() or check_columns() or check_diagonals():
                    played = True 
                    break
                board[pos["row"]][pos["col"]] = " "
                    
            # Check for blocking the player ( Block player's winning position )
            if not played:
                for pos in available_pos:
                    cur_player = player
                    board[pos["row"]][pos["col"]] = cur_player
                    if check_rows() or check_columns() or check_diagonals():
                        cur_player = computer
                        board[pos["row"]][pos["col"]] = cur_player
                        played = True
                        break
                    cur_player = computer
                    board[pos["row"]][pos["col"]] = " "
            
            # Play random
            if not played:
                pos = available_pos[random.randint(0, pos_left - 1)]
                board[pos["row"]][pos["col"]] = cur_player

        # Remove the available position from list
        available_pos.remove(pos)
        pos_left -= 1
        
        #### Draw on screen ####
        draw()
        
        # Check win
        if check_rows() or check_columns() or check_diagonals():
            print(cur_player, "WON!")
            input("Press ENTER to exit...")
            exit()

        # Switch player
        if cur_player == player:
            cur_player = computer
        else:
            cur_player = player

    # Game is a draw
    print("DRAW!")
    input("Press ENTER to exit...")
