
#pragma once

#include "import/GameLibrary.hpp"

namespace sb {
	class MicAnalyzer {
	public:
		static void start();
		static void stop();
		
		static double getAmplitude();
		static double getFrequency();
		static double getPitch();
	};
}
