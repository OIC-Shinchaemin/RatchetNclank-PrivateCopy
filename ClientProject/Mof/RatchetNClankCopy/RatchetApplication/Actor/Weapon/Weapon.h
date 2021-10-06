#ifndef RATCHET_ACTOR_WEAPON_WEAPON_H
#define RATCHET_ACTOR_WEAPON_WEAPON_H


#include "../Actor.h"


namespace ratchet::actor::weapon {
class Weapon : public ::ratchet::actor::Actor {
    using super = ::ratchet::actor::Actor;
private:
    //! ������
    bool _equipmented;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Weapon();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Weapon();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="flag"></param>
    void SetEquipmentedFlag(bool flag) {
        this->_equipmented = flag;
    }
    /// <summary>
    /// ����
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