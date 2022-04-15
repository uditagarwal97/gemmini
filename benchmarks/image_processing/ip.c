// C Program to read a PGMB image
// and print its parameters
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flower_image.h"

// Structure for storing the
// image data
typedef struct PGMImage {
	char pgmType[3];
	unsigned char** data;
	unsigned int width;
	unsigned int height;
	unsigned int maxValue;
} PGMImage;

// Function to ignore any comments
// in file
void ignoreComments(FILE* fp)
{
	int ch;
	char line[100];

	// Ignore any blank lines
	while ((ch = fgetc(fp)) != EOF
		&& isspace(ch))
		;

	// Recursively ignore comments
	// in a PGM image commented lines
	// start with a '#'
	if (ch == '#') {
		fgets(line, sizeof(line), fp);
		ignoreComments(fp);
	}
	else
		fseek(fp, -1, SEEK_CUR);
}

// Function to open the input a PGM
// file and process it
bool openPGM(PGMImage* pgm,
			const char* filename)
{
	// Open the image file in the
	// 'read binary' mode
	FILE* pgmfile
		= fopen(filename, "rb");

	// If file does not exist,
	// then return
	if (pgmfile == NULL) {
		printf("File does not exist\n");
		return false;
	}

	ignoreComments(pgmfile);
	fscanf(pgmfile, "%s",
		pgm->pgmType);

	// Check for correct PGM Binary
	// file type
	if (strcmp(pgm->pgmType, "P5")) {
		fprintf(stderr,
				"Wrong file type!\n");
		exit(EXIT_FAILURE);
	}

	ignoreComments(pgmfile);

	// Read the image dimensions
	fscanf(pgmfile, "%d %d",
		&(pgm->width),
		&(pgm->height));

	ignoreComments(pgmfile);

	// Read maximum gray value
	fscanf(pgmfile, "%d", &(pgm->maxValue));
	ignoreComments(pgmfile);

	// Allocating memory to store
	// img info in defined struct
	pgm->data
		= malloc(pgm->height
				* sizeof(unsigned char*));

	// Storing the pixel info in
	// the struct
	if (pgm->pgmType[1] == '5') {

		fgetc(pgmfile);

		for (int i = 0;
			i < pgm->height; i++) {
			pgm->data[i]
				= malloc(pgm->width
						* sizeof(unsigned char));

			// If memory allocation
			// is failed
			if (pgm->data[i] == NULL) {
				fprintf(stderr,
						"malloc failed\n");
				exit(1);
			}

			// Read the gray values and
			// write on allocated memory
			fread(pgm->data[i],
				sizeof(unsigned char),
				pgm->width, pgmfile);
		}
	}

	// Close the file
	fclose(pgmfile);

	return true;
}

// Function to print the file details
void readPGM(PGMImage* pgm)
{

	printf("Width of img : %d px\n",
		pgm->width);
	printf("Height of img : %d px\n",
		pgm->height);
	printf("Max Gray value : %d\n",
		pgm->maxValue);
	
	for (int i = 0; i < 10; i++)
		printf("%d ", pgm->data[i][0]);
}

// Driver Code
int main(int argc, char const* argv[])
{
	PGMImage* pgm = malloc(sizeof(PGMImage));
	const char* ipfile;

	if (argc == 2)
		ipfile = argv[1];
	else
		ipfile = "gfg_logo.pgm";

	printf("\tip file : %s\n", ipfile);

	// Process the image and print
	// its details
	if (openPGM(pgm, ipfile))
		readPGM(pgm);

	return 0;
}

