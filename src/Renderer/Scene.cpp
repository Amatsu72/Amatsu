#include "../pch.h"
#include "Scene.h"
#include <imgui.h>
#include "Renderer.h"

#include "../Event/KeyEvent.h"

#include <GLFW/glfw3.h>

namespace Engine {

	Scene::Scene() :m_camera_controller(16.0f / 9.0f, 0.1f, 100.0f), m_width(1280), m_height(720)
	{
		//floor vao
		float planeVertices[] = {
			-20.5f, -10.1f, -50.5f,  0.0f, 0.0f,
			 20.5f, -10.1f, -50.5f,  2.0f, 0.0f,
			 20.5f, -10.1f, -10.5f,  2.0f, 2.0f,
			 20.5f, -10.1f, -10.5f,  2.0f, 2.0f,
			-20.5f, -10.1f, -10.5f,  0.0f, 2.0f,
			-20.5f, -10.1f, -50.5f,  0.0f, 0.0f
		};
		auto floor_vertex_array = VertexArrayLibrary::load("floor");
		std::shared_ptr<VertexBuffer> vertex_buffer = VertexBuffer::create(planeVertices, sizeof(planeVertices));
		vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		floor_vertex_array->add_vertex_buffer(vertex_buffer);
		
		point_light_positions[0] = glm::vec3(0.7f, 0.2f, 2.0f);
		point_light_positions[1] = glm::vec3(2.3f, -3.3f, -4.0f);
		point_light_positions[2] = glm::vec3(-4.0f, 2.0f, -12.0f);
		point_light_positions[3] = glm::vec3(0.0f, 0.0f, -3.0f);

		//directional light
		directional_light = DirectionalLight::create(direcitonal_color, glm::vec3(1.0f, 0, 0), 0.1f, 0.7f, 1.0f);
		for (int i = 0; i < 4; ++i)
			point_lights.push_back(PointLight::create(glm::vec3(1.0f), point_light_positions[i], 0.1f, 0.5f, 1.0f));
		//spot light
		spot_light = SpotLight::create(glm::vec3(1.0),
			m_camera_controller.get_camera().get_position(),
			m_camera_controller.get_camera().get_front(),
			0.1f, 0.5f, 1.0f, glm::cos(glm::radians(12.5f)),
			glm::cos(glm::radians(12.5f + 5.0f)));
		//point light
		float light_vertices[] = {
			-0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			-0.1f,  0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,

			-0.1f, -0.1f,  0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,
			-0.1f, -0.1f,  0.1f,

			-0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,
			-0.1f, -0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,

			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,

			-0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f, -0.1f,  0.1f,
			-0.1f, -0.1f,  0.1f,
			-0.1f, -0.1f, -0.1f,

			-0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f, -0.1f
		};
		auto point_vertex_array = VertexArrayLibrary::load("point");
		std::shared_ptr<VertexBuffer> point_vertex_buffer = VertexBuffer::create(light_vertices, sizeof(light_vertices));
		point_vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"}
			});
		point_vertex_array->add_vertex_buffer(point_vertex_buffer);

		//cube
		float cube_vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};
		auto cube_vertex_array = VertexArrayLibrary::load("cube");
		std::shared_ptr<VertexBuffer> cube_vertex_buffer = VertexBuffer::create(cube_vertices, sizeof(cube_vertices));
		cube_vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"}
			});
		cube_vertex_array->add_vertex_buffer(cube_vertex_buffer);

		//grass
		float grassVertices[] = {
			-1.5f, -1.5f, -0.5f,  0.0f, 0.0f,
			 1.5f, -1.5f, -0.5f,  1.0f, 0.0f,
			 1.5f,  1.5f, -0.5f,  1.0f, 1.0f,
			 1.5f,  1.5f, -0.5f,  1.0f, 1.0f,
			-1.5f,  1.5f, -0.5f,  0.0f, 1.0f,
			-1.5f, -1.5f, -0.5f,  0.0f, 0.0f
		};
		auto grass_vertex_array = VertexArrayLibrary::load("grass");
		std::shared_ptr<VertexBuffer> grass_vertex_buffer = VertexBuffer::create(grassVertices, sizeof(grassVertices));
		grass_vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		grass_vertex_array->add_vertex_buffer(grass_vertex_buffer);

		vegetation[0] = glm::vec3(-10.5f, -8.5f, -30.48f);
		vegetation[1] = glm::vec3(12.5f,  -8.5f, -39.51f);
		vegetation[2] = glm::vec3(10.0f,  -8.5f, -38.7f);
		vegetation[3] = glm::vec3(-5.3f,  -8.5f, -32.3f);
		vegetation[4] = glm::vec3(7.5f,   -8.5f, -30.6f);

		//windows
		glm::vec3 window_position[3];
		window_position[0] = glm::vec3(-10.5f, -8.5f, -15.48f);
		window_position[1] = glm::vec3(12.5f, -8.5f, -25.51f);
		window_position[2] = glm::vec3(10.0f, -8.5f, -20.7f);
		for (unsigned int i = 0; i < 3; i++)
		{
			float distance = glm::length(m_camera_controller.get_camera().get_position() - window_position[i]);
			sorted[distance] = window_position[i];
		}

		//shaders
		auto floor_shader = ShaderLibrary::load("../../../../assets/shaders/Texture.glsl");
		auto phong_shader = ShaderLibrary::load("../../../../assets/shaders/Phong.glsl");
		auto blin_shader = ShaderLibrary::load("../../../../assets/shaders/BlinnPhong.glsl");
		auto light_shader = ShaderLibrary::load("../../../../assets/shaders/Light.glsl");
		auto outlining_shader = ShaderLibrary::load("../../../../assets/shaders/Outlining.glsl");
		auto cube_shader = ShaderLibrary::load("../../../../assets/shaders/Reflect.glsl");
		auto wall_shader = ShaderLibrary::load("../../../../assets/shaders/NormalMap.glsl");

		std::dynamic_pointer_cast<OpenGLShader>(light_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(light_shader)->set_float4("u_color", glm::vec4(1.0f));
		std::dynamic_pointer_cast<OpenGLShader>(floor_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(floor_shader)->set_int("u_Texture", 0);
		std::dynamic_pointer_cast<OpenGLShader>(cube_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(cube_shader)->set_int("u_Skybox", 0);
		std::dynamic_pointer_cast<OpenGLShader>(wall_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(wall_shader)->set_int("u_DiffuseMap", 0);
		std::dynamic_pointer_cast<OpenGLShader>(wall_shader)->set_int("u_NormalMap", 1);
		//textures
		TextureLibrary::load("../../../../assets/textures/marble.jpg");
		TextureLibrary::load("../../../../assets/textures/grass.png");
		TextureLibrary::load("../../../../assets/textures/window.png");
		TextureLibrary::load("../../../../assets/textures/brickwall/brickwall.jpg");
		//model
		model = Model::create("../../../../assets/models/nanosuit/nanosuit.obj");
		planet = Model::create("../../../../assets/models/planet/planet.obj");
		rock = Model::create("../../../../assets/models/rock/rock.obj");
		//draw_outlining
		RenderCommand::set_stencil_test(true);
		RenderCommand::set_stencil_func(RenderAPI::Func::NOTEQUAL, 1, 0xFF);
		RenderCommand::set_stencil_op(RenderAPI::Op::KEEP, RenderAPI::Op::KEEP, RenderAPI::Op::REPLACE);

		//frame buffer
		frame_buffer = FrameBuffer::create(m_width, m_height);
		auto texture_attachment = Texture2D::create_attachment(m_width, m_height, use_msaa);
		frame_buffer->attach(texture_attachment);
		auto render_buffer = RenderBuffer::create(m_width, m_height, use_msaa);
		render_buffer->attach_frame_buffer();
		frame_buffer->check();

		//quad
		float quadVertices[] = { 
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
		
			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};
		auto quad_vertex_array = VertexArrayLibrary::load("quad");
		std::shared_ptr<VertexBuffer> quad_vertex_buffer = VertexBuffer::create(quadVertices, sizeof(quadVertices));
		quad_vertex_buffer->set_layout({
			{ShaderDataType::Float2, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		quad_vertex_array->add_vertex_buffer(quad_vertex_buffer);
		
		auto screen_shader = ShaderLibrary::load("../../../../assets/shaders/FrameBuffer.glsl");
		std::dynamic_pointer_cast<OpenGLShader>(screen_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(screen_shader)->set_int("u_ScreenTexture", 0);

		//cube map
		sky_box = CubeMap::create("../../../../assets/textures/skybox/");

		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
		auto cube_map_vertex_array = VertexArrayLibrary::load("sky_box");
		std::shared_ptr<VertexBuffer> cube_map_vertex_buffer = VertexBuffer::create(skyboxVertices, sizeof(skyboxVertices));
		cube_map_vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			});
		cube_map_vertex_array->add_vertex_buffer(cube_map_vertex_buffer);

		auto cube_map_shader = ShaderLibrary::load("../../../../assets/shaders/CubeMap.glsl");
		std::dynamic_pointer_cast<OpenGLShader>(cube_map_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(cube_map_shader)->set_int("u_Skybox", 0);
		
		//instance 
		ShaderLibrary::load("../../../../assets/shaders/instance.glsl");	

		modelMatrices = new glm::mat4[amount];
		srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
		float radius = 100.0;
		float offset = 25.0f;
		for (unsigned int i = 0; i < amount; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			// 1. translation: displace along circle with 'radius' in range [-offset, offset]
			float angle = (float)i / (float)amount * 360.0f;
			float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float x = sin(angle) * radius + displacement;
			displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
			displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float z = cos(angle) * radius + displacement;
			model = glm::translate(model, glm::vec3(x, y, z));

			// 2. scale: Scale between 0.05 and 0.25f
			float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
			model = glm::scale(model, glm::vec3(scale));

			// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
			float rotAngle = static_cast<float>((rand() % 360));
			model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

			// 4. now add to list of matrices
			modelMatrices[i] = model;
		}
		std::shared_ptr<VertexBuffer> instance_buffer = VertexBuffer::create(modelMatrices, amount * sizeof(glm::mat4));
		instance_buffer->set_layout({ {{ShaderDataType::Mat4, "instanceMatrix"}} });
		rock->add_instance_buffer(instance_buffer);
		//uniform buffer
		uniform_buffer = UniformBuffer::create({ {ShaderDataType::Mat4, "u_View"},{ShaderDataType::Mat4, "u_Projection"} }, 0);
		uniform_buffer->set_mat4(m_camera_controller.get_projection(), 0);
			
		//shadow mapping
		prepare_shadow_mapping();
	}

	void Scene::on_update(Timestep ts)
	{
		m_camera_controller.update(ts);
		
		if (use_frame_buffer)
		{
			frame_buffer->bind();
			RenderCommand::set_depth_test(true);
			RenderCommand::set_clear_color(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			RenderCommand::clear(true, true, false);
		}
		else
		{
			RenderCommand::set_clear_color(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			RenderCommand::clear(true, true, true);
		}

		//uniform buffer object
		uniform_buffer->set_mat4(m_camera_controller.get_camera().get_view_matrix(), sizeof(glm::mat4));
	
		Renderer::begin_scene(m_camera_controller.get_camera(), directional_light, point_lights, spot_light);
		//light setting
		directional_light->set_color(direcitonal_color);
		directional_light->set_direction(direction);
		
		if(use_spot_light)
		{
			spot_light->set_position(m_camera_controller.get_camera().get_position());
			spot_light->set_direction(m_camera_controller.get_camera().get_front());
		}
			
		if (draw_outlining)//dont't write the floor to the stencil buffer
			RenderCommand::set_stencil_mask(0x00);

		//draw floor
		auto shader = ShaderLibrary::get("Texture");
		auto texture = TextureLibrary::get("marble");
		texture->bind();
		auto floor_va = VertexArrayLibrary::get("floor");
		Renderer::submit(shader, floor_va, glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 2.0f)));
		//wall
		//glm::mat4 wall_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, -30, -40));
		//wall_trans = glm::rotate(wall_trans, glm::radians(90.0f), glm::normalize(glm::vec3(1.0, 0.0, 0.0)));
		//auto wall_shader = ShaderLibrary::get("NormalMap");
		//std::dynamic_pointer_cast<OpenGLShader>(wall_shader)->bind();
		//std::dynamic_pointer_cast<OpenGLShader>(wall_shader)->set_float3("u_lightPos", light_pos);

		//auto wall = TextureLibrary::get("brickwall");
		//wall->bind();
		//
		//Renderer::submit(shader, floor_va, wall_trans);
		if (draw_outlining)
		{
			RenderCommand::set_stencil_func(RenderAPI::Func::ALWAYS, 1, 0xFF);
			RenderCommand::set_stencil_mask(0xFF);
		}
		//draw model
		std::shared_ptr<Shader> model_shader;

		if(blinn)
			model_shader = ShaderLibrary::get("BlinnPhong");		
		else
			model_shader = ShaderLibrary::get("Phong");
			
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
		Renderer::submit(*model, model_shader, trans, true);
		Renderer::submit(*planet, model_shader, glm::translate(glm::mat4(1.0), glm::vec3(10, 0, -30)));

		if (draw_outlining) //draw outlining
		{
			RenderCommand::set_stencil_func(RenderAPI::Func::NOTEQUAL, 1, 0xFF);
			RenderCommand::set_stencil_mask(0x00);
			RenderCommand::set_depth_test(false);
			auto outlining_shader = ShaderLibrary::get("Outlining");
			Renderer::submit(*model, outlining_shader, glm::scale(trans, glm::vec3(1.03f, 1.03f, 1.03f)));
		}
		RenderCommand::set_stencil_mask(0xFF);
		RenderCommand::set_stencil_func(RenderAPI::Func::ALWAYS, 0, 0xFF);
		RenderCommand::set_depth_test(true);		

		//instance 
		if (instance)
		{
			auto instance_shader = ShaderLibrary::get("instance");
			Renderer::submit_instance(*rock, instance_shader, amount, false);
		}
		//draw point light
		if(use_point_light)
		{
			auto light_shader = ShaderLibrary::get("Light");
			auto point_va = VertexArrayLibrary::get("point");
			for (int i = 0; i < 4; ++i)
			{
				Renderer::submit(light_shader, point_va, glm::translate(glm::mat4(1.0f), point_light_positions[i]));
			}
		}
		//draw reflect box
		if(flect_box)
		{
			auto cube_shader = ShaderLibrary::get("Reflect");
			auto cube_va = VertexArrayLibrary::get("cube");
			Renderer::submit(cube_shader, cube_va);
			std::dynamic_pointer_cast<OpenGLShader>(cube_shader)->set_float3("u_CameraPosition", m_camera_controller.get_camera().get_position());
		}

		//draw grass
		auto grass_texture = TextureLibrary::get("grass");
		auto grass_va = VertexArrayLibrary::get("grass");
		grass_texture->bind();
		for (int i = 0; i < 5; ++i)
			Renderer::submit(shader, grass_va, glm::translate(glm::mat4(1.0f), vegetation[i]));

		//draw window
		auto window_texture = TextureLibrary::get("window");
		auto window_va = VertexArrayLibrary::get("grass");
		window_texture->bind();
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
			Renderer::submit(shader, window_va, glm::translate(glm::mat4(1.0f), it->second));

		//batch render
		if (batch_render)
		{
			std::vector<glm::vec3> box_position;
			box_position.push_back(glm::vec3(2.0f, 5.0f, -15.0f));
			box_position.push_back(glm::vec3(-1.5f, -2.2f, -2.5f));
			box_position.push_back(glm::vec3(-3.8f, -2.0f, -12.3f));
			box_position.push_back(glm::vec3(2.4f, -0.4f, -3.5f));
			box_position.push_back(glm::vec3(-1.7f, 3.0f, -7.5f));
			box_position.push_back(glm::vec3(1.3f, -2.0f, -2.5f));
			box_position.push_back(glm::vec3(1.5f, 2.0f, -2.5f));
			box_position.push_back(glm::vec3(1.5f, 0.2f, -1.5f));
			box_position.push_back(glm::vec3(-1.3f, 1.0f, -1.5f));
			Renderer::submit_batch(box_position);
		}

		//skybox
		if (use_sky_box)
		{
			auto cube_map_shader = ShaderLibrary::get("CubeMap");
			auto sky_va = VertexArrayLibrary::get("sky_box");
			sky_box->bind();
			RenderCommand::set_depth_func(RenderAPI::Func::LEQUAL);
			RenderCommand::set_depth_mask(false);
			Renderer::submit(cube_map_shader, sky_va, glm::translate(glm::mat4(1.0f), m_camera_controller.get_camera().get_position()));
			RenderCommand::set_depth_func(RenderAPI::Func::LESS);
			RenderCommand::set_depth_mask(true);
		}

		//frame_buffer
		if (use_frame_buffer)
		{
			frame_buffer->blit();
			
			if (!use_msaa)
			{
				auto quad_va = VertexArrayLibrary::get("quad");
				frame_buffer->unbind();
				RenderCommand::set_depth_test(false);
				RenderCommand::set_clear_color(glm::vec4(1.0f));
				RenderCommand::clear(true, false, false);
				frame_buffer->texture_bind();
				auto screen_shader = ShaderLibrary::get("FrameBuffer");
				//RenderCommand::set_line_mode();  
				Renderer::submit(screen_shader, quad_va);
			}
		}

		//draw_depth_scene();
		Renderer::end_scene();	
	}

	void Scene::ui_render()
	{
		static bool show = true;
		//ImGui::ShowDemoWindow(&show);
		ImGui::Begin("Settings");
		ImGui::Text("Press 'R' to Refresh scene!");
		ImGui::ColorEdit3("direcitonal Color", glm::value_ptr(direcitonal_color));
		ImGui::DragFloat3("model position", glm::value_ptr(position));
		ImGui::DragFloat3("direction", glm::value_ptr(direction));
		ImGui::Checkbox("show sky box", &use_sky_box);
		ImGui::Checkbox("show bacth render", &batch_render);
		ImGui::Checkbox("show outlining", &draw_outlining);
		ImGui::Checkbox("use frame buffer", &use_frame_buffer);
		ImGui::Checkbox("instance", &instance);
		ImGui::Checkbox("MSAA", &use_msaa);
		ImGui::Checkbox("BlinnPhong", &blinn);
		ImGui::DragFloat3("light pos", glm::value_ptr(light_pos));
		ImGui::End();
	}

	void Scene::on_event(Event& event)
	{
		
		if (event.get_event_type() == EventType::KeyPressed)
		{
			KeyPressedEvent& e = (KeyPressedEvent&)event;
			if (e.get_key_code() == KeyCode::R)
			{
				frame_buffer = FrameBuffer::create(m_width, m_height);
				//frame_buffer->set_width_height(m_width, m_height);
				auto texture_attachment = Texture2D::create_attachment(m_width, m_height, use_msaa);
				frame_buffer->attach(texture_attachment);
				auto render_buffer = RenderBuffer::create(m_width, m_height, use_msaa);
				render_buffer->attach_frame_buffer();
				frame_buffer->check();
				frame_buffer->unbind();
			}
		}		
		if (event.get_event_type() == EventType::WindowResize)
		{
			m_width = dynamic_cast<WindowResizeEvent&>(event).get_width();
			m_height = dynamic_cast<WindowResizeEvent&>(event).get_height();	
		}
		m_camera_controller.on_event(event);
		
	}

	void Scene::draw_depth_scene()
	{
		RenderCommand::set_clear_color(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		//RenderCommand::clear(true, true, false);

		//render depth map
		float near_plane = 1.0f, far_plane = 7.5;

		glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4 view = glm::lookAt(light_pos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		auto depth_shader = ShaderLibrary::get("Depth");
		std::dynamic_pointer_cast<OpenGLShader>(depth_shader)->set_mat4("u_Projection", projection);
		std::dynamic_pointer_cast<OpenGLShader>(depth_shader)->set_mat4("u_View", view);	
		RenderCommand::set_viewport(0, 0, m_width, m_height);
		depth_frame_buffer->bind();
		RenderCommand::clear(false, true, false);
		auto wood_texture = TextureLibrary::get("wood");
		wood_texture->bind();

		auto floor_va = VertexArrayLibrary::get("plane");
		Renderer::submit(depth_shader, floor_va, glm::mat4(1.0f));

		auto va = VertexArrayLibrary::get("xxx");
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
		model = glm::scale(model, glm::vec3(0.5f));
		Renderer::submit(depth_shader, va, model);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
		model = glm::scale(model, glm::vec3(0.5f));
		Renderer::submit(depth_shader, va, model);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
		model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(0.25));
		Renderer::submit(depth_shader, va, model);
		//depth_frame_buffer->unbind();
		
		RenderCommand::set_viewport(0, 0, m_width, m_height);
		RenderCommand::clear(true, true, false);

		////render scene
		//auto shadow_map_shader = ShaderLibrary::get("ShadowMapping");
		//std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->set_mat4("u_Projection", projection);
		//std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->set_mat4("u_View", view);
		//std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->set_mat4("u_LightSpace", projection * view);
		//std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->set_float3("u_ViewPosition", m_camera_controller.get_camera().get_position());
		//std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->set_float3("u_LightPos", light_pos);
		//box_texture->bind(0);
		//depth_frame_buffer->texture_bind(1);
		//
		//Renderer::submit(shadow_map_shader, floor_va, glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 2.0f)));
		//Renderer::submit(shadow_map_shader, va, glm::translate(glm::mat4(1.0), point_light_positions[0]));
		//Renderer::submit(shadow_map_shader, va, glm::translate(glm::mat4(1.0), point_light_positions[1]));
		//Renderer::submit(shadow_map_shader, va, glm::translate(glm::mat4(1.0), point_light_positions[2]));
		//Renderer::submit(shadow_map_shader, va, glm::translate(glm::mat4(1.0), point_light_positions[3]));
		
		//use depth map	
		auto quad_va = VertexArrayLibrary::get("yyy");		
		auto test_quad_shader = ShaderLibrary::get("TestQuad");
		test_quad_shader->bind();
		test_quad_shader->set_float("u_near", near_plane);
		test_quad_shader->set_float("u_far", far_plane);
		depth_frame_buffer->texture_bind();
		Renderer::submit(test_quad_shader, quad_va);
	}

	void Scene::prepare_shadow_mapping()
	{
		//load shader
		auto test_quad = ShaderLibrary::load("../../../../assets/shaders/TestQuad.glsl");
		std::dynamic_pointer_cast<OpenGLShader>(test_quad)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(test_quad)->set_int("u_DepthMap", 0);

		ShaderLibrary::load("../../../../assets/shaders/Depth.glsl");

		auto shadow_map_shader = ShaderLibrary::load("../../../../assets/shaders/ShadowMapping.glsl");
		std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->set_int("u_Texture", 0);
		std::dynamic_pointer_cast<OpenGLShader>(shadow_map_shader)->set_int("u_ShadowMap", 1);
		
		//floor
		float planeVertices[] = {
			// positions            // normals         // texcoords
			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
			 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
		};

		auto plane_va = VertexArrayLibrary::load("plane");
		std::shared_ptr<VertexBuffer> plane_vb = VertexBuffer::create(planeVertices, sizeof(planeVertices));
		plane_vb->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		plane_va->add_vertex_buffer(plane_vb);
		//cube
		float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			 // bottom face
			 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 // top face
			 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			  1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
		};
		auto cube_va = VertexArrayLibrary::load("xxx");
		std::shared_ptr<VertexBuffer> cube_vb = VertexBuffer::create(vertices, sizeof(vertices));
		cube_vb->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		cube_va->add_vertex_buffer(cube_vb);
		//quad
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		auto quad_va = VertexArrayLibrary::load("yyy");
		std::shared_ptr<VertexBuffer> quad_vb = VertexBuffer::create(quadVertices, sizeof(quadVertices));
		quad_vb->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		quad_va->add_vertex_buffer(quad_vb);
		//texture
		TextureLibrary::load("../../../../assets/textures/wood.png");
		//fbo
		depth_frame_buffer = FrameBuffer::create(m_width, m_height);
		auto depth_map = Texture2D::create_depth_map(m_width, m_height);
		depth_frame_buffer->attach(depth_map);
		depth_frame_buffer->check();
		depth_frame_buffer->unbind();
	}
}