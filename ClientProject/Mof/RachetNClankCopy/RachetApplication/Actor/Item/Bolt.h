#ifndef RATCHET_BOLT_H
#define RATCHET_BOLT_H


#include "../../Actor.h"

#include "Base/Core/Observable.h"


namespace ratchet {
class Bolt : public ratchet::Actor {
    using super = ratchet::Actor;
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
    virtual bool Initialize(ratchet::Actor::Param* param) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_BOLT_H