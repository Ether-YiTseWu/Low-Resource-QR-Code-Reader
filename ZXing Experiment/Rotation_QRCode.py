import cv2 
import imutils
import subprocess

deg = 0
fileName = "./qrcode_3.jpg"
image = cv2.imread(fileName)
deg_list     = []
content_list = []
error_list   = []
answer_list  = []
while deg != 360:
    # Image Processing
    rotated = imutils.rotate_bound(image, deg)
    cv2.imwrite("qrcode_test.png", rotated)
    # Get std output
    result = subprocess.run(['./ZXingReader', './qrcode_test.png'], stdout = subprocess.PIPE)
    result_string = result.stdout.decode('utf-8')
    # Parse
    result_string = result_string.split()
    try:
        if result_string[15] != "NoError":
            answer_list.append(0)
        else:
            answer_list.append(1)
    except:
        answer_list.append(0)
    print("Degree : ", deg)
    deg += 1

count = 0
error = 0
for i in answer_list:
    if i == 0:
        error += 1
        print(count)
    count += 1
print("Precision : ", (count-error)/count)
