/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2023, Peartree Studios Ltd
 *
 * histogram.cpp - histogram algorithm
 */
#include <stdint.h>

#include <libcamera/base/log.h>

#include "../histogram_status.h"
#include "histogram.h"
#include <linux/bcm2835-isp.h>

using namespace RPiController;
using namespace libcamera;

LOG_DEFINE_CATEGORY(RPiRawHistogram)

#define NAME "rpi.histogram"

Histogram::Histogram(Controller *controller)
	: Algorithm(controller)
{
}

char const *Histogram::name() const
{
	return NAME;
}

void Histogram::process(StatisticsPtr &stats, Metadata *imageMetadata)
{
	Histogram status;
	status.lo[0] = stats->hist[0].r_hist[0];
	status.lo[1] = stats->hist[0].g_hist[0];
	status.lo[2] = stats->hist[0].b_hist[0];

	status.lo[0] = stats->hist[0].r_hist[NUM_HISTOGRAM_BINS - 1];
	status.lo[1] = stats->hist[0].g_hist[NUM_HISTOGRAM_BINS - 1];
	status.lo[2] = stats->hist[0].b_hist[NUM_HISTOGRAM_BINS - 1];

	imageMetadata->set("histogram.status", status);
}

/* Register algorithm with the system. */
static Algorithm *create(Controller *controller)
{
	return new Histogram(controller);
}
static RegisterAlgorithm reg(NAME, &create);