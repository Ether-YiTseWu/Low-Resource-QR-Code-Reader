# Low-Resource-QR-Code-Reader         
              
## Overview
Topic : QR Code Reader Optimization for Low Resource Embedded System              
                    
Purpose : The purpose of the project is to develop a QR code reader with low memory usage and short execution time for a AR glass based on a low resource embedded system. The AR glass make people examine the decode result of a QR code.        
               
## Program Version Comparison
The program is run on Raspberry 4 2GB, and the memory usage is estimated by Valgrind        
              
![Program Comparison](https://github.com/Steven-YiTseWu/Low-Resource-QR-Code-Reader/blob/main/Report/Program_Comparison.png)
               
## Environment Requirement
- zxing-cpp : [nu-book/zxing-cpp](https://github.com/nu-book/zxing-cpp)
- libpng : [glennrp/libpng](https://github.com/glennrp/libpng)
- Valgrind : [Valgrind Home](https://valgrind.org/)
- stb : [nothings/stb](https://github.com/nothings/stb)
- lodepng : [lvandeve/lodepng](https://github.com/lvandeve/lodepng)
- CImg : [GreycLab/CImg](https://github.com/GreycLab/CImg)

**Tips : Use pkg-config tool to compile programs**

## Some Useful Website Links
- [A simple libpng example program](http://zarb.org/~gc/html/libpng.html)
- [pkg-config Tool](https://www.cntofu.com/book/46/linux_system/ru_he_shi_yongpkg_-_config_gong_ju_bian_yi_lian_ji.md)
- [png_read_info and png_read_image](https://www.twblogs.net/a/5e4e99c8bd9eee101e830ae6)
