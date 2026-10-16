#include "assets/office.hpp"

class Office{
public:
	void Update(){
		office.Draw();
	}

	void SetPosition(const glm::vec3& newPosition){
		office.SetPosition(newPosition);
	}

	const glm::vec3& GetPosition(){
		return office.GetPosition();
	}

private:
	Assets::Office office;
};
