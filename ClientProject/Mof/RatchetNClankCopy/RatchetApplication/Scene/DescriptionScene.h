#ifndef RATCHET_SCENE_DESCRIPTION_SCENE_H
#define RATCHET_SCENE_DESCRIPTION_SCENE_H


#include "Scene.h"


namespace ratchet::scene {
class GameDescription {
private:
public:
    void Render(std::shared_ptr<ratchet::ResourceMgr> r) {
        auto font = r->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-�A�i���O�e���r�t�H���g");

        const char* text;

        text = "�Q�[���̑������";
        ::CGraphicsUtilities::RenderString(400.0, 100.0f, text);

        text = " �� ESCAPE�L�[�ŃQ�[���I��\n\n \
�� N�L�[�ōU��\n\n \
�� J�L�[�ŃW�����v\n\n \
�� Shift�L�[�ŕύX ����I����Shift��������0~8�L�[\n\n \
�� V�L�[�ŕ��킪�I������Ă���Ε���g�p\n\n \
�� WASD�L�[�ňړ�\n\n \
�� �\���L�[�ŃJ�����ړ�\n\n \
�� Q�L�[�ŃJ�����␳\n";
        ::CGraphicsUtilities::RenderString(130.0 + 1, 240.0f + 1, def::color_rgba_u32::kBlue, text);
        ::CGraphicsUtilities::RenderString(130.0, 240.0f, text);

        text = "Start�{�^���EShift�L�[�Ŗ߂�";
        ::CGraphicsUtilities::RenderString(460.0, 700.0f, text);
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