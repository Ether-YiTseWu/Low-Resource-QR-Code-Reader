#include <iostream>
#include "qrcode/QRReader.h"
#include "GlobalHistogramBinarizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

using namespace std;

unsigned int width;
unsigned int height;
unsigned char* read_png_file(const char *filename);

int main(void) 
{
    // Read Img
    const char *filePath = "image/qrcode_1.png";
    unsigned char *img = read_png_file(filePath);
    int w = width;
    int h = height;
    
    // Convert
    ZXing::ImageView *imgView = new ZXing::ImageView {img, w, h, ZXing::ImageFormat::RGBX};
    ZXing::GlobalHistogramBinarizer binarizer(*imgView);  // Must use global histogram binarizer (no hybridbinarizer)
    ZXing::BinaryBitmap& bitmap(binarizer);
    
    // Decode (Need to put BinaryBitmap Class Object into Reader)
    ZXing::DecodeHints hints;
    ZXing::QRCode::Reader r(hints);
    
    // Print
    wcout << "QR Code Content : " << r.decode(bitmap).text() << endl;
    
    return 1;
}

unsigned char* read_png_file(const char *filename) 
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

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);
    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);
    if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    int numchan = 4;

    // Set up row pointer
    png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    unsigned int i, j;
    for (i = 0; i < height; i++)
        row_pointers[i] = (png_bytep)malloc(png_get_rowbytes(png,info));
    png_read_image(png, row_pointers);

    // Put row pointers data into image
    unsigned char *image = (unsigned char *) malloc (numchan*width*height);
    int count = 0;
    for (i = 0 ; i < height ; i++)
    {
        for (j = 0 ; j < numchan*width ; j++)
        {
            image[count] = row_pointers[i][j];
            count += 1;
        }
    }
    fclose(fp);
    for (i = 0; i < height; i++)
        free(row_pointers[i]) ;
    free(row_pointers) ;

    return image;     
}
