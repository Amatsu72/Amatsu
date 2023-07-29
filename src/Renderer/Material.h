#pragma once
#include "Texture.h"
#include "Shader.h"

namespace Engine {

	class Material
	{
	public:
		Material(std::shared_ptr<Texture2D> diffuse_map = nullptr
			, std::shared_ptr<Texture2D> m_specular_map = nullptr,
			float shininess = 32.0f);
		~Material(){}

		inline void set_diffuse_map(std::shared_ptr<Texture2D> texture)
		{
			m_diffuse_map = texture;
		}
		inline void set_specular_map(std::shared_ptr<Texture2D> texture)
		{
			m_specular_map = texture;
		}

		inline void set_shininess(float shininess) { m_shininess = shininess; }
		inline float get_shininess() const { return m_shininess; }

		void use();
		void bind(std::shared_ptr<Shader>& shader);

	private:
		static const int s_diffuse_slot = 0;
		static const int s_specular_slot = 1;

		std::shared_ptr<Texture2D> m_diffuse_map;
		std::shared_ptr<Texture2D> m_specular_map;
		float m_shininess;
	};

}