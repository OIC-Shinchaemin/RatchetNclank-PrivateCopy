#ifndef RATCHET_ACTOR_ITEM_NANOTECH_ITEM_H
#define RATCHET_ACTOR_ITEM_NANOTECH_ITEM_H


#include "../Actor.h"

#include "Base/Core/Observable.h"


namespace ratchet {
namespace actor {
namespace item {
class NanotechItem : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    struct Param : public super::Param {
        //! 移動
        Mof::CVector3 speed;
        //! 回転
        Mof::CVector3 angle;
    };
private:
    //! 移動
    Mof::CVector3 _init_speed;
    //! 回転
    Mof::CVector3 _init_angle;
    //! 通知用
    base::core::Observable<int> _money_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NanotechItem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NanotechItem();
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
};
}
}
}
#endif // !RATCHET_ACTOR_ITEM_NANOTECH_ITEM_H