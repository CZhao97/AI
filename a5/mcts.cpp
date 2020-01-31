#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <time.h>
#include <assert.h>

using namespace std;

int turn = 1;

int board[6][7] = {0};
int empty[7] = {5,5,5,5,5,5,5};

int sim[6][7] = {0};
int sim_empty[7] = {5,5,5,5,5,5,5};

void display(int arr[6][7]){
	char const * symbol = "";
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


int get_move(){
	int move;
	cout << "Please enter your move: " << flush;
	while (!(cin >> move) || (move > 7 || move < 1)){
		cout << "Error: Please enter a number between 1~7: ";
		cin.clear();
		cin.ignore(123,'\n');
	}
	return move - 1;
}

bool comp(int a, int b){ 
    return (a < b); 
}

int result(int arr[6][7], int a[7], int j){	// j is index of col of last move
	int start, end;
	int i = a[j]--;					// get coordinates of last move
	if (i<3){	// vertical check
		if(arr[i][j]==arr[i+1][j] && arr[i+1][j]==arr[i+2][j] && arr[i+2][j]==arr[i+3][j])
			return arr[i][j];
	}
	start = max(0, j-3);
	end = min(3, j);
	for (start; start<=end; start++){		// horizontal check
		if (arr[i][start]==arr[i][start+1] && arr[i][start+1]==arr[i][start+2] && arr[i][start+2]==arr[i][start+3])
			return arr[i][j];
	}
	start = min({i,j,3},comp);
	end = abs(min({2-i,3-j,0},comp));
	for (start; start >= end; start--){		// diagnal \ check
		if (arr[i-start][j-start]==arr[i-start+1][j-start+1] && arr[i-start+1][j-start+1]==arr[i-start+2][j-start+2] && arr[i-start+2][j-start+2]==arr[i-start+3][j-start+3])
			return arr[i][j];
	}
	start = min({i,6-j,3},comp);
	end = abs(min({0,2-i,j-3},comp));
	for (start; start >= end; start--){		// diagnal / check 
		if (arr[i-start][j+start]==arr[i-start+1][j+start-1] && arr[i-start+1][j+start-1]==arr[i-start+2][j+start-2] && arr[i-start+2][j+start-2]==arr[i-start+3][j+start-3])
			return arr[i][j];
	}
	for (i=0; i<7; i++){		// if top row is not full, game is in progress
		if (!arr[0][i]){
			return 2;
		}
	}
	return 0;		// draw
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

int ith_legal_move(int arr[7], int i){
	int index = 0;
	for (int j=0; j<7; j++){
		if (arr[j] != -1){
			if (i == index)
				return j;
			index++;
		}
	}
	cout << "ith_legal_move has been called with wrong arguments\n";
	return -1;
}

int NumOfChildren(int arr[7]){
	int num = 0;
	for (int i=0; i<7; i++){
		if (arr[i] != -1){
			num++;
		}
	}
	return num;
}

class Node{
public:
	int move;
	int state;
	float score = 0;
	float visit = 0;
	int NumOfChild;
	Node* parent = NULL;
	vector<Node*> children;
};

void propagation(Node* leaf, int result){
	// Node* cur = leaf;
	// cout << result;
	if (result != 0){
		while (leaf){
			leaf->score -= turn*result;
			leaf->visit++;
			leaf = leaf->parent;
			turn = -turn;
		}
	}
	else {
		while(leaf){
			leaf->visit++;
			leaf->score += 0.5;
			leaf = leaf->parent;
		}
	}
	return;
}


int simulation(Node* leaf){
	if (leaf->state != 2)
		return leaf->state;
	int player = turn;
	vector<int> sim_moves;
	int i, j, index, outcome;
	sim_moves = legal_move(sim_empty);

	while(NumOfChildren(sim_empty) != 0){
		index = rand() % sim_moves.size();
		j = sim_moves[index];
		i = sim_empty[j];
		sim[i][j] = player;

		player = -player;

		outcome = result(sim, sim_empty, j);
		
		if (outcome != 2){
			// display(sim);
			// cout << outcome<<" ";
			return outcome;
		}
		sim_moves = legal_move(sim_empty);
	}
	// display(sim);
	cout << "simulation has been called with wrong arguments\n";
	return -1;
}

Node* expansion(Node* leaf, int j){
	int last_move;
	Node* child = new Node();		// create child to be expanded from leaf
	child->visit = 0;
	child->score = 0;
	child->parent = leaf;		// set parent of child to leaf
	last_move = ith_legal_move(sim_empty, j);		// find move to be made by leaf to produce child
	child->move = last_move;
	sim[sim_empty[last_move]][last_move] = turn;		// update simulation board
	child->state = result(sim, sim_empty, last_move);
	child->NumOfChild = NumOfChildren(sim_empty);
	leaf->children.push_back(child);
	turn = -turn;
	assert(child != NULL);
	return child;
}

Node* selection(Node* root){
	Node* cur = root, *child;
	int last_move, j;
	float cur_ucb = 0, max_ucb;
	vector<Node*>::iterator itr;
	while (cur->state == 2){		// game in progress
		j = cur->children.size();	// what if j = 0 and numberofchild = 0
		if (j < cur->NumOfChild){		// have child to expand
			return expansion(cur, j);
		}
		else{
			max_ucb = -200;

			for (int i=0; i<cur->children.size(); i++){
				float a = cur->children[i]->visit;
				// cout << a <<'\n';
				assert(a > 0);
				cur_ucb = cur->children[i]->score/a;
				// cout << cur_ucb << '\n';
				
				float temp = 2*log(float(cur->visit))/a;
				assert(temp != NULL);
				if (temp < 0){
					cout << temp << "why is it negative????\n";
				}
				;
				cur_ucb += sqrt(temp); 
				
				if (cur_ucb > max_ucb){
					max_ucb = cur_ucb;
					child = cur->children[i];
				}
			}
			assert(max_ucb != -200);
			assert(cur != child);
			cur = child;
			last_move = cur->move;
			if (last_move>6 || last_move<0){
				cout << cur->move<< "bug in selection\n";
				break;
			}
			assert(sim_empty[last_move] >= 0);
			sim[sim_empty[last_move]--][last_move] = turn;
			turn = -turn;
		}
	}
	return cur;
}



int MCTS(Node* root){
	int result, j, cur_visit, max_visit = -1;
	Node* leaf;
	for (int i=0; i<300000; i++){
		memcpy(sim, board, 168);
		memcpy(sim_empty, empty, 28);	// copy original board to simulation board
		turn = 1;
		leaf = selection(root);
		if (leaf->move>6 || leaf->move<0)
			cout << leaf->move<< "bug after selection\n";
		result = simulation(leaf);
		propagation(leaf, result);
	}
	vector<Node*>::iterator itr;
	for(itr = root->children.begin(); itr != root->children.end(); itr++){
		cur_visit = (*itr)->visit;
		cout << "Score: "<< (*itr)->score <<" Visit: " <<(*itr)->visit << '\n';
		// cout << " UCB: " << (((*itr)->score)/((*itr)->visit))  ; //+ sqrt(2*log(root->visit)/(*itr)->visit)*2 << " root visit: "<< root->visit<<'\n'
		if (cur_visit > max_visit){
			max_visit = cur_visit;
			j = (*itr)->move;
		}
	}
	return j;
}

void delete_tree(Node* root){
	if (root && root->NumOfChild != 0){
		for (int i=0; i<root->children.size(); i++)
			delete_tree(root->children[i]);
	}
	else if (root){
		delete root;
		return;
	}
	delete root;
	return;
}

int main(){
	srand((unsigned)time(NULL));	// rng
	int first;
	int move;
	int win;
	cout << "Welcome to the upgraded version of Connect 4!\n\n";
	display(board);
	cout << "To make a move, please enter the number on top of game board that corresponds to your move\n\n";
	cout << "Now, if you wish to make the first move, please enter 1, else enter 2: " << flush;
	Node* root;
	while (!(cin >> first) || (first != 1 && first != 2)){
		cout << "Error: Please enter 1 or 2: ";
		cin.clear();
		cin.ignore(123,'\n');
	}

	if (first == 1){
		move = get_move();
		board[5][move] = -1;
		empty[move]--;
	}

	while(1){	
		root = new Node();
		root->state = 2;
		root->NumOfChild = NumOfChildren(empty);
		root->visit = 1;
		root->score = 0;
		move = MCTS(root);	// move by computer
		cout << "Computer made move at: " << move+1<<"\n";
		board[empty[move]][move] = 1;
		display(board);
		delete_tree(root);
		win = result(board, empty, move);
		if (win != 2){	// game over
			cout << win << "\n";
			break;
		}
		while (1){	// get a valid player move
			move = get_move();
			if (board[0][move])
				cout << "please enter a valid move where the location of move is empty\n";
			else
				break;
		}
		board[empty[move]][move] = -1;	// move by player
		win = result(board, empty, move);
		if (win!=2){	// game over
			display(board);
			cout << win << "\n";
			break;
		}
	}


	return 0;
}
