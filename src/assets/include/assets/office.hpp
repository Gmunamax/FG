#include <engine/graphics/model.hpp>
#include <span>
#include <vector>

namespace Assets{

class Office: public Model{
public:
	Office():
		Model{officeVertexes, GetShader()}
	{}

private:
	static std::span<float> GetVertexes();
	static std::span<unsigned> GetIndices();
	static std::vector<float> officeVertexes;

	static std::shared_ptr<Shader> GetShader(){
		static const char* vertex = "\
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

		static const char* fragment = "\
			#version 330\n\
			\n\
			out vec4 fragColor;\n\
			\n\
			void main(){\n\
			\t	fragColor = vec4(1,1,0,0);\n\
			}\n\
		";

		static Shader shader{vertex, fragment};
		static std::shared_ptr<Shader> ptr{&shader};

		return ptr;
	}
};

}
