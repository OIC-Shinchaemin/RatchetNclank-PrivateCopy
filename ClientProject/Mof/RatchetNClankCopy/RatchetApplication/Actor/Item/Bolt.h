#ifndef RATCHET_ACTOR_ITEM_BOLT_H
#define RATCHET_ACTOR_ITEM_BOLT_H


#include "../Actor.h"

#include "Base/Core/Observable.h"


namespace ratchet::actor::item {
class Bolt : public ratchet::actor::Actor {
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
    Bolt();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Bolt();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<int>* GetMoneySubject(void);
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
#endif // !RATCHET_ACTOR_ITEM_BOLT_H