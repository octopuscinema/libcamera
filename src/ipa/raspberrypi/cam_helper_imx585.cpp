/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021, Raspberry Pi Ltd
 *
 * cam_helper_imx585.cpp - camera helper for imx585 sensor
 */

#include <math.h>

#include "cam_helper.h"

using namespace RPiController;

class CamHelperImx585 : public CamHelper
{
public:
	CamHelperImx585();
	uint32_t gainCode(double gain) const override;
	double gain(uint32_t gainCode) const override;
	void getDelays(int &exposureDelay, int &gainDelay,
		       int &vblankDelay, int &hblankDelay) const override;
	unsigned int hideFramesStartup() const override;
	unsigned int hideFramesModeSwitch() const override;

private:
	/*
	 * Smallest difference between the frame length and integration time,
	 * in units of lines.
	 */
	static constexpr int frameIntegrationDiff = 2;
};

CamHelperImx585::CamHelperImx585()
	: CamHelper({}, frameIntegrationDiff)
{
}

uint32_t CamHelperImx585::gainCode(double gain) const
{
	int code = 66.6667 * log10(gain);
	return std::max(0, std::min(code, 0xf0));
}

double CamHelperImx585::gain(uint32_t gainCode) const
{
	return pow(10, 0.015 * gainCode);
}

void CamHelperImx585::getDelays(int &exposureDelay, int &gainDelay,
				int &vblankDelay, int &hblankDelay) const
{
	exposureDelay = 2;
	gainDelay = 2;
	vblankDelay = 2;
	hblankDelay = 2;
}

unsigned int CamHelperImx585::hideFramesStartup() const
{
	/* There's 8 frames that should be ignored after the imx585 resumes from standby. */
	return 8;
}

unsigned int CamHelperImx585::hideFramesModeSwitch() const
{
	/* There's 8 frames that should be ignored after the imx585 resumes from standby. */
	return 8;
}

static CamHelper *create()
{
	return new CamHelperImx585();
}

static RegisterCamHelper reg("imx585", &create);
