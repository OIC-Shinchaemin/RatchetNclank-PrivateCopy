#ifndef RACHET_TITLE_SCENE_H
#define RACHET_TITLE_SCENE_H


#include "Scene.h"

#include <memory>

#include "Base/Core/ServiceLocator.h"
#include "../GameDefine.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"
#include "../Stage/Stage.h"
#include "../Actor/Character/Player.h"
#include "Base/Core/Observable.h"
#include "../Game/GameManager.h"
#include "../Game/GameSystem/OptionSystem.h"
#include "../UI/TitleInfoMenu.h"


namespace rachet {
class TitleScene : public rachet::Scene,
    public base::core::Observer<const rachet::OptionSystem::Info&> {
    using super = rachet::Scene;
private:
    //! �X�e�[�W
    Stage _stage;
    //! �J����
    std::shared_ptr<rachet::Camera> _stage_view_camera;
    //! �J�����R���g���[��
    base::core::ServiceLocator<rachet::CameraController> _camera_controller;
    //! �\���p
    std::shared_ptr<rachet::Player> _demo_actor;
    //! �ʒm�p
    base::core::Observable<bool> _option_system_subject;
    //! �ʒm�p
    base::core::Observable<bool> _title_menu_subject;
    //! �Q�[��
    std::weak_ptr<rachet::GameManager> _game;
    //! UI�n��
    rachet::UICreator<rachet::TitleInfoMenu> _ui_creator;
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
    TitleScene();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TitleScene();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<rachet::Actor>& ptr) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const rachet::OptionSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<rachet::GameManager> ptr);
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
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
};
}
#endif // !RACHET_TITLE_SCENE_H