import random

def play_a_new_game():

    def isempty(current_state):
        empty_blocks = []
        for i,g in enumerate(current_state):
            if (g==' '):
                empty_blocks.append(i)
        return empty_blocks
            
    def playAgain():
        # This function returns True if the player wants to play again, otherwise it returns False.
        print('Do you want to play again? (yes or no)')
        return input().lower().startswith('y')

    
    def draw(current_state = [1,2,3,4,5,6,7,8,9]):
        # initialize an empty board
        board = " -----" * 3
        board += "\n"
        number = 0
        # there are 5 rows in a standard tic-tac-toe board
        for i in range(5):
            # switch between printing vertical and horizontal bars
            if i%2 == 0:
                board += "|  " + str(current_state[number]) + "  " + "|  " + str(current_state[number+1]) + "  " + "|  " + str(current_state[number+2]) + "  " + "|"
                number+=3
            else:
                board += " -----" * 3
            # don't forget to start a new line after each row using "\n"
            board += "\n"
        board += " -----" * 3
        board += "\n"
        print(board)

    def isWinner(board, letter):
        # Given a board and a player's letter, this function returns True if that player has won.
        # We use bo instead of board and le instead of letter so we don't have to type as much.
        return ((board[6] == letter and board[7] == letter and board[8] == letter) or # across the top
        (board[3] == letter and board[4] == letter and board[5] == letter) or # across the middle
        (board[0] == letter and board[1] == letter and board[2] == letter) or # across the bottom
        (board[6] == letter and board[3] == letter and board[0] == letter) or # down the left side
        (board[7] == letter and board[4] == letter and board[1] == letter) or # down the middle
        (board[8] == letter and board[5] == letter and board[2] == letter) or # down the right side
        (board[6] == letter and board[4] == letter and board[2] == letter) or # diagonal
        (board[8] == letter and board[4] == letter and board[0] == letter)) # diagonal


    def find_best_move(space,turn,n=100):
        final_decision = [[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]] #w,l,d
        total_ratio = []
        for i in range(n):
            temp_turn = turn
            temp = space.copy()
            decision_make = []
            flag = 2
            if len(isempty(space))==1:
                ava_block = isempty(space)
                random_move = random.choice(ava_block) 
                return random_move 
            while len(isempty(temp))!=0:
                ava_block = isempty(temp)
                random_move = random.choice(ava_block)   
                decision_make.append(random_move)
                if temp_turn == -1:
                    symbol = 'X'
                    temp_turn = -2
                else:
                    symbol = 'O'
                    temp_turn = -1
                temp[random_move] = symbol
                computer_win = isWinner(temp,'X')
                user_win = isWinner(temp,'O')
                if computer_win:
                    flag = 1
                    break
                elif user_win:
                    flag = 0
                    break
                else:
                    flag = -1
            if flag == 2:
                return 100
            elif flag == 1:
                final_decision[decision_make[0]][0] += 1
            elif flag == 0:
                final_decision[decision_make[0]][1] += 1
            else:
                final_decision[decision_make[0]][2] += 1

        for j in range(9):
            total = final_decision[j][0]+final_decision[j][1]+final_decision[j][2]
            if total != 0:
                total_ratio.append((final_decision[j][0]-final_decision[j][1]+final_decision[j][2])/total)
            else:
                total_ratio.append(-1)

        return total_ratio.index(max(total_ratio))

            
            
    #learn how to select random number from list at web:
    #https://stackoverflow.com/questions/306400/how-to-randomly-select-an-item-from-a-list
    while True:
        print('Welcome to world of Tic-Tac-Toe!')
        while (True):
            who_first = input('Enter "c" for computer first or "u" for user first or "q" to quit the game:')
            if (who_first == 'q'):
                print('Quit successfully!')
                return
            elif (who_first != 'c' and who_first != 'u'):
                print('"',who_first,'"', 'is an invalid input.')
                print('*'*50)
                continue
            elif(who_first == 'c'):
                print('You choose Computer(X) first.')
                turn = -1
                break
            else:
                print('You choose User(O) first.')
                turn = -2
                break
        print ('Please input the number you want to move based on the graph below:')
        draw()
        print('-'*80)
        print('Game start!')
        print('-'*80)
        space  = [' ',' ',' ',' ',' ',' ',' ',' ',' ']
        while(True):
            if turn==-2:
                user_move = input('Enter the number you want to move into:')
                if user_move=='q':
                    print('Quit Successfully!')
                    return
                if (user_move != '1') and (user_move != '2') and (user_move != '3') and (user_move != '4') and (user_move != '5') and (user_move != '6') and (user_move != '7') and (user_move != '8') and (user_move != '9'):
                    print('Input Invalid!')
                    continue
                else:
                    
                    if space[int(user_move)-1]==' ':
                        space[int(user_move)-1] = 'O'
                        print('User turn:')
                        draw(space)
                        print('-'*80)
                        turn=-1
                    else:
                        print('Error occured! You can only move to the empty space!')
                        continue
                        
            else:
                
                computer_move = find_best_move(space,turn,n=20000)
                if computer_move != 100:
                    turn=-2
                    space[computer_move] = 'X'
                    print('Computer turn:')
                    draw(space)
                    print('-'*80)
                else:
                    turn=-1
                    

            computer_win = isWinner(space,'X')
            user_win = isWinner(space,'O')
            if computer_win:
                print('Computer wins!')
                print('-'*80)
                break
            elif user_win:
                print('You win!')
                print('-'*80)
                break
            elif len(isempty(space))==0:
                print('Draw!')
                print('-'*80)
                break
        if playAgain():
            print('-'*80)
        else:
            print('Game End!')
            return
    
            

