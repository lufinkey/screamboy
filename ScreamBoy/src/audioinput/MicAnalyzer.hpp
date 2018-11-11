
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
		
		double getFrequency() const;
		
	private:
		MicInputData* inputData;
	};
}
