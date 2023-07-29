#include "../pch.h"
#include "Material.h"
#include "../Paltform/OpenGL/OpenGLShader.h"
#include <glm.hpp>

namespace Engine {

    Material::Material(std::shared_ptr<Texture2D> diffuse_map, std::shared_ptr<Texture2D> specular_map, float shininess)
        :m_shininess(shininess)
    {
        auto black_texture = Texture2D::create_flat_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        m_diffuse_map = diffuse_map ? diffuse_map : black_texture;
        m_specular_map = specular_map ? specular_map : black_texture;
        
    }
    void Material::use()
    {
        m_diffuse_map->bind(s_diffuse_slot);
        m_specular_map->bind(s_specular_slot);
    }
    void Material::bind(std::shared_ptr<Shader>& shader)
    {
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_int("u_Material.diffuse", s_diffuse_slot);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_int("u_Material.specular", s_specular_slot);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->set_float("u_Shininess", m_shininess);
    }

}