
#include "ScreamBoi.hpp"
#include "aspects/PitchAmplitudePlacerAspect.hpp"

namespace sb {
	ScreamBoi::ScreamBoi(AssetManager* assetManager) {
		auto animProvider = assetManager->get<AnimationProvider>("screamboi");
		if(animProvider == nullptr) {
			animProvider = new AnimationProvider();
			
			auto texture = assetManager->loadTexture("assets/screamboi.png");
			animProvider->addAnimation("default", new Animation(1.0, texture));
			
			assetManager->add("screamboi", animProvider);
		}
		
		auto transform2d = new Transform2DAspect();
		auto sprite = new SpriteAspect(animProvider, "default");
		sprite->setScale({0.4, 0.4});
		auto placer = new PitchAmplitudePlacerAspect(RectangleD(-200, -150, 400, 300));
		
		addAspects({
			transform2d,
			sprite,
			placer
		});
	}
	
	String ScreamBoi::getDebugDescription() const {
		auto transform2d = getAspect<Transform2DAspect>();
		return "ScreamBoi @ "+transform2d->getPosition().toString();
	}
}
