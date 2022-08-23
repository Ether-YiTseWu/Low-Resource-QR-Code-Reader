#include <iostream>
#include "qrcode/QRReader.h"
#include "GlobalHistogramBinarizer.h"
#include <png.h>

using namespace std;

int main(void) 
{
    // Read Img
    unsigned int width;
    unsigned int height;
    const char *filePath = "image/qrcode_1_gray.png";
    
    // Open File and read it (get two variables, png and info)
    FILE *fp = fopen(filePath, "rb");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
                
    // Set up img1D
    unsigned char *img1D = (unsigned char*)malloc(sizeof(unsigned char) * height * width);
    int count = 0;
    for (unsigned i = 0; i < height; i++)
    {
        png_bytep row_data = (png_bytep)png_malloc(png, png_get_rowbytes(png, info));
        png_read_rows(png, (png_bytepp)&row_data, NULL, 1);
        for (unsigned j = 0 ; j < png_get_rowbytes(png, info) ; j++)
        {
            img1D[count] = row_data[j];
            count += 1;
        }
        free(row_data);
    }
    
    // Free
    png_destroy_read_struct(&png, &info, 0);
    
    // Convert
    ZXing::ImageView *imgView = new ZXing::ImageView {img1D, (int)width, (int)height, ZXing::ImageFormat::Lum};
    ZXing::GlobalHistogramBinarizer binarizer(*imgView);  // Must use global histogram binarizer (no hybridbinarizer)
    ZXing::BinaryBitmap& bitmap(binarizer);
    
    // Free
    free(img1D);
    
    // Decode (Need to put BinaryBitmap Class Object into Reader)
    ZXing::DecodeHints hints;
    ZXing::QRCode::Reader r(hints);
    
    // Print
    wcout << "QR Code Content : " << r.decode(bitmap).text() << endl;
    
    return 1;
}
