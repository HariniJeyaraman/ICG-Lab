import cv2
import copy

img = cv2.imread("lena.png")
w, h = img.shape[:2] 
crop_img = img[int(w/4):int(3*w/4), int(h/4):int(3*h/4)].copy()
cv2.imshow("cropped", crop_img)
cv2.waitKey(0)