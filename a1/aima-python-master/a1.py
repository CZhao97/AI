# a1.py

from search import *
import time
#identify personal eightpuzzle 
class EightPuzzle(Problem):

    #create the initial state
    def __init__(self, initial, goal=(1, 2, 3, 4, 5, 6, 7, 8, 0)):

        self.goal = goal
        Problem.__init__(self, initial, goal)
    #find which square is index 0
    def find_blank_square(self, state):

        return state.index(0)
    #find possible actions
    def actions(self, state):

        possible_actions = ['UP', 'DOWN', 'LEFT', 'RIGHT']       
        index_blank_square = self.find_blank_square(state)

        if index_blank_square % 3 == 0:
            possible_actions.remove('LEFT')
        if index_blank_square < 3:
            possible_actions.remove('UP')
        if index_blank_square % 3 == 2:
            possible_actions.remove('RIGHT')
        if index_blank_square > 5:
            possible_actions.remove('DOWN')

        return possible_actions
    
    #give the result after some specific steps
    def result(self, state, action):
        # blank is the index of the blank square
        blank = self.find_blank_square(state)
        new_state = list(state)

        delta = {'UP':-3, 'DOWN':3, 'LEFT':-1, 'RIGHT':1}
        neighbor = blank + delta[action]
        new_state[blank], new_state[neighbor] = new_state[neighbor], new_state[blank]

        return tuple(new_state)

    #check if question solved
    def goal_test(self, state):

        return state == self.goal

    #check the sample solvable or not
    def check_solvability(self, state):

        inversion = 0
        for i in range(len(state)):
            for j in range(i+1, len(state)):
                if (state[i] > state[j]) and state[i] != 0 and state[j]!= 0:
                    inversion += 1
        
        return inversion % 2 == 0
    #return the heuristic value
    def h(self, node):

        return sum((s != 0 and s != g) for (s, g) in zip(node.state, self.goal))

# create the Ypuzzle class
class YPuzzle(Problem):

    #create the initial state
    def __init__(self, initial, goal=(1, 2, 3, 4, 5, 6, 7, 8, 0)):

        self.goal = goal
        Problem.__init__(self, initial, goal)

    #find which square is index 0
    def find_blank_square(self, state):

        return state.index(0)

    #find possible actions
    def actions(self, state):
        
        possible_actions = ['UP', 'DOWN', 'LEFT', 'RIGHT']       
        index_blank_square = self.find_blank_square(state)


        if index_blank_square == 0 or index_blank_square == 2 or index_blank_square == 5 or index_blank_square == 8 or index_blank_square == 1:
            possible_actions.remove('LEFT')

        if index_blank_square == 1 or index_blank_square == 4 or index_blank_square == 7 or index_blank_square == 8 or index_blank_square == 0:
            possible_actions.remove('RIGHT')

        if index_blank_square == 0 or index_blank_square == 1 or index_blank_square == 3:
            possible_actions.remove('UP')
            
        if index_blank_square == 5 or index_blank_square == 7 or index_blank_square == 8:
            possible_actions.remove('DOWN')

        return possible_actions

    #give the result after some specific steps
    def result(self, state, action):

        # blank is the index of the blank square
        blank = self.find_blank_square(state)
        new_state = list(state)

        delta = {'UP':-3, 'DOWN':3, 'LEFT':-1, 'RIGHT':1}
        neighbor = blank + delta[action]

        if blank == 0:
            neighbor = neighbor - 1
        elif blank == 8:
            neighbor = neighbor + 1
        elif blank == 6 and action == 'DOWN':
            neighbor = neighbor - 1
        elif blank == 2 and action == 'UP':
            neighbor = neighbor + 1
        
        new_state[blank], new_state[neighbor] = new_state[neighbor], new_state[blank]

        return tuple(new_state)
    #check if question solved
    def goal_test(self, state):

        return state == self.goal
    #check the sample solvable or not
    def check_solvability(self, state):
        
        blank = state.index(0)

        if blank == 0:
            if state[1] != 2 or state[2] != 1 or state[8] != 7:
                return False
        elif blank == 1:
            if state[0] != 1 or state[4] != 2 or state[8] != 7:
                return False
            
        elif blank == 8:
            if state[0] != 1 or state[1] != 2 or state[6] != 7:
                return False

        else:
            if state[0] != 1 or state[1] != 2 or state[8] != 7:
                return False
                        
        inversion = 0
        for i in range(2,8):
            for j in range(i+1, 8):
                if (state[i] > state[j]) and state[i] != 0 and state[j]!= 0:
                    inversion += 1

            
        return inversion % 2 == 0

    #return the heuristic value
    def h(self, node):

        return sum((s != 0 and s != g) for (s, g) in zip(node.state, self.goal))

#fucntion to create a sample of 8 puzzle
def make_rand_8puzzle():
    import random
    state = [x for x in range(9)]
    random.shuffle(state)
    obj=EightPuzzle(state)
    while obj.check_solvability(state)!=True:
        random.shuffle(state)
    obj.initial=tuple(state)
    return obj
#fucntion to create a sample of Y puzzle
def make_rand_Ypuzzle():
    import random
    state = [x for x in range(9)]
    random.shuffle(state)
    obj=YPuzzle(state)
    while obj.check_solvability(state)!=True:
        random.shuffle(state)
    obj.initial=tuple(state)
    return obj

#function of astar_search
def astar_search(problem, h=None):
    h = memoize(h or problem.h, 'h')
    return best_first_graph_search(problem, lambda n: n.path_cost + h(n))

