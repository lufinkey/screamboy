
#include "Game.hpp"
#include "audioinput/MicAnalyzer.hpp"
#include "objects/ScreamBoi.hpp"

namespace sb {
	Game::Game()
		: world(nullptr) {
		//
	}
	
	void Game::initialize() {
		//
	}
	
	void Game::loadContent(AssetManager* assetManager) {
		assetManager->addAssetType<AnimationProvider>([](auto loadInfo) -> AnimationProvider* {
			throw IllegalStateException("cannot load animation provider, sorry");
		});
		
		MicAnalyzer::start();
		auto viewSize = getWindow()->getViewport()->getSize();
		world = new World(assetManager, {
			new WorldCamera(RectangleD(0, 0, viewSize.x, viewSize.y), {0,0}, viewSize)
		});
		world->addObject(new ScreamBoi(assetManager));
	}
	
	void Game::unloadContent(AssetManager* assetManager) {
		delete world;
		world = nullptr;
		MicAnalyzer::stop();
	}
	
	void Game::update(ApplicationData appData) {
		world->update(appData);
	}
	
	void Game::draw(ApplicationData appData, Graphics graphics) const {
		world->draw(appData, graphics);
		
		graphics.setColor(Colors::BLACK);
		graphics.drawString((String)"pitch: "+MicAnalyzer::getPitch(), 10, 40);
		graphics.drawString((String)"amplitude: "+MicAnalyzer::getAmplitude(), 10, 80);
	}
}
