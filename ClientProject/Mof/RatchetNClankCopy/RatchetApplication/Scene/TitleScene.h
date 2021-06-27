#ifndef RATCHET_SCENE_TITLE_SCENE_H
#define RATCHET_SCENE_TITLE_SCENE_H


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
#include "../UI/UICreator.h"


namespace ratchet {
namespace scene {
class TitleLogo {
private:
    //! �e�N�X�`��
    std::weak_ptr<Mof::CTexture> _texture;
    //! �\��
    bool _show;
    //! �\��
    base::core::Timer _show_timer;
public:
    TitleLogo() :
        _texture(),
        _show(false),
        _show_timer() {
        _show_timer.Initialize(3.0f, false);
    }
    ~TitleLogo() {
        _show = false;
    }

    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
        this->_texture = ptr;
    }
    bool Update(float delta_time) {
        if (_show_timer.Tick(delta_time)) {
            _show = true;
        } // if
        return true;
    }
    bool Render(void) {
        if (!_show) {
            return false;
        } // if
        if (auto tex = _texture.lock()) {
            tex->Render(200.0f, 100.0f);
        } // if
        return true;
    }
};


class TitleScene : public ratchet::scene::Scene,
    public base::core::Observer<const ratchet::game::gamesystem::OptionSystem::Info&> {
    using super = ratchet::scene::Scene;
private:
    //! �X�e�[�W
    Stage _stage;
    //! �J����
    std::shared_ptr<ratchet::camera::Camera> _stage_view_camera;
    //! �J�����R���g���[��
    base::core::ServiceLocator<ratchet::camera::CameraController> _camera_controller;
    //! �\���p
    std::shared_ptr<ratchet::actor::character::Player> _demo_actor;
    //! �ʒm�p
    base::core::Observable<bool> _option_system_subject;
    //! �ʒm�p
    base::core::Observable<bool> _title_menu_subject;
    //! �Q�[��
    std::weak_ptr<ratchet::game::GameManager> _game;
    //! UI�n��
    ratchet::ui::UICreator<ratchet::ui::TitleInfoMenu> _ui_creator;
    //! �^�C�g��
    TitleLogo _logo;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const ratchet::game::gamesystem::OptionSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr);
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
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
};
}
}
#endif // !RATCHET_SCENE_TITLE_SCENE_H