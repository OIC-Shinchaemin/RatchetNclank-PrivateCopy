#include "DescriptionScene.h"

#include "../Gamepad.h"


bool my::DescriptionScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        //::g_pInput->IsKeyPush(MOFKEY_RETURN) ||
        //::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        ::g_pInput->IsKeyPush(MOFKEY_LSHIFT)) {
        _subject.Notify(scene::SceneMessage(my::SceneType::kTitleScene, ""));
    } // if
    return true;
}

bool my::DescriptionScene::LoadingUpdate(float delta_time) {
    return false;
}

bool my::DescriptionScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    if (auto resource = _resource.lock()) {
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-�A�i���O�e���r�t�H���g");

        const char* text;
        
        text = "�Q�[���̑������";
        ::CGraphicsUtilities::RenderString(400.0, 100.0f, text);

        text = " �� ESCAPE�L�[�ŃQ�[���I��\n\n \
�� Z�L�[�ōU��\n\n \
�� X�L�[�ŃW�����v\n\n \
�� Shift�L�[�ŕύX ����I����Shift��������0~8�L�[\n\n \
�� V�L�[�ŕ��킪�I������Ă���Ε���g�p\n\n \
�� WASD�L�[�ňړ�\n\n \
�� �\���L�[�ŃJ�����ړ�\n\n \
�� Q�L�[�ŃJ�����␳\n";
        //font->RenderString(400.0, 350.0f, text);
        ::CGraphicsUtilities::RenderString(130.0 + 1, 240.0f + 1, def::color_rgba_u32::kBlue, text);
        ::CGraphicsUtilities::RenderString(130.0, 240.0f, text);



        text = "Start�{�^���EShift�L�[�Ń^�C�g���ɖ߂�";
        ::CGraphicsUtilities::RenderString(460.0, 700.0f, text);
    } // if

    return true;
}

my::DescriptionScene::DescriptionScene() {
}

my::DescriptionScene::~DescriptionScene() {
}

void my::DescriptionScene::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}

std::string my::DescriptionScene::GetName(void) {
    return my::SceneType::kDescriptionScene;
}

bool my::DescriptionScene::Load(std::shared_ptr<my::Scene::Param> param) {
    auto re = super::Load(param);

    super::LoadComplete();
    return re;
}