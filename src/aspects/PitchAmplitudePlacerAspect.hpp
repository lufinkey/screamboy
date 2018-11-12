
#pragma once

#include "import/GameLibrary.hpp"

namespace sb {
	class PitchAmplitudePlacerAspect: public Drawable2DAspect {
	public:
		PitchAmplitudePlacerAspect(RectangleD rect);
		
		virtual void update(const ApplicationData& appData) override;
		virtual void draw(DrawContext context, Graphics graphics) const override;
		
	private:
		RectangleD rect;
		double pitch;
		double pitchVelocity;
		double amplitude;
		double amplitudeVelocity;
	};
}
