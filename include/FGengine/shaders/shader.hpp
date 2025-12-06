#pragma once
#include <vector>
#include <string>
#include <forward_list>
#include "shaderproperty.hpp"

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
				return;
			}
			else{
				std::forward_list<Shader*>::iterator itr = shaderslist.begin();
				for(int i = 0; i != id; i++){
					++itr;
				}
				*itr = element;
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
	

	std::vector<Uniforms::UniformData*> uniforms;
	std::vector<Shader*> allshaders;

	GLuint shaderid;

	// forward list<Pair (id,pointer)>. 
	//Creating element:
	//If new id is not > max.id (id is free), pair points to special Shader object that means this id is free.
	//If new id IS > max.id (new id), adds new pair
	//Deleting element:
	//If id is last, deleting pair
	//If id is not last, pair will point to null-Shader.
	//Editing:
	//Just changing pointer
	//Access:
	//In Shader class it will be used to access all elements in loop. So, for(TemporaryPointer p : thisarray) { if(!p.Empty()){ p.DoSomething() } p.GoToPointer()}
	//For deleting/adding it's not neccesary to do max perfomance.

	class ShaderSourceReader{
		std::string* file;
		long cpos = 0;
		const static inline std::string stopcharacters{" \n\t:;{}()[]\\|/*+-=%#!~`.,<>\"'@$^&"};
	
	public:

		std::string ReadWord(){
			std::string word;

			for(; IsEOF() or IsAStopCharacter((*file)[cpos]); cpos++){
				word += (*file)[cpos];
				cpos++;
			}
			return word;
		}

	private:
		bool IsAStopCharacter(char character){
			return stopcharacters.find(character) != std::string::npos;
		}
	
	public:

		bool IsEOF(){
			return cpos <= file->length();
		}

	public:

		ShaderSourceReader(std::string* file){
			this->file = file;
		}
	};

public:
	
	void Load(std::string& file){
		ApplyUniforms(file);
	}

private:
	void ApplyUniforms(std::string& file){
		std::string word;
		ShaderSourceReader reader {&file};


		while( !reader.IsEOF() ){
			word = reader.ReadWord();
			if(word == "uniform"){
				const char* type = reader.ReadWord().c_str();
				const char* name = reader.ReadWord().c_str();
				AddNewUniform(name, type);
			}
		}
	}

	void AddNewUniform(const char* name, const char* type){
		if(type == "vec4"){
			uniforms.emplace_back(name, shaderid, (glm::vec4*)nullptr);
		}
		else if(type == "vec3"){
			uniforms.emplace_back(name, shaderid, (glm::vec3*)nullptr);
		}
		else if(type == "mat4"){
			uniforms.emplace_back(name, shaderid, (glm::mat4*)nullptr);
		}
		else if(type == "mat3"){
			uniforms.emplace_back(name, shaderid, (glm::mat3*)nullptr);
		}
	}

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