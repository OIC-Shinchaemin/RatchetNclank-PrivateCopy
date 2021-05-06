#include "ClearScene.h"

#include "../Gamepad.h"


bool my::ClearScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    

    if (auto resource = _resource.lock()) {
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-�A�i���O�e���r�t�H���g");
        auto text = "Game Clear !\n";
        font->RenderString(400.0, 350.0f, text);
        text = "Please Press   Start Button or \n                          Enter Key !";
        font->RenderString(260.0, 400.0f, text);
    } // if

    return true;
}

my::ClearScene::ClearScene() {
}

my::ClearScene::~ClearScene() {
}

void my::ClearScene::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}

std::string my::ClearScene::GetName(void) {
    return my::SceneType::kClearScene;
}

bool my::ClearScene::Load(std::shared_ptr<my::Scene::Param> param) {
    auto re = super::Load(param);
    return re;
}

bool my::ClearScene::Update(float delta_time) {
    super::Update(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kTitleScene, ""));
    } // if
    return true;
}