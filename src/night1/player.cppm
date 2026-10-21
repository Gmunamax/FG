module;
#include <FGengine/graphics/camera.hpp>

export module Night1:Player;

using FGengine::Graphics::Camera;

namespace Night1{

	class Player{
	public:
		void Update(){
			camera.Update();
		}

		void SetPosition(const glm::vec3& newPosition){
			camera.SetPosition(newPosition);
		}

		glm::vec3 GetPosition(){
			return camera.GetPosition();
		}

		void SetRotation(const glm::vec3& newRotation){
			camera.SetRotation(newRotation);
		}

		glm::vec3 GetRotation(){
			return camera.GetRotation();
		}

	private:
		Camera camera;
	};

}
