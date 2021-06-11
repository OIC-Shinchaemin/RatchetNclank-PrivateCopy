#include "ClearScene.h"

#include "../Gamepad.h"


bool ratchet::scene::ClearScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kTitleScene, ""));
    } // if
    return true;
}

bool ratchet::scene::ClearScene::LoadingUpdate(float delta_time) {
    return false;
}

bool ratchet::scene::ClearScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    if (auto resource = _resource.lock()) {
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");
        auto text = "Game Clear !\n";
        font->RenderString(400.0, 350.0f, text);
        text = "Please Press   Start Button or \n                          Enter Key !";
        font->RenderString(260.0, 400.0f, text);
    } // if

    return true;
}

ratchet::scene::ClearScene::ClearScene() {
}

ratchet::scene::ClearScene::~ClearScene() {
}

void ratchet::scene::ClearScene::OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) {
}

std::string ratchet::scene::ClearScene::GetName(void) {
    return ratchet::scene::SceneType::kClearScene;
}

bool ratchet::scene::ClearScene::Load(std::shared_ptr<ratchet::scene::Scene::Param> param) {
    auto re = super::Load(param);

    super::LoadComplete();
    return re;
}