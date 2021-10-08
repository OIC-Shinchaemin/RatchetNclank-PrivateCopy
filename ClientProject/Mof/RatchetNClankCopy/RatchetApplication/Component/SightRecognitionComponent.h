#ifndef RATCHET_COMPONENT_SIGHT_RECOGNITION_COMPONENT_H
#define RATCHET_COMPONENT_SIGHT_RECOGNITION_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>
#include <vector>

#include "../Effect/EffectEmitter.h"

struct ContactEnemyMessage {
};
using ContactEnemyMessageSubject = base::core::Observable<const ContactEnemyMessage&>;
using ContactEnemyMessageListener = base::core::Observer<const  ContactEnemyMessage&>;

struct FindEnemyMessage {
};
using FindEnemyMessageSubject = base::core::Observable<const FindEnemyMessage&>;
using FindEnemyMessageListener = base::core::Observer<const  FindEnemyMessage&>;


namespace ratchet::component::player { class PlayerComponent; }
namespace ratchet::component::enemy { class EnemyComponent; }
namespace ratchet::component {
class SightRecognitionComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! ����
    float _range;
    //! �F��
    std::vector<std::weak_ptr<ratchet::actor::Actor>> _recognized;
    //! �F����
    int _recognizing_count;
    //std::vector<std::string> _recognizing;
    //! �L����
    std::weak_ptr<ratchet::component::player::PlayerComponent> _player_com;
    //! �L����
    std::weak_ptr<ratchet::component::enemy::EnemyComponent> _ENEMY_com;
    //! �G�t�F�N�g
    //std::shared_ptr<effect::EffectEmitter> _effect_emitter;
    //! ��G
    bool _contact_enemy;
    //! �ʒm
    ContactEnemyMessageSubject _contact_enemy_message_subject;
    //! �ʒm
    FindEnemyMessageSubject _find_enemy_message_subject;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void SenseEffectEmit(void);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority">�D��x</param>
    SightRecognitionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    SightRecognitionComponent(const SightRecognitionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SightRecognitionComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto  GetContactEnemyMessageSubject(void) {
        return &this->_contact_enemy_message_subject;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetFindEnemyMessageSubject(void) {
        return &this->_find_enemy_message_subject;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<std::weak_ptr<ratchet::actor::Actor>>& GetRecognized(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_SIGHT_RECOGNITION_COMPONENT_H