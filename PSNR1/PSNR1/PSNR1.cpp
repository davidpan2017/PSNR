// PSNR1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "YUVFile.h"
#include "YUVpsnr.h"
#include <ctime>
#include <cstdio>

//Output format error
void FormatError()
{
	puts("Arguments required: filename1 filename2 width height format");
	puts("Format can be: 444 or 422 or 420");
	getchar();
}

/*

*/
int main(int argc, char *argv[])
{

	// Ensure argument was okay.
	if (argc != 6) {
		FormatError();
		return 1;
	}


	char *pCh;
	// Convert to ulong WITH CHECKING!
	unsigned int  width = 0;
	unsigned int  height = 0;
	unsigned int  format = 0;
	char* filename1 = argv[1];
	char* filename2 = argv[2];
	width = strtoul(argv[3], &pCh, 10);
	height = strtoul(argv[4], &pCh, 10);
	format = strtoul(argv[5], &pCh, 10);
	if (format != 444 && format != 422 && format != 420)
	{
		FormatError();
		return 1;
	}

	std::clock_t start;
	double duration;

	start = std::clock();

	YUVFile* file1 = new YUVFile(filename1, format, width, height);
	YUVFile* file2 = new YUVFile(filename2, format, width, height);
	YUVpsnr* calculator = new YUVpsnr(file1, file2);
	calculator->OpenFiles();
	int nFrames = calculator->GetFrameCount();
	for (int i = 0; i < nFrames; i++)
	{
		calculator->CalculateNextFrame();
	}

	calculator->CalculateAverage();

	calculator->CloseFiles();
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	double dSequencePSNR = (calculator->py + calculator->pu + calculator->pv) / 3.0 / calculator->acc;
	int nFramePerSec = (int) ( (double)nFrames / duration);

	fprintf(stdout, "Sequence level PSNR score:  %10.2f \nProcessing speed: \t\t %d  frames/sec\n", dSequencePSNR, nFramePerSec);


	delete file1;
	delete file2;
	delete calculator;

	return 0;
}


