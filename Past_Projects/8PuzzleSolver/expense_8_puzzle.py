import heapq
from queue import Queue
from datetime import datetime
import copy
import sys
import os

class node:
    def __init__(self, state = None, movedTile = 0):
        self.state = state
        self.parent = None
        self.move = "Start"
        self.movedTile = movedTile
        self.costToHere = 0
        self.HnC = 0
        self.heuristic = None

def bfs(start, goal):   # Breadth First Search
    #Initialize Stats and Queue
    temp = node(copy.deepcopy(start))
    visited = []
    xLoc = 0
    yLoc = 0
    pop = 0
    expand = 0
    newNode = 0
    fringe = 0
    
    # Insert first node to queue
    q = Queue()
    q.put(temp)
    
    #If the current node is not equal to the goal
    while(temp.state != goal):
        count = 0
        
        #Pop the head of the queue
        temp = q.get()
        pop += 1
        
        #If solution found, break
        if(temp.state == goal):
            break
        
        #Pop Node from queue, add the neighboring states (Next Moves) to the queue
        if(q.qsize() > fringe):
            fringe = q.qsize()
        
        #Find the location of the blank space (0)
        for x in range(len(temp.state)):
            for y in range(len(temp.state[x])):
                if temp.state[x][y] == "0":
                    xLoc = x
                    yLoc = y
        
        if "true" in sys.argv: #Dump File Stuff
            file.write("Generating Successors from: ")
            file.write("[")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])):
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("] action = " + temp.move + " | " + "parent = ")
            if temp.parent == None:
                file.write("none ")
            else:
                file.write("[")
                for x in range(len(temp.parent.state)):
                    for y in range(len(temp.parent.state[x])):
                        file.write(temp.parent.state[x][y])
                    file.write(" ")
                file.write("] ")             
            file.write("action = " + temp.move + "\n")
                    
        # Generate possible nodes from the current node
        if temp.state not in visited:
            
            #add Current Node to Visited
            visited.append(temp.state)
            expand += 1
            
            #check for Right move / check if there is enough space for 0 to move Right (Same logic for L, D, & U)
            if(yLoc > 0):
                count += 1
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Right"
                ins.movedTile = temp.state[xLoc][yLoc-1]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc-1]    # set 0 to the new value
                ins.state[xLoc][yLoc-1] = "0"

                if ins.state not in visited:
                    q.put(ins)
                    newNode += 1
            
            #check for Left move / check if there is enough space for 0 to move Left
            if(yLoc < 2):    
                count += 1        
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Left"
                ins.movedTile = temp.state[xLoc][yLoc+1]   
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc+1]    
                ins.state[xLoc][yLoc+1] = "0"
                
                if ins.state not in visited:
                    q.put(ins)
                    newNode += 1
            
            #check for Down move / check if there is enough space for 0 to move Down
            if(xLoc > 0):
                count += 1 
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Down"
                ins.movedTile = temp.state[xLoc-1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc-1][yLoc]    
                ins.state[xLoc-1][yLoc] = "0"
                
                if ins.state not in visited:
                    q.put(ins)
                    newNode += 1
            
            #check for Up move / check if there is enough space for 0 to move Up
            if(xLoc < 2):
                count += 1 
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Up"
                ins.movedTile = temp.state[xLoc+1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc+1][yLoc]    
                ins.state[xLoc+1][yLoc] = "0"
                
                if ins.state not in visited:
                    q.put(ins)
                    newNode += 1
                
            #print(temp.state)
            
            if "true" in sys.argv: # Dump File Stuff
                file.write("Generated " + str(count) +" nodes\nclosed: ")
                for v in visited:
                    file.write("[")
                    for x in range(len(v)):
                        for y in range(len(v[x])):
                            file.write(v[x][y])
                        file.write(" ")
                    file.write("] ")
                file.write("\nfringe:\n")  
                for s in list(q.queue):
                    file.write("[")
                    for x in range(len(s.state)):
                        for y in range(len(s.state[x])):
                            file.write(s.state[x][y])
                        file.write(" ")
                    file.write("], Action = " + s.move + ", Parent = [") 
                    for x in range(len(s.parent.state)):
                        for y in range(len(s.parent.state[x])):
                            file.write(s.parent.state[x][y])
                        file.write(" ")
                    file.write("]\n")
                file.write("\n")
                
    # Printing Results to console
    print("\nNodes Popped: ", pop)
    print("Nodes Expanded: ", expand)
    print("Nodes Gen: ", newNode)
    print("Fringe Size: ", fringe)
    print("\nDepth\tTile Moved")
    
    path = []
    tileM = []
    cost = 0
    
    if "true" in sys.argv: # Dump File
        file.write("goal found: ")
        
    while(temp.state != start):
        if "true" in sys.argv: #Dump File
            file.write("'[")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("], move = " + str(temp.movedTile) + " " + temp.move + ", PARENT->>' ")
            
        path.append(temp.move)
        tileM.append(temp.movedTile)
        temp = temp.parent

    if "true" in sys.argv: # Dump File
        file.write("\nNodes Popped: " + str(pop))
        file.write("\nNodes Expanded: " + str(expand))
        file.write("\nNodes Generated: " + str(newNode))
        file.write("\nFringe Size: "+ str(fringe))
        
    i = 1
    while path:
        t = tileM.pop()
        print(i,"\t:", t, "moves", path.pop())
        i += 1
        
        cost = int(t) + cost
    
    print("\nSolution found at depth", i-1, "with cost of", cost)

    #Run through the queue again
        
