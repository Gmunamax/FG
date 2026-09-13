#include <engine/utils/player.hpp>
#include <engine/graphics/camera.hpp>

class OfficePlayer: public Player{
public:
	OfficePlayer(const Camera::PositionType& position, const Camera::RotationType& rotation){
		camera.SetPosition(position);
		camera.SetRotation(rotation);
	}

protected:
	void UpdateProperties(TimeType timeDelta){}	

private:
	Camera camera;
};
