#include <iostream>
#include <math.h>

#include "bitmap.h"

using namespace std;

int main()
{
    const int imageWidth = 800, imageHeight = 600;

    Bitmap bitmap(imageWidth, imageHeight);

    const int R = 255;
    const int centerX = imageWidth/2, centerY = imageHeight / 2;

    for(int x = 0; x < imageWidth; x++){
        for(int y = 0; y < imageHeight; y++ ) {
            int distance = sqrt((x-centerX) * (x-centerX) + (y-centerY) * (y-centerY));

            if(distance<R) bitmap.setPixel(x,y,0,distance,255-distance);
            else bitmap.setPixel(x,y,0,0,0);
        }
    }

    bitmap.save("circle.bmp");
    return 0;
}

