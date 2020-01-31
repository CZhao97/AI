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

class connect_4 {
private:
	int board[6][7] = {0};
	int empty[7] = {5,5,5,5,5,5,5};

public:
	connect_4(){}
	~connect_4(){}
	int display(int arr[6][7]){
		string temp = "\n   1     2     3     4     5     6     7\n-------------------------------------------\n";
		char const * symbol = "";
		for (int i = 0; i < 6; i++){
			for (int k = 0; k < 7; k++){
				if (arr[i][k]==0)
					symbol = " ";
				else if (arr[i][k]==1)
					symbol = "O";
				else
					symbol = "X";
				temp = temp + "|  " + symbol + "  ";
			}
			temp = temp + "|\n-------------------------------------------\n";
		}
		cout << temp << endl;
	}


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
		return move - 1;
	}


	// https://www.geeksforgeeks.org/stdmin-in-cpp/
	bool comp(int a, int b){ 
	    return (a < b); 
	}

	int check_full(int arr[6][7]){
		for (int i=0; i<7; i++){
			if (!arr[0][i]){
				return -1;
			}
		}
		return 0;
	}

	int check_win(int arr[6][7], int a[7], int j){
		int i = a[j];
		a[j]--;
		if (i<3){
			if(arr[i][j]==arr[i+1][j] && arr[i+1][j]==arr[i+2][j] && arr[i+2][j]==arr[i+3][j])
				return arr[i][j];
		}


		int start = max(0, j-3);
		int end = min(3, j);
		for (start; start<=end; start++){
			if (arr[i][start]==arr[i][start+1] && arr[i][start+1]==arr[i][start+2] && arr[i][start+2]==arr[i][start+3])
				return arr[i][j];
		}

		start = min(i,j);
		end = min(5-i,6-j);
		int temp_i = i - start;
		int temp_j = j - start;
		int count = 0;
		int total = start + end + 1;

		for (int n = 0; n < total ; n++){
			if (arr[temp_i + n][temp_j + n] == arr[i][j]){
				count++;
			}
			else{
				count = 0;
			}
			if(count==4){
				return arr[i][j];
			}
		}

		start = min(5-i,j);
		end = min(i,6-j);
		temp_i = i + start;
		temp_j = j - start;
		count = 0;
		total = start + end + 1;
		for (int n = 0; n < total ; n++){
			if (arr[temp_i - n][temp_j + n] == arr[i][j]){
				count++;
			}
			else{
				count = 0;
			}
			if(count==4){
				return arr[i][j];
			}
		}

		return check_full(arr);
	}



	vector<int> legal_move(int arr[7]){
		vector<int> move;
		for (int i=0; i<7; i++){
			if (arr[i] != -1){
				move.push_back(i);
			}
		}
		return move;
	}


	int calculate_score(int i,int j){
		int score = 0 temp,score = 0;
		
		start = min(i,j);
		end = min(5-i,6-j);
		int temp_i = i - start;
		int temp_j = j - start;
		int count = 0;
		int total = start + end + 1;
		int temp = arr[temp_i][temp_j];

		for (int n = 0; n < total ; n++){
			if (arr[temp_i + n][temp_j + n] == temp){
				count+=2;
			}
			else if(arr[temp_i + n][temp_j + n] == 0){
				count+=1;
			}
			else{
				score += count;
				temp = arr[temp_i + n][temp_j + n]
				count = 0;
			}
		}

		
		start = min(5-i,j);
		end = min(i,6-j);
		temp_i = i + start;
		temp_j = j - start;
		count = 0;
		total = start + end + 1;
		temp = arr[temp_i][temp_j];
		for (int n = 0; n < total ; n++){
			if (arr[temp_i - n][temp_j + n] == temp){
				count++;
			}
			else if(arr[temp_i - n][temp_j + n]==0){
				count+=1;
			}
			else{
				store += count;
				temp = arr[temp_i - n][temp_j + n];
				count = 0;
			}
		}

		start = min(j,0);
		end = max(j)


	}

	vector<int> best_some_return(vector<int> vec){
		int n = vec.size();
		if (n<2){
			return vec;
		}
		vector<int> move;
		int score[n];
		int move[n];
		for (int index=0; index<vec.size(); index++){
			int j = vec[index];
			int i = empty[j];
			score[index] = calculate_score(i,j);
			move[index] = j;
		}
		int a = score[0] , b = score[1];
		for (int i=0; i<n; i++) 
      		for (int j=i+1; j<n; j++) 
         		if (arr[i]*arr[j] > a*b) 
            		a = arr[i], b = arr[j]; 
        move.push_back(i);
        move.push_back(j);
		return move;
	}


	int next_move(int arr[6][7],int a[7]){
		int playout = 10000, score, win_max = -100000000, win_moves, index, win_flag, row, col;
		bool player;
		int arr_sim[6][7];
		int a_empty[7];
		vector<int> moves = legal_move(empty);
		vector<int> valid_moves;
		for(std::vector<int>::const_iterator itr = moves.begin(); itr != moves.end(); itr++){
			score = 0;
			arr[empty[*itr]][*itr] = 1;
			if (check_win(arr, empty, *itr)==1){
				empty[*itr]++;
				return *itr;
			}
			

			for (int k=0; k<playout; k++){
				player = true;
				memcpy(arr_sim, arr, sizeof(int)*42);
				memcpy(a_empty, empty, sizeof(int)*7);
				valid_moves = legal_move(a_empty);
				
				valid_moves = best_some_return(valid_moves);

				while(valid_moves.size() != 0){
					index = rand() % valid_moves.size();
					col = valid_moves[index];
					row = a_empty[col];
					arr_sim[row][col] = player? 2:1;

					player = !player;

					win_flag = check_win(arr_sim, a_empty, col);
					valid_moves = legal_move(a_empty);
					
					if (win_flag == 1){
						score++;
						break;
					}
					else if (win_flag == 2){
						score-=3;
						break;
					}
					
				}

			}
		    if(score>win_max){
		    	win_max= score;
		    	win_moves = *itr;
		    }
		    arr[empty[*itr]+1][*itr] = 0;
		    empty[*itr]++;
		}

		cout << "\n";
		return win_moves;
	}

	int game_start(){

		srand((unsigned)time(NULL));
		int first;
		int move;
		int win;
		cout << "Welcome to the world of Connect 4!\n";
		display(board);
		cout << "Please enter the number above the game board!\n";
		cout << "Please enter 1 for user first, else enter 2 for computer first: " << flush;
		
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
			move = get_next_move();
			board[5][move] = 2;
			empty[move]--;
		}

		while(true){
			move = next_move(board,empty);
			cout << "Computer made move at: " << move+1<<"\n";
			board[empty[move]][move] = 1;

			display(board);
			win = check_win(board, empty, move);
			if (win != -1){
				cout << win << "\n";
				break;
			}

			while (1){
				move = get_next_move();
				if (board[0][move])
					cout << "please enter a valid move where the location of move is empty\n";
				else
					break;
			}

			board[empty[move]][move] = 2;
			win = check_win(board, empty, move);
			if (win!=-1){
				display(board);
				cout << win << "\n";
				break;
			}

		}

		return 0;
	}
};

int main(){
	connect_4 game;
	game.game_start();
	return 0;
}