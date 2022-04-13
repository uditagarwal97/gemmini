#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void saveImage(unsigned char *img[], int width, int height) {

    FILE *f = fopen("out.ppm", "wb");
    fprintf(f, "P5\n%i %i 255\n", width, height);
    fwrite(img, sizeof(img), 1, f);
    fclose(f);
}

int main(int argc, char *argv[]) {

    char *filename;

    if (argc == 2) {
        filename = argv[1];
    } else {
        printf("Must supply the path to an image file.\n");
    }

    int width, height, channels;

    unsigned char *rgb_image = stbi_load(filename, &width, &height, &channels, 1);
    unsigned char qimage[height][width];

    for(int i=0;i<height;i++)
   {
    for(int j=0;j<width;j++)
     {
       qimage[i][j] = rgb_image[i*height + j];
       printf("%d ", qimage[i][j]);
     }
   }

   FILE *f = fopen("out.ppm", "wb");
   fprintf(f, "P5\n%i %i 255\n", width, height);
   fwrite(qimage, sizeof(qimage), 1, f);
   fclose(f);
   return 0;
}
