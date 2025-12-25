#pragma once
#include <vector>
#include <string>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include "uniform.hpp"

class Shader{

	class ShadersList{
		std::forward_list<Shader*> shaderslist;

		std::forward_list<Shader*>::iterator lastelementcarret =  shaderslist.end();
		std::forward_list<Shader*>::size_type size = 0;

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
			bool IsFree(){
				return *listiterator == nullptr;
			}
			const std::forward_list<Shader*>::iterator ToStlIterator(){
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
		bool SetElement(unsigned long id, Shader* element){
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
			//Move carret to here and rewrite pointer to shader
			//Error if id > size (if not do it, we'll have to create elements with ids from size to id and delete them and this once this id becomes free)
		}
		
		//returns id that will be chosen for element
		std::forward_list<Shader*>::size_type AddElementBack(Shader* element){
			iterator beforeit = shaderslist.before_begin();
			iterator it = shaderslist.begin();
			for(std::forward_list<Shader*>::size_type id = 0; id < size; id++){
				if(it.IsFree()){
					*it = element;
					return id;
				}
				++it;
				++beforeit;
			}
			shaderslist.insert_after(beforeit.ToStlIterator(), element);
			size++;
			return size;
		}
		void RemoveElement(unsigned long id){
			if(id == size){
				iterator i = shaderslist.before_begin();
				iterator afteri = shaderslist.begin();
				while(afteri.IsFree()){
					shaderslist.erase_after(i.ToStlIterator());
					++i;
					++afteri;
				}
			}
			else if(id < size){
				SetElement(id, nullptr);
			}
		}
		unsigned long GetSize(){
			return size;
		}

	};

	static ShadersList shaderslist;
	ShadersList::size_type listid;
	
	GLuint shaderid = 0;

public:

	struct ObjectDescription{
		GLuint type;
		std::vector<const char*> filepathes;
	};
	
	void Load(std::vector<ObjectDescription> descriptions){
		if(shaderid == 0){
			LinkShader( CompileObjects(descriptions) );
		}
	}

private:
	
	std::vector<GLuint> CompileObjects(std::vector<ObjectDescription> descriptions);

	void LinkShader(std::vector<GLuint> shaderparts);

	void CheckLoadingForErrors();

	void CheckForError(GLenum type, const char* errorheader);

	static const char* compileerror;
	static const char* linkerror;

public:

	template<typename UniformType>
	static void SendUniformForAll(UniformType value){
		for(Shader*& element : shaderslist){
			if(element != nullptr){
				value.SetShader(element->shaderid);
				value.Send();
			}
		}
	}

	const GLuint& ToGL(){
		return shaderid;
	}

	Shader(){
		listid = shaderslist.AddElementBack(this);
	}
	~Shader(){
		shaderslist.RemoveElement(listid);
	}
};