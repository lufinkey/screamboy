
#include "Game.hpp"

namespace sb {
	void Game::initialize() {
		//
	}
	
	void Game::loadContent(AssetManager* assetManager) {
		micAnalyzer.start();
	}
	
	void Game::unloadContent(AssetManager* assetManager) {
		micAnalyzer.stop();
	}
	
	void Game::update(ApplicationData appData) {
		auto freq = micAnalyzer.getFrequency();
		Console::writeLine((String)"frequency: "+freq);
	}
	
	void Game::draw(ApplicationData appData, Graphics graphics) const {
		//
	}
}
