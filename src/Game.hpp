
#pragma once

#include "import/GameLibrary.hpp"
#include "audioinput/MicAnalyzer.hpp"

namespace sb
{
    class Game: public Application {
	public:
		virtual void initialize() override;
		virtual void loadContent(AssetManager*) override;
		virtual void unloadContent(AssetManager*) override;
		
		virtual void update(ApplicationData) override;
		virtual void draw(ApplicationData, Graphics) const override;
		
	private:
		MicAnalyzer micAnalyzer;
    };
}
