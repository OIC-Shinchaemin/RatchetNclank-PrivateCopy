#include "ClearScene.h"

#include "../Gamepad.h"


bool my::ClearScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    auto text = "Game Clear !\n";
    ::CGraphicsUtilities::RenderString(400.0, 400.0f, "%s", text);

    text = "Press StartButton or EnterKey";
    ::CGraphicsUtilities::RenderString(380.0, 450.0f, "%s", text);
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
    super::_loaded = true;
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