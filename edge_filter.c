#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vemu.h"
#include "energy.h"

/*-------STRUCTURES---------*/
typedef struct {
	int rows;
	int cols;
	unsigned char* data;
} sImage;

/*-------PROTOTYPES---------*/
long getImageInfo(FILE*, long, int);
void copyImageInfo(FILE* inputFile, FILE* outputFile);
void copyColorTable(FILE* inputFile, FILE* outputFile, int nColors);

int main(int argc, char* argv[]) {
	FILE	*bmpInput, *bmpOutput;
	sImage originalImage;
	sImage edgeImage;
	unsigned int X, Y;
	int I, J;
	long sumX, sumY;
	int nColors, SUM;
	unsigned long vectorSize;
	unsigned long fileSize, fileSize2;
	int GX[3][3];
	int GY[3][3];
	unsigned char *pChar, someChar;
	unsigned int row, col;

	someChar = '0'; pChar = &someChar;

	if(argc < 2) {
		printf("Usage: %s bmpInput.bmp\n", argv[0]);
		exit(0);
	};
	printf("Reading filename %s\n", argv[1]);

	/*-------DECLARE INPUT & OUTPUT FILES-------*/
	bmpInput = fopen(argv[1], "rb");
	bmpOutput = fopen("output.bmp", "wb");
	if(bmpOutput == NULL) {
	   printf("opening file failed \n");
	   return;
	}
	/*---SET POINTER TO BEGINNING OF FILE----*/
	fseek(bmpInput, 0L, SEEK_END);

	/*-------GET INPUT BMP DATA--------*/
	fileSize = getImageInfo(bmpInput, 2, 4);
	originalImage.cols = (int)getImageInfo(bmpInput, 18, 4);
	originalImage.rows = (int)getImageInfo(bmpInput, 22, 4);
	edgeImage.rows = originalImage.rows;
	edgeImage.cols = originalImage.cols;

	/*--------PRINT DATA TO SCREEN----------*/
	printf("Width: %d\n", originalImage.cols);
	printf("Height: %d\n", originalImage.rows);
	printf("File size: %lu\n", fileSize);

	nColors = (int)getImageInfo(bmpInput, 46, 4);
	printf("nColors: %d\n", nColors);

	/*------ALLOCATE MEMORY FOR FILES--------*/
	vectorSize = fileSize - (14+40+4*nColors);
	printf("vectorSize: %lu\n", vectorSize);
	// edgeImage.data = farmalloc(vectorSize*sizeof(unsigned char));
	edgeImage.data = (unsigned char*) malloc(vectorSize*sizeof(unsigned char));
	if(edgeImage.data == NULL) {
		printf("Failed to malloc edgeImage.data\n");
		exit(0);
	}
	printf("%lu bytes malloc'ed for edgeImage.data\n", vectorSize);

	// originalImage.data = farmalloc(vectorSize*sizeof(unsigned char));
	originalImage.data = (unsigned char*) malloc(vectorSize*sizeof(unsigned char));
	if(originalImage.data == NULL) {
		printf("Failed to malloc originalImage.data\n");
		exit(0);
	}
	printf("%lu bytes malloc'ed for originalImage.data\n", vectorSize);

	/*------COPY HEADER AND COLOR TABLE---------*/
	copyImageInfo(bmpInput, bmpOutput);

	copyColorTable(bmpInput, bmpOutput, nColors);

	fseek(bmpInput, (14+40+4*nColors), SEEK_SET);

	fseek(bmpOutput, (14+40+4*nColors), SEEK_SET);

	/* Read input.bmp and store it's raster data into originalImage.data */
	for(row=0; row<=originalImage.rows-1; row++) {
		for(col=0; col<=originalImage.cols-1; col++) {
			fread(pChar, sizeof(char), 1, bmpInput);
			*(originalImage.data + row*originalImage.cols + col) = *pChar;
		}
	}

	/** Start profiling cycle & energy using VarEMU **/
	statistics st;
	start_cycle();
	/*****************************************/

	/*---------------------------------------------------
	  YOUR EDGE DETECTION ALGORITHM STARTS HERE
	---------------------------------------------------*/
	  
	
	/*---------------------------------------------------
	  YOUR EDGE DETECTION ALGORITHM ENDS HERE
	---------------------------------------------------*/

	/** Stop profiling cycle & energy using VarEMU,
		and print out the results. **/
    end_cycle();

    st = get_energy();
    printf("%lld\t%lld\t%lld\n",st.delta_cycles, st.delta_dyn, st.delta_slp);
    /*****************************************/

	printf("See output.bmp for results\n");
	fclose(bmpInput);
	fclose(bmpOutput);
	// farfree(edgeImage.data);			/* Finished with edgeImage.data */
	// farfree(originalImage.data);	/* Finished with originalImage.data */
	free(edgeImage.data);			/* Finished with edgeImage.data */
	free(originalImage.data);	/* Finished with originalImage.data */
	return 0;
}

/*----------GET IMAGE INFO SUBPROGRAM--------------*/
long getImageInfo(FILE* inputFile, long offset, int numberOfChars) {
	unsigned char *ptrC;
	long value = 0L;
	unsigned char dummy;
	int	i;

	dummy = '0';
	ptrC = &dummy;

	fseek(inputFile, offset, SEEK_SET);

	for(i=1; i<=numberOfChars; i++) {
		fread(ptrC, sizeof(char), 1, inputFile);
		/* calculate value based on adding bytes */
		value = (long)(value + (*ptrC)*(pow(256, (i-1))));
	}

	return(value);
} /* end of getImageInfo */

/*-------------COPIES HEADER AND INFO HEADER----------------*/
void copyImageInfo(FILE* inputFile, FILE* outputFile) {
	unsigned char *ptrC;
	unsigned char dummy;
	int	i;

	dummy = '0';
	ptrC = &dummy;

	fseek(inputFile, 0L, SEEK_SET);

	fseek(outputFile, 0L, SEEK_SET);

	for(i=0; i<=50; i++) {
		fread(ptrC, sizeof(char), 1, inputFile);
		fwrite(ptrC, sizeof(char), 1, outputFile);
	}
}

/*----------------COPIES COLOR TABLE-----------------------------*/
void copyColorTable(FILE* inputFile, FILE* outputFile, int numColors) {
	unsigned char *ptrC;
	unsigned char dummy;
	int i;

	dummy = '0';
	ptrC = &dummy;

	fseek(inputFile, 54L, SEEK_SET);
	fseek(outputFile, 54L, SEEK_SET);

	/* there are (4*nColors) bytesin color table */
	for(i = 0; i <= (4*numColors); i++) {
		fread(ptrC, sizeof(char), 1, inputFile); 
		fwrite(ptrC, sizeof(char), 1, outputFile);
	}
}
