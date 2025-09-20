#include "FGengine/scene/scene.hpp"
#include "FGengine/objects/model/model.hpp"
// #include "FG/models/fgscene/fgfloor.hpp"
#include "FG/models/cube.hpp"
// #include "FGengine/mechanics/camRotation/camRotation.hpp"
// #include "FGengine/mechanics/walking/walking.hpp"
#include "FG/models/floor.hpp"
#include "FG/shaders.hpp"
#include "FGengine/structures/vertex.hpp"
#define STH_FRAG "resources/shaders/sth.frag"
#define STH_VERT "resources/shaders/sth.vert"

class RotatingPyramid2: virtual public Scene{

	Buffer vbo;
	Point3d position = {0,0,-5};
	Point3d rotation = {0};
	glm::mat4 vbotransform = 1;
	unsigned int shaderprogram;
	int size;
	bool rotate = false;
	using VertexType = Vertex3d;

	void Transform(){
		vbotransform = 1;
		vbotransform = glm::translate(vbotransform,glm::vec3{position.x,position.y,position.z});
		vbotransform = glm::rotate(vbotransform,(float)glm::radians(rotation.x),glm::vec3{1,0,0});
		vbotransform = glm::rotate(vbotransform,(float)glm::radians(rotation.y),glm::vec3{0,1,0});
		vbotransform = glm::rotate(vbotransform,(float)glm::radians(rotation.z),glm::vec3{0,0,1});
	}

	virtual void Loading(Window* w) override{
		this->win = w;

		cam.SetFrustum();

		auto obj = Pyramid::Load();
		
		vbo.Generate(GL_ARRAY_BUFFER);
		VertexType::SelectVAO();
		vbo.Select();
		vbo.Load(sizeof(VertexType)*obj.size(),obj.data(),GL_STATIC_DRAW);
		VertexType::Init();
		size = obj.size();
		Transform();

		ShaderProgram::SetObjectMatrix(&vbotransform);

		GLuint vertshad = LoadShader(STH_FRAG, GL_FRAGMENT_SHADER);

		GLuint fragshad = LoadShader(STH_VERT, GL_VERTEX_SHADER);

		shaderprogram = LinkProgram(vertshad, fragshad);
	}

	virtual void Drawing() override{
		ShaderProgram::SendMatrixTo(shaderprogram);
		VertexType::SelectVAO();
		vbo.Select();

		glDrawArrays(GL_TRIANGLES,0,size);
	}

	virtual void KeyPressed(SDL_KeyboardEvent& key) override{
		if(key.keysym.sym == SDLK_b){
			quit();
		}
		if(key.keysym.sym == SDLK_r){
			static bool xray = false;
			
			xray = !xray;
			
			if(xray)
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

			win->Update();
			
		}
		if(key.keysym.sym == SDLK_e){
			rotate = !rotate;
		}
	}

	virtual void Cycle() override{
		if(rotate){
			rotation.z--;
			rotation.y--;
			Transform();
			win->Update();
		}
	}

	virtual void Deleting() override{

	}

public:
	static RotatingPyramid2* New(){
		return new RotatingPyramid2{};
	}
	void Delete(){
		delete this;
	}
};

class FgScene: virtual public Scene{
	
	Model<Vertex3d> floor;

	// void OpenWindow(){
	// 	for(int i = 0; i == GetSystemRefreshRate(); i++){
	// 		//OPACITY: FADE IN
	// 		//and some other cool stuff
	// 		win->Update();
	// 	}
	// }

	bool rotation = false;


	unsigned int shaderprogram;

	
	

	virtual void Loading(Window* w) override{
		this->win = w;
		floor.Init();
		floor.Load(Cube::Load());

		floor.SetPosition({0,0,-2});
		floor.SetScale({0.3});


		cam.SetFrustum();

		// SetRotationKeys(SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT);
		// WalkSetKeys(SDLK_w,SDLK_s,SDLK_a,SDLK_d);

		GLuint vertshad = LoadShader(STH_FRAG, GL_FRAGMENT_SHADER);

		GLuint fragshad = LoadShader(STH_VERT, GL_VERTEX_SHADER);

		shaderprogram = LinkProgram(vertshad, fragshad);

		floor.SetShaderProgram(shaderprogram);
		glDeleteShader(vertshad);
		glDeleteShader(fragshad);
	}

	virtual void Drawing() override{
		floor.Draw();

		
	}

	virtual void KeyPressed(SDL_KeyboardEvent& key) override{
		// WalkStart(key);
		// CamRotationStart(key);
		if(key.keysym.sym == SDLK_b){
			quit();
		}
		if(key.keysym.sym == SDLK_r){
			static bool xray = false;
			
			xray = !xray;
			
			if(xray)
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

			win->Update();
			
		}
		if(key.keysym.sym == SDLK_e){
			rotation = !rotation;
		}
	}

	virtual void KeyReleased(SDL_KeyboardEvent& key) override{
		// WalkEnd(key);
		// CamRotationEnd(key);
	}

	Point3d rt = {0};

	virtual void Cycle() override{

		
		// WalkMove();
		// CamRotationMove();
		if(rotation){
			rt.z--;
			rt.y--;
			floor.SetRotation(rt);
			win->Update();
		}
		// std::cout << f.x << " " << f.y << ' ' << f.z << std::endl;
	}

	virtual void Deleting() override{

	}

public:
	static FgScene* New(){
		return new FgScene{};
	}
	void Delete(){
		delete this;
	}
};