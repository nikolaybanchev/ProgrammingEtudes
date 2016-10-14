#include <iostream>
#include <math.h>

#include "bitmap.h"

using namespace std;


int mandelbrotAtPoint(double u, double v){
    double re = u;
    double im = v;
    double tempRe;
    for(int i=0; i < 1000; i++){
        tempRe = re*re - im*im + u;
        im = re * im * 2 + v;
        re = tempRe;
        double d2 = re*re + im*im;
        if( d2 > 2 ) return i;
    }
    return 0;
}

int main()
{
    const int imageWidth = 1280, imageHeight = 1024;

    Bitmap bitmap(imageWidth, imageHeight);

    //interesting values at http://www.nahee.com/Derbyshire/manguide.html
    double plotWidth = 0.0005;
    double plotHeight = plotWidth * imageHeight / imageWidth;
    double plotOriginX = 0.273 - plotWidth/2.;
    double plotOriginY = 0.0058 - plotHeight/2.;

    for(int x = 0; x < imageWidth; x++){
        for(int y = 0; y < imageHeight; y++ ) {
            double plotX = plotOriginX + plotWidth  * x / imageWidth;
            double plotY = plotOriginY + plotHeight * y / imageHeight;

            int p = mandelbrotAtPoint(plotX, plotY) + 25;
            if( p>255 ) p = 255;
            if( p<100 ) p = 0;
            bitmap.setPixel(x,y,0,p,0);
        }
    }

    bitmap.save("testpic.bmp");
    return 0;
}

