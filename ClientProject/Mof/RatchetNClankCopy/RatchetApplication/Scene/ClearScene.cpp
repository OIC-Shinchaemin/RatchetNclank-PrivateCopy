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
        font->RenderString(_clear_text_position.x, _clear_text_position.y, _clear_text.c_str());
        font->RenderString(_next_text_position.x, _next_text_position.y, _next_text.c_str());
    } // if

    return true;
}

ratchet::scene::ClearScene::ClearScene() :
    _clear_text("Game Clear !\n"),
    _clear_text_position(400.0, 200.0f),
    _next_text("Press Enter Key \n\nTo Title"),
    _next_text_position(260.0, 400.0f) {
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