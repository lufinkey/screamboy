
#pragma once

#include "import/GameLibrary.hpp"

namespace sb {
	struct MicPrivateData;
	
	class MicAnalyzer {
		friend struct MicPrivateData;
	public:
		MicAnalyzer(const MicAnalyzer&) = delete;
		MicAnalyzer();
		virtual ~MicAnalyzer();
		
		void start(int index);
		void stop();
		
		double getPitch() const;
		double getAmplitude() const;
		
	private:
		MicPrivateData* privateData;
	};
}
