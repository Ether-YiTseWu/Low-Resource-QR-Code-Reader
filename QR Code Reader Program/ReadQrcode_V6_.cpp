#include <iostream>
#include "qrcode/QRReader.h"
#include "GlobalHistogramBinarizer.h"
#include <png.h>

using namespace std;

unsigned int width;
unsigned int height;
png_bytep* read_png_file(const char *filename);

int main(void) 
{
    // Read Img
    const char *filePath = "image/qrcode_1_gray.png";
    png_bytep* img2D = read_png_file(filePath);
    unsigned char img1D[width*height];
    int count = 0;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            img1D[count] = img2D[i][j];
            count += 1;
        }
    }
    
    // Convert
    ZXing::ImageView *imgView = new ZXing::ImageView {img1D, (int)width, (int)height, ZXing::ImageFormat::Lum};
    ZXing::GlobalHistogramBinarizer binarizer(*imgView);  // Must use global histogram binarizer (no hybridbinarizer)
    ZXing::BinaryBitmap& bitmap(binarizer);
    
    // Decode (Need to put BinaryBitmap Class Object into Reader)
    ZXing::DecodeHints hints;
    ZXing::QRCode::Reader r(hints);
    
    // Print
    wcout << "QR Code Content : " << r.decode(bitmap).text() << endl;
    
    return 1;
}

png_bytep* read_png_file(const char *filename) 
{
    FILE *fp = fopen(filename, "rb");
    png_byte bit_depth;
    png_byte color_type;
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);

    // Set up row pointer
    png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (unsigned i = 0; i < height; i++)
        row_pointers[i] = (png_bytep)malloc(png_get_rowbytes(png,info));
    png_read_image(png, row_pointers);
    
    // Free memory usage
    for (unsigned i = 0; i < height; i++)
        free(row_pointers[i]);
    png_destroy_read_struct( &png, &info, 0);

    return row_pointers;     
}