def ucs(start, goal):   # Uniform Cost Search (g(n))
    #Initialize Stats and Variables
    xLoc = 0
    yLoc = 0
    pop = 0
    expand = 0
    newNode = 0
    fringe = 0
    
    #Create a queue
    temp = node(copy.deepcopy(start))
    q = []
    
    #Insert first node into queue (Priority), Use the time to break ties/same cost
    heapq.heappush(q, (temp.costToHere, datetime.now(), temp))
    visited = {}
    
    # If the current node is not equal to the goal
    while(temp.state != goal):
        count = 0
        
        # Pop the head of the queue
        temp.costToHere, t, temp = heapq.heappop(q)   # Get the cost to this node and the node it self
        pop += 1

        if(temp.state == goal):
            break
        
        #Pop Node from queue, add the neighboring states (Next Moves) to the queue
        if(len(q) > fringe):
            fringe = len(q)
            
        if "true" in sys.argv: #Dump File Stuff
            file.write("Generating Successors from: ")
            file.write("[")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("] action = " + temp.move + "Cost g(n) = " + str(temp.costToHere)+ "|" + "parent = ")
            if temp.parent == None:
                file.write("none ")
            else:
                file.write("[")
                for x in range(len(temp.parent.state)):
                    for y in range(len(temp.parent.state[x])):
                        file.write(temp.parent.state[x][y])
                    file.write(" ")
                file.write("] ")
            if(temp.parent != None):    
                file.write("action = " + temp.parent.move + " Cost g(n) = " + str(temp.parent.costToHere))
            file.write("\n")
        
        # Generate possible nodes from the current node
        if (tupledList(temp.state) not in visited):
            #Add the current state into visited
            visited[tupledList(temp.state)] = temp.costToHere
            expand += 1

            #Find the location of the blank space (0)
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    if temp.state[x][y] == "0":
                        xLoc = x
                        yLoc = y
            
            #check for Right move move / check if there is enough space for 0 to move Right [Logic repeats 3 more times for L, D, & U]
            if(yLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Right"
                ins.movedTile = temp.state[xLoc][yLoc-1]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc-1]    # set 0 to the new value
                ins.state[xLoc][yLoc-1] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                
                if (tupledList(ins.state) not in visited): #If the new node is not in visited
                    count += 1
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))    #push to queue
                    newNode += 1
                elif ((tupledList(ins.state) in visited) and (visited[tupledList(ins.state)] > ins.costToHere)): #if the node has been visited but has current has cheaper route
                    count += 1
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.costToHere   #Update Visited
                    newNode += 1
            
            #check for Left move / check if there is enough space for 0 to move Left
            if(yLoc < 2):        
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Left"
                ins.movedTile = temp.state[xLoc][yLoc+1]   
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc+1]    
                ins.state[xLoc][yLoc+1] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                
                if (tupledList(ins.state) not in visited):
                    count += 1
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))
                    newNode += 1
                elif ((tupledList(ins.state) in visited) and (visited[tupledList(ins.state)] > ins.costToHere)):
                    count += 1
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.costToHere
                    newNode += 1
            
            #check for Down move / check if there is enough space for 0 to move Down
            if(xLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Down"
                ins.movedTile = temp.state[xLoc-1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc-1][yLoc]    
                ins.state[xLoc-1][yLoc] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                
                if (tupledList(ins.state) not in visited):
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))
                    newNode += 1
                    count += 1
                elif ((tupledList(ins.state) in visited) and (visited[tupledList(ins.state)] > ins.costToHere)):
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.costToHere
                    newNode += 1
                    count += 1
            
            #check for Up move / check if there is enough space for 0 to move Up
            if(xLoc < 2):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Up"
                ins.movedTile = temp.state[xLoc+1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc+1][yLoc]    
                ins.state[xLoc+1][yLoc] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                
                if (tupledList(ins.state) not in visited):
                    count += 1
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))
                    newNode += 1
                elif ((tupledList(ins.state) in visited) and (visited[tupledList(ins.state)] > ins.costToHere)):
                    count += 1
                    heapq.heappush(q, (ins.costToHere, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.costToHere
                    newNode += 1
                
            q.sort()    # sort newly inserted nodes in the queue
                
            #print(visited[tupledList(temp.state)])
            
            if "true" in sys.argv: #Dump file
                file.write("Generated " + str(count) + " nodes\nclosed: ")
                for v in visited:
                    file.write("[")
                    for x in range(len(v)):
                        for y in range(len(v[x])):
                            file.write(v[x][y])
                        file.write(" ")
                    file.write("] ")
                file.write("\nfringe:\n")  
                for s in q:
                    file.write("[")
                    for x in range(len(s[2].state)):
                        for y in range(len(s[2].state[x])):
                            file.write(s[2].state[x][y])
                        file.write(" ")
                    file.write("], Action = " + s[2].move + ", Cost g(n) = " + str(s[2].costToHere) + ", Parent = [") 
                    for x in range(len(s[2].parent.state)):
                        for y in range(len(s[2].parent.state[x])):
                            file.write(s[2].parent.state[x][y])
                        file.write(" ")
                    file.write("] \n")
                file.write("\n")  
                
    # Print Results
    print("\nNodes Popped: ", pop)
    print("Nodes Expanded: ", expand)
    print("Nodes Gen: ", newNode)
    print("Fringe Size: ", fringe)
    print("\nDepth\tTile Moved")
    
    path = []
    tileM = []
    cost = 0
    
    if "true" in sys.argv:
        file.write("goal found: ")
        
    while(temp.state != start):
        if "true" in sys.argv: 
            file.write("'[")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("], ")
            file.write("move = " + str(temp.movedTile) + " cost g(n) = " + str(temp.costToHere) + " " + temp.move + ", PARENT->>' ")
            
        path.append(temp.move)
        tileM.append(temp.movedTile)
        temp = temp.parent
            
    if "true" in sys.argv:
        file.write("\nNodes Popped: " + str(pop))
        file.write("\nNodes Expanded: " + str(expand))
        file.write("\nNodes Generated: " + str(newNode))
        file.write("\nFringe Size: "+ str(fringe))
        
    i = 1
    while path:
        t = tileM.pop()
        print(i,"\t:", t, "moves", path.pop())
        i += 1
        
        cost = int(t) + cost
    
    print("\nSolution found at depth", i-1, "with cost of", cost)                    
        
def greedy(start, goal):    #Greedy Search (h(n))
    #Create a queue and initialize stats
    xLoc = 0
    yLoc = 0
    pop = 0
    expand = 0
    newNode = 0
    fringe = 0
    visited = []  
    q = []
    
    temp = node(copy.deepcopy(start))
    temp.heuristic = calcHeurDisplace(temp, goal)   #Calculate the heuristic using displaced tiles
    
    # Push first node into queue (Priority)
    heapq.heappush(q, (temp.heuristic, datetime.now(), temp))
    
    #If the current node is not equal to the goal
    while(temp.state != goal):
        count = 0
        
        # Pop the head of the queue and get the temp and the new heuristic
        temp.heuristic, time, temp = heapq.heappop(q)
        pop += 1

        # If goal reached, break
        if(temp.state == goal):
            break
        
        if(len(q) > fringe):
            fringe = len(q)
            
        if "true" in sys.argv: # Dump File
            file.write("Generating Successors from: [")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])):
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("] action = " + temp.move + "Cost h(n) = " + str(temp.heuristic) +"|" + "parent = ")
            if temp.parent == None:
                file.write("none ")
            else:
                file.write("[")
                for x in range(len(temp.parent.state)):
                    for y in range(len(temp.parent.state[x])):
                        file.write(temp.parent.state[x][y])
                    file.write(" ")
                file.write("] ")
            if(temp.parent != None):    
                file.write("action = " + temp.parent.move + " Cost g(n) = " + str(temp.parent.costToHere))
            file.write("\n")
        
        # Generate possible nodes from the current node if either the node is not visited or the current node has a better solution than the visited.
        if(temp.state not in visited):
            
            q.clear #clear queue
            visited.append(temp.state)  # Add current node to visited
            expand += 1

            #Find the location of the blank space (0)
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    if temp.state[x][y] == "0":
                        xLoc = x
                        yLoc = y
                        
            #check for Right move / check if there is enough space for 0 to move Right
            if(yLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Right"
                ins.movedTile = temp.state[xLoc][yLoc-1]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc-1]    # set 0 to the new value
                ins.state[xLoc][yLoc-1] = "0"
                
                if (ins.state not in visited):
                    count += 1
                    t = temp.movedTile
                    ins.costToHere = temp.costToHere + int(t)
                    ins.heuristic = calcHeurDisplace(ins, goal)
                    heapq.heappush(q, (ins.heuristic, datetime.now(), ins))
                    newNode += 1
                    
            #check for Left move / check if there is enough space for 0 to move Left
            if(yLoc < 2):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Left"
                ins.movedTile = temp.state[xLoc][yLoc+1]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc+1]    # set 0 to the new value
                ins.state[xLoc][yLoc+1] = "0"
                
                if ins.state not in visited:
                    count += 1
                    t = temp.movedTile
                    ins.costToHere = temp.costToHere + int(t)
                    ins.heuristic = calcHeurDisplace(ins, goal)
                    heapq.heappush(q, (ins.heuristic, datetime.now(), ins))
                    newNode += 1
                    
            #check for Down move / check if there is enough space for 0 to move Down
            if(xLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Down"
                ins.movedTile = temp.state[xLoc-1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc-1][yLoc]    # set 0 to the new value
                ins.state[xLoc-1][yLoc] = "0"
                
                if ins.state not in visited:
                    count += 1
                    t = temp.movedTile
                    ins.costToHere = temp.costToHere + int(t)
                    ins.heuristic = calcHeurDisplace(ins, goal)
                    heapq.heappush(q, (ins.heuristic, datetime.now(), ins))
                    newNode += 1
                    
            #check for Up move / check if there is enough space for 0 to move Up
            if(xLoc < 2):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Up"
                ins.movedTile = temp.state[xLoc+1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc+1][yLoc]    # set 0 to the new value
                ins.state[xLoc+1][yLoc] = "0"
                
                if ins.state not in visited:
                    count += 1
                    t = temp.movedTile
                    ins.costToHere = temp.costToHere + int(t)
                    ins.heuristic = calcHeurDisplace(ins, goal)
                    heapq.heappush(q, (ins.heuristic, datetime.now(), ins))
                    newNode += 1
                
            q.sort() #sort newly inserted values
            
            #print(temp.heuristic)
            
            if "true" in sys.argv: # Dump File
                file.write("Generated " + str(count) +" nodes\nclosed: ")   
                for v in visited:
                    file.write("[")
                    for x in range(len(v)):
                        for y in range(len(v[x])):
                            file.write(v[x][y])
                        file.write(" ")
                    file.write("] ")
                file.write("\nfringe:\n")  
                for s in q:
                    file.write("[")
                    #for x in range(len(s)):
                    for x in range(len(s[2].state)):
                        for y in range(len(s[2].state[x])):
                            file.write(s[2].state[x][y])
                        file.write(" ")
                    file.write("], Action = " + s[2].move + ", Cost h(n) = " + str(s[2].heuristic) + ", Parent = [") 
                    for x in range(len(s[2].parent.state)):
                        for y in range(len(s[2].parent.state[x])):
                            file.write(s[2].parent.state[x][y])
                        file.write(" ")
                    file.write("] \n")
                file.write("\n")  
    
    # Print Result
    path = []
    tileM = []
    cost = 0
    
    print("\nDepth\tTile Moved")
    
    if "true" in sys.argv:
        file.write("goal found: ")
        
    while(temp.state != start):
        if "true" in sys.argv:
            file.write("'[")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("], ")
            file.write("move = " + str(temp.movedTile) + " " + str(temp.move) + " heuristic h(n) = " + str(temp.heuristic) + ", PARENT->>' ")
        path.append(temp.move)
        tileM.append(temp.movedTile)
        temp = temp.parent
        
    if "true" in sys.argv:
        file.write("\nNodes Popped: " + str(pop))
        file.write("\nNodes Expanded: " + str(expand))
        file.write("\nNodes Generated: " + str(newNode))
        file.write("\nFringe Size: "+ str(fringe))
        
    while(temp.state != start):
        path.append(temp.move)
        tileM.append(temp.movedTile)
        temp = temp.parent
        
    i = 1
    while path:
        t = tileM.pop()
        print(i,"\t:", t, "moves", path.pop())
        i += 1
        
        cost = int(t) + cost
    
    print("\nNodes Popped: ", pop)
    print("Nodes Expanded: ", expand)
    print("Nodes Gen: ", newNode)
    print("Fringe Size: ", fringe)
        
    print("\nSolution found at depth", i-1, "with cost of", cost)
    
       
    #Run through the queue again       

def Astar(start, goal):     # A* (g(n) + h(n))
    #Create a queue and initialize
    xLoc = 0
    yLoc = 0
    pop = 0
    expand = 0
    newNode = 0
    fringe = 0
    q = []
    visited = {}
    temp = node(copy.deepcopy(start))

    # Push the node into the queue
    heapq.heappush(q, (temp.HnC, datetime.now(), temp))
    
    #If the current node is not equal to the goal
    while(temp.state != goal):
        count = 0
        
        #Pop the head of the queue
        temp.HnC, time, temp = heapq.heappop(q)
        pop += 1

        #if node is equal to the goal, break
        if(temp.state == goal):
            break
        
        if(len(q) > fringe):
            fringe = len(q)
            
        if "true" in sys.argv: # Dump File
            file.write("Generating Successors from: [")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("] action = " + temp.move + " Cost g(n) = " + str(temp.costToHere) + " Heuristic h(n) = " + str(temp.heuristic)  + " total f(n) = " + str(temp.HnC) + "|" + "parent = ")
            if temp.parent == None:
                file.write("none ")
            else:
                file.write("[")
                for x in range(len(temp.parent.state)):
                    for y in range(len(temp.parent.state[x])):
                        file.write(temp.parent.state[x][y])
                    file.write(" ")
                file.write("] ")
            if(temp.parent != None):    
                file.write(" " + "action = " + temp.parent.move + " Cost g(n) = " + str(temp.parent.costToHere) + " Heuristic h(n) = " + str(temp.parent.heuristic)  + " total f(n) = " + str(temp.parent.HnC) + "|" + "parent = ")
            file.write("\n")
        
        # Generate possible nodes from the current node
        if tupledList(temp.state) not in visited:
            expand += 1
            
            #Add the current state into visited
            visited[tupledList(temp.state)] = temp.costToHere

            #Find the location of the blank space (0)
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    if temp.state[x][y] == "0":
                        xLoc = x
                        yLoc = y
            
            #check for down move / check if there is enough space for 0 to move Right
            if(yLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Right"
                ins.movedTile = temp.state[xLoc][yLoc-1]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc-1]    # set 0 to the new value
                ins.state[xLoc][yLoc-1] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                ins.heuristic = calcHeurManHatt(ins, goal)
                ins.HnC = ins.costToHere + ins.heuristic
                
                if  (tupledList(ins.state) not in visited):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    newNode += 1
                    count += 1
                elif ((tupledList(ins.state) in visited) and visited[tupledList(ins.state)] > ins.HnC):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.HnC
                    newNode += 1
                    count += 1
            
            #check for up move / check if there is enough space for 0 to move Left
            if(yLoc < 2):            
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Left"
                ins.movedTile = temp.state[xLoc][yLoc+1]   
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc+1]    
                ins.state[xLoc][yLoc+1] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                ins.heuristic = calcHeurManHatt(ins, goal)
                ins.HnC = ins.costToHere + ins.heuristic
                
                if  (tupledList(ins.state) not in visited):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    newNode += 1
                    count += 1
                elif ((tupledList(ins.state) in visited) and visited[tupledList(ins.state)] > ins.HnC):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.HnC
                    newNode += 1
                    count += 1
            
            #check for left move / check if there is enough space for 0 to move Down
            if(xLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Down"
                ins.movedTile = temp.state[xLoc-1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc-1][yLoc]    
                ins.state[xLoc-1][yLoc] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                ins.heuristic = calcHeurManHatt(ins, goal)
                ins.HnC = ins.costToHere + ins.heuristic
                
                if  (tupledList(ins.state) not in visited):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    newNode += 1
                    count += 1
                elif ((tupledList(ins.state) in visited) and visited[tupledList(ins.state)] > ins.HnC):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.HnC
                    newNode += 1
                    count += 1
            
            #check for right move / check if there is enough space for 0 to move Up
            if(xLoc < 2):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Up"
                ins.movedTile = temp.state[xLoc+1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc+1][yLoc]    
                ins.state[xLoc+1][yLoc] = "0"
                t = temp.movedTile
                ins.costToHere = temp.costToHere + int(t)
                ins.heuristic = calcHeurManHatt(ins, goal)
                ins.HnC = ins.costToHere + ins.heuristic
                
                if  (tupledList(ins.state) not in visited):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    newNode += 1
                    count += 1
                elif ((tupledList(ins.state) in visited) and visited[tupledList(ins.state)] > ins.HnC):
                    heapq.heappush(q, (ins.HnC, datetime.now(), ins))
                    visited[tupledList(ins.state)] = ins.HnC
                    newNode += 1
                    count += 1
                
                ''''''
                
            #print(temp.HnC)
            
            if "true" in sys.argv:
                file.write("Generated " + str(count) + " nodes\nclosed: ")
                for v in visited:
                    file.write("[")
                    for x in range(len(v)):
                        for y in range(len(v[x])):
                            file.write(v[x][y])
                        file.write(" ")
                    file.write("] ")
                file.write("\nfringe:\n")  
                for s in q:
                    file.write("[")
                    for x in range(len(s[2].state)):
                        for y in range(len(s[2].state[x])):
                            file.write(s[2].state[x][y])
                        file.write(" ")
                    file.write("], Action = " + s[2].move + ", Cost g(n) = " + str(s[2].costToHere) + ", Heuristics h(n) = " + str(s[2].heuristic) + ", Total f(n) = " + str(s[2].HnC) + ", Parent = [") 
                    for x in range(len(s[2].parent.state)):
                        for y in range(len(s[2].parent.state[x])):
                            file.write(s[2].parent.state[x][y])
                        file.write(" ")
                    file.write("] \n")
                file.write("\n")  
    
    # Print Results
    print("\nNodes Popped: ", pop)
    print("Nodes Expanded: ", expand)
    print("Nodes Gen: ", newNode)
    print("Fringe Size: ", fringe)
    print("\nDepth\tTile Moved")
    
    path = []
    tileM = []
    cost = 0
    
    if "true" in sys.argv:
        file.write("goal found: ")
            
        while(temp.state != start):
            if "true" in sys.argv:
                file.write("'[")
                for x in range(len(temp.state)):
                    for y in range(len(temp.state[x])): 
                        file.write(temp.state[x][y])
                    file.write(" ")
                file.write("], ")
                file.write("move = " + str(temp.movedTile) + " " + str(temp.move) + " heuristic h(n) = " + str(temp.heuristic) + " cost g(n) = " + str(temp.costToHere)  + " total f(n) = " + str(temp.HnC) + ", PARENT->>' ")
            path.append(temp.move)
            tileM.append(temp.movedTile)
            temp = temp.parent
                
        if "true" in sys.argv:
            file.write("\nNodes Popped: " + str(pop))
            file.write("\nNodes Expanded: " + str(expand))
            file.write("\nNodes Generated: " + str(newNode))
            file.write("\nFringe Size: "+ str(fringe))
    
    while(temp.state != start):
        path.append(temp.move)
        tileM.append(temp.movedTile)
        temp = temp.parent
        
    i = 1
    while path:
        t = tileM.pop()
        print(i,"\t:", t, "moves", path.pop())
        i += 1
        
        cost = int(t) + cost
    
    print("\nSolution found at depth", i-1, "with cost of", cost)
    
       
    #Run through the queue again                     

def dfs(start, goal):   # Depth First Search
    #Create a queue
    temp = node(copy.deepcopy(start))
    q = []
    q.append(temp)
    visited = []
    
    xLoc = 0
    yLoc = 0
    
    pop = 0
    expand = 0
    newNode = 0
    fringe = 0
    
    #If the current node is not equal to the goal
    while(temp.state != goal):
        count = 0
        
        # pop the head of the queue
        temp = q.pop()
        pop += 1
        
        if(temp.state == goal):
            break
        
        #Pop Node from queue, add the neighboring states (Next Moves) to the queue
        if(len(q) > fringe):
            fringe = len(q)
        
        #Find the location of the blank space (0)
        for x in range(len(temp.state)):
            for y in range(len(temp.state[x])):
                if temp.state[x][y] == "0":
                    xLoc = x
                    yLoc = y
                    
        if "true" in sys.argv: #Dump File Stuff
            file.write("Generating Successors from: [")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])):
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("] action = " + temp.move + " | " + "parent = ")
            if temp.parent == None:
                file.write("none ")
            else:
                file.write("[")
                for x in range(len(temp.parent.state)):
                    for y in range(len(temp.parent.state[x])):
                        file.write(temp.parent.state[x][y])
                    file.write(" ")
                file.write("] ")             
            file.write("action = " + temp.move + "\n")
            
        # Generate possible nodes from the current node
        if temp.state not in visited:
            
            #add Current Node to Visited
            visited.append(temp.state)
            expand += 1
            
            #check for down move / check if there is enough space for 0 to move Right
            if(yLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Right"
                ins.movedTile = temp.state[xLoc][yLoc-1]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc-1]    # set 0 to the new value
                ins.state[xLoc][yLoc-1] = "0"

                if ins.state not in visited:
                    q.append(ins)
                    newNode += 1
                    count += 1
            
            #check for up move / check if there is enough space for 0 to move Left
            if(yLoc < 2):            
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Left"
                ins.movedTile = temp.state[xLoc][yLoc+1]   
                
                ins.state[xLoc][yLoc] = temp.state[xLoc][yLoc+1]    
                ins.state[xLoc][yLoc+1] = "0"
                
                if ins.state not in visited:
                    q.append(ins)
                    newNode += 1
                    count += 1
            
            #check for left move / check if there is enough space for 0 to move Down
            if(xLoc > 0):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Down"
                ins.movedTile = temp.state[xLoc-1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc-1][yLoc]    
                ins.state[xLoc-1][yLoc] = "0"
                
                if ins.state not in visited:
                    q.append(ins)
                    newNode += 1
                    count += 1
            
            #check for right move / check if there is enough space for 0 to move Up
            if(xLoc < 2):
                ins = node(copy.deepcopy(temp.state))
                ins.parent = temp
                ins.move = "Up"
                ins.movedTile = temp.state[xLoc+1][yLoc]
                
                ins.state[xLoc][yLoc] = temp.state[xLoc+1][yLoc]    
                ins.state[xLoc+1][yLoc] = "0"
                
                if ins.state not in visited:
                    q.append(ins)
                    newNode += 1
                    count += 1
                
            #print(temp.state)

            if "true" in sys.argv: # Dump File Stuff
                file.write("Generated " + str(count) +" nodes\nclosed: ")
                for v in visited:
                    file.write("[")
                    for x in range(len(v)):
                        for y in range(len(v[x])):
                            file.write(v[x][y])
                        file.write(" ")
                    file.write("] ")
                file.write("\nfringe:\n")  
                for s in list(q):
                    file.write("[")
                    for x in range(len(s.state)):
                        for y in range(len(s.state[x])):
                            file.write(s.state[x][y])
                        file.write(" ")
                    file.write("], Action = " + s.move + ", Parent = [")
                    for x in range(len(s.parent.state)):
                        for y in range(len(s.parent.state[x])):
                            file.write(s.parent.state[x][y])
                        file.write(" ")
                    file.write("]\n")
                file.write("\n")
    path = []
    tileM = []
    cost = 0
    
    if "true" in sys.argv: # Dump File
        file.write("goal found: ")
        
    while(temp.state != start):
        if "true" in sys.argv: #Dump File
            file.write("'[")
            for x in range(len(temp.state)):
                for y in range(len(temp.state[x])): 
                    file.write(temp.state[x][y])
                file.write(" ")
            file.write("], move = " + str(temp.movedTile) + " " + temp.move + ", PARENT->>' ")
            
        path.append(temp.move)
        tileM.append(temp.movedTile)
        temp = temp.parent

    if "true" in sys.argv: # Dump File
        file.write("\nNodes Popped: " + str(pop))
        file.write("\nNodes Expanded: " + str(expand))
        file.write("\nNodes Generated: " + str(newNode))
        file.write("\nFringe Size: "+ str(fringe))
        
    i = 1
    while path:
        t = tileM.pop()
        print(i,"\t:", t, "moves", path.pop())
        i += 1
        
        cost = int(t) + cost
    
    print("\nSolution found at depth", i-1, "with cost of", cost)

    #Run through the queue again

