#pragma once
#include <span>
#include <engine/graphics/model.hpp>
#include <engine/utils/player.hpp>

class NPC: public Player{
public:
	NPC(Model& model):
		model{model}
	{}

	void WalkTo(const glm::vec3& newDestination){
		destination = newDestination;
	}

protected:
	void UpdateProperties(TimeType timeDelta){
		glm::vec3 position = model.GetPosition();
		glm::vec3 rotation = model.GetRotation();

		glm::vec3 distance = destination - position;
		if(glm::length(distance) < finishCheckError){
			return;
		}
		glm::vec3 speedVector = glm::normalize(distance) * walkSpeed;
		position += speedVector * timeDelta;

		model.SetPosition(position);
		model.SetRotation(rotation);
	}

private:
	Model& model;
	glm::vec3 destination;
	float walkSpeed = 3;
	float finishCheckError = 0.3;
};

class TB1{
public:
	TB1(const Model& office, const glm::vec3& startPosition):
		office(office)
	{
		model.SetPosition(startPosition);
	}

	void Update(){
		UpdateAI();
		npc.Update();
		model.Draw();
	}

private:
	void UpdateAI(){
		static bool actionRequired = false;
		static bool actionHandled = false;
		static bool reverseMovement = false;
		static Timer timer;
		if(((int)timer.GetTime() % 7) == 0){
			if(!actionHandled){
				actionRequired = true;
			}
		}
		else{
			actionHandled = false;
		}
		if(actionRequired){
			actionHandled = true;
			if(reverseMovement){
				npc.WalkTo({-20, 5, 1});
			}
			else{
				npc.WalkTo({2, 5, 1});
			}
			reverseMovement = !reverseMovement;
			actionRequired = false;
		}
	}

	static std::span<float> GetModel(){
		static float vertexes[]{
			1, 0, -1,
			-1, 0, 1,
			-1, 0, -1,

			-1, 0, 1,
			1, 0, -1,
			1, 0, 1
		};

		return vertexes;
	}

	static Shader GetShader(){
		static const char* vertex = "\
			#version 330\n\
			\n\
			layout (location = 0) in vec3 pos;\n\
			\n\
			uniform mat4 model;\n\
			layout(std140) uniform camera{\n\
				mat4 projection;\n\
				mat4 view;\n\
			};\n\
			\
			void main(){\n\
			\t	gl_Position = projection * view * model * vec4(pos, 1.0);\n\
			}\
		";

		static const char* fragment = "\
			#version 330\n\
			\n\
			out vec4 fragColor;\n\
			\n\
			void main(){\n\
			\t	fragColor = vec4(0.5,0.5,0.5,0);\n\
			}\n\
		";

		Shader shader{vertex, fragment};

		return shader;
	}

	std::shared_ptr<Shader> shader = std::make_shared<Shader>(GetShader());
	Model model{GetModel(), shader};
	NPC npc{model};
	const Model& office;
};
