#include <iostream>
#include <string>
#include <memory>
#include "qrcode/QRReader.h"
#include "DecodeHints.h"
#include "BinaryBitmap.h"
#include "GlobalHistogramBinarizer.h"
#include "ImageView.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

using namespace ZXing;
using namespace std;

int main(void) 
{
    // Read Img
    int width, height, channels;
    string filePath = "image/qrcode_1.png";
    unique_ptr<stbi_uc, void(*)(void*)> buffer(stbi_load(filePath.c_str(), &width, &height, &channels, 3), stbi_image_free);
    const ImageView& img{buffer.get(), width, height, ImageFormat::RGB};
    GlobalHistogramBinarizer binarizer(img);  // Must use global histogram binarizer (no hybridbinarizer)
    BinaryBitmap& bitmap(binarizer);
    cout << width << " X " << height << ", Channels : " << channels << endl;

    // Decode (Need to put BinaryBitmap Class Object into Reader)
    DecodeHints hints;
    QRCode::Reader r(hints);
    auto result = r.decode(bitmap);
    
    // Print
    wcout << "QR Code Content : " << result.text() << endl;

    return 1;
}
