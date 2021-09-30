#ifndef RATCHET_GAME_GRAPHICS_RENDER_COMMAND_TASK_H
#define RATCHET_GAME_GRAPHICS_RENDER_COMMAND_TASK_H


#include "RenderCommand.h"


namespace ratchet::game::graphics {
class RenderCommandTask {
protected:
    //! �R�}���h�L���[
    std::vector<ratchet::game::graphics::RenderCommandList> _commands;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="layerCount"></param>
    RenderCommandTask(std::size_t layer);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="command"></param>
    /// <param name="layer"></param>
    /// <returns></returns>
    bool Push(const std::shared_ptr<ratchet::game::graphics::RenderCommand>& command, int layer);
    /// <summary>
    /// ���s
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