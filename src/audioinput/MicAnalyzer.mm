
#include "MicAnalyzer.hpp"

#if defined(TARGETPLATFORM_IOS) || defined(TARGETPLATFORM_MAC)
#import <AudioKit/AudioKit.h>
#import <AudioKit/AudioKit-Swift.h>

namespace sb {
	bool MicAnalyzer_started = false;
	AKMicrophone* MicAnalyzer_microphone = nil;
	AKFrequencyTracker* MicAnalyzer_tracker = nil;
	
	void MicAnalyzer::start() {
		if(MicAnalyzer_started) {
			return;
		}
		if(MicAnalyzer_microphone == nil) {
			MicAnalyzer_microphone = [[AKMicrophone alloc] init];
		}
		if(MicAnalyzer_tracker == nil) {
			MicAnalyzer_tracker = [[AKFrequencyTracker alloc] init:MicAnalyzer_microphone hopSize:512.0 peakCount:20.0];
		}
		[AudioKit setOutput:[[AKBooster alloc] init:MicAnalyzer_tracker gain:0]];
		NSError* error = nil;
		if(![AudioKit startAndReturnError:&error]) {
			throw Exception(String(error.localizedDescription));
		}
		[MicAnalyzer_microphone start];
		[MicAnalyzer_tracker start];
		MicAnalyzer_started = true;
	}
	
	void MicAnalyzer::stop() {
		if(!MicAnalyzer_started) {
			return;
		}
		[MicAnalyzer_tracker stop];
		[MicAnalyzer_microphone stop];
		NSError* error = nil;
		if(![AudioKit startAndReturnError:&error]) {
			Console::writeError(String(error.localizedDescription));
		}
		[AudioKit setOutput:nil];
		MicAnalyzer_started = false;
	}
	
	double MicAnalyzer::getAmplitude() {
		if(MicAnalyzer_tracker == nil) {
			return 0;
		}
		return MicAnalyzer_tracker.amplitude;
	}
	
	double MicAnalyzer::getFrequency() {
		if(MicAnalyzer_tracker == nil) {
			return 0;
		}
		return MicAnalyzer_tracker.frequency;
	}
	
	double MicAnalyzer::getPitch() {
		static const float LOG2 = Math::log(2.0);
		double frequency = getFrequency();
		return Math::max(0.0, Math::log(frequency / 440.0) / LOG2 * 12.0 + 69.0);
	}
}
#endif
