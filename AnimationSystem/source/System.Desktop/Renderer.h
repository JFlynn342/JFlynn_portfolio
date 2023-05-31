#pragma once
#include "Game.h"
namespace Animation {
	class Renderer : public Library::Game {
	public:
		void Initialize() override;
	private:
		inline static const DirectX::XMVECTORF32 BackgroundColor{ DirectX::Colors::CornflowerBlue };
	};
}