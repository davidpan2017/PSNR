#pragma once
#include "Header.h"
#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class YUVFile
{
public:
	YUVFile(char* cFilename, int iFormat, int iWidth, int iHeight);
	~YUVFile();

	char* filename;

	//Open the file
	void Open() { file =fopen(filename, "rb"); }

	//close the file
	void Close() {
		fclose(file); file = 0;
	}

	//Calculate the frame count of the file. Assume file already opened.
	int getFrameCount();

	int format=0;

	// frame width and height
	int width = 0;
	int height =0;

	YuvFrame      cFrame;
	void readFrame();

private:
	FILE*         file = 0;
	//set factor for UV sampleing
	double fwidth = 0.5;
	double fheight = 0.5;
	void  mem(ColorComponent* cc);
	void  readColorComponent(ColorComponent* cc, FILE* file);
	void  YUVFrame(YuvFrame* f, int width, int height, double fwidth, double fheight);

};

