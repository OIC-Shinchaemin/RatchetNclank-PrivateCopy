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


namespace ratchet::scene {
class TitleLogo {
private:
    //! �ʒu
    Mof::CVector2 _position;
    //! Y�f�t�H���g�ʒu
    float _default_position_y;
    //! �ʒu
    Mof::CVector2 _position_offset;
    //! �e�N�X�`��
    std::weak_ptr<Mof::CTexture> _texture;
    //! �\��
    bool _show;
    //! �\��
    base::core::Timer _show_timer;
    //! �A���t�@�l
    float _alpha;
    //! �A���t�@�l�ő�l
    float _alpha_max;
    //! �A���t�@�l����
    float _alpha_increments;
    //! �\���g�嗦
    float _scale;
public:
    TitleLogo() :
        _position(),
        _default_position_y(250.0f),
        _position_offset(Mof::CVector2(-10.0f, 0.0f)),
        _texture(),
        _show(false),
        _show_timer(),
        _alpha(0.0f),
        _alpha_max(1.0f),
        _alpha_increments(0.03f),
        _scale(0.8f) {
        _show_timer.Initialize(0.8f, false);
    }
    ~TitleLogo() {
        _show = false;
    }

    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
        auto center = Mof::CVector2(::g_pFramework->GetWindow()->GetWidth() * 0.5f, ::g_pFramework->GetWindow()->GetHeight() * 0.5f);
        this->_texture = ptr;
        auto size = Mof::CVector2(ptr->GetWidth(), ptr->GetHeight()) * _scale;
        auto half_size = size * 0.5f;

        _position = Mof::CVector2(center.x - half_size.x, _default_position_y) + _position_offset;
    }
    bool Update(float delta_time) {
        if (_show_timer.Tick(delta_time)) {
            _show = true;
        } // if

        if (_show) {
            _alpha = std::clamp(_alpha + _alpha_increments, 0.0f, _alpha_max);
        } // if
        return true;
    }
    bool Render(void) {
        if (!_show) {
            return false;
        } // if
        if (auto tex = _texture.lock()) {
            auto color = Mof::CVector4(1.0f, 1.0f, 1.0f, _alpha).ToU32Color();
            tex->RenderScale(_position.x, _position.y, _scale, color, Mof::TextureAlignment::TEXALIGN_BOTTOMLEFT);
        } // if
        return true;
    }
};


class TitleScene : public ratchet::scene::Scene,
    public base::core::Observer<const ratchet::game::gamesystem::OptionSystem::Info&> {
    using super = ratchet::scene::Scene;
private:
    //! bgm
    //Mof::CStreamingSoundBuffer _bgm;
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
    //! �J�E���^�[
    base::core::Timer _loading_counter;
    //! �J�E���^�[
    int _loading_dot_count;
    //! �o�ߎ��� / ���v����
    float _loading_progress;
    //! �I��
    bool _scene_end;
    //! ���̓^�C�}�[
    base::core::Timer _input_timer;
    //! ���̓t���O
    bool _input_flag;
private:
    /// <summary>
    /// �t�F�[�h�A�E�g
    /// </summary>
    /// <param name=""></param>
    void FadeOutStart(void);
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
#endif // !RATCHET_SCENE_TITLE_SCENE_H