#modified by indicating the node removed
def best_first_graph_search(problem, f):
    count = 0
    f = memoize(f, 'f')
    node = Node(problem.initial)
    frontier = PriorityQueue('min', f)
    frontier.append(node)
    explored = set()
    while frontier:
        node = frontier.pop()
        count = count + 1
        if problem.goal_test(node.state):
            return node, count
        explored.add(node.state)
        for child in node.expand(problem):
            if child.state not in explored and child not in frontier:
                frontier.append(child)
            elif child in frontier:
                if f(child) < frontier[child]:
                    del frontier[child]
                    frontier.append(child)
    return None

#manhattan fucntion for eight puzzle
def manhattan_8(node):
    state = node.state
    index_goal = {0:[2,2], 1:[0,0], 2:[0,1], 3:[0,2], 4:[1,0], 5:[1,1], 6:[1,2], 7:[2,0], 8:[2,1]}
    index_state = {}
    index = [[0,0], [0,1], [0,2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]]
    
    for i in range(len(state)):
        index_state[state[i]] = index[i]
    
    mhd = 0
    
    for i in range(8):
        for j in range(2):
            mhd = abs(index_goal[i+1][j] - index_state[i+1][j]) + mhd
    
    return mhd

#manhattan fucntion for Y puzzle
def manhattan_y(node):
    state = node.state
    index_goal = {0:[3,1], 1:[0,0], 2:[0,2], 3:[1,0], 4:[1,1], 5:[1,2], 6:[2,0], 7:[2,1], 8:[2,2]}
    index_state = {}
    index = [[0,0], [0,2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2], [3,1]]
    
    for i in range(len(state)):
        index_state[state[i]] = index[i]
    
    mhd = 0
    
    for i in range(8):
        for j in range(2):
            mhd = abs(index_goal[i+1][j] - index_state[i+1][j]) + mhd
    
    return mhd

#function to display eight puzzle
def display(state):
    for num ,elt in enumerate(state,start=1):
        print(elt if elt !=0 else '*', end = ' ' if num%3 else '\n')

#fucntion to compare the result of manhattan and misplaced tile heuristic for eight puzzle
def max_cpm_8(node):
    temp = EightPuzzle(node.state)
    return max(manhattan_8(node),temp.h(node))

#fucntion to compare the result of manhattan and misplaced tile heuristic for y puzzle
def max_cpm_y(node):
    temp = YPuzzle(node.state)
    return max(manhattan_y(node),temp.h(node))


times_10 = ['1st', '2nd', '3rd', '4th', '5th', '6th', '7th', '8th', '9th', '10th']

for i in range(10):
    x = make_rand_8puzzle()
    print(x.initial)

    start_time_h = time.time()
    a_s_h , a_s_h_removed = astar_search(x)
    elapsed_time_h = time.time() - start_time_h

    start_time_m = time.time()
    a_s_m , a_s_m_removed = astar_search(x,h = manhattan_8)
    elapsed_time_m = time.time() - start_time_m


    start_time_max = time.time()
    a_s_max , a_s_max_removed = astar_search(x,h = max_cpm_8)
    elapsed_time_max = time.time() - start_time_max
    print('It is the ', times_10[i], ' sample of eight_puzzle')
    print('For h algorithm, the total running time is ', elapsed_time_h)
    print('For h algorithm, the length of solution is ', len(a_s_h.solution()))
    print('For h algorithm, the total number of nodes that were removed from frontier is ', a_s_h_removed)


    print('For manhattan algorithm,  the total running time is ', elapsed_time_m , )
    print('For manhattan algorithm, the length of solution is ', len(a_s_m.solution()))
    print('For manhattan algorithm, the total number of nodes that were removed from frontier is ', a_s_m_removed)

    print('For the max of the misplaced tile heuristic and the Manhattan distance heuristic, the total running time is ', elapsed_time_max)
    print('For the max of the misplaced tile heuristic and the Manhattan distance heuristic, the length of solution is ', len(a_s_max.solution()))
    print('For the max of the misplaced tile heuristic and the Manhattan distance heuristic, the total number of nodes that were removed from frontier is ', a_s_max_removed)
    print('\n')
    print('-'*100)
    print('\n')

print('+'*100)

for i in range(10):
    x = make_rand_Ypuzzle()
    print(x.initial)

    start_time_h = time.time()
    a_s_h , a_s_h_removed = astar_search(x)
    elapsed_time_h = time.time() - start_time_h

    start_time_m = time.time()
    a_s_m , a_s_m_removed = astar_search(x,h = manhattan_y)
    elapsed_time_m = time.time() - start_time_m


    start_time_max = time.time()
    a_s_max , a_s_max_removed = astar_search(x,h = max_cpm_y)
    elapsed_time_max = time.time() - start_time_max

    print('It is the ', times_10[i], ' sample of Ypuzzle')
    print('For h algorithm, the total running time is ', elapsed_time_h)
    print('For h algorithm, the length of solution is ', len(a_s_h.solution()))
    print('For h algorithm, the total number of nodes that were removed from frontier is ', a_s_h_removed)


    print('For manhattan algorithm,  the total running time is ', elapsed_time_m , )
    print('For manhattan algorithm, the length of solution is ', len(a_s_m.solution()))
    print('For manhattan algorithm, the total number of nodes that were removed from frontier is ', a_s_m_removed)

    print('For the max of the misplaced tile heuristic and the Manhattan distance heuristic, the total running time is ', elapsed_time_max)
    print('For the max of the misplaced tile heuristic and the Manhattan distance heuristic, the length of solution is ', len(a_s_max.solution()))
    print('For the max of the misplaced tile heuristic and the Manhattan distance heuristic, the total number of nodes that were removed from frontier is ', a_s_max_removed)
    print('\n')
    print('-'*100)
    print('\n')




