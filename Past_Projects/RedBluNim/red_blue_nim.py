#Rudy Orozco / 1001864902 / CSE 4308-005

from queue import Queue
from datetime import datetime
import sys

# Value Node
class value:
    def __init__(self):
        self.Blue = 0
        self.Red = 0
        self.Value = None   # use this as the utility value

# Functionality goes here
def abMinMax(state, depthLim):
    alpha = -sys.maxsize
    beta = sys.maxsize
    res = value()

    #Check for Blue Pile Decisions
    #print("passed in state: ", state)
    res, bag = abMaxVal(state, alpha, beta, depthLim, 1) # Returns Util Val, Blue, and Red M
    
    if bag[0] != state[0]:
        print("Takes " + str(state[0] - bag[0]) + " Red Marbles\n")
    if bag[1] != state[1]:
        print("Takes " + str(state[1] - bag[1]) + " Blue Marbles\n")
    
    return res, bag

#For Making Decisions ========================
def abMaxVal(state, a, b, depthLim, depth):
    # TERMINAL TEST & DEPTH LIMIT
    if (depth == depthLim) and (depthLim != -1):
        if Ver == "s":
            score = -abs(state[0] - state[1])
        else:
            score = abs(state[0] - state[1])
        return score, state
    
    if (state[0] <= 0) or (state[1] <= 0):
        #print("Max Terminal", state, ((state[0]*2) + (state[1]*3)), "|| Alpha:", a, "Beta:", b, "\n")
        if Ver == "s":
            score = -((state[0]*2) + (state[1]*3))
        else:
            score = ((state[0]*2) + (state[1]*3))
        return score, state
    
    bag = [0,0]
    
    v = -sys.maxsize
    
    # for all successors
    if Ver == "s":    # FOR STANDARD
        if state[0] >= 2:
            newState = [state[0]-2, state[1]] # 2R
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: return v, newState
            if v > a: 
                a = v
                bag = [state[0]-2, state[1]]
                
        if state[1] >= 2:    
            newState = [state[0], state[1]-2] # 2B
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: return v, newState
            if v > a: 
                a = v
                bag = [state[0], state[1]-2]

        if state[0] >= 1:
            newState = [state[0]-1, state[1]] # 1R
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: return v, newState
            if v > a: 
                a = v
                bag = [state[0]-1, state[1]]
                                        
        if state[1] >= 1:
            newState = [state[0], state[1]-1] # 1B
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: 
                return v, newState
            if v > a: 
                a = v
                bag = [state[0], state[1]-1]
    else:    # FOR MISERE
        if state[1] >= 1:
            newState = [state[0], state[1]-1] # 1B
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: 
                return v, newState
            if v > a: 
                a = v
                bag = [state[0], state[1]-1]

        if state[0] >= 1:
            newState = [state[0]-1, state[1]] # 1R
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: return v, newState
            if v > a: 
                a = v
                bag = [state[0]-1, state[1]]

        if state[1] >= 2:    
            newState = [state[0], state[1]-2] # 2B
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: return v, newState
            if v > a: 
                a = v
                bag = [state[0], state[1]-2]
                
        if state[0] >= 2:
            newState = [state[0]-2, state[1]] # 2R
            newV, other = abMinVal(newState, a, b, depthLim, depth+1)
            v = max(v, newV)
            if v >= b: return v, newState
            if v > a: 
                a = v
                bag = [state[0]-2, state[1]]
                
    return v, bag

def abMinVal(state, a, b, depthLim, depth):
    #print("Min")
    if (depth == depthLim) and (depthLim != -1):
        if Ver == "s":
            score = abs(state[0] - state[1])
        else:
            score = -abs(state[0] - state[1])
        return score, state
    
    if (state[0] <= 0) or (state[1] <= 0): 
        #print("Min Terminal", state, ((state[0]*2) + (state[1]*3)), "|| Alpha:", a, "Beta:", b, "\n")
        if Ver == "s":
            score = ((state[0]*2) + (state[1]*3))
        else:
            score = -((state[0]*2) + (state[1]*3))
        return score, state
    
    bag = [0,0]
    
    v = sys.maxsize
    
    # for all successors
    if Ver == "s":  # FOR STANDARD 
        if state[0] >= 2:     
            newState = [state[0]-2, state[1]] # 2R
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0]-2, state[1]]
                
        if state[1] >= 2:         
            newState = [state[0], state[1]-2] # 2B
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0], state[1]-2]
                
        if state[0] >= 1:    
            newState = [state[0]-1, state[1]] # 1R
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0]-1, state[1]]
                
        if state[1] >= 1:     
            newState = [state[0], state[1]-1] # 1B
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0], state[1]-1]
    else:   # FOR MISERE 
        if state[1] >= 1:     
            newState = [state[0], state[1]-1] # 1B
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0], state[1]-1]
                
        if state[0] >= 1:    
            newState = [state[0]-1, state[1]] # 1R
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0]-1, state[1]]

        if state[1] >= 2:         
            newState = [state[0], state[1]-2] # 2B
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0], state[1]-2]
                
        if state[0] >= 2:     
            newState = [state[0]-2, state[1]] # 2R
            newV, other = abMaxVal(newState, a, b, depthLim, depth + 1)
            v = min(v, newV)
            if v <= a: return v, newState
            if v < b: 
                b = v
                bag = [state[0]-2, state[1]]
                
    return v, bag

#MAIN CODE ========================================================
BlueM = 0
RedM = 0
Ver = "s"
FirstPlay = "c"
Depth = -1
run = True

# red_blue_nim.py [1]<num-red> [2]<num-blue> [3]<version> [4]<first-player> [OMIT]<depth>
if len(sys.argv) < 3:
    print("ERROR: Not enough arguments passed in")
    exit()
    
