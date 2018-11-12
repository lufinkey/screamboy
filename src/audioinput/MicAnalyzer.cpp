
#include "MicAnalyzer.hpp"
#include <SDL.h>
#include <pitch_detection.h>

namespace sb {
	
	struct MicPrivateData {
		MicAnalyzer* micAnalyzer = nullptr;
		SDL_AudioDeviceID deviceId = 0;
		bool opened = false;
		
		double pitch = 0;
		double amplitude = 0;
		
		MicPrivateData(MicAnalyzer* micAnalyzer)
			: micAnalyzer(micAnalyzer) {
			//
		}
	};
	
	
	void MicAnalyzer_AudioCallback(void* userdata, Uint8* stream, int len) {
		auto micData = (MicPrivateData*)userdata;
		
		auto floatStream = std::vector<float>((float*)stream, (float*)stream + (size_t)(len / sizeof(float)));
		auto dubStream = std::vector<double>();
		dubStream.reserve(floatStream.size());
		for(auto num : floatStream) {
			dubStream.push_back((double)num);
		}
		double pitch = get_pitch_yin(dubStream, 44100);
		if(pitch > 0) {
			static const float LOG2 = Math::log(2.0);
			pitch = Math::max(0.0, Math::log(pitch / 440.0) / LOG2 * 12.0 + 69.0);
		}
		double amplitude = 0;
		for(double sample : dubStream) {
			amplitude += sample * sample;
		}
		amplitude = Math::sqrt(amplitude / dubStream.size());
		micData->pitch = pitch;
		micData->amplitude = amplitude;
	}
	
	
	
	MicAnalyzer::MicAnalyzer()
		: privateData(new MicPrivateData(this)) {
		//
	}
	
	MicAnalyzer::~MicAnalyzer() {
		if(privateData->opened) {
			stop();
		}
		delete privateData;
	}
	
	void MicAnalyzer::start(int index) {
		if(privateData->opened) {
			throw Exception("already started");
		}
		
		SDL_AudioSpec want, have;

		SDL_zero(want);
		want.freq = 44100;
		want.format = AUDIO_F32;
		want.channels = 1;
		want.samples = 1024;
		want.callback = MicAnalyzer_AudioCallback;
		want.userdata = privateData;
		
		const char* deviceName = SDL_GetAudioDeviceName(index, 1);
		if(deviceName == nullptr) {
			throw Exception((String)"Couldn't find device at index "+index);
		}
		privateData->deviceId = SDL_OpenAudioDevice(deviceName, 1, &want, &have, 0);
		
		if(privateData->deviceId == 0) {
			throw Exception((String)"Failed to open audio: "+SDL_GetError());
		}
		if (have.format != want.format) {
			SDL_CloseAudioDevice(privateData->deviceId);
			privateData->deviceId = 0;
			throw Exception("Couldn't open desired audio format");
		}
		
		privateData->opened = true;
		SDL_PauseAudioDevice(privateData->deviceId, 0);
	}
	
	void MicAnalyzer::stop() {
		if(!privateData->opened) {
			return;
		}
		SDL_CloseAudioDevice(privateData->deviceId);
		privateData->deviceId = 0;
		privateData->pitch = 0;
		privateData->amplitude = 0;
		privateData->opened = false;
	}
	
	double MicAnalyzer::getPitch() const {
		return privateData->pitch;
	}
	
	double MicAnalyzer::getAmplitude() const {
		return privateData->amplitude;
	}
}
