#pragma once
#include <glm.hpp>

namespace Engine {

	class Texture
	{
	public:	
		enum Type { Diffuse, Specular, Emission, Reflect };
		virtual ~Texture() = default;
		virtual uint32_t get_width() const = 0;
		virtual uint32_t get_height() const = 0;

		virtual void set_data(void* data, uint32_t size) = 0;
		virtual void bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D :public Texture
	{
	public:
		static std::shared_ptr<Texture2D> create(uint32_t width, uint32_t height, void* data);
		static std::shared_ptr<Texture2D> create(const std::string& path);
		static std::shared_ptr<Texture2D> create_flat_color(const glm::vec4& color);
		static std::shared_ptr<Texture2D> create_attachment(uint32_t width, uint32_t height, bool msaa, uint32_t samples = 4);
		static std::shared_ptr<Texture2D> create_depth_map(uint32_t width, uint32_t height);
	};
	
	class CubeMap
	{
	public:
		virtual void bind() const = 0;
		virtual ~CubeMap() = default;

		static std::shared_ptr<CubeMap> create(const std::string& path);
	};

	class TextureLibrary
	{
	public:
		static std::shared_ptr<Texture2D> load(const std::string& filepath)
		{
			return s_instance->load_impl(filepath);
		}
		static std::shared_ptr<Texture2D> load(const std::string& name, const std::string& filepath)
		{
			return s_instance->load_impl(name, filepath);
		}
		static std::shared_ptr<Texture2D> get(const std::string& name)
		{
			return s_instance->get_impl(name);
		}
		static bool exists(const std::string& name)
		{
			return s_instance->exists_impl(name);
		}
	private:
		void add(const std::string& name, const std::shared_ptr<Texture2D>& texture);

		std::shared_ptr<Texture2D> load_impl(const std::string& filepath);
		std::shared_ptr<Texture2D> load_impl(const std::string& name, const std::string& filepath);
		std::shared_ptr<Texture2D> get_impl(const std::string& name);

		bool exists_impl(const std::string& name) const;

		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_textures;

		static TextureLibrary* s_instance;
	};

}