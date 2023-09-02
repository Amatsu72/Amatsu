#include "../pch.h"
#include "Material.h"
#include "../Paltform/OpenGL/OpenGLShader.h"
#include <glm.hpp>

namespace Engine {

    Material::Material(std::shared_ptr<Texture2D> diffuse_map, std::shared_ptr<Texture2D> specular_map, 
        std::shared_ptr<Texture2D> emission_map, std::shared_ptr< Texture2D> reflect_map, float shininess)
        :m_shininess(shininess)
    {
        auto black_texture = Texture2D::create_flat_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        m_diffuse_map = diffuse_map ? diffuse_map : black_texture;
        m_specular_map = specular_map ? specular_map : black_texture;
        m_emission_map = emission_map ? emission_map : black_texture;
        m_reflect_map = reflect_map ? reflect_map : black_texture;
    }

    void Material::set_texture_map(std::shared_ptr<Texture2D> texture, Texture::Type type)
    {
        switch (type)
        {
            case Texture::Type::Diffuse:
                set_diffuse_map(texture);
                break;
            case Texture::Type::Specular:
                set_specular_map(texture);
                break;
            case Texture::Type::Emission:
                set_emission_map(texture);
                break;
            case Texture::Type::Reflect:
                set_reflect_map(texture);
                break;
            default: 
                std::cout << "unkonwn texture type!" << std::endl;
        }
    }
    void Material::use()
    {
        m_diffuse_map->bind(s_diffuse_slot);
        m_specular_map->bind(s_specular_slot);
        m_emission_map->bind(s_emission_slot);
        m_reflect_map->bind(s_reflect_slot);
    }
    void Material::bind(const std::shared_ptr<Shader>& shader)
    {
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_int("u_Material.diffuse", s_diffuse_slot);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_int("u_Material.specular", s_specular_slot);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_int("u_Material.emission", s_emission_slot);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_int("u_Material.reflect", s_reflect_slot);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_Material.shininess", m_shininess);
    }

}