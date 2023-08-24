#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

namespace Engine {

	class Model
	{
	public:
		Model() = delete;
		Model(const std::string& path)
		{
			load_model(path);
		}
		const std::vector<Mesh>& get_meshes() const { return m_meshes; }
	private:
		void load_model(const std::string& path);
		void process_node(aiNode* node, const aiScene* scene);
		Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
		std::shared_ptr<Material> load_material(aiMaterial* m);
	
		std::vector<Mesh> m_meshes;
		std::string m_directory;
	};

}