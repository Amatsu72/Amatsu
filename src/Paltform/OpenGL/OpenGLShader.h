#pragma once
#include "../../Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Engine {

	class OpenGLShader :public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);
		~OpenGLShader() override;

		void bind() const override;
		void unbind() const override;

		void set_int(const std::string& name, int value) override;
		void set_float(const std::string& name, float value) override;
		void set_float3(const std::string& name, const glm::vec3& value) override;
		void set_float4(const std::string& name, const glm::vec4& value) override;
		void set_mat4(const std::string& name, const glm::mat4& value) override;

		void set_float2(const std::string& name, const glm::vec2& value);
		void set_mat3(const std::string& name, const glm::mat3& value);
		const std::string& get_name() const override { return m_name; }

	private:
		std::string read_file(const std::string& filepath);
		std::unordered_map<GLenum, std::string> pre_process(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shader_source);

		uint32_t m_render_id;
		std::string m_name;
	};

}