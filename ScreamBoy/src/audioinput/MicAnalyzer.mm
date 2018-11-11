
#include "MicAnalyzer.hpp"
#import <AudioKit/AudioKit.h>
#import <AudioKit/AudioKit-Swift.h>

namespace sb {
#if defined(TARGETPLATFORM_IOS) || defined(TARGETPLATFORM_MAC)
	struct MicInputData {
		MicInputData() {
			microphone = [[AKMicrophone alloc] init];
			frequencyTracker = [[AKFrequencyTracker alloc] init:microphone hopSize:512.0 peakCount:20.0];
		}
		
		AKMicrophone* microphone;
		AKFrequencyTracker* frequencyTracker;
	};
	
	MicAnalyzer::MicAnalyzer()
		: inputData(new MicInputData()) {
		//
	}
	
	MicAnalyzer::~MicAnalyzer() {
		delete inputData;
	}
	
	void MicAnalyzer::start() {
		NSError* error = nil;
		if(![AudioKit startAndReturnError:&error]) {
			throw Exception(String(error.localizedDescription));
		}
		[inputData->microphone start];
		[inputData->frequencyTracker start];
	}
	
	double MicAnalyzer::getFrequency() const {
		return inputData->frequencyTracker.frequency;
	}
	
#endif
}
