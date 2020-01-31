import os
import time
#global variable to count the clauses
count_c = 0
#function to make N-queen set
def make_queen_sat(N):
	global count_c
	f=open('sample_queen.txt','w+')
	f.truncate(0)
	print('c ',N,'-queens problem (sat)',sep='',file=f)
	constraint = []
	# case of N = 1
	if (N==1):
		print('c 1-queen problem (sat)',file=f)
		print('p cnf 1 1',file=f)
		print('1 0')
		count = 1
		f.close()
		f=open('sample_queen.txt','r')
		string = f.read()
		f.close()
		return string
	
	count_c = 0
	##row constraints
	for i in range(1,N+1):
		only_one = []
		row_num_end = (i*N)+1
		row_num_start = ((i-1)*N)+1 
		for row in range(row_num_start,row_num_end):
				only_one.append(row)
				for col in range(row+1,row_num_end):
					count_c += 1
					constraint.append([-row,-col,0])
		only_one.append(0)
		count_c += 1
		constraint.append(only_one)

	##col constraints
	for i in range(1,N+1):
		only_one = []
		col_num_end = N*N - (N-i) + 1
		col_num_start = i
		for col in range(col_num_start,col_num_end,N):
				only_one.append(col)
				for col_son in range(col+N,col_num_end,N):
					count_c += 1
					constraint.append([-col,-col_son,0])
		only_one.append(0)
		count_c += 1
		constraint.append(only_one)

	##diag constraints
	N_square = N*N
	for i in range(N_square,N,-N):
		for j in range(i,0,-N-1):
			for n in range(j-N-1,0,-N-1):
				count_c += 1
				constraint.append([-n,-j,0])

	for i in range(1+N,N_square,N):
		for j in range(i,N_square,N+1):
			for n in range(j+N+1,N_square,N+1):
				count_c += 1
				constraint.append([-j,-n,0])

	for i in range(N_square-N+1,1,-N):
		for j in range(i,1,-N+1):
			for n in range(j-N+1,1,-N+1):
				count_c += 1
				constraint.append([-n,-j,0])

	for i in range(2*N,N_square,N):
		for j in range(i,N_square,N-1):
			for n in range(j+N-1,N_square,N-1):
				count_c += 1
				constraint.append([-j,-n,0])


	##put the constraints in file
	print('p cnf ',N*N,' ',count_c,sep='',file=f)
	for element in constraint:
		for cnm in element:
			print(cnm,end=' ',file=f)
		print('',file=f)
	
	f.close()
	#get the string from out result
	f=open('sample_queen.txt','r')
	string = f.read()
	f.close()
	return string


# you can call this function to get the string of constrains
def return_sol(file):
	f = open(file, "r")
	
	answer = f.readlines()
	return answer



# draw with a string based on return_sol(file)
def draw_queen_sat_sol(sol):
	if (sol[0]=='UNSAT\n'):
		print('Unsatisfiable!')
		return
	lst = [int(x) for x in sol[1].split()]
	import math
	length = math.sqrt(len(lst)-1)
	lst = lst[:len(lst)-1]
	for i,element in enumerate(lst):
		print('@' if element>0 else '.', end = '\n' if (i+1)%length==0 else ' ')

#test function to examine with p from 0.1 to 0.9 each 10 times
def test():
	temp = []
	count_clause = []
	return_time = 0
	i=2
	while(return_time <= 10):
		make_queen_sat(i)
		count_clause.append(count_c)
		st = time.time()
		os.system('minisat sample_queen.txt out')
		return_time = time.time() - st
		temp.append(return_time)
		print(i,return_time,count_c)
		i+=1
	return temp,count_clause

	



