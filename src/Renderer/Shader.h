#pragma once
#include <glm.hpp>

namespace Engine {

	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_int(const std::string& name, int vaule) = 0;
		virtual void set_float(const std::string& name, float value) = 0;
		virtual void set_float3(const std::string& name, const glm::vec3& value) = 0;
		virtual void set_float4(const std::string& name, const glm::vec4& value) = 0;
		virtual void set_mat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& get_name() const = 0;

		static std::shared_ptr<Shader> create(const std::string& filepath);
		static std::shared_ptr<Shader> create(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);
	};

	class ShaderLibrary
	{
	public:
		void add(const std::string& name, const std::shared_ptr<Shader>& shader);
		void add(const std::shared_ptr<Shader>& shader);

		std::shared_ptr<Shader> load(const std::string& filepath);
		std::shared_ptr<Shader> load(const std::string& name, const std::string& filepath);

		std::shared_ptr<Shader> get(const std::string& name);
		bool exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
	};

}