import cv2 
import subprocess

scale_percent = 100
image = cv2.imread("./image/qrcode_3.jpg")
scale_list     = []
content_list = []
error_list   = []
answer_list  = []
while scale_percent != 0:
    # Image Processing
    width  = int(image.shape[1] * scale_percent / 100) # 縮放後圖片寬度
    height = int(image.shape[0] * scale_percent / 100) # 縮放後圖片高度
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
    print("Scale Percent : ", scale_percent)
    scale_percent -= 1

count = 0
error = 0
for i in answer_list:
    if i == 0:
        error += 1
        print(100 - count)
    count += 1
print("Precision : ", (count-error)/count)