if not (sys.argv[1].isdigit()) or not (sys.argv[2].isdigit()):
    print("ERROR: Use Integers for number of marbles")
    exit()
    
RedM = int(sys.argv[1])
BlueM = int(sys.argv[2])
root = [RedM, BlueM]
colorPile = "TEST"
numMarblet = "TEST2"
numMarb = 0

if (sys.argv[len(sys.argv) - 1].isdigit()) and (len(sys.argv) != 3):
    if int(sys.argv[len(sys.argv) - 1]) > 1:
        Depth = int(sys.argv[len(sys.argv) - 1])

print("============================")
# Version Check
if "misere" in sys.argv:
    Ver = "m"
    print("Version: Misere")
else:
    print("Version: Standard")

if "human" in sys.argv:
    FirstPlay = "h"
    print("First Play: Human")
else:
    print("First Play: Computer")
    
if Depth == -1:
    print("Depth Limit: Not Set")
else:
    print("Depth Limit:", Depth)
    
print("Current bag: " + str(RedM) + " Red, " + str(BlueM) + " Blue\n============================")

if (RedM <= 0) or (BlueM <= 0):
    print("ERROR: Cannot use negative integers, please try again.")
    exit()

# Setup res
res = 0, [0,0]
res[1][0] = RedM
res[1][1] = BlueM

while(run):
    # Computer Goes First
    if FirstPlay == "c":
        if run == True:
            #Computer Turn
            print("\nComputer deciding...")
            res = abMinMax(root, Depth)
            if (res[1][0] <= 0) or (res[1][1] <= 0):
                if Ver == "s":
                    print("\n// GAME OVER // \n[Standard] Computer Wins: " + str((res[1][0]*2 + res[1][1]*3)))
                else:
                    print("\n// GAME OVER // \n[Misere] Computer Loses: " + str(-(res[1][0]*2 + res[1][1]*3)))
                run = False

            print("Current bag: " + str(res[1][0]) + " Red, " + str(res[1][1]) + " Blue\n")
            
        if run == True:
            #Human Turn
            color = ""
            loop = True
            while(loop):    
                colorPile = input("Choose b/B or r/R Marbles: ")
                if colorPile == "b" or colorPile == "B" or colorPile == "r" or colorPile == "R":
                    loop = False
            loop = True
            while(loop):
                if ((colorPile == "b") or (colorPile == "B")) and (res[1][1] < 2):
                    print("Blue has one marble left.")
                    numMarb = 1
                    loop = False
                elif ((colorPile == "r") or (colorPile == "R")) and (res[1][0] < 2):
                    print("Blue has one marble left.")
                    numMarb = 1
                    loop = False
                else:
                    numMarblet = input("Choose 1 or 2 Marbles: ")
                    if numMarblet == "1" or numMarblet == "2":
                        numMarb = int(numMarblet)
                        loop = False
            
            if (colorPile == "b") or (colorPile == "B"):
                #print("chose Blue")
                root = [res[1][0], res[1][1] - numMarb]
            else:
                #print("chose red")
                root = [res[1][0] - numMarb, res[1][1]]
                
            if (root[0] <= 0) or (root[1] <= 0):
                if Ver == "s":
                    print("\n\n// GAME OVER // \n[Standard] Computer Loses: " + str(-(root[0]*2 + root[1]*3)))
                else:
                    print("\n\n// GAME OVER // \n[Misere] Computer Wins: " + str((root[0]*2 + root[1]*3)))
                run = False
            print("Current bag: " + str(root[0]) + " Red, " + str(root[1]) + " Blue\n")
        
    else:
        # Human Goes First
        if run == True:
            #Human Turn
            color = ""
            loop = True
            while(loop):    
                colorPile = input("Choose b/B or r/R Marbles: ")
                #print("Color Chosen\n", colorPile)
                if colorPile == "b" or colorPile == "B" or colorPile == "r" or colorPile == "R":
                    loop = False
            loop = True
            while(loop):
                if ((colorPile == "b") or (colorPile == "B")) and (res[1][1] < 2):
                    print("Blue has one marble left.")
                    numMarb = 1
                    loop = False
                elif ((colorPile == "r") or (colorPile == "R")) and (res[1][0] < 2):
                    print("Blue has one marble left.")
                    numMarb = 1
                    loop = False
                else:
                    numMarblet = input("Choose 1 or 2 Marbles: ")
                    if numMarblet == "1" or numMarblet == "2":
                        numMarb = int(numMarblet)
                        loop = False
            
            if (colorPile == "b") or (colorPile == "B"):
                #print("chose Blue")
                root = [res[1][0], res[1][1] - numMarb]
            else:
                #print("chose red")
                root = [res[1][0] - numMarb, res[1][1]]
                
            if (root[0] <= 0) or (root[1] <= 0):
                if Ver == "s":
                    print("\n\n// GAME OVER // \n[Standard] Computer Loses: " + str(-(root[0]*2 + root[1]*3)))
                else:
                    print("\n\n// GAME OVER // \n[Misere] Computer Wins: " + str((root[0]*2 + root[1]*3)))
                run = False
                
        if run == True:
            #Computer Turn
            print("\nComputer deciding...")
            res = abMinMax(root, Depth)
            if (res[1][0] <= 0) or (res[1][1] <= 0):
                if Ver == "s":
                    print("\n// GAME OVER // \n[Standard] Computer Wins: " + str((res[1][0]*2 + res[1][1]*3)))
                else:
                    print("\n// GAME OVER // \n[Misere] Computer Loses: " + str(-(res[1][0]*2 + res[1][1]*3)))
                run = False
        
            print("Current bag: " + str(res[1][0]) + " Red, " + str(res[1][1]) + " Blue\n")