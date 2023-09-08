#include "../pch.h"
#include "Light.h"
#include "../Paltform/OpenGL/OpenGLShader.h"

namespace Engine {

	template<typename ... Args>
	std::string string_format(const std::string& format, Args ... args)
	{
		// get size
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...);
		auto size = static_cast<size_t>(size_s);
		// get buffer
		std::string buf;
		buf.resize(size);
		std::snprintf(buf.data(), size + 1, format.c_str(), args ...);
		return buf;
	}

	void Light::set_intensity(float ambient, float diffuse, float specular)
	{
		m_ambient_intensity = ambient;
		m_diffuse_intensity = diffuse;
		m_specular_intensity = specular;
	}

	/////////////////////////////////////////////////////////////////////////

	void DirectionalLight::bind(std::shared_ptr<Shader>& shader)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float3("u_DirectionalLight.color", m_color);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float3("u_DirectionalLight.direction", m_direction);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_DirectionalLight.ambient", m_ambient_intensity);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_DirectionalLight.diffuse", m_diffuse_intensity);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_DirectionalLight.specular", m_specular_intensity);
	}

	std::shared_ptr<DirectionalLight> DirectionalLight::create(const glm::vec3& color, const glm::vec3& direction, float ambient, float diffuse, float specular)
	{
		return std::make_shared<DirectionalLight>(color, direction, ambient, diffuse, specular);
	}

	/////////////////////////////////////////////////////////////////////////

	void PointLight::set_attenuation(float constant, float linear, float quadratic)
	{
		m_constant = constant;
		m_linear = linear;
		m_quadratic = quadratic;
	}

	void PointLight::bind(std::shared_ptr<Shader>& shader, int index)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float3(string_format("u_PointLights[%d].color", index), m_color);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float3(string_format("u_PointLights[%d].position", index), m_position);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float(string_format("u_PointLights[%d].ambient", index), m_ambient_intensity);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float(string_format("u_PointLights[%d].diffuse", index), m_diffuse_intensity);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float(string_format("u_PointLights[%d].specular", index), m_specular_intensity);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float(string_format("u_PointLights[%d].constant", index), m_constant);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float(string_format("u_PointLights[%d].linear", index), m_linear);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float(string_format("u_PointLights[%d].quadratic", index), m_quadratic);
	}

	std::shared_ptr<PointLight> PointLight::create(const glm::vec3& color, const glm::vec3& position, float ambient, float diffuse, 
		float specular, float constant, float linear, float quadratic)
	{
		return std::make_shared<PointLight>(color, position, ambient, diffuse, specular, constant, linear, quadratic);
	}

	/////////////////////////////////////////////////////////////////////////


	void SpotLight::set_attenuation(float constant, float linear, float quadratic)
	{
		m_constant = constant;
		m_linear = linear;
		m_quadratic = quadratic;
	}

	void SpotLight::set_cuts(float cut_off, float outer_cut_off)
	{
		m_cut_off = cut_off;
		m_outer_cut_off = outer_cut_off;
	}

	void SpotLight::bind(std::shared_ptr<Shader>& shader)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float3("u_SpotLight.color", m_color);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float3("u_SpotLight.position", m_position);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float3("u_SpotLight.direction", m_direction);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.ambient", m_ambient_intensity);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.diffuse", m_diffuse_intensity);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.specular", m_specular_intensity);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.constant", m_constant);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.linear", m_linear);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.quadratic", m_quadratic);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.cutOff", m_cut_off);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_SpotLight.outerCutOff", m_outer_cut_off);
	}

	std::shared_ptr<SpotLight> SpotLight::create(const glm::vec3& color, const glm::vec3& position, const glm::vec3& direction, float ambient, 
		float diffuse, float specular, float cut_off, float outer_cut_off, float constant, float linear, float quadratic)
	{
		return std::make_shared<SpotLight>(color, position, direction, ambient, diffuse, specular, cut_off, outer_cut_off, constant, linear, quadratic);
	}

}