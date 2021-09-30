#ifndef RATCHET_GAME_GRAPHICS_RENDER_MESH_COMMAND_H
#define RATCHET_GAME_GRAPHICS_RENDER_MESH_COMMAND_H


#include "RenderCommand.h"

#include <Mof.h>


namespace ratchet::game::graphics {
class RenderMeshCommand : public ratchet::game::graphics::RenderCommand {
private:
    //! メッシュ
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! 表示色
    Mof::CVector4 _color;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="rect"></param>
    /// <param name="col"></param>
    RenderMeshCommand(const std::shared_ptr<Mof::CMeshContainer> ptr, const Mof::CVector4& color);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Execute(void) override;
};
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H