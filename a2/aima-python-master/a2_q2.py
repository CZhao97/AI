#function to check solution is right or not
def check_teams(graph,csp_sol):
    #get each var and its vals
    for i, value in graph.items():
	#save the current group number
        temp = csp_sol[i]
	#check if one constrains not obeyed than return false, otherwise return true
        for val in value:
            if temp == csp_sol[val]:
                return False
    return True
