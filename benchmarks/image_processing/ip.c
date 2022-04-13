#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char *argv[]) {

    char *filename;

    if (argc == 2) {
        filename = argv[1];
    } else {
        printf("Must supply the path to an image file.\n");
    }

    int width, height, channels;

    float *rgb_image = stbi_loadf(filename, &width, &height, &channels, 1);

    for(int i=0;i<height;i++)
   {
    for(int j=0;j<width;j++)
     {
       printf("%f", rgb_image[i*height + j]);
     }
   }

   return 0;
}
