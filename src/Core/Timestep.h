#pragma once

namespace Engine {

	class Timestep
	{
	public:
		Timestep(float time)
			:m_time(time) {}
		operator float() const { return m_time; }
		float getSeconds() const { return m_time; }
		float getMilliseconds() const { return m_time * 1000.0f; }

	private:
		float m_time;
	};

}