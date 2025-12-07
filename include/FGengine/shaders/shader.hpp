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
		unsigned long maxid = 0;

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

		//returns true on success, false otherwise
		bool SetElement(unsigned long id, Shader* element){
			if(id > maxid){
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
			//Error if id > maxid (if not do it, we'll have to create elements with ids from maxid to id and delete them and this once this id becomes free)
		}
		void AddElementBack(Shader* element){
			//So, because we can't add element to end of list, we'll add it to begining. And id 1 will mean last element of list
			shaderslist.push_front(element);
			maxid++;
			//Maybe we'll store carret pointing to last element, so we'll copy it here, add new element to shaderslist and give it this new shader.
		}
		void RemoveElement(unsigned long id){
			SetElement(id, nullptr);
			if(id == maxid){
				iterator i = shaderslist.before_begin();
				iterator afteri = i;
				++afteri;
				while(afteri.IsFree()){
					shaderslist.erase_after(i.ToStlIterator());
					++i;
					++afteri;
				}
			}
		}

	};

	static ShadersList shaderslist;
	
	GLuint shaderid = 0;

public:

	struct ObjectDescription{
		GLuint type;
		std::vector<const char*> filepathes;
	};
	
	void Load(std::vector<ObjectDescription> descriptions){
		shaderid = LinkShader( CompileObjects(descriptions) );
	}

private:
	
	std::vector<GLuint> CompileObjects(std::vector<ObjectDescription> descriptions);

	GLuint LinkShader(std::vector<GLuint> shaderparts);

	void CheckLoadingForErrors();


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

	void Bind(){
		glUseProgram(shaderid);
	}

	Shader(){}
	~Shader(){}
};