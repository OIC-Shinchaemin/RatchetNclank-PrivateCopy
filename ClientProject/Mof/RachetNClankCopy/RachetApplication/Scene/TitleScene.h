#ifndef MY_TITLE_SCENE_H
#define MY_TITLE_SCENE_H


#include "Scene.h"

#include <memory>

#include "My/Core/ServiceLocator.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"
#include "../Stage/Stage.h"


namespace my {
class TitleScene : public my::Scene {
    using super = my::Scene;
private:
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! ���
    std::weak_ptr<Mof::CTexture> _backbround;
    //! �X�e�[�W
    Stage _stage;
    //! �J����
    std::shared_ptr<my::Camera> _stage_view_camera;
    //! �J�����R���g���[��
    my::ServiceLocator<my::CameraController> _camera_controller;
    //! ����
    Mof::CTexture _water_surface;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
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
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
};
}
#endif // !MY_TITLE_SCENE_H