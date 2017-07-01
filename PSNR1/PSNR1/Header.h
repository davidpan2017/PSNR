#pragma once
typedef struct
{
	int             width;
	int             height;
	unsigned char*  data;
} ColorComponent;

typedef struct
{
	ColorComponent lum;
	ColorComponent cb;
	ColorComponent cr;
} YuvFrame;

#define   OUT "%d,%04d"
