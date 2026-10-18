module;
#include "assets/office.hpp"

export module Night1:Office;

namespace Night1{

	class Office{
	public:
		void Update(){
			office.Draw();
		}

	private:
		Assets::Office office;
	};

}
