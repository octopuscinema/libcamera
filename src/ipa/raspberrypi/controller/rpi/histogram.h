#pragma once

#include "../algorithm.h"
#include "../metadata.h"

namespace RPiController 
{
	class Histogram : public Algorithm
	{
	public:
		Histogram(Controller *controller);
		char const *name() const override;
		void process(StatisticsPtr &stats, Metadata *imageMetadata) override;
	};
}