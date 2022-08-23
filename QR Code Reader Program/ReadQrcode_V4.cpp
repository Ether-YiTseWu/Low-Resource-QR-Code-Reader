#include <iostream>
#include "qrcode/QRReader.h"
#include "GlobalHistogramBinarizer.h"

#include "lodepng/lodepng.h"
using namespace std;

int main(void) 
{
    // Read Img
    unsigned int *width = new unsigned int[1], *height = new unsigned int[1], *channels = new unsigned int[1];
    const char *filePath = new char[18];
    filePath = "image/qrcode_1.png";
    vector<unsigned char> imgVector; //the raw pixels
    unsigned flag = lodepng::decode(imgVector, *width, *height, filePath);
    unsigned char *imgChar = new unsigned char[imgVector.size()];
    
    // Convert
    int w = *width, h = *height;
    for (int i = 0; i < imgVector.size(); i++)
        imgChar[i] = imgVector[i];
    ZXing::ImageView *imgView = new ZXing::ImageView {imgChar, w, h, ZXing::ImageFormat::RGBX};
    ZXing::GlobalHistogramBinarizer binarizer(*imgView);  // Must use global histogram binarizer (no hybridbinarizer)
    ZXing::BinaryBitmap& bitmap(binarizer);
    
    // Delete
    delete [] width, height, channels, filePath, imgChar, imgView;
    
    // Decode (Need to put BinaryBitmap Class Object into Reader)
    ZXing::DecodeHints hints;
    ZXing::QRCode::Reader r(hints);
    
    // Print
    wcout << "QR Code Content : " << r.decode(bitmap).text() << endl;
    
    return 1;
}
