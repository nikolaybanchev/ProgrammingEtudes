#include <iostream>
#include <math.h>
#include <cstdio>
#include "bitmap.h"

using namespace std;

int main()
{
    const int imageWidth = 800, imageHeight = 600;

    const int animationLength = 15;

    for(int frameN = 0;frameN < animationLength;frameN++){
        cout << "Processing frame " << frameN << " of " << animationLength<<endl;

        //**************Generating single image ***************************************
        Bitmap bitmap(imageWidth, imageHeight);
        const int centerX = imageWidth / 2, centerY = imageHeight / 2;
        
        //drawing on every pixel with nested for cycles
        for(int x = 0; x < imageWidth; x++){
            for(int y = 0; y < imageHeight; y++ ) {
                //polar coord system args
                double phi = atan2(x - centerX, y - centerY);
                double R = hypot(x - centerX, y - centerY);

                //calculate polar sine curve
                double curveRadius = sin(phi*frameN)*127+128;
                double curveX = centerX + sin(phi)*curveRadius;
                double curveY = centerY + cos(phi)*curveRadius;

                int distanceFromCurve = hypot(curveX - x, curveY - y);

                //calculate gradient based on distance from curve
                int blue = distanceFromCurve * 2, red = distanceFromCurve * 2 - 255;
                if(blue > 255) blue = 255;
                if(red < 0) red = 0;

                if(R < curveRadius)bitmap.setPixel(x, y, red, 0,blue);
                else bitmap.setPixel(x, y, 0,0,0);
            }
        }
        //drawing curve only
        double delta = 0.0001;
        for(double alpha=-3.1415;alpha < 3.1415; alpha += delta){

            double radius = sin(alpha*frameN)*127+128;
            double x = centerX + sin(alpha)*radius;
            double y = centerY + cos(alpha)*radius;

            bitmap.setPixel(x,y,128,128,128);

        }
        //************** End image generation  ***************************************

        char fileName[100]; //allocate buffer for string Plain C-style, I am unfamiliar with C++ string sorry :)
        sprintf(fileName,"%04d.bmp",frameN); // %04d is substituted with frameN in number format 0000, 0001, 0002 ....
        bitmap.save(fileName);

    }

    return 0;
}

