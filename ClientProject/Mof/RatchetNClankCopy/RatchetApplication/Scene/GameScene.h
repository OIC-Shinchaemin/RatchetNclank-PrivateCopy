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

namespace ratchet {
namespace scene {
class GameScene : public ratchet::scene::Scene, public base::core::Observer<const ratchet::ShopSystem::Info&> {
    using super = ratchet::scene::Scene;
    using this_type = ratchet::scene::GameScene;
private:
    //! �ǉ�
    std::vector<std::shared_ptr<ratchet::Actor>> _created_actors;
    //! �폜
    std::vector<std::shared_ptr<ratchet::Actor>> _delete_actors;
    //! �Q�[��
    ratchet::GameWorld _game_world;
    //! �����_���[
    ratchet::Renderer _renderer;
    //! �R���W����
    ratchet::PhysicsWorld _physic_world;
    //! �X�e�[�W
    Stage _stage;
    //! �ď�����
    bool _re_initialize;
    //! ���j���[
    base::core::Observable<bool> _pause_menu_subject;


    //! �Q�[��
    std::weak_ptr<ratchet::GameManager> _game;
    //! �C�x���g
    std::weak_ptr<ratchet::EventManager> _event;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<ratchet::Actor>& ptr);
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
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::Actor>& ptr) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::ShopSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::GameManager> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<ratchet::EventManager> ptr);
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
}
#endif // !RATCHET_SCENE_GAME_SCENE_H