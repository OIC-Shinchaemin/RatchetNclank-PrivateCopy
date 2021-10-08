#ifndef RATCHET_GAME_GRAPHICS_RENDER_MESH_COMMAND_H
#define RATCHET_GAME_GRAPHICS_RENDER_MESH_COMMAND_H


#include "RenderCommand.h"

#include <memory>

#include <Mof.h>

#include "../../GameDefine.h"


namespace ratchet::game::graphics {
class RenderMeshCommand : public ratchet::game::graphics::RenderCommand {
private:
    //! �g�����X�t�H�[��
    //def::Transform _transform;
    //! �g�����X�t�H�[��
    Mof::CMatrix44 _world;
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
    RenderMeshCommand(const std::shared_ptr<Mof::CMeshContainer> ptr, const Mof::CMatrix44& world, const Mof::CVector4& color);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Execute(void) override;
};
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H