import random
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
