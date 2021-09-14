#ifndef RATCHET_ACTOR_ITEM_BULLET_ITEM_H
#define RATCHET_ACTOR_ITEM_BULLET_ITEM_H


#include "../Actor.h"

#include "Base/Core/Observable.h"
#include "../../Game/GameSystem/WeaponSystem.h"


namespace ratchet ::actor::item {
class BulletItem : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    enum class Type {
        BombGlove,
        Pyrocitor,
        Blaster,
        CountMax
    };
    struct Param : public super::Param {
        //! 移動
        Mof::CVector3 speed;
        //! 回転
        Mof::CVector3 angle;
        //! タイプ
        Type type;
        //! 数
        int count = 0;
    };
private:
    //! 移動
    Mof::CVector3 _init_speed;
    //! 回転
    Mof::CVector3 _init_angle;
    //! タイプ
    Type _item_type;
    //! 数
    int _item_count;
    //! 通知用
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&> _weapon_system_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BulletItem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BulletItem();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetTypeName(ratchet::actor::item::BulletItem::Type type) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&>* GetWeaponSystemSubject(void);
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
#endif // !RATCHET_ACTOR_ITEM_BULLET_ITEM_H