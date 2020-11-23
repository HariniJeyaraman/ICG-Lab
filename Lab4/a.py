import numpy as np
import cv2
import copy
import matplotlib.pyplot as plt
img = cv2.imread("lena.png")
print(type(img))
rows,cols,channel = img.shape

def displayImage(name, img):
    cv2.imshow('{}'.format(name),img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

f1 = np.zeros((rows,cols))

for i in range(rows):
    for j in range(cols):
        r,g,b=img[i][j]
        f1[i][j]=(0.299*r)+(0.587*g)+(0.114*b)

print(f1[0][0])
cv2.imwrite("f1.png",f1)

def apply_threshold(val):
    if val>=127:
        return 255
    else:
        return 0
# P1=f1
P1=copy.deepcopy(f1)
for i in range(rows):
    for j in range(cols):
        val=f1[i][j]
        P1[i][j] = apply_threshold(val)

displayImage('P1_Binary',P1)
cv2.imwrite("P1Binary.png",P1)

#Floyd Algo
f2=copy.deepcopy(f1)
a=3.0/8
b=2.0/8
c=3.0/8

for i in range(rows):
    for j in range(cols):
        old_pixel = f1[i][j]
        new_pixel = apply_threshold(old_pixel)
        f2[i][j] = new_pixel
        e = old_pixel - new_pixel
        if i!=rows-1 and j!=cols-1:
     	    f1[i+1][j+1] =f1[i+1][j+1] + (b*e)
        if i!=rows-1:
     	    f1[i+1][j] =f1[i+1][j] + (a*e)
        if j!=cols-1:     	
     	    f1[i][j+1] =f1[i][j+1] + (c*e)
cv2.imshow('fig',f2)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.imwrite("FloydBinary.png",f2)

#Calculating Error
sumE1=0.0
sumE2=0.0
totc=0
E1 = [[0 for i in range(cols)] for j in range(rows)]
E2 = [[0 for i in range(cols)] for j in range(rows)]
for i in range(rows):
  for j in range(cols):
  	E1[i][j]=abs(f1[i][j]-P1[i][j])
  	E2[i][j]=abs(f1[i][j]-f2[i][j])
# print(f1)
for i in range(rows):
  for j in range(cols):
  	e1=0.0
  	e2=0.0
  	ct=0
  	for r in range(i-1,i+2):
  		for c in range(j-1 ,j+2):
  			if r<rows and c<cols:
  				e1+=E1[i][j]
  				e2+=E2[i][j]
  				ct=ct+1
  	sumE1+=(e1/ct)
  	E1[i][j]=e1*1.0/ct
  	sumE2+=(e2/ct)
  	E2[i][j]=e2*1.0/ct  	
  	totc=totc+1
print("Error1=")

print(np.array(E1))
cv2.imwrite("error1.png",np.array(E1))

print("Error2=")

print(np.array(E2))
cv2.imwrite("error2.png",np.array(E2))
