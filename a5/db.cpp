// adapted from https://github.com/RobertSzkutak/SUNY-Fredonia/blob/master/CSIT461-Intro-To-AI-Engineering/Connect4/main.cpp
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <iterator>
#include <time.h>
#include <algorithm>
#include <cstring>
#include <limits>

using namespace std; 

class Connect4{

    private:
        int board[6][7] = {0};
        int empty[7] = {5,5,5,5,5,5,5};
        int chip;
	public:
		Connect4() {}
		~Connect4() {}
		
	void display(){  
        string temp = "\n   1     2     3     4     5     6     7\n-------------------------------------------\n";
        char const * symbol = "";
        for (int i = 0; i < 6; i++){
            for (int k = 0; k < 7; k++){
                if (board[i][k]==0)
                    symbol = " ";
                else if (board[i][k]==1)
                    symbol = "O";
                else
                    symbol = "X";
                temp = temp + "|  " + symbol + "  ";
            }
            temp = temp + "|\n-------------------------------------------\n";
        }
        cout << temp << endl;
    };
	int get_next_move(){
        int move;
        cout << "Please input the number you want to move based on the numbers above: " << flush;
        while (true){
            cin >> move;
            if (!(move) || (move < 1 || move > 7)){
                cout << "Error: Please enter a number from  1 to 7:";
                cin.clear();
                continue;
            }
            break;
        }
        move--;
        dropChip(move, 2);
        return move;
    }
	int check_win(int j){
        int i = empty[j]+1;
        if (i<3){
            if(board[i][j]==board[i+1][j] && board[i+1][j]==board[i+2][j] && board[i+2][j]==board[i+3][j])
                return board[i][j];
        }

        int start = max(0, j-3);
        int end = min(3, j);
        for (start; start<=end; start++){
            if (board[i][start]==board[i][start+1] && board[i][start+1]==board[i][start+2] && board[i][start+2]==board[i][start+3])
                return board[i][j];
        }

        start = min(i,j);
        end = min(5-i,6-j);
        int temp_i = i - start;
        int temp_j = j - start;
        int count = 0;
        int total = start + end + 1;

        for (int n = 0; n < total ; n++){
            if (board[temp_i + n][temp_j + n] == board[i][j]){
                count++;
            }
            else{
                count = 0;
            }
            if(count==4){
                return board[i][j];
            }
        }

        start = min(5-i,j);
        end = min(i,6-j);
        temp_i = i + start;
        temp_j = j - start;
        count = 0;
        total = start + end + 1;
        for (int n = 0; n < total ; n++){
            if (board[temp_i - n][temp_j + n] == board[i][j]){
                count++;
            }
            else{
                count = 0;
            }
            if(count==4){
                return board[i][j];
            }
        }

        for (int i=0; i<7; i++){
            if (!board[0][i]){
                return 0;
            }
        }
        return 3;
    }
	void dropChip(int col, int val){   
        board[empty[col]][col] = val;
        empty[col]--;
        return;
    }
	void removeChip(int col){   
        empty[col]++;
        board[empty[col]][col] = 0;
        return;
    }
	int next_move(){    
        for(int i = 0; i < 7; i++){
            if(empty[i] != -1){
                dropChip(i, 1);
                if(check_win(i) == 1)
                    return i;
                removeChip(i);
                dropChip(i, 2);
                if(check_win(i) == 2){
                    removeChip(i);
                    dropChip(i, 1);
                    return i;
                } 
                removeChip(i);
            }
        }
        

        int priority[7] = {0};
        

        for(int i = 0; i < 7; i++){
            
            if(board[0][i] == 0){
                dropChip(i, 1);
           
                for(int j = 0; j < 7; j++){
                    if(board[0][j] == 0){
                        dropChip(j, 2);
                    
                        if(check_win(j) == 2)
                            priority[i] = -1;
                        removeChip(j);
                    }
                }
                
                if(priority[i] == 0){
                    for(int j = 0; j < 7; j++){
                        if(board[0][j] == 0){
                            dropChip(j, 1);
                        
                            if(check_win(j) == 1)
                                priority[i] += 2;
                            else{
                                for(int h = 0; h < 7; h++){
                                    if(board[0][h] == 0){
                                        dropChip(h, 1);
                                
                                        if(check_win(h) == 1)
                                            priority[i]++;
                                
                                        removeChip(h);
                                    }
                                }
                            }
                    
                            removeChip(j);
                        }
                    }
                }
                removeChip(i);
            }
            else
                priority[i] = -2;
        }
        

        int maxPriority = 0;
        for(int i = 0; i < 7; i++){
                if(priority[i] > maxPriority){
                    maxPriority = priority[i];
                }
        }
        while(true){
            int column = rand() % 7;
            if(priority[column] == maxPriority){   
                dropChip(column, 1);
                return column;
            }
        }
    }
};


int main()
{
    srand((unsigned)time(NULL));
    Connect4 connect4;
    int first;
    int move;
    int win;
    cout << "Welcome to the world of Connect 4!\n";
    connect4.display();
    cout << "Please enter the number above the game board!\n";
    cout << "Now, if you wish to make the first move, please enter 1, else enter 2: " << flush;
    
    while (true){
        cin >> first;
        if(!first || (first != 1 && first != 2)){
            cout << "Error Occured: Only 1 or 2 accepted: ";
            cin.clear();
            continue;
        }
        break;
    }
    if (first == 1){
        move = connect4.get_next_move();
    }

    while(true){
        move = connect4.next_move();  // move by computer
        cout << "Computer made move at: " << move+1<<"\n";
        connect4.display();
        win = connect4.check_win(move);
        if (win != 0){ // game over
            cout << win << "\n";
            break;
        }


        move = connect4.get_next_move();

        win = connect4.check_win(move);
        if (win != 0){   // game over
            connect4.display();
            cout << win << "\n";
            break;
        }

    }

    return 0;

}