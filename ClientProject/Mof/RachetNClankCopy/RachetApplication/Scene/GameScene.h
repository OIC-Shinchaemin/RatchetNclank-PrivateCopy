#ifndef RACHET_GAME_SCENE_H
#define RACHET_GAME_SCENE_H


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

namespace rachet {
class GameScene : public rachet::Scene, public base::core::Observer<const rachet::ShopSystem::Info&> {
    using super = rachet::Scene;
    using this_type = rachet::GameScene;
private:
    //! �ǉ�
    std::vector<std::shared_ptr<rachet::Actor>> _created_actors;
    //! �폜
    std::vector<std::shared_ptr<rachet::Actor>> _delete_actors;
    //! �Q�[��
    rachet::GameWorld _game_world;
    //! �����_���[
    rachet::Renderer _renderer;
    //! �R���W����
    rachet::PhysicsWorld _physic_world;
    //! �X�e�[�W
    Stage _stage;
    //! �ď�����
    bool _re_initialize;
    //! ���j���[
    base::core::Observable<bool> _pause_menu_subject;


    //! �Q�[��
    std::weak_ptr<rachet::GameManager> _game;
    //! �C�x���g
    std::weak_ptr<rachet::EventManager> _event;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<rachet::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<rachet::Actor>& ptr);
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
    virtual void OnNotify(const char* type, const std::shared_ptr<rachet::Actor>& ptr) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const rachet::ShopSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<rachet::GameManager> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<rachet::EventManager> ptr);
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
    virtual bool Load(std::shared_ptr<rachet::Scene::Param>  param) override;
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
#endif // !RACHET_GAME_SCENE_H