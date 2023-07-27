#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


namespace Engine {

	class Camera
	{
	public:
		Camera();
		~Camera() {}

		const glm::vec3& get_position() const { return m_position; }
		void set_position(const glm::vec3& position);
		void set_projection(const glm::mat4& projection_matrix);

		inline const glm::mat4& get_projection_matrix() const { return m_projection_matrix; }
		inline const glm::mat4& get_view_matrix() const { return m_view_matrix; }
		inline const glm::mat4& get_view_projection_matrix() const { return m_view_projection_matrix; }

		inline const glm::vec3& get_front() const { return m_front; }
		inline const glm::vec3& get_right() const { return m_right; }
		inline const glm::vec3& get_up() const { return m_up; }
		inline const glm::vec3& get_world_up() const { return m_world_up; }

		inline float get_yaw() const { return m_yaw; }
		inline float get_pitch() const { return m_pitch; }
		void set_yaw(float yaw);
		void set_pitch(float pitch);

	private:
		void recaculate();
		void update_camera_vectors();

		glm::mat4 m_projection_matrix;
		glm::mat4 m_view_matrix;
		glm::mat4 m_view_projection_matrix;

		glm::vec3 m_position = { 0.0f,0.0f,0.0f };
		glm::vec3 m_front = { 0.0f,0.0f,-1.0f };
		glm::vec3 m_right;
		glm::vec3 m_up;
		glm::vec3 m_world_up = { 0.0f, 1.0f, 0.0f };

		float m_yaw = -90.0;
		float m_pitch = 0.0f;
	};
}
