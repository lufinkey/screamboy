
#include "PitchAmplitudePlacerAspect.hpp"
#include "MicAnalyzer.hpp"

namespace sb {
	PitchAmplitudePlacerAspect::PitchAmplitudePlacerAspect(RectangleD rect)
	: rect(rect),
	pitch(0),
	pitchVelocity(1.0),
	amplitude(0),
	amplitudeVelocity(1.0){
		//
	}
	
	void PitchAmplitudePlacerAspect::update(const ApplicationData& appData) {
		double newPitch = MicAnalyzer::getPitch();
		double newAmplitude = MicAnalyzer::getAmplitude();
		double frameSpeedMult = appData.getFrameSpeedMultiplier();
		
		if(newAmplitude > 0.03) {
			pitch = pitch + Math::min(((newPitch / 180.0) - pitch), (1.0 * pitchVelocity * frameSpeedMult));
			amplitude = amplitude + Math::min(((newAmplitude / 0.3) - amplitude), (1.0 * amplitudeVelocity * frameSpeedMult));
		}
		
		auto transform2d = getAspect<Transform2DAspect>();
		auto position = transform2d->getLocalPosition();
		position.x = rect.x + (pitch * rect.width);
		position.y = rect.y + (amplitude * rect.height);
		transform2d->setLocalPosition(position);
	}
	
	void PitchAmplitudePlacerAspect::draw(DrawContext context, Graphics graphics) const {
		graphics.setColor(Colors::RED);
		graphics.drawRect(rect);
	}
}
