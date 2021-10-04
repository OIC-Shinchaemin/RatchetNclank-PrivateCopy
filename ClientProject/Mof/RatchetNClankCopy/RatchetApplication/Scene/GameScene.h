#ifndef RATCHET_SCENE_GAME_SCENE_H
#define RATCHET_SCENE_GAME_SCENE_H


#include "Scene.h"

#include <memory>
#include <vector>

#include "../Game/GameManager.h"
#include "../Event/EventManager.h"
#include "../Game/GameWorld.h"
#include "../Game/Renderer.h"
#include "../Game/PhysicsWorld.h"
#include "../Stage/Stage.h"
#include "../Game/GameSystem/ShopSystem.h"
#include "../Actor/Character/Player.h"
#include "../Actor/Character/Character.h"
#include "../Game/GameSystem/Text/TextSystem.h"
#include "../Event/StageViewEvent.h"
#include "../Effect/EffectContainer.h"
#include "../Component/SightRecognitionComponent.h"
#include "../Event/ShipEvent.h"
#include "../MessageObservationManager.h"
#include "DescriptionScene.h"


namespace ratchet::scene {
class GameScene :
    public ratchet::scene::Scene,
    public base::core::Observer<const ratchet::game::gamesystem::ShopSystem::Info&>,
    public event::StageViewEventMessageListener,
    public ratchet::actor::character::CharacterDamageApplyMessageListener,
    public ContactEnemyMessageListener,
    public event::ShipEventEndMessageListener,
    public ratchet::game::gamesystem::text::TextSystemOpenMessageListener,
    public ratchet::game::gamesystem::text::TextSystemClosedMessageListener {
    using super = ratchet::scene::Scene;
    friend class GameSceneInitializer;
private:
    //! �ǉ�
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _created_actors;
    //! �폜
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _delete_actors;
    //! �Q�[��
    ratchet::game::GameWorld _game_world;
    //! �����_���[
    ratchet::game::Renderer _renderer;
    //! �R���W����
    ratchet::game::PhysicsWorld _physic_world;
    //! �X�e�[�W
    Stage _stage;
    //! �ď�����
    bool _re_initialize;
    //! �ď�����
    bool _player_dead;
    //! ���j���[
    base::core::Observable<bool> _pause_menu_subject;
    //! �e�L�X�g 
    std::shared_ptr<game::gamesystem::text::TextSystem> _text_system;
    //! �Q�[��
    std::weak_ptr<ratchet::game::GameManager> _game;
    //! �C�x���g
    std::weak_ptr<ratchet::event::EventManager> _event;
    //! �G�t�F�N�g
    std::shared_ptr<effect::EffectContainer> _effect;
    //! �J�E���^�[
    base::core::Timer _loading_counter;
    //! �J�E���^�[
    int _loading_dot_count;
    //! �o�ߎ��� / ���v����
    float _loading_progress;
    //! �\��
    bool _show_how_to_play;
public:
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// �ď�����
    /// </summary>
    void ReInitialize(void);
protected:
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool SceneUpdate(float delta_time) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool LoadingUpdate(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool LoadingRender(void) override;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameScene();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GameScene();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::ShopSystem::Info& info) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::event::StageViewEventMessage& message) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::event::ShipEventEndMessage& message) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::actor::character::CharacterDamageApplyMessage& message) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ContactEnemyMessage& message) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(game::gamesystem::text::TextSystemOpenMessageListener::Message message) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(game::gamesystem::text::TextSystemClosedMessageListener::Message message) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) override;
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<super::Param>  param) override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_SCENE_GAME_SCENE_H