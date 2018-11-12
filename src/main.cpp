
#include "Game.hpp"

int main(int argc, char* argv[]) {
	auto game = new sb::Game();
	int retVal = game->run(fgl::Window::getDefaultSettings(), fgl::Application::ORIENTATION_LANDSCAPE);
	delete game;
	return retVal;
}