if __name__ == '__main__':
  play_a_new_game()      




'''
import random

def play_a_new_game():

    def isempty(current_state):
        empty_blocks = []
        for i,g in enumerate(current_state):
            if (g==' '):
                empty_blocks.append(i)
        return empty_blocks
            
    def playAgain():
        # This function returns True if the player wants to play again, otherwise it returns False.
        print('Do you want to play again? (yes or no)')
        return input().lower().startswith('y')

    
    def draw(current_state = [1,2,3,4,5,6,7,8,9]):
        # initialize an empty board
        board = " -----" * 3
        board += "\n"
        number = 0
        # there are 5 rows in a standard tic-tac-toe board
        for i in range(5):
            # switch between printing vertical and horizontal bars
            if i%2 == 0:
                board += "|  " + str(current_state[number]) + "  " + "|  " + str(current_state[number+1]) + "  " + "|  " + str(current_state[number+2]) + "  " + "|"
                number+=3
            else:
                board += " -----" * 3
            # don't forget to start a new line after each row using "\n"
            board += "\n"
        board += " -----" * 3
        board += "\n"
        print(board)

    def isWinner(board, letter):
        # Given a board and a player's letter, this function returns True if that player has won.
        # We use bo instead of board and le instead of letter so we don't have to type as much.
        return ((board[6] == letter and board[7] == letter and board[8] == letter) or # across the top
        (board[3] == letter and board[4] == letter and board[5] == letter) or # across the middle
        (board[0] == letter and board[1] == letter and board[2] == letter) or # across the bottom
        (board[6] == letter and board[3] == letter and board[0] == letter) or # down the left side
        (board[7] == letter and board[4] == letter and board[1] == letter) or # down the middle
        (board[8] == letter and board[5] == letter and board[2] == letter) or # down the right side
        (board[6] == letter and board[4] == letter and board[2] == letter) or # diagonal
        (board[8] == letter and board[4] == letter and board[0] == letter)) # diagonal


    def find_best_move(space,turn,n=100):
        result = []
        index = []
        legal_move = isempty(space)
        for i in legal_move:
            temp = space.copy()
            temp_turn = turn
            if temp_turn == -1:
                symbol = 'X'
                temp_turn = -2
            else:
                symbol = 'O'
                temp_turn = -1
            temp[i] = symbol
            temp_saved = temp.copy()
            temp_turn_saved = temp_turn
            total = 0
            for j in range(n):
                temp = temp_saved.copy()

                temp_turn = temp_turn_saved
                while isempty(temp)!=[]:
                    ava_block = isempty(temp)
                    random_move = random.choice(ava_block)
                    if temp_turn == -1:
                        symbol = 'X'
                        temp_turn = -2
                    else:
                        symbol = 'O'
                        temp_turn = -1
                    temp[random_move] = symbol
                    computer_win = isWinner(temp,'X')
                    user_win = isWinner(temp,'O')
                    if computer_win:
                        total += 10 - (sum(x != ' ' for x in temp))
                        break
                    elif user_win:
                        total -= 10 - (sum(x != ' ' for x in temp))
                        break
            result.append(total)
            index.append(i) 
        return index[result.index(max(result))]



            
            
    #learn how to select random number from list at web:
    #https://stackoverflow.com/questions/306400/how-to-randomly-select-an-item-from-a-list
    while True:
        print('Welcome to world of Tic-Tac-Toe!')
        while (True):
            who_first = input('Enter "c" for computer first or "u" for user first or "q" to quit the game:')
            if (who_first == 'q'):
                print('Quit successfully!')
                return
            elif (who_first != 'c' and who_first != 'u'):
                print('"',who_first,'"', 'is an invalid input.')
                print('*'*50)
                continue
            elif(who_first == 'c'):
                print('You choose Computer(X) first.')
                turn = -1
                break
            else:
                print('You choose User(O) first.')
                turn = -2
                break
        print ('Please input the number you want to move based on the graph below:')
        draw()
        print('-'*80)
        print('Game start!')
        print('-'*80)
        space  = [' ',' ',' ',' ',' ',' ',' ',' ',' ']
        while(True):
            if turn==-2:
                user_move = input('Enter the number you want to move into:')
                if user_move=='q':
                    print('Quit Successfully!')
                    return
                if (user_move != '1') and (user_move != '2') and (user_move != '3') and (user_move != '4') and (user_move != '5') and (user_move != '6') and (user_move != '7') and (user_move != '8') and (user_move != '9'):
                    print('Input Invalid!')
                    continue
                else:
                    
                    if space[int(user_move)-1]==' ':
                        space[int(user_move)-1] = 'O'
                        print('User turn:')
                        draw(space)
                        print('-'*80)
                        turn=-1
                    else:
                        print('Error occured! You can only move to the empty space!')
                        continue
                        
            else:
                computer_move = find_best_move(space,turn,n=1000)
                if computer_move != 100:
                    turn=-2
                    space[computer_move] = 'X'
                    print('Computer turn:')
                    draw(space)
                    print('-'*80)
                else:
                    turn=-1
                    

            computer_win = isWinner(space,'X')
            user_win = isWinner(space,'O')
            if computer_win:
                print('Computer wins!')
                print('-'*80)
                break
            elif user_win:
                print('You win!')
                print('-'*80)
                break
            elif len(isempty(space))==0:
                print('Draw!')
                print('-'*80)
                break
        if playAgain():
            print('-'*80)
        else:
            print('Game End!')
            return
    
            

if __name__ == '__main__':
  play_a_new_game()      
'''

