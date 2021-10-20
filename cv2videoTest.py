import numpy as np
import cv2

cap = capture =cv2.VideoCapture('track_video.mp4')
while(cap.isOpened()):
    ret, frame = cap.read()

    if frame is None:
        continue

    resize = cv2.resize(frame, (640, 480))

    # edge detection
    gray = cv2.cvtColor(resize, cv2.COLOR_BGR2GRAY)
        # best edge tracking results with blurring -- exp with threshold
    blurred = cv2.medianBlur(gray,5)
    blurred_contour = blurred = cv2.medianBlur(gray,3)
    G_blurred = cv2.GaussianBlur(gray,(3,3),cv2.BORDER_DEFAULT)
    edges = cv2.Canny(blurred, threshold1=150, threshold2=300, apertureSize=3, L2gradient=False)

    # Preliminary line tracking stuff -- HoughLines --> looks like contour based approach is best
        # https://github.com/tprlab/pitanq-dev/tree/master/selfdrive/follow_line
        # https://const-toporov.medium.com/line-following-robot-with-opencv-and-contour-based-approach-417b90f2c298
    
    # masking test...
    cv2.rectangle(blurred_contour,(0,0),(resize.shape[1], 160),(0,0,0),-1)
    #cv2.rectangle(blurred_contour,(0,0),(200, resize.shape[0]),(0,0,0),-1)
    #cv2.rectangle(blurred_contour,(440,0),(640, resize.shape[0]),(0,0,0),-1)

    edges2 = cv2.Canny(blurred_contour, threshold1=150, threshold2=300, apertureSize=3, L2gradient=False)   

    # contours testing
    ret,thresh = cv2.threshold(edges2,254,300,cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(resize,contours,-1,(255,0,0),5)

    # line detection
    # minLineLength = 100
    # maxLineGap = 10
    # lines = cv2.HoughLinesP(edges2,1,np.pi/180,100,minLineLength,maxLineGap)
    # for x1,y1,x2,y2 in lines[0]:
    #     cv2.line(resize,(x1,y1),(x2,y2),(255,0,0),8)
    
    #cv2.imshow('edges blur', edges)
    #cv2.imshow('blurred_masked', blurred_contour)
    cv2.imshow('contours',resize)
    cv2.imshow('edges', edges2)
    #cv2.imshow('lines', resize)

    # cv2.imshow('medianBlur', grayim)
    # cv2.imshow('frame',resize)
    # cv2.imshow('edges', edges)
    # cv2.imshow('laplacian', laplacian)
    # cv2.imshow('Adaptive Mean Thresholding', th2)
    # cv2.imshow('Adaptive Gaussian Thresholding', th3)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()


# NOTES EDGE DETECTION
# --> dont think we want adaptive thresholding because we want only the whiteist thing on screen to be there --> could be good for 
#       multi track use if big enough sample size in the future.
# laplacian = cv2.Laplacian(gray.copy(),cv2.CV_8U,13)

    # adaptive thresholding -- improving edge detection --> WE MAY NOT WANT ADAPTIVE THRESHOLDING FOR THIS APPLICATION

        # median blur takes sample (kernel) of pixels, finds median, and replaces central pixel with that value
        # Supposedly this is useful for reducing certain types of noise especially salt & pepper noise 
        # in our case it seems to just be reducing resolution but we can play around with it some more
    #grayim = cv2.medianBlur(gray,5)
    # th2 = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_MEAN_C,\
    #             cv2.THRESH_BINARY,201,2)
    # th3 = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,\
    #             cv2.THRESH_BINARY,11,2)

# NOTES LINE DETECTION

# --> doesn't keep lines on screen only small fleeting lines everywhere --> play with params
# minLineLength = 100
    # maxLineGap = 10
    # lines = cv2.HoughLinesP(edges,1,np.pi/180,100,minLineLength,maxLineGap)
    # for x1,y1,x2,y2 in lines[0]:
    #     cv2.line(resize,(x1,y1),(x2,y2),(255,0,0),8)

# --> Gave decently long lines by extrapolating them but still only straight and converge to point quickly
    # lines = cv2.HoughLines(edges,1,np.pi/180,200)
    # if lines is not None:
    #     for line in lines:
    #         rho,theta = line[0]
    #         a = np.cos(theta)
    #         b = np.sin(theta)
    #         x0 = a*rho
    #         y0 = b*rho
    #         x1 = int(x0 + 1000*(-b))
    #         y1 = int(y0 + 1000*(a))
    #         x2 = int(x0 - 1000*(-b))
    #         y2 = int(y0 - 1000*(a))

    #         cv2.line(resize,(x1,y1),(x2,y2),(255,0,0),5)