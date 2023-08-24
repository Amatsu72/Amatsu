#include "../pch.h"
#include "Model.h"

namespace Engine {
	
	void Model::load_model(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		m_directory = path.substr(0, path.find_last_of('/'));

		process_node(scene->mRootNode, scene);
	}

	void Model::process_node(aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(process_mesh(mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; ++i)
		{
			process_node(node->mChildren[i], scene);
		}
	}

	Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indices;
		std::shared_ptr<Material> material;

		for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;
			aiVector3D& ai_vertex = mesh->mVertices[i];
			vertex.Position = { ai_vertex.x, ai_vertex.y, ai_vertex.z };
			aiVector3D& ai_normal = mesh->mNormals[i];
			vertex.Normal = { ai_normal.x, ai_normal.y, ai_normal.z };
			if (mesh->mTextureCoords[0])  // has tex coord?
			{
				aiVector3D& ai_tex_coord = mesh->mTextureCoords[0][i];
				vertex.TexCoord = { ai_tex_coord.x, ai_tex_coord.y };
			}
			else
			{
				vertex.TexCoord = { 0.0f, 0.0f };
			}
			vertices.push_back(vertex);
		}

		for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace& face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j += 3)
			{
				Index index = { face.mIndices[j] ,face.mIndices[j + 1] ,face.mIndices[j + 2] };
				indices.push_back(index);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* ai_material = scene->mMaterials[mesh->mMaterialIndex];
			material = load_material(ai_material);
		}
		return Mesh(vertices, indices, material);
	}

	std::shared_ptr<Material> Model::load_material(aiMaterial* m)
	{
		std::shared_ptr<Material> material = std::make_shared<Material>();
		
		constexpr uint32_t tex_type_num = 2;
		std::array<aiTextureType, tex_type_num> ai_types = { aiTextureType_DIFFUSE, aiTextureType_SPECULAR };
		std::array<Texture::Type, tex_type_num> types = { Texture::Type::Diffuse,Texture::Type::Specular };

		for (uint32_t tex_type_index = 0; tex_type_index < tex_type_num; ++tex_type_index)
		{
			aiTextureType ai_type = ai_types[tex_type_index];
			Texture::Type type = types[tex_type_index];	

			for (uint32_t i = 0; i < m->GetTextureCount(ai_type); ++i)
			{
				aiString str;
				m->GetTexture(ai_type, i, &str);
				std::string path = m_directory + '/' + str.C_Str();

				std::string temp = str.C_Str();
				auto last_dot = temp.rfind('.');
				auto count = last_dot == std::string::npos ? temp.size() : last_dot;
				if (!TextureLibrary::exists(temp.substr(0,count)))
				{
					std::shared_ptr<Texture2D> texture = TextureLibrary::load(path);
					material->set_texture_map(texture, type);
				}
			}
		}
		return material;
	}
	
}