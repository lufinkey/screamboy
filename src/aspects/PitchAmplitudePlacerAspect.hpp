
#pragma once

#include "import/GameLibrary.hpp"
#include "audioinput/MicAnalyzer.hpp"

namespace sb {
	class PitchAmplitudePlacerAspect: public WorldObjectAspect, public Drawable {
	public:
		PitchAmplitudePlacerAspect(RectangleD rect);
		
		virtual void update(const ApplicationData& appData) override;
		virtual void draw(DrawContext context, Graphics graphics) const override;
		
		void setDebugDrawEnabled(bool debugDraw);
		bool isDebugDrawEnabled() const;
		
	protected:
		virtual void onAddObjectToWorld(World* world) override;
		virtual void onRemoveObjectFromWorld(World* world) override;
		
	private:
		MicAnalyzer micAnalyzer;
		RectangleD rect;
		double pitch;
		double pitchVelocity;
		double amplitude;
		double amplitudeVelocity;
		bool debugDraw;
	};
}
