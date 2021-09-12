#ifndef RATCHET_ACTOR_GIMMICK_WALL_H
#define RATCHET_ACTOR_GIMMICK_WALL_H


#include "../Actor.h"


namespace ratchet::actor::gimmick {
class Wall : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Wall();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Wall();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_ACTOR_GIMMICK_WALL_H