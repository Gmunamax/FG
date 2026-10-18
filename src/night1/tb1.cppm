module;
#include <engine/graphics/model.hpp>
#include "assets/tb1.hpp"

export module Night1:TB1;
import :TB1ai;

namespace Night1{

	class TB1{
	public:
		TB1(Door* door):
			ai{door}
		{}

		void Update(){
			ai.Update();
			tb1.Draw();
		}

		void SetPosition(const glm::vec3& newPosition){
			tb1.SetPosition(newPosition);
		}

		const glm::vec3& GetPosition(){
			return tb1.GetPosition();
		}

	private:
		Assets::TB1 tb1;
		TB1ai ai;
	};

}
