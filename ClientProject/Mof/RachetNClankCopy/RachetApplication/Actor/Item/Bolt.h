#ifndef MY_BOLT_H
#define MY_BOLT_H


#include "../../Actor.h"

#include "Base/Core/Observable.h"


namespace my {
class Bolt : public my::Actor {
    using super = my::Actor;
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
    my::Observable<int> _money_subject;
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
    my::Observable<int>* GetMoneySubject(void);
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
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
};
}
#endif // !MY_BOLT_H