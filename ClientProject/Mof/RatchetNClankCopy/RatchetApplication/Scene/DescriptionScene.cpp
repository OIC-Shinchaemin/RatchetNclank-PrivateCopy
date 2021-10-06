#include "DescriptionScene.h"

#include "../Gamepad.h"


bool ratchet::scene::DescriptionScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_LSHIFT)) {
        _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kTitleScene, ""));
    } // if
    return true;
}

bool ratchet::scene::DescriptionScene::LoadingUpdate(float delta_time) {
    return false;
}

bool ratchet::scene::DescriptionScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    if (auto resource = _resource.lock()) {
        auto desc = GameDescription();
        desc.Render(resource);
    } // if

    return true;
}

ratchet::scene::DescriptionScene::DescriptionScene() {
}

ratchet::scene::DescriptionScene::~DescriptionScene() {
}

void ratchet::scene::DescriptionScene::OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) {
}

std::string ratchet::scene::DescriptionScene::GetName(void) {
    return ratchet::scene::SceneType::kDescriptionScene;
}

bool ratchet::scene::DescriptionScene::Load(std::shared_ptr<ratchet::scene::Scene::Param> param) {
    auto re = super::Load(param);

    super::LoadComplete();
    return re;
}