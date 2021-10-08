#ifndef RATCHET_GAME_GRAPHICS_RENDER_COMMAND_H
#define RATCHET_GAME_GRAPHICS_RENDER_COMMAND_H


#include <memory>
#include <vector>


namespace ratchet::game::graphics {
	class RenderCommand {
	public:
		/// <summary>
		/// é¿çs
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Execute(void) = 0;
	};
	using RenderCommandPtr = std::shared_ptr<RenderCommand>;
	using RenderCommandList = std::vector<RenderCommandPtr>;
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_COMMAND_H