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
#include <FGengine/properties/projectionMatrix.hpp>

struct ProjectionMatrixFixture{
	FGengine::ProjectionMatrix projectionMatrix;

	FGengine::floatType nearz = 1;
	FGengine::floatType farz = 200;
	FGengine::floatType fov = 75 * M_PI/180;
	FGengine::AspectRatio aspectRatio {100, 200};

	ProjectionMatrixFixture(){
		projectionMatrix.SetNearDistance(nearz);
		projectionMatrix.SetFarDistance(farz);
		projectionMatrix.SetFOV(fov);
		projectionMatrix.SetAspectRatio(&aspectRatio);
		projectionMatrix.SetProjectionMode(FGengine::ProjectionMatrix::ProjectionMode::Frustum);
	}
};

BOOST_AUTO_TEST_SUITE(ProjectionMatrix)

BOOST_FIXTURE_TEST_CASE(Calculation, ProjectionMatrixFixture){
	FGengine::ProjectionMatrix::ProjectionMatrixType matrix = projectionMatrix.CalculateProjectionMatrix();
	glm::mat4 mustBe = glm::perspective<FGengine::floatType>(glm::radians(fov), aspectRatio, nearz, farz);
	bool isEqual = matrix == mustBe;
	BOOST_TEST(isEqual);
}

BOOST_AUTO_TEST_SUITE_END()
