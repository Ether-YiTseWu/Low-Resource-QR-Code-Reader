#include <iostream>
#include "qrcode/QRReader.h"
#include "GlobalHistogramBinarizer.h"

#include "CImg/CImg.h"
using namespace std;
using namespace cimg_library;

int main(void) 
{
    // Read Img
    CImg<unsigned char> img_raw("image/qrcode_1.png");
    int w = img_raw.width();
    int h = img_raw.height();
    
    // Convert
    ZXing::ImageView *imgView = new ZXing::ImageView {img_raw.data(), w, h, ZXing::ImageFormat::RGBX};
    ZXing::GlobalHistogramBinarizer binarizer(*imgView);  // Must use global histogram binarizer (no hybridbinarizer)
    ZXing::BinaryBitmap& bitmap(binarizer);
    
    // Decode (Need to put BinaryBitmap Class Object into Reader)
    ZXing::DecodeHints hints;
    ZXing::QRCode::Reader r(hints);
    
    // Print
    wcout << "QR Code Content : " << r.decode(bitmap).text() << endl;
    
    return 1;
}
