
#pragma once

#include "import/GameLibrary.hpp"

namespace sb {
	class ScreamBoi: public WorldObject {
	public:
		ScreamBoi(AssetManager* assetManager);
		
		virtual String getDebugDescription() const override;
	};
}
