#include "image.h"

int main(){
    Image green = Image("images/GRN.bmp");
    green.writeImageToFile("GRN.bmp");

    Image yellow = Image(500, 500, 255, 255, 0);
    yellow.writeImageToFile("YEL.bmp");

    Image cyan = Image(500, 500, 0, 255, 255);
    cyan.writeImageToFile("CYA.bmp");

    Image cyan2 = Image(cyan);
    cyan2.writeImageToFile("CYA2.bmp");

    Image empty = Image(500, 500);
    empty.writeImageToFile("EMPTY.bmp");

    Image purple = Image(500, 500, 255, 0, 255);
    purple.writeImageToFile("PRP.bmp");
    return 0;
}
