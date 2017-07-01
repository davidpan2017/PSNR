#pragma once
#include "YUVFile.h"

/*
Calculate the PSNR for two YUV file
*/
class YUVpsnr
{
public:
	YUVpsnr(YUVFile* file1, YUVFile* file2);
	~YUVpsnr();

	YUVFile* org_file = 0;
	YUVFile* rec_file = 0;

	double	AveragePSNR_Y = 0.0;
	double	AveragePSNR_U = 0.0;
	double	AveragePSNR_V = 0.0;

	double	psnrY, psnrU, psnrV;
	int		acc = 10000;
	int		py, pu, pv;
	int		frames;



	int		currentFrame = 0;

	void OpenFiles() { org_file->Open(); rec_file->Open();
	};

	void CloseFiles() {
		org_file->Close(); rec_file->Close();
	};

	//Calculate how many frames can be calculated
	int GetFrameCount();

	//Calculate the psnr for each channel for next frame
	void CalculateNextFrame();
	void CalculateAverage();

private:
	double psnr(ColorComponent& rec, ColorComponent& org);
	void getPSNR(double& psnrY, double& psnrU, double& psnrV, YuvFrame& rcFrameOrg, YuvFrame& rcFrameRec);

};

