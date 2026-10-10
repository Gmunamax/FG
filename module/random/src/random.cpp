#include <random.hpp>
#include <random>

namespace Random{

	RandomType GetRandomNumber(RandomType min, RandomType max){
		std::random_device random;
		std::mt19937 generator(random());
		std::uniform_int_distribution distribution{min, max};
		return distribution(generator);
	}

}
