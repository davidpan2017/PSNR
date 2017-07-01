#include "YUVpsnr.h"


YUVpsnr::YUVpsnr(YUVFile* file1, YUVFile* file2)
{
	org_file = file1;
	rec_file = file2;
}


YUVpsnr::~YUVpsnr()
{
}

//Open the two files and return the smallest frames
int YUVpsnr::GetFrameCount()
{
	int nOrgFrame = org_file->getFrameCount();
	int nRecFrame = rec_file->getFrameCount();
	if (nOrgFrame < nRecFrame)
		frames = nOrgFrame;
	else
	{
		frames = nRecFrame;
	}

	return frames;
}


void YUVpsnr::CalculateNextFrame()
{
	currentFrame++;

	org_file->readFrame();
	rec_file->readFrame();

	getPSNR(psnrY, psnrU, psnrV, org_file->cFrame, rec_file->cFrame);
	AveragePSNR_Y += psnrY;
	AveragePSNR_U += psnrU;
	AveragePSNR_V += psnrV;

	py = (int)floor(acc * psnrY + 0.5);
	pu = (int)floor(acc * psnrU + 0.5);
	pv = (int)floor(acc * psnrV + 0.5);

	return;
}

void YUVpsnr::CalculateAverage()
{
	py = (int)floor(acc * AveragePSNR_Y / (double)frames + 0.5);
	pu = (int)floor(acc * AveragePSNR_U / (double)frames + 0.5);
	pv = (int)floor(acc * AveragePSNR_V / (double)frames + 0.5);
}


double YUVpsnr::psnr(ColorComponent& rec, ColorComponent& org)
{
	unsigned char*  pOrg = org.data;
	unsigned char*  pRec = rec.data;
	double          ssd = 0;
	int             diff;

	for (int r = 0; r < rec.height; r++)
	{
		for (int c = 0; c < rec.width; c++)
		{
			diff = pRec[c] - pOrg[c];
			ssd += (double)(diff * diff);
		}
		pRec += rec.width;
		pOrg += org.width;
	}

	if (ssd == 0.0)
	{
		return 99.99;
	}
	return (10.0 * log10((double)rec.width * (double)rec.height * 65025.0 / ssd));
}

void YUVpsnr::getPSNR(double& psnrY, double& psnrU, double& psnrV, YuvFrame& rcFrameOrg, YuvFrame& rcFrameRec)
{
	psnrY = psnr(rcFrameRec.lum, rcFrameOrg.lum);
	psnrU = psnr(rcFrameRec.cb, rcFrameOrg.cb);
	psnrV = psnr(rcFrameRec.cr, rcFrameOrg.cr);
}
