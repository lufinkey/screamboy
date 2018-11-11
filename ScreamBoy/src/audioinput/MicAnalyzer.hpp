
#pragma once

#include "import/GameLibrary.hpp"

namespace sb {
	struct MicInputData;
	
	class MicAnalyzer {
	public:
		MicAnalyzer(const MicAnalyzer&) = delete;
		MicAnalyzer();
		virtual ~MicAnalyzer();
		
		void start();
		void stop();
		
		double getFrequency() const;
		
	private:
		MicInputData* inputData;
		bool started;
	};
}
