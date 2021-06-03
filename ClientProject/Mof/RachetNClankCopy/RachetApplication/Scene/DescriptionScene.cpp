#include "DescriptionScene.h"

#include "../Gamepad.h"


bool my::DescriptionScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kTitleScene, ""));
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
        auto text = "DescriptionScene !\n";
        font->RenderString(400.0, 350.0f, text);
        text = "Please Press   Start Button or \n                          Enter Key !";
        font->RenderString(260.0, 400.0f, text);
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