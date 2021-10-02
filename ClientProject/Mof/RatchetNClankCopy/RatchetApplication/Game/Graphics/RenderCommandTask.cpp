#include "RenderCommandTask.h"


ratchet::game::graphics::RenderCommandTask::RenderCommandTask(std::size_t layer) :
    _commands(layer) {
}

bool ratchet::game::graphics::RenderCommandTask::Push(const std::shared_ptr<ratchet::game::graphics::RenderCommand>& command, std::uint32_t layer) {
    if (layer >= _commands.size()) {
        _ASSERT_EXPR(false, L"描画コマンドをレイヤー外に追加しようとしています");
        return false;
    } // if
    _commands[layer].push_back(command);
    return true;
}

bool ratchet::game::graphics::RenderCommandTask::Execute(void) {
    for (auto& layer : _commands) {
        for (auto& command : layer) {
            command->Execute();
        } // for
    } // for
    return true;
}