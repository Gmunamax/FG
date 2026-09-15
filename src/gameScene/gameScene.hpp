#include <engine/graphics/shader.hpp>
#include <engine/videoOutput/eventsPack.hpp>
#include <engine/graphics/model.hpp>
#include <FGengine/special/window.hpp>
#include <memory>
#include "officePlayer.hpp"
#include "officeModel.hpp"
#include "tb1.hpp"

class GameScene final: public EventsPack{
public:
	GameScene(FGengine::Window* win):
		window(win)
	{
		office.SetPosition({0, 4, 1});
	}

	void Draw() override{
		window->Clear();
		player.Update();
		office.Draw();
		tb1.Update();
		window->Update();
	}

	void KeyPress(Key key) override{

	}

	void KeyRelease(Key key) override{

	}

private:
	OfficePlayer player{{0,0,1}, {90, 0, 0}};
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShader, fragmentShader);
	Model office{officeVertexes, shader};
	TB1 tb1;
	static inline std::vector<float> officeVertexes = GetOfficeModel();

	static const char* vertexShader;
	static const char* fragmentShader;

	FGengine::Window* window;
};
