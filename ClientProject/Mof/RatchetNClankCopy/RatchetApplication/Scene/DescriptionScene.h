#ifndef RATCHET_SCENE_DESCRIPTION_SCENE_H
#define RATCHET_SCENE_DESCRIPTION_SCENE_H


#include "Scene.h"
#include "../GameDefine.h"


namespace ratchet::scene {
class GameDescription {
private:
    //! �\��
    bool _show = false;
    //! �ʒu
    Mof::CVector2 _title_position = Mof::CVector2(400.0, 100.0f);
    //! �ʒu
    Mof::CVector2 _desc_position = Mof::CVector2(130.0, 240.0f);
    //! �ʒu
    Mof::CVector2 _back_position = Mof::CVector2(460.0, 700.0f);
    //! �e�L�X�g
    std::string _title_text = "�Q�[���̑������";
    //! �e�L�X�g
    std::string _desc_text = " �� Escape(Esc)�L�[�ŃQ�[���I��\n\n \
�� N�L�[�ōU��\n\n \
�� J�L�[�ŃW�����v\n\n \
�� Shift�L�[�ŕύX\n\n \
�� V�L�[�ŕ��킪�I������Ă���Ε���g�p\n\n \
�� WASD�L�[�ňړ�\n\n \
�� �\���L�[�ŃJ�����ړ�\n\n \
�� Q�L�[�ŃJ�����␳\n";
    //! �e�L�X�g
    std::string _back_text = "Escape(Esc)�L�[�Ŗ߂�";
public:
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsShow(void) const {
        return this->_show ;
    }
    void Show(void) {
        this->_show = true;
    }
    void Hide(void) {
        this->_show = false;
    }
    void Render(const Mof::CVector2& position, const std::string& text) {
        ::CGraphicsUtilities::RenderString(position.x, position.y, text.c_str());
    }
    void Render(std::shared_ptr<ratchet::ResourceMgr> r) {
        this->Render(_title_position, _title_text);
        this->Render(_desc_position, _desc_text);
        this->Render(_back_position, _back_text);
    }
};
class DescriptionScene : public ratchet::scene::Scene {
    using super = ratchet::scene::Scene;
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
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DescriptionScene();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~DescriptionScene();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) override;
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
    virtual bool Load(std::shared_ptr<super::Param> param) override;
};
}
#endif // !RATCHET_SCENE_DESCRIPTION_SCENE_H