def calcHeurManHatt(state, goal):   # Used in A*
    total = 0
    for x in range(len(state.state)):
        for y in range(len(state.state[x])):    # Go through each tile
            for i in range(len(goal)):
                for j in range(len(goal[i])):       
                    if state.state[x][y] == goal[i][j]:     # When matching tile is found in the goal, 
                        total += int(state.state[x][y])*(abs(x-i) + abs(y-j))   # find the distance and multiply the cost (distance * cost = heuristic) due to weight of higher cost moves
    return total

def calcHeurDisplace(state, goal):  # Used in Greedy
    h = 0
    for x in range(len(state.state)):
        for y in range(len(state.state[x])):    # Go through each tile
            if state.state[x][y] != goal[x][y]: h += 5  # increment by 5 to have higher weight
            
    return h
    
def tupledList(state): # Tupling Function for nested list
    return tuple(tuple(s) for s in state)

#MAIN CODE ========================================================
stArr = ([0,0,0])
glArr = ([0,0,0])

#Create array for Start
file = open(sys.argv[1])
i = 0
for f in file:
    if "END OF FILE" in f:
        break
    
    stArr[i] = f.split()
    i += 1
file.close()

#Create array for Goal
file = open(sys.argv[2])
i = 0
for f in file:
    if f == "END OF FILE":
        break
    
    glArr[i] = f.split()
    i += 1
file.close()

args = sys.argv
if "true" in sys.argv:
    d = datetime.today().strftime("%Y-%m-%d")
    t = datetime.now().strftime("%H-%M-%S")
    
    st = "trace-" + str(d) + "=" + str(t) + ".txt"
    file = open(st, "x")
    file.write("command line arguments: ")
    for i in sys.argv:
        file.write("'" + i + "'" + " ")

if "bfs" in sys.argv:
    if "true" in sys.argv: file.write("\n" + "Running bfs\n")
    bfs(stArr, glArr)
    file.close()
elif "ucs" in sys.argv:
    if "true" in sys.argv: file.write("\n" + "Running ucs\n")
    ucs(stArr, glArr)
    file.close()
elif "greedy" in sys.argv:
    if "true" in sys.argv: file.write("\n" + "Running greedy\n")
    greedy(stArr, glArr)
    file.close()
elif "A*" in sys.argv:
    if "true" in sys.argv: file.write("\n" + "Running A*\n")
    Astar(stArr, glArr)
    file.close()
elif "dfs" in sys.argv:
    if "true" in sys.argv: file.write("\n" + "Running A*\n")
    dfs(stArr, glArr)
    file.close()
else:
    if "true" in sys.argv: file.write("\n" + "Running A* [Default]\n")
    Astar(stArr, glArr)
    file.close()