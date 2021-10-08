#ifndef RATCHET_ACTOR_CHARACTER_ENEMY_H
#define RATCHET_ACTOR_CHARACTER_ENEMY_H


#include "Character.h"

#include "../../Game/GameSystem/GameQuest.h"
#include "../../Effect/EffectEmitter.h"
#include "../../Effect/EffectContainer.h"


namespace ratchet::actor::character {
class Enemy : public ratchet::actor::character::Character {
    using super = ratchet::actor::character::Character;
public:
    enum class MotionType {
        IdleWait,
        MoveRun,
        AttackOne,
        Damage,
        CountMax,
    };
private:
    //! �ʒm�p
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&> _quest_subject;
    //! �G�t�F�N�g
    std::weak_ptr<effect::EffectContainer>_effect_container;
    //! �G�t�F�N�g
    //std::shared_ptr<ratchet::effect::EffectEmitter> _effect_emitter;
    //! �G�t�F�N�g
    //std::shared_ptr<ratchet::effect::EffectEmitter> _star_effect_emitter;
    //! �G�t�F�N�g
    ratchet::effect::EffectEmitterHolder _effect_emitter_holder;
    //! �ȈՉe
    std::shared_ptr<actor::Actor> _shadow_child_actor;

    /// <summary>
    /// ��ԕύX
    /// </summary>
    virtual void Activate(void) override;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Enemy();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    //std::shared_ptr<ratchet::effect::EffectEmitter> GetEffectEmitter(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    //std::shared_ptr<ratchet::effect::EffectEmitter> GetStarEffectEmitter(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    auto GetEffectEmitterHolder(void) {
        return &this->_effect_emitter_holder;
    };
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// �A�C�e��
    /// </summary>
    /// <param name=""></param>
    void GenerateDropItem(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_ENEMY_H