import cv2 
import subprocess

scale_percent = 100
image = cv2.imread("./7_M.png")
width  = image.shape[1]
height = image.shape[0]
answer_list  = []
while width != 1:
    # Image Processing
    width -= 1
    height -= 1
    dim = (width, height) # 圖片形狀 
    shrink = cv2.resize(image, dim, interpolation = cv2.INTER_AREA) 
    cv2.imwrite("qrcode_test.png", shrink)
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

count = 1
error = 0
width  = image.shape[1]
height = image.shape[0]
for i in answer_list:
    if i == 0:
        error += 1
        print(width - count, "*", height - count, " Error")
    count += 1