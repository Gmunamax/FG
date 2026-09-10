#include <iostream>
#include <gl/gl.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <print>
#include <FGengine/structures/uniform.hpp>

class Floor{
public:
	Floor(){
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, vertexes, GL_STATIC_DRAW);

		unsigned int vert = CreateShader(GL_VERTEX_SHADER, &vertexShader);
		unsigned int frag = CreateShader(GL_FRAGMENT_SHADER, &fragmentShader);
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vert);
		glAttachShader(shaderProgram, frag);
		glLinkProgram(shaderProgram);
		glDeleteShader(vert);
		glDeleteShader(frag);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		objectMatrix.SetShader(shaderProgram);
		objectMatrix = glm::translate(glm::mat4{1}, {0,0.1,z});
		objectMatrix.Send();
	}

	void Draw(){
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
	static inline float z = -1;

private:
	unsigned int CreateShader(GLenum type, const char* const* source){
		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, source, NULL);
		glCompileShader(shader);

		int  success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::println("ERROR::SHADER::COMPILATION_FAILED");
			std::cout << infoLog << std::endl;
		}
		return shader;
	}

	FGengine::Uniform<1, glm::mat4> objectMatrix{"model"};
	unsigned int vbo;
	unsigned int vao;

	unsigned int shaderProgram;
	const char* vertexShader = "\
	#version 330\n\
	\n\
	layout (location = 0) in vec3 pos;\n\
	\n\
	uniform mat4 model;\n\
	layout(std140) uniform camera{\n\
		mat4 projection;\n\
		mat4 view;\n\
	};\n\
	\
	void main(){\n\
	\t	gl_Position = projection * view * model * vec4(pos, 1.0);\n\
	}\
	";
	const char* fragmentShader = "\
	#version 330\n\
	\n\
	out vec4 fragColor;\n\
	\n\
	void main(){\n\
	\t	fragColor = vec4(0,0,1,0);\n\
	}\n\
	";

	static inline float vertexes[] {
		-1, 1, 0,
		1, 1, 0,
		-1, -1,0,
		-1, -1, 0
	};
};

