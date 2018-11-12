
#include "PitchAmplitudePlacerAspect.hpp"
#include "audioinput/MicAnalyzer.hpp"

namespace sb {
	PitchAmplitudePlacerAspect::PitchAmplitudePlacerAspect(RectangleD rect)
		: rect(rect),
		pitch(0),
		pitchVelocity(2.0),
		amplitude(0),
		amplitudeVelocity(2.0) {
		//
	}
	
	void PitchAmplitudePlacerAspect::update(const ApplicationData& appData) {
		double newPitch = micAnalyzer.getPitch();
		double newAmplitude = micAnalyzer.getAmplitude();
		double frameSpeedMult = appData.getFrameSpeedMultiplier();
		
		if(newAmplitude > 0.04) {
			if(newPitch > 0) {
				double constrainedPitch = (newPitch - 40) / 60.0;
				if(constrainedPitch < 0) {
					constrainedPitch = 0;
				}
				else if(constrainedPitch > 60) {
					constrainedPitch = 60;
				}
				pitch = pitch + Math::min((constrainedPitch - pitch), (1.0 * pitchVelocity * frameSpeedMult));
			}
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
		
		graphics.setColor(Colors::BLACK);
		graphics.drawString((String)"pitch: "+micAnalyzer.getPitch(), rect.x+10, rect.y+40);
		graphics.drawString((String)"amplitude: "+micAnalyzer.getAmplitude(), rect.x+10, rect.y+80);
	}
	
	void PitchAmplitudePlacerAspect::onAddObjectToWorld(World* world) {
		world->addDrawable(this);
		micAnalyzer.start(0);
	}
	
	void PitchAmplitudePlacerAspect::onRemoveObjectFromWorld(World* world) {
		world->removeDrawable(this);
		micAnalyzer.stop();
	}
}
