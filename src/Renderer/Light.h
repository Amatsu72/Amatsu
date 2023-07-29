#pragma once
#include <glm.hpp>
#include "Shader.h"

namespace Engine{

	class Light
	{
	public:		
		virtual ~Light() = default;

		inline float get_ambient_intensity() const { return m_ambient_intensity; }
		inline float get_diffuse_intensity() const { return m_diffuse_intensity; }
		inline float get_specular_intensity() const { return m_specular_intensity; }

		inline void set_ambient_intensity(float ambient) { m_ambient_intensity = ambient; }
		inline void set_diffuse_intensity(float diffuse) { m_ambient_intensity = diffuse; }
		inline void set_specular_intensity(float specular) { m_ambient_intensity = specular; }
		void set_intensity(float ambient, float diffuse, float specular);

	protected:
		Light(float ambient, float diffuse, float specular)
			:m_ambient_intensity(ambient), m_diffuse_intensity(diffuse), m_specular_intensity(specular) {}

		float m_ambient_intensity;
		float m_diffuse_intensity;
		float m_specular_intensity;
	};

	class DirectionalLight :public Light
	{
	public:
		DirectionalLight(const glm::vec3& direction, float ambient, float diffuse, float specular)
			:m_direction(direction), Light(ambient, diffuse, specular) {}

		inline const glm::vec3& get_direction() const { return m_direction; }
		inline void set_direction(const glm::vec3& direction) { m_direction = direction; }

		void bind(std::shared_ptr<Shader>& shader);

	private:
		glm::vec3 m_direction;
	};

	class PointLight :public Light
	{
	public:
		PointLight(const glm::vec3& position, float ambient, float diffuse, float specular,
			float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
			:m_position(position),m_constant(constant),m_linear(linear),m_quadratic(quadratic),Light(ambient, diffuse, specular) {}

		inline const glm::vec3& get_position() const { return m_position; }
		inline void set_position(const glm::vec3& position) { m_position = position; }

		inline float get_constant() const { return m_constant; }
		inline float get_linear() const { return m_linear; }
		inline float get_quadratic() const { return m_quadratic; }

		inline void set_constant(float constant) { m_constant = constant; }
		inline void set_linear(float linear) { m_linear = linear; }
		inline void set_quadratic(float quadratic) { m_quadratic = quadratic; }
		void set_attenuation(float constant, float linear, float quadratic);

		void bind(std::shared_ptr<Shader>& shader, int index = 0);
	private:
		glm::vec3 m_position;

		float m_constant;
		float m_linear;
		float m_quadratic;
	};

	class SpotLight :public Light
	{
	public:
		SpotLight(const glm::vec3& position, const glm::vec3& direction, float ambient, float diffuse, float specular,
			float cut_off, float outer_cut_off, float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
			:m_position(position), m_direction(direction), m_constant(constant), m_linear(linear), m_quadratic(quadratic),
			m_cut_off(cut_off), m_outer_cut_off(outer_cut_off), Light(ambient, diffuse, specular) {}

		inline const glm::vec3& get_position() const { return m_position; }
		inline void set_position(const glm::vec3& position) { m_position = position; }
		inline const glm::vec3& get_direction() const { return m_direction; }
		inline void set_direction(const glm::vec3& direction) { m_direction = direction; }

		inline float get_constant() const { return m_constant; }
		inline float get_linear() const { return m_linear; }
		inline float get_quadratic() const { return m_quadratic; }
		inline float get_cut_off() const { return m_cut_off; }
		inline float get_outer_cut_off() const { return m_outer_cut_off; }

		inline void set_constant(float constant) { m_constant = constant; }
		inline void set_linear(float linear) { m_linear = linear; }
		inline void set_quadratic(float quadratic) { m_quadratic = quadratic; }
		inline void set_cut_off(float cut_off) { m_cut_off = cut_off; }
		inline void set_outer_cut_off(float outer_cut_off) { m_outer_cut_off = outer_cut_off; }

		void set_attenuation(float constant, float linear, float quadratic);
		void set_cuts(float cut_off, float outer_cut_off);

		void bind(std::shared_ptr<Shader>& shader);

	private:
		glm::vec3 m_position;
		glm::vec3 m_direction;

		float m_constant;
		float m_linear;
		float m_quadratic;

		float m_cut_off;
		float m_outer_cut_off;
	};
}