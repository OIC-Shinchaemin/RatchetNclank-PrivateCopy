#ifndef RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H
#define RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H


#include "RenderCommand.h"

#include <memory>

#include <Mof.h>

#include "../../GameDefine.h"


namespace ratchet::game::graphics {
    class RenderAnimationMeshCommand : public ratchet::game::graphics::RenderCommand {
    private:
        //! メッシュ
        std::weak_ptr<Mof::CMeshContainer> _mesh;
        //! アニメーション
        Mof::LPMeshMotionController _motion;
        //! 表示色
        Mof::CVector4 _color;
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="rect"></param>
        /// <param name="col"></param>
        RenderAnimationMeshCommand(const std::shared_ptr<Mof::CMeshContainer> ptr, Mof::LPMeshMotionController motion, const Mof::CVector4& color);
        /// <summary>
        /// 実行
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        virtual bool Execute(void) override;
    };
}
#endif // !RATCHET_GAME_GRAPHICS_RENDER_ANIMATION_MESH_COMMAND_H