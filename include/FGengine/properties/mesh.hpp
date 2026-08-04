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
#pragma once
#include <vector>
#include "FGengine/structures/matrix.hpp"
#include "FGengine/structures/uniform.hpp"
#include "FGengine/structures/shaderid.hpp"

namespace FGengine{

template<typename VertexType, typename ElementsType>
class Mesh{
public:
	using VertexesList = std::vector<VertexType>;
	using Face = std::vector<ElementsType>;
	using ElementsList = std::vector<Face>;
	using TransformMatrixType = Matrix<4,4,double>;
	using NormalMatrixType = Matrix<3,3,double>;

private:
	static constexpr int VBOusage;
	static constexpr int EBOusage;

	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;

	struct FaceLocation{

		long offset;
		int size;

		void Draw() const{
			glDrawElements(GL_TRIANGLE_STRIP, size, ElementsType::gldatatype(), (void*)(sizeof(ElementsType) * offset));
		}

		FaceLocation(long offset, int size): offset(offset), size(size){}
	};
	
	Uniform<1, TransformMatrixType*> objectMatrixUniform{"fg_objectmatrix"};
	Uniform<1, NormalMatrixType*> normalMatrixUniform{"fg_normalmatrix"};
	std::vector<FaceLocation> facelocators;

	template<typename VertexAttribType>
	void InitVertexAttribute(const unsigned int index){
		if(VertexAttribType::PropertyType::gldatatype() == GL_DOUBLE)
			glVertexAttribLPointer(index, VertexAttribType::GetLength(), VertexAttribType::PropertyType::gldatatype(), VertexType::GetStride(), (void*)VertexAttribType::GetOffset());
		else
			glVertexAttribPointer(index, VertexAttribType::GetLength(), VertexAttribType::PropertyType::gldatatype(), false, VertexType::GetStride(), (void*)VertexAttribType::GetOffset());
		glEnableVertexAttribArray(index);
	}

public:
	//Must be called once, after Model created and OpenGL context loaded
	void Init(){
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		InitVertexAttribute<typename VertexType::VertexPosition>(0);
		InitVertexAttribute<typename VertexType::VertexColor>(1);
		InitVertexAttribute<typename VertexType::VertexNormal>(2);

		glBindVertexArray(0);
	}

	void Select(){
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void Draw() const{
		for(const FaceLocation& face : facelocators){
			face.Draw();
		}
	}

	void SetShader(const ShaderID newshader){
		objectMatrixUniform.SetShader(newshader);
		normalMatrixUniform.SetShader(newshader);
	}

	void SendMatrixes(const TransformMatrixType* transform){
		objectMatrixUniform.Send(transform);
		NormalMatrixType normalMatrix {glm::transpose(glm::inverse(*transform))};
		normalMatrixUniform.Send(&normalMatrix);
	}

public:
	void Load(const VertexesList& vertexes, const ElementsList& elements){
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType)*vertexes.size(), vertexes.data(), VBOusage);
		std::vector<ElementsType> newbuffer;
		long long maxsize = 0;
		for(const Face& face : elements){
			facelocators.emplace_back(maxsize, face.size());
			maxsize+=face.size();
			for(short i = 0; i < face.size(); ++i)
				newbuffer.emplace_back(face.at(i));
		}
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, newbuffer.size()*sizeof(ElementsType), newbuffer.data(), EBOusage);
	}

	void Delete(){
		glDeleteVertexArrays(1,&vao);
		glDeleteBuffers(1, &vbo);
		facelocators.clear();
		facelocators.shrink_to_fit();
		glDeleteBuffers(1, &ebo);
	}

};

}
