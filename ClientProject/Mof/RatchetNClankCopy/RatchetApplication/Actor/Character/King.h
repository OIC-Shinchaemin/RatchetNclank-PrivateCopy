#ifndef RATCHET_ACTOR_CHARACTER_KING_H
#define RATCHET_ACTOR_CHARACTER_KING_H


#include "../Actor.h"

#include "../../Game/GameSystem/Text/TextSystem.h"
#include "Scarecrow.h"
#include "../../Camera/CameraController.h"
#include "../../Component/CameraComponent.h"
#include "../../Effect/EffectContainer.h"


namespace ratchet::scene {
class GameScene;
}
namespace ratchet::actor::character {
class Player;
class King :
    public actor::Actor,
    public ratchet::actor::character::ScarecrowEndMessageListener {
    using super = actor::Actor;
private:
    //! �n�e�i
    std::weak_ptr<Mof::CTexture> _question_texture;
    //! �ʒm�p
    ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
    //! �ʒm�p
    base::core::Observable<const ratchet::camera::CameraController::CameraInfo&> _player_camera_subject;
    //! �J�J�V�ǉ���Q�[���V�[��
    std::weak_ptr<ratchet::scene::GameScene> _actor_container;
    //! ��
    int _quest_index;
    //! ��
    int _quest_count;
    //! �J�����R���g���[��
    base::core::ServiceLocator<ratchet::camera::CameraController> _scarecrow_view_camera_controller;
    //! �J�����R���g���[��
    base::core::ServiceLocator<ratchet::camera::CameraController>* _player_view_camera_controller;
    //! ���_
    Mof::CVector3 _scarecrow_view_position;
    //! �G�t�F�N�g
    std::weak_ptr<effect::EffectContainer>_effect_container;
    //! �G�t�F�N�g
    std::weak_ptr<ratchet::actor::character::Player> _player;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    King();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~King();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::actor::character::ScarecrowEndMessage& message);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameScene(const std::shared_ptr<scene::GameScene>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayer(const std::shared_ptr<ratchet::actor::character::Player>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCameraontroller(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemMessageSubject(void) {
        return &this->_text_system_message_subject;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetPlayerCameraSubject(void) {
        return &this->_player_camera_subject;
    }
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
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ��b
    /// </summary>
    void Talk(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_KING_H