#include "../../pch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <gtc/type_ptr.hpp>

namespace Engine {

	static GLenum shader_type_from_string(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		std::cout << "Unkonwn shader type!" << std::endl;
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = read_file(filepath);
		auto shader_source = pre_process(source);
		compile(shader_source);

		auto last_slash = filepath.find_last_of("/\\");
		last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
		auto last_dot = filepath.rfind('.');
		auto count = last_dot == std::string::npos ? filepath.size() - last_slash : last_dot - last_slash;
		m_name = filepath.substr(last_slash, count);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src)
		:m_name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertex_src;
		sources[GL_FRAGMENT_SHADER] = fragment_src;
		compile(sources);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_render_id);
	}
	void OpenGLShader::bind() const
	{
		glUseProgram(m_render_id);
	}
	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}
	void OpenGLShader::set_int(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_render_id, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::set_float(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_render_id, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::set_float3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_render_id, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	void OpenGLShader::set_float4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_render_id, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::set_mat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_render_id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::set_float2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_render_id, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::set_mat3(const std::string& name, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_render_id, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	std::string OpenGLShader::read_file(const std::string& filepath)
	{
		std::string result;
		std::fstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			std::cout << "could not open file:" << filepath << std::endl;
		}
		return result;
		
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::pre_process(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shader_sources;
		const char* type_token = "#type";
		size_t type_token_length = strlen(type_token);
		size_t pos = source.find(type_token, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			if (eol == std::string::npos)
			{
				std::cout << "synatax error" << std::endl;
				return std::unordered_map<GLenum, std::string>();
			}
			size_t begin = pos + type_token_length + 1;
			std::string type = source.substr(begin, eol - begin);
			if (!shader_type_from_string(type))
			{
				std::cout << "invalid shader type specified!" << std::endl;
				return std::unordered_map<GLenum, std::string>();
			}
			size_t next_line_pos = source.find_first_not_of("\r\n", eol);
			pos = source.find(type_token, next_line_pos);
			shader_sources[shader_type_from_string(type)] =
				source.substr(next_line_pos, pos - (next_line_pos == std::string::npos ? source.size() - 1 : next_line_pos));
		}
		return shader_sources;
	}
	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shader_source)
	{
		GLuint program = glCreateProgram();
		if (shader_source.size() > 2)
		{
			std::cout << "only support 2 shaders" << std::endl;
			return;
		}
		std::array<GLenum, 2> gl_shader_ids;
		int gl_shader_ids_index = 0;
		for (auto& kv : shader_source)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;
			GLuint shader = glCreateShader(type);

			const GLchar* source_c_str = source.c_str();
			glShaderSource(shader, 1, &source_c_str, 0);
			glCompileShader(shader);

			GLint is_compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
			if (is_compiled == GL_FALSE)
			{
				GLint max_length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
				std::vector<GLchar> info_log(max_length);
				glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);
				glDeleteShader(shader);
				
				std::cout << "Shader compilation failure:"  << std::endl;
				for (auto& c : info_log)
					std::cout << c;
				break;
			}
			glAttachShader(program, shader);
			gl_shader_ids[gl_shader_ids_index++] = shader;
		}
		glLinkProgram(program); 

		GLint is_linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&is_linked);
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
			std::vector<GLchar> info_log(max_length);
			glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);
			glDeleteProgram(program);

			for (auto id : gl_shader_ids)
				glDeleteShader(id);

			std::cout << "Shader link failure:" << std::endl;
			for (auto& c : info_log)
				std::cout << c;
			return;
		}
		for (auto id : gl_shader_ids)
			glDetachShader(program, id);

		m_render_id = program;
	}
}