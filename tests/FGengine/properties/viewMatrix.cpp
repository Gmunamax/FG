// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#include "../fgengineFixture.hpp"
#include <boost/test/unit_test.hpp>
#include <FGengine/properties/viewMatrix.hpp>
#include <glm/mat4x4.hpp>

struct ViewMatrixFixture{
	using Vector = FGengine::Vector<3, FGengine::floatType, FGengine::VectorType::Point>;
	using PositionType = Vector;
	using RotationType = Vector;
	
	FGengine::ViewMatrix viewMatrix;

	static inline PositionType position {1,2,3};
	static inline RotationType rotation {4,5,6};

	ViewMatrixFixture(){
		viewMatrix.SetPosition(position);
		viewMatrix.SetRotation(rotation);
	}
};

BOOST_AUTO_TEST_SUITE(ViewMatrix)

glm::mat4 GetReferenceMatrix(){
	glm::mat4 matrix {1};
	matrix = glm::rotate(matrix, glm::radians(ViewMatrixFixture::rotation.x), {1,0,0});
	matrix = glm::rotate(matrix, glm::radians(ViewMatrixFixture::rotation.y), {0,1,0});
	matrix = glm::rotate(matrix, glm::radians(ViewMatrixFixture::rotation.z), {0,0,1});
	matrix = glm::translate(matrix, ViewMatrixFixture::position.toGlm());
	return matrix;
}

BOOST_FIXTURE_TEST_CASE(Calculation, ViewMatrixFixture){
	FGengine::ViewMatrix::ViewMatrixType matrix = viewMatrix.CalculateViewMatrix();
	glm::mat4 mustBe = GetReferenceMatrix();
	bool isEqual = matrix == mustBe;
	BOOST_TEST(isEqual);
}

BOOST_AUTO_TEST_SUITE_END()
