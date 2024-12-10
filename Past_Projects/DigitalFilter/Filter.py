import csv
import cmath
import math
import matplotlib.pyplot as plt
import numpy as np

def DFTConvolve(x, h):
    bigN = len(x) + len(h) - 1  # Length of N
    lenx = len(x) - 1   # orignal x len
    lenh = len(h) - 1    # orignal h len
    
    for i in range((bigN - len(x))): # Pad 0 on x
        x.append(0)
    for i in range((bigN - len(h))): # Pad 0 on h
        h.append(0)
    
    # Compute DFT of x
    xOutput = []
    for i in range(bigN):
        res = 0
        for j in range(bigN):
            res += float(x[j]) * cmath.exp(-2j * math.pi * i * j / bigN)
        xOutput.append(res)
        
    # Compute DFT of h
    hOutput = []
    for i in range(bigN):
        res = 0
        for j in range(bigN):
            res += float(h[j]) * cmath.exp(-2j * math.pi * i * j / bigN)
        hOutput.append(res)
        
    # Compute x*h per y index
    yOutput = []
    for i in range(bigN):
        yOutput.append(xOutput[i] * hOutput[i])
    
    # Inverse DFT on y
    yres = []
    for i in range(bigN):
        res = 0
        for j in range(bigN):
            res += yOutput[j] * cmath.exp(2j * math.pi * i * j / bigN)
        yres.append((res/bigN).real) 
    
    return yres[lenh:bigN - lenh]

def DiffEQ(x, b, a = [1]):
    yOut = []
    
    mSize = len(b) - 1
    nSize = len(a) - 1
    
    for n in range(len(x)):
        xSum = 0
        ySum = 0
        
        for m in range(mSize + 1):  # Calculate xSum
            if n - m >= 0:  
                xSum += float(b[m]) * float(x[n - m])  
                
        for m in range(1, nSize + 1):  # Calculate Sum
            if n - m > 0: 
                ySum += float(a[m]) * float(y[n - m])  
        
        yOut.append(xSum - ySum)
    
    # Remove 0 value indexes
    nelen = max(mSize, nSize) 
    yOut = yOut[nelen:]  
    
    return yOut

def convolution(x, h):
    lenx = len(x)
    lenh = len(h)
    nsize = lenx + lenh - 1
    yres = []
    
    for n in range(nsize): # for each element in y(n)
        sum = 0
        count = 0
        for k in range(lenx):
            if (n-k >= 0) and (n-k < lenh): # Check for bounds for h[] to print
                sum += float(x[k])*float(h[n-k])
                #print( "n = " + str(n) + " | x[" + str(k) + "] + h[" + str(n-k) + "]")
        count += 1
        #print(count)
        yres.append(sum)
    
    # Remove 0 Values
    yres = yres[lenh - 1:lenx]

    return yres

def stdSig(x):
    output = []
    for n in range(len(x)):
        output.append(float(x[n]))
        
    return output

#======================================================================================================================
xarry = []
harry = []
newArr = []
xbigN = None
hbigN = None
Output = []

with open("input.csv", mode = 'r') as file:
    csvF = csv.reader(file)
    for lines in csvF:
        xarry = lines
    xbigN = len(xarry)
    
with open("filter.csv", mode = 'r') as file:
    csvF = csv.reader(file)
    for lines in csvF:
        harry = lines
    hbigN = len(harry)
    
inputSig = stdSig(xarry)
with open("DFTConvolve_Out.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerows([inputSig])
    
filterSig = stdSig(harry)
with open("DFTConvolve_Out.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerows([filterSig])
    
Output1 = convolution(xarry, harry)
with open("convolution_Out.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerows([Output1])

Output2 = DiffEQ(xarry, harry)
with open("DiffEQ_Out.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerows([Output2])

Output3 = DFTConvolve(xarry, harry)
with open("DFTConvolve_Out.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerows([Output3])
    

#Output = stdSig(xarry)

y1 = np.array(Output1)
y2 = np.array(Output2)
y3 = np.array(Output3)
y4 = np.array(inputSig)
y5 = np.array(filterSig)

fig, axes = plt.subplots(nrows=5, ncols=1, figsize=(15, 10))

axes[0].plot(y1)
axes[0].set_title('Convolution')
axes[0].grid(True)

axes[1].plot(y2)
axes[1].set_title('Differential Equation')
axes[1].grid(True)

axes[2].plot(y3)
axes[2].set_title('DFT Convolution')
axes[2].grid(True)
axes[2].set_ylabel('Amplitude')

axes[3].plot(y4)
axes[3].set_title('Input')
axes[3].grid(True)

axes[4].plot(y5)
axes[4].set_title('Filter')
axes[4].grid(True)
axes[4].set_xlabel('Time')

#plt.tight_layout()
fig.subplots_adjust(hspace=0.7)
plt.show()