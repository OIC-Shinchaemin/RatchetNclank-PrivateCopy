#ifndef RATCHET_BULLET_ITEM_H
#define RATCHET_BULLET_ITEM_H


#include "../../Actor.h"

#include "Base/Core/Observable.h"
#include "../../Game/GameSystem/WeaponSystem.h"


namespace ratchet {
class BulletItem : public ratchet::Actor {
    using super = ratchet::Actor;
public:
    enum class Type {
        BombGlove,
        Pyrocitor,
        Blaster,
        CountMax
    };
    struct Param : public super::Param {
        //! �ړ�
        Mof::CVector3 speed;
        //! ��]
        Mof::CVector3 angle;
        //! �^�C�v
        Type type;
        //! ��
        int count = 0;
    };
private:
    //! �ړ�
    Mof::CVector3 _init_speed;
    //! ��]
    Mof::CVector3 _init_angle;
    //! �^�C�v
    Type _item_type;
    //! ��
    int _item_count;
    //! �ʒm�p
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&> _weapon_system_subject;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BulletItem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BulletItem();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetTypeName(ratchet::BulletItem::Type type) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&>* GetWeaponSystemSubject(void);
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::Actor::Param* param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_BULLET_ITEM_H