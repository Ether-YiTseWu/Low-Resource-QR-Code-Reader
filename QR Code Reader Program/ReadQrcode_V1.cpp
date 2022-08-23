#include <iostream>
#include <string>
#include <memory>
#include "ReadBarcode.h"

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
    ImageView img{buffer.get(), width, height, ImageFormat::RGB};
    cout << width << " X " << height << ", Channels : " << channels << endl;

    // Decode (Need to put ImageView Class Object into ReadBarcode)
    DecodeHints hints;
    auto results = ReadBarcodes(img, hints);
    
    // Print
    if (results.empty())
    {
        cout << "There is no QR code in the image!" << endl;
        return 1;
    }
    for (int i = 0 ; i < results.size() ; i++) 
    {
        cout  << "String Format : "  << ToString(results[i].format()) << endl;
        wcout << "QR Code Content : " << results[i].text() << endl;
    }
    
    return 1;
}
