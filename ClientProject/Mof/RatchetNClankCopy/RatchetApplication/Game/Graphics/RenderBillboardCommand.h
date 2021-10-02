#ifndef RATCHET_GAME_GRAPHICS_RENDER_BILLBOARD_COMMAND_H
#define RATCHET_GAME_GRAPHICS_RENDER_BILLBOARD_COMMAND_H


#include "RenderCommand.h"

#include <memory>

#include <Mof.h>


namespace ratchet::game::graphics {
class RenderBillboardCommand : public ratchet::game::graphics::RenderCommand {
private:
    //! �e�N�X�`��
    std::weak_ptr<Mof::CTexture> _texture;
    //! �r���{�[�h
    Mof::CMatrix44 _matrix;
    //! �F
    Mof::CVector4 _color;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="rect"></param>
    /// <param name="col"></param>
    RenderBillboardCommand(const std::shared_ptr<Mof::CTexture> ptr, const Mof::CMatrix44& matrix, const Mof::CVector4 color);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Execute(void) override;
};
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_BILLBOARD_COMMAND_H