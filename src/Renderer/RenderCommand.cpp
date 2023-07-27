#include "../pch.h"
#include "RenderCommand.h"
#include "../Paltform/OpenGL/OpenGLRenderAPI.h"

namespace Engine {

	RenderAPI* RenderCommand::s_renderAPI = new OpenGLRenderAPI;

}