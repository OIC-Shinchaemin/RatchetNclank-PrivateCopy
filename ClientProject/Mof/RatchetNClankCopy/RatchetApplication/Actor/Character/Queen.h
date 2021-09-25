#ifndef RATCHET_ACTOR_CHARACTER_QUEEN_H
#define RATCHET_ACTOR_CHARACTER_QUEEN_H


#include "Character.h"


namespace ratchet::actor::character {
class Queen:
    public actor::character::Character {
    using super = actor::character::Character;
private:
    //! �C�x���g���΍ς�
    bool _event_activated;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Queen();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Queen();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ��b
    /// </summary>
    void Talk(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_QUEEN_H