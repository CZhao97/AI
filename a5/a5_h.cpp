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
	int score_table[6][7] = {0};


public:
	
	connect_4(){}
	~connect_4(){}
	int display(int arr[6][7]){
		string temp = "\n  1   2   3   4   5   6   7\n-----------------------------\n";
		char const * symbol = "";
		for (int i = 0; i < 6; i++){
			for (int k = 0; k < 7; k++){
				if (arr[i][k]==0)
					symbol = " ";
				else if (arr[i][k]==1)
					symbol = "O";
				else
					symbol = "X";
				temp = temp + "| " + symbol + " ";
			}
			temp = temp + "|\n-----------------------------\n";
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

	int check_win(int arr[6][7], int a[7], int j){	// j is index of col of last move
		int i = a[j];					// get coordinates of last move
		a[j]--;
		if (i<3){	// vertical check
			if(arr[i][j]==arr[i+1][j] && arr[i+1][j]==arr[i+2][j] && arr[i+2][j]==arr[i+3][j])
				return arr[i][j];
		}


		int start = max(0, j-3);
		int end = min(3, j);
		for (start; start<=end; start++){	// horizontal check
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

	int check_tl(int arr[6][7], i, j){
		for (int n = 1; n<4 ; n++){
			int start = min(i,j);
			int end = min(5-i,6-j);
			int temp_i = i - start;
			int temp_j = j - start;
			int count = 0;
			int total = start + end + 1;
			if (arr[i-1][j-1] && )
		}
		
	}

	int get_score(int arr[6][7], int score_table[6][7], int a[7]){
		int i, score;
		for (int j = 0; j < 7; j++){
			i = a[j];
			score = 0;

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
		}
	}


	int next_move(int arr[6][7],int a[7]){
		int playout = 10000, win, index, outcome, i, j;
		bool player;
		int arr_sim[6][7];
		int a_empty[7];
		vector<int> moves = legal_move(empty); // legal moves of original board
		vector<int>::iterator itr;
		vector<int> score;
		vector<int> sim_moves;
		for(itr = moves.begin(); itr != moves.end(); itr++){	// for each legal move
			arr[empty[*itr]][*itr] = 1;
			if (check_win(arr, empty, *itr)==1){		// computer win after first move
				empty[*itr]++;
				return *itr;
			}
			win = 0;

			for (int k=0; k<playout; k++){	// simulate n times n=playout
				player = true;
				memcpy(arr_sim, arr, 168);
				memcpy(a_empty, empty, 28);
				sim_moves = legal_move(a_empty);
				


				while(sim_moves.size() != 0){
					index = rand() % sim_moves.size();
					j = sim_moves[index];
					i = a_empty[j];
					arr_sim[i][j] = player? 2:1;

					player = !player;

					outcome = check_win(arr_sim, a_empty, j);
					sim_moves = legal_move(a_empty);
					
					if (outcome == 1){	// computer win
						win++;
						break;
					}
					else if (outcome == 2){
						win-=2;
						break;
					}
					
				}

			}
		    score.push_back(win);
		    arr[empty[*itr]+1][*itr] = 0;
		    empty[*itr]++;
		}
		for (i=0; i<score.size(); i++){
			cout<< score[i] << " ";
		}
		cout << "\n";
		return moves[max_element(score.begin(),score.end())-score.begin()];	// return the best move
	}

	int game_start(){

		srand((unsigned)time(NULL));	// rng
		int first;
		int move;
		int win;
		cout << "Welcome to the world of Connect 4!\n";
		display(board);
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
			move = get_next_move();
			board[5][move] = 2;
			empty[move]--;
		}

		while(true){
			move = next_move(board,empty);	// move by computer
			cout << "Computer made move at: " << move+1<<"\n";
			board[empty[move]][move] = 1;

			display(board);
			win = check_win(board, empty, move);
			if (win != -1){	// game over
				cout << win << "\n";
				break;
			}

			while (1){	// get a valid player move
				move = get_next_move();
				if (board[0][move])
					cout << "please enter a valid move where the location of move is empty\n";
				else
					break;
			}

			board[empty[move]][move] = 2;	// move by player
			win = check_win(board, empty, move);
			if (win!=-1){	// game over
				display(board);
				cout << win << "\n";
				break;
			}

		}

		return 0;
	}
};

int main(){
	connect_4 gamestart;
	gamestart.game_start();
	return 0;
}