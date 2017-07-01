#include "YUVFile.h"


/*
YUV file constructor. Need to have filename, format, width, height information
*/
YUVFile::YUVFile(char* cFilename, int iFormat, int iWidth, int iHeight)
{
	filename = cFilename;
	width = iWidth;
	height = iHeight;

	format = iFormat;
	//set factor for UV sampleing
	switch (format)
	{
	case 444:
		fwidth = 1.0;
		fheight = 1.0;
		break;
	case 422:
		fwidth = 0.5;
		fheight = 1.0;
		break;
	case 420:
		fwidth = 0.5;
		fheight = 0.5;
		break;
	case 400:
		fwidth = 0.0;
		fheight = 0.0;
		break;
	default:
		break;
	}

	YUVFrame(&cFrame, width, height, fwidth, fheight);

	return;
}


YUVFile::~YUVFile()
{
}



int YUVFile::getFrameCount()
{
	fseek(file, 0, SEEK_END);
	size_t fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	int sizePerFrame = (int)((double)width*(double)height * (1.0 + fwidth*fheight*2.0));
	double dFrames = (double)fsize / (double)(sizePerFrame);
	int frames = (int)dFrames;
	return frames;
}



void  YUVFile::mem(ColorComponent* cc)
{
	if (!(cc->data = new unsigned char[cc->width * cc->height]))
	{
		fprintf(stderr, "\nERROR: memory allocation failed!\n\n");
		exit(-1);
	}
}

/*
* Allocate memory for YUV frame
* fwidth, fheight are factores for size of UV channel
* for YUV 4:4:4 fwidth = fheight = 1
* for YUV 4:2:2 fwidth = 0.5 fheight = 1.0
* for YUV 4:2:0 fwidth = 0.5, fheight = 0.5
*/
void  YUVFile::YUVFrame(YuvFrame* f, int width, int height, double fwidth, double fheight)
{
	f->lum.width = width;
	f->lum.height = height;
	mem(&f->lum);

	f->cb.width = (int)((double)width * fwidth);
	f->cb.height = (int)((double)height * fheight);
	mem(&f->cb);

	f->cr.width = f->cb.width;
	f->cr.height = f->cb.height;
	mem(&f->cr);
}

void  YUVFile::readColorComponent(ColorComponent* cc, FILE* file)
{
	unsigned int size = cc->width*cc->height;
	unsigned int rsize;

	rsize = fread(cc->data, sizeof(unsigned char), size, file);
}

void YUVFile::readFrame()
{
	readColorComponent(&cFrame.lum, file);
	readColorComponent(&cFrame.cb, file);
	readColorComponent(&cFrame.cr, file);
}

