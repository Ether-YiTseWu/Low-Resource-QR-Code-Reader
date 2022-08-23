import cv2
import os

fileName = "qrcode_1.png"

field  = cv2.imread("./field.png")
qrCode = cv2.imread("./" + fileName)

### Shrink to 
width  = 50 # 縮放後圖片寬度
height = 50 # 縮放後圖片高度
dim = (width, height) # 圖片形狀 
shrink = cv2.resize(qrCode, dim, interpolation = cv2.INTER_AREA) 
cv2.imwrite("qrcode_test.png", shrink)

### Combine
qrCode_test = cv2.imread("./qrcode_test.png")
field[105:105+width, 300:300+height] = qrCode_test 
cv2.imwrite("field_" + fileName, field)

### Call OS system
os.system('./ZXingReader ./field_' + fileName)
