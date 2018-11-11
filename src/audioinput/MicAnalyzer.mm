
#include "MicAnalyzer.hpp"

#if defined(TARGETPLATFORM_IOS) || defined(TARGETPLATFORM_MAC)
#import <AudioKit/AudioKit.h>
#import <AudioKit/AudioKit-Swift.h>

namespace sb {
	struct MicInputData {
		MicInputData() {
			microphone = [[AKMicrophone alloc] init];
			frequencyTracker = [[AKFrequencyTracker alloc] init:microphone hopSize:512.0 peakCount:20.0];
		}
		
		AKMicrophone* microphone;
		AKFrequencyTracker* frequencyTracker;
	};
	
	MicAnalyzer::MicAnalyzer()
		: inputData(new MicInputData()),
		started(false) {
		//
	}
	
	MicAnalyzer::~MicAnalyzer() {
		if(started) {
			stop();
		}
		delete inputData;
	}
	
	void MicAnalyzer::start() {
		NSError* error = nil;
		if(![AudioKit startAndReturnError:&error]) {
			throw Exception(String(error.localizedDescription));
		}
		[inputData->microphone start];
		[inputData->frequencyTracker start];
		started = true;
	}
	
	void MicAnalyzer::stop() {
		[inputData->frequencyTracker stop];
		[inputData->microphone stop];
		NSError* error = nil;
		if(![AudioKit stopAndReturnError:&error]) {
			Console::writeError(String(error.localizedDescription));
		}
		started = false;
	}
	
	double MicAnalyzer::getFrequency() const {
		return inputData->frequencyTracker.frequency;
	}
}
#endif
