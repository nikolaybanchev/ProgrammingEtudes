#ifndef BITMAP
#define BITMAP

#include <iostream>
#include <fstream>

class Bitmap {
private:
    unsigned char* _pixels;
    int _width;
    int _height;
    int _sizeData;
    int _padSize;

public:

    Bitmap(int width, int height):
        _width(width),_height(height){

        _padSize  = (4-(width*3)%4)%4;
        _sizeData = _width*_height*3 + _height*_padSize;
        _pixels   = new unsigned char[_sizeData];
    }

    void setPixel(int x, int y,
                  unsigned char red,
                  unsigned char green,
                  unsigned char blue){
        int pixelAddr = (y*_width + x)*3 + y* _padSize;
        _pixels[pixelAddr] = blue;
        _pixels[pixelAddr+1] = green;
        _pixels[pixelAddr+2] = red;
    }

    void save(char * fileName){

        unsigned char file[14] = {
            'B','M', // magic
            0,0,0,0, // size in bytes
            0,0, // ignored
            0,0, // ignored
            40+14,0,0,0 // start of data offset
        };
        unsigned char info[40] = {
            40,0,0,0, // info hd size
            (unsigned char)(_width) ,    // width least significant
            (unsigned char)(_width >>8), // width
            (unsigned char)(_width >>16),// width
            (unsigned char)(_width >>24),// width most significant
            (unsigned char)(_height),     // heigth least significant
            (unsigned char)(_height>>8),  // heigth
            (unsigned char)(_height>>16), // heigth
            (unsigned char)(_height>>24), // heigth most significant
            1,0, // number color planes
            24,0, // bits per pixel
            0,0,0,0, // compression is none
            (unsigned char)(_sizeData),
            (unsigned char)(_sizeData>> 8),
            (unsigned char)(_sizeData>>16),
            (unsigned char)(_sizeData>>24), // image bits size
            0x13,0x0B,0,0, // horz resoluition in pixel / m
            0x13,0x0B,0,0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
            0,0,0,0, // ignored
            0,0,0,0, // ignored
            };

        int sizeAll  = _sizeData + sizeof(file) + sizeof(info);

        file[2] = (unsigned char)(sizeAll);
        file[3] = (unsigned char)(sizeAll>> 8);
        file[4] = (unsigned char)(sizeAll>>16);
        file[5] = (unsigned char)(sizeAll>>24);


        std::ofstream stream(fileName,std::ofstream::binary);

        stream.write( (char*)file, sizeof(file) );
        stream.write( (char*)info, sizeof(info) );
        stream.write( (char*)_pixels,_sizeData );

        stream.close();
    }

    ~Bitmap(){
        delete _pixels;
    }

};

#endif // BITMAP

