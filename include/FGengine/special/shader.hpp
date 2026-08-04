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
#include <forward_list>
#include "FGengine/structures/shaderid.hpp"
#include "FGengine/structures/uniform.hpp"

namespace FGengine{

class Shader{

	class ShadersList{
		std::forward_list<Shader*> shaderslist;

		std::forward_list<Shader*>::size_type size;

	public:
		class iterator{
			std::forward_list<Shader*>::iterator listiterator;

		public:
			iterator(std::forward_list<Shader*>::iterator i): listiterator(i){}

			Shader*& operator*(){
				return *listiterator;
			}
			iterator& operator++(){
				++listiterator;
				return *this;
			}
			bool operator==(const iterator& other){
				return listiterator == other.listiterator;
			}
			bool operator!=(const iterator& other){
				return listiterator != other.listiterator;
			}
			bool isFree(){
				return *listiterator == nullptr;
			}
			const std::forward_list<Shader*>::iterator toStl(){
				return listiterator;
			}
		};

		iterator begin(){
			return {shaderslist.begin()};
		}
		iterator end(){
			return {shaderslist.end()};
		}

		using size_type = std::forward_list<Shader*>::size_type;

		//returns true on success, false otherwise
		bool setElement(unsigned long id, Shader* element){
			if(id > size){
				return false;
			}
			else{
				std::forward_list<Shader*>::iterator itr = shaderslist.begin();
				for(int i = 0; i != id; i++){
					++itr;
				}
				*itr = element;
				return true;
			}
		}

		std::forward_list<Shader*>::size_type pushBack(Shader* element){
			iterator beforeit = shaderslist.before_begin();
			iterator it = shaderslist.begin();
			for(std::forward_list<Shader*>::size_type id = 0; id < size; id++){
				if(it.isFree()){
					*it = element;
					return id;
				}
				++it;
				++beforeit;
			}
			shaderslist.insert_after(beforeit.toStl(), element);
			size++;
			return size;
		}

		void remove(unsigned long id){
			if(id == size){
				iterator i = shaderslist.before_begin();
				iterator afteri = shaderslist.begin();
				while(afteri.isFree()){
					shaderslist.erase_after(i.toStl());
					++i;
					++afteri;
				}
			}
			else if(id < size){
				setElement(id, nullptr);
			}
		}

		unsigned long getSize(){
			return size;
		}

		ShadersList(){
			size = 0;
		}
	};

	static inline ShadersList shaderslist;
	ShadersList::size_type listid;
	
	ShaderID shaderid;

public:

	struct ObjectDescription{
		unsigned int type;
		std::vector<const char*> filepathes;
	};
	
	void Load(std::vector<ObjectDescription> descriptions);

	template<unsigned Count, typename ValueType>
	static void SendUniformToAll(const char* uniformName, const ValueType* value){
		Uniform<Count, ValueType*> uniform {uniformName};
		for(Shader*& element : shaderslist){
			if(element->shaderid != 0){
				uniform.SetShader(element->shaderid);
				uniform.Send(value);
			}
		}
	}

	void Delete(){
		// glDeleteProgram(shaderid);
		shaderid = 0;
	}

	ShaderID GetID() const{
		return shaderid;
	}

	Shader(){
		listid = shaderslist.pushBack(this);
	}
	Shader(const Shader& shader){
		this->shaderid = shader.shaderid;
		this->listid = shader.listid;
	}
	~Shader(){
		shaderslist.remove(listid);
	}
};

}
