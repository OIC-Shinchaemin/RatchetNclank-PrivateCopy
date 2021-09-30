#ifndef RATCHET_GAME_GRAPHICS_RENDER_MESH_COMMAND_H
#define RATCHET_GAME_GRAPHICS_RENDER_MESH_COMMAND_H


#include "RenderCommand.h"

#include <Mof.h>


namespace ratchet::game::graphics {
class RenderMeshCommand : public ratchet::game::graphics::RenderCommand {
private:
    //! ���b�V��
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! �\���F
    Mof::CVector4 _color;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="rect"></param>
    /// <param name="col"></param>
    RenderMeshCommand(const std::shared_ptr<Mof::CMeshContainer> ptr, const Mof::CVector4& color);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Execute(void) override;
};
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H