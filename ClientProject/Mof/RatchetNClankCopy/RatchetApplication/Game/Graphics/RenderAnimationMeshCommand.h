#ifndef RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H
#define RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H


#include "RenderCommand.h"

#include <Mof.h>


namespace ratchet::game::graphics {
class RenderRectangleCommand : public ratchet::game::graphics::RenderCommand {
private:
    //! 矩形
    Mof::CRectangle	_rectangle;
    //! 色
    unsigned int _color;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="l"></param>
    /// <param name="t"></param>
    /// <param name="r"></param>
    /// <param name="b"></param>
    /// <param name="col"></param>
    RenderRectangleCommand(float l, float t, float r, float b, unsigned int col);    
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="rect"></param>
    /// <param name="col"></param>
    RenderRectangleCommand(const Mof::CRectangle& rect, unsigned int col);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Execute(void) override;
};
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H