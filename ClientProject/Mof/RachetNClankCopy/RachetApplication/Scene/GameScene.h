#ifndef MY_GAME_SCENE_H
#define MY_GAME_SCENE_H


#include "Scene.h"

#include <memory>
#include <vector>

#include "My/Core/Observer.h"
#include "My/UI/UICanvas.h"
#include "../Game/GameWorld.h"
#include "../Game/Renderer.h"
#include "../Game/PhysicsWorld.h"
#include "../Stage/Stage.h"
#include "../Game/GameManager.h"


namespace my {
class GameScene : public my::Scene {
    using super = my::Scene;
private:
    //! �ǉ�
    std::vector<std::shared_ptr<my::Actor>> _created_actors;
    //! �폜
    std::vector<std::shared_ptr<my::Actor>> _delete_actors;
    //! �Q�[��
    my::GameWorld _game_world;
    //! �����_���[
    my::Renderer _renderer;
    //! �R���W����
    my::PhysicsWorld _physic_world;
    //! �X�e�[�W
    Stage _stage;
    //! �ď�����
    bool _re_initialize;
    // ����
    Mof::CDirectionalLight _simple_light;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! �Q�[��
    std::weak_ptr<my::GameManager> _game;
    //! �폜
    std::vector<std::shared_ptr<my::Actor>> _for_bridge_event_actors;
    //! �Q�[���C�x���g
    my::Observable<const char*, const std::shared_ptr<my::Actor>& > _bridge_event_subject;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �ď�����
    /// </summary>
    void ReInitialize(void);
protected:
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<my::GameManager> ptr);
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
    virtual bool Load(std::shared_ptr<my::Scene::Param>  param) override;
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
    virtual bool Input(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Render(void) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_GAME_SCENE_H