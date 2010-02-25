#include <stdio.h>
#include "engine/EasyBMP/EasyBMP.h"

int main () {
    int i, j;
    BMP test;
    test.SetSize(512, 512);
    test.SetBitDepth(24);

    RGBApixel red, green, blue;

    red.Red = green.Green = blue.Blue = 255;
    red.Alpha = green.Alpha = blue.Alpha = 255;
    red.Blue = red.Green = green.Red = green.Blue = blue.Red = blue.Green = 0;

    for (i = 0; i < 512; i++) {
	for (j = 0; j < 512; j++) {
	    if ((i + j) % 512 < 512 / 3)
		test.SetPixel(i, j, red);
	    else if ((i + j) % 512 < 2 * (512 / 3))
		test.SetPixel(i, j, green);
	    else
		test.SetPixel(i, j, blue);
	}
    }

    test.WriteToFile("test.bmp");

    return 0;
}
