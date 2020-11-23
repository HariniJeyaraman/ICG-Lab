import numpy as np
import cv2
import copy
from matplotlib import pyplot as plt

img = cv2.imread("inputimg.png")
# plt.imshow(img)
# plt.show()
(height, width) = img.shape[:2] 

#scaling
res = cv2.resize(img, (int(width*2), int(height*2)))
cv2.imwrite('scaled_img.jpg', res) 


(rows, cols) = img.shape[:2] 
# getRotationMatrix2D creates a matrix needed for transformation. 
# We want matrix for rotation w.r.t center to 45 degree without scaling. 
M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 15, 1) 
res = cv2.warpAffine(img, M, (cols, rows))
cv2.imwrite('rotated_img.jpg', res) 

# img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# center = (img.shape[1]//2, img.shape[0] //2) # Get the image center
# rotation_matrix = cv2.getRotationMatrix2D(center, -45, 1) # Calculate the rotation matrix
# new_img = cv2.warpAffine(img, rotation_matrix, (img.shape[1], img.shape[0])) # Transform input image
# cv2.imwrite('rotated_new.jpg', new_img) 

M = np.float32([[1, 0, 10], [0, 1, 20]]) 
res2 = cv2.warpAffine(img, M, (cols, rows)) 
cv2.imwrite('translated.jpg', res2) 


# new=copy.deepcopy(img)
# # for i in range(int(height)):
# #     for j in range(int(width)):
# #         new[2*i][2*j]=img[i][j]
# cv2.imwrite('scaled_custom.jpg', new) 
