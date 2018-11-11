
#include "Game.hpp"
#include "audioinput/MicAnalyzer.hpp"

namespace sb {
	void Game::initialize() {
		//
	}
	
	void Game::loadContent(AssetManager* assetManager) {
		MicAnalyzer::start();
	}
	
	void Game::unloadContent(AssetManager* assetManager) {
		MicAnalyzer::stop();
	}
	
	void Game::update(ApplicationData appData) {
		MicAnalyzer::update();
		Console::writeLine((String)"amplitude: "+MicAnalyzer::getAmplitude());
	}
	
	void Game::draw(ApplicationData appData, Graphics graphics) const {
		double pitch = MicAnalyzer::getPitch();
		auto window = appData.getWindow();
		auto viewSize = window->getViewport()->getSize();
		double y = (pitch / 180.0) * viewSize.y;
		graphics.setColor(Colors::RED);
		graphics.fillRect((viewSize.x/2.0) - 5.0, y, 10.0, 5.0);
	}
}
