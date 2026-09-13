#include <engine/graphics/shader.hpp>
#include <engine/videoOutput/eventsPack.hpp>
#include <engine/graphics/model.hpp>
#include <FGengine/special/window.hpp>
#include <memory>
#include "officePlayer.hpp"

class GameScene final: public EventsPack{
public:
	GameScene(FGengine::Window* win):
		window(win)
	{}

	void Draw() override{
		window->Clear();
		player.Update();
		window->Update();
	}

	void KeyPress(Key key) override{

	}

	void KeyRelease(Key key) override{

	}

private:
	OfficePlayer player{{0,0,1}, {90, 0, 0}};
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShader, fragmentShader);

	static const char* vertexShader;
	static const char* fragmentShader;

	FGengine::Window* window;
};
