#ifndef RATCHET_ACTOR_WEAPON_WEAPON_H
#define RATCHET_ACTOR_WEAPON_WEAPON_H


#include "../Actor.h"


namespace ratchet::actor::weapon {
class Weapon : public ::ratchet::actor::Actor {
    using super = ::ratchet::actor::Actor;
private:
    //! 装備中
    bool _equipmented;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Weapon();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Weapon();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="flag"></param>
    void SetEquipmentedFlag(bool flag) {
        this->_equipmented = flag;
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEquipmented(void) const {
        return this->_equipmented;
    }
    virtual void Scaling(void) {
    }
};
}
#endif // !RATCHET_ACTOR_WEAPON_WEAPON_H