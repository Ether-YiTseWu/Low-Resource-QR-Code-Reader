#include <iostream>
#include "qrcode/QRReader.h"
#include "GlobalHistogramBinarizer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int main(void) 
{
    // Read Img
    int *width = new int[1], *height = new int[1], *channels = new int[1];
    const char *filePath = new char[18];
    filePath = "image/qrcode_1_gray.png";
    const ZXing::ImageView& img{stbi_load(filePath, width, height, channels, 0), *width, *height, ZXing::ImageFormat::Lum};
    ZXing::GlobalHistogramBinarizer binarizer(img);  // Must use global histogram binarizer (no hybridbinarizer)
    ZXing::BinaryBitmap& bitmap(binarizer);

    // Decode (Need to put BinaryBitmap Class Object into Reader)
    ZXing::DecodeHints hints;
    ZXing::QRCode::Reader r(hints);
    
    // Print
    std::wcout << "QR Code Content : " << r.decode(bitmap).text() << std::endl;
    delete [] width, height, channels, filePath;

    return 1;
}
