#ifndef RATCHET_GAME_GRAPHICS_RENDER_COMMAND_TASK_H
#define RATCHET_GAME_GRAPHICS_RENDER_COMMAND_TASK_H


#include "RenderCommand.h"


namespace ratchet::game::graphics {
enum class RenderLayer {
    Opacity3D,
    Transparent3D,
    CountMax
};
class RenderCommandTask {
protected:
    //! コマンドキュー
    std::vector<ratchet::game::graphics::RenderCommandList> _commands;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="layerCount"></param>
    RenderCommandTask(std::size_t layer = static_cast<std::size_t>(ratchet::game::graphics::RenderLayer::CountMax));
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="command"></param>
    /// <param name="layer"></param>
    /// <returns></returns>
    bool Push(const std::shared_ptr<ratchet::game::graphics::RenderCommand>& command, std::uint32_t layer);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Execute(void);
    //int GetLayerCount(void) const {
        //return _commands.size();
    //}
};
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_COMMAND_TASK_H