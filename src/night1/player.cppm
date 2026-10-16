module;
#include <engine/graphics/camera.hpp>
#include <engine/utils/player.hpp>

export module Night1:Player;

namespace Night1{

	class Player: public ::Player{
	public:
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

		virtual void UpdateProperties(TimeType time) override{
			camera.Update();
		}
	};

}