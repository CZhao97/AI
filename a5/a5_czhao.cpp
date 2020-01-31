#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <iterator>
#include <time.h>
#include <algorithm>
#include <cstring>

using namespace std; 

int board[6][7] = {0};
int empty[7] = {5,5,5,5,5,5,5};


int sim[6][7] = {0};
int sim_empty[7] = {5,5,5,5,5,5,5};

void board_display(int arr[6][7]){
	string symbol;
	cout << "\n  1   2   3   4   5   6   7\n";
	for (int i = 0; i<6; i++){
		for (int j = 0; j<7; j++){
			if (arr[i][j]==0)
				symbol = " ";
			else if (arr[i][j]==1)
				symbol = "O";
			else
				symbol = "X";
			cout << "| " << symbol << " ";
		}
		cout << "|\n-----------------------------\n";
	}
}


int get_next_move(){
	int move;
	cout << "Please enter your next move: " << flush;
	while (true){
		cin >> move;
		if (!move||(move<1||move>7)){
			cout << "Error Occured: Please enter a number from 1 to 7: ";
			cin.clear();
			continue;
			// cin.ignore(123,'\n');
		}
		break;
	}
	return move - 1;
}



bool comp(int a, int b){ 
    return (a < b); 
}


int result(int arr[6][7], int a[7], int j){	// j is index of col of last move
	int start, end;
	int i = a[j];					// get coordinates of last move
	a[j]--;

	if (i<3){	// vertical check
		if(arr[i][j]==arr[i+1][j] && arr[i+1][j]==arr[i+2][j] && arr[i+2][j]==arr[i+3][j])
			return arr[i][j];
	}

	start = max(0, j-3);
	end = min(3, j);
	for (start; start<=end; start++){	// horizontal check
		if (arr[i][start]==arr[i][start+1] && arr[i][start+1]==arr[i][start+2] && arr[i][start+2]==arr[i][start+3])
			return arr[i][j];
	}

	start = min({i,j,3},comp);
	end = abs(min({2-i,3-j,0},comp));
	for (start; start >= end; start--){
		if (arr[i-start][j-start]==arr[i-start+1][j-start+1] && arr[i-start+1][j-start+1]==arr[i-start+2][j-start+2] && arr[i-start+2][j-start+2]==arr[i-start+3][j-start+3])
			return arr[i][j];
	}

	start = min({i,6-j,3},comp);
	end = abs(min({0,2-i,j-3},comp));
	for (start; start >= end; start--){
		if (arr[i-start][j+start]==arr[i-start+1][j+start-1] && arr[i-start+1][j+start-1]==arr[i-start+2][j+start-2] && arr[i-start+2][j+start-2]==arr[i-start+3][j+start-3])
			return arr[i][j];
	}
	for (i=0; i<7; i++){
		if (!arr[0][i]){
			return -1;
		}
	}
	return 0;
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

	
int next_move(int arr[6][7]){
	int playout = 10000, win, index, outcome, i, j;
	bool player;
	vector<int> moves = legal_move(empty); // legal moves of original board
	vector<int>::iterator itr;
	vector<int> score;
	vector<int> sim_moves;
	for(itr = moves.begin(); itr != moves.end(); itr++){	// for each legal move
		arr[empty[*itr]][*itr] = 1;
		if (result(arr, empty, *itr)==1){		// computer win after first move
			empty[*itr]++;
			return *itr;
		}
		win = 0;

		for (int k=0; k<playout; k++){	// simulate n times n=playout
			player = true;
			memcpy(sim, arr, 168);
			memcpy(sim_empty, empty, 28);
			sim_moves = legal_move(sim_empty);
			


			while(sim_moves.size() != 0){
				index = rand() % sim_moves.size();
				j = sim_moves[index];
				i = sim_empty[j];
				sim[i][j] = player? 2:1;

				player = !player;

				outcome = result(sim, sim_empty, j);
				sim_moves = legal_move(sim_empty);
				
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

int main(){

	srand((unsigned)time(NULL));	// rng
	int first;
	int move;
	int win;
	cout << "Welcome to the original version of Connect 4!\n\n";
	board_display(board);
	cout << "To make a move, please enter the number on top of game board that corresponds to your move\n\n";
	cout << "Now, if you wish to make the first move, please enter 1, else enter 2: " << flush;
	
	while (!(cin >> first) || (first != 1 && first != 2)){
		cout << "Error: Please enter 1 or 2: ";
		cin.clear();
		cin.ignore(123,'\n');
	}

	if (first == 1){
		move = get_next_move();
		board[5][move] = 2;
		empty[move]--;
	}

	do{
		move = next_move(board);	// move by computer
		cout << "Computer made move at: " << move+1<<"\n";
		board[empty[move]][move] = 1;

		board_display(board);
		win = result(board, empty, move);
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
		win = result(board, empty, move);
		if (win!=-1){	// game over
			board_display(board);
			cout << win << "\n";
			break;
		}

	}
	while (legal_move(empty).size()>0);

	return 0;
}
