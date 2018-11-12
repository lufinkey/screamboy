
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
		/*double pitch = MicAnalyzer::getPitch();
		auto window = appData.getWindow();
		auto viewSize = window->getViewport()->getSize();
		double y = (pitch / 180.0) * viewSize.y;
		graphics.setColor(Colors::RED);
		graphics.fillRect((viewSize.x/2.0) - 5.0, y, 10.0, 5.0);*/
	}
}
