import random
import time
import os
def rand_graph(n,p):
    #create a empty dictionary
    graph = {}
    #set default of graph
    for i in range(n):
        graph.setdefault(i, [])
    #random create the relationship between vars
    for i in range(n):
	#increase the index by one
        for j in range(i+1,n):
            if random.random()<=p:
                graph[i].append(j)
                graph[j].append(i)
    return graph



# transfer the ice breaker sat to minisat problem
def make_ice_breaker_sat(graph,k):
    f=open('sample_ice_breaker.txt','w+')
    f.truncate(0)
    count = 0
    print('c ice-breaker problem (sat) with ',k,' group',sep='',file=f)
    constraint=[]
    num_population = len(graph)
    for i in graph:
        # solve ice breaker constraints by adding constraints
        for friends in graph[i]:
            # eliminate duplicates by comparison
            if (i<friends):
                for group in range(k):
                    count+=1
                    constraint.append([-i-1-(group*num_population),-friends-1-(group*num_population),0])
        # every group has one people
        constraint.append([x*num_population+i+1 for x in range(k)]+[0])
        count+=1

        #solve people not in multiple groups
        for j in range(k):
            for n in range(j+1,k):
                count+=1
                constraint.append([-j*num_population-i-1,-n*num_population-i-1,0])
                
    print('p cnf ',num_population*k,' ',count,sep='',file=f)
    for element in constraint:
        for cnm in element:
            print(cnm,end=' ',file=f)
        print('',file=f)
    f.close()
    f=open('sample_ice_breaker.txt','r')
    string = f.read()
    f.close()
    return string


#binary method to find the minimized k of ice breaker problem
def find_min_teams(graph):
    if len(graph) == 0:
        return 0
    i = 0
    j = len(graph)
    k = (i+j)//2
    while(True):
        if k == j:
            return k
        if k == i:
            return j
        string = make_ice_breaker_sat(graph,k)
        os.system('minisat sample_ice_breaker.txt some.out')
        f=open('some.out','r')
        answer = f.readlines()
        if(answer[0]=='UNSAT\n'):
            i = k
        else:
            j = k
        k = (i+j)//2
    return k


#main function to test with n=20 from 0.1 to 0.9
def main():
    n = 17
    for j in range(1,10):
        print(j/10)
        for i in range(10):
            a = rand_graph(n, j/10)
            st = time.time()
            b = find_min_teams(a)
            print(b, time.time()-st)

    return

 
