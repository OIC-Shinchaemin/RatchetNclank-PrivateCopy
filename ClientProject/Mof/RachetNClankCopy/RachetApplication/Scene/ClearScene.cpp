#include "ClearScene.h"

#include "../Gamepad.h"


bool rachet::ClearScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(scene::SceneMessage(rachet::SceneType::kTitleScene, ""));
    } // if
    return true;
}

bool rachet::ClearScene::LoadingUpdate(float delta_time) {
    return false;
}

bool rachet::ClearScene::SceneRender(void) {
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

rachet::ClearScene::ClearScene() {
}

rachet::ClearScene::~ClearScene() {
}

void rachet::ClearScene::OnNotify(const char* type, const std::shared_ptr<rachet::Actor>& ptr) {
}

std::string rachet::ClearScene::GetName(void) {
    return rachet::SceneType::kClearScene;
}

bool rachet::ClearScene::Load(std::shared_ptr<rachet::Scene::Param> param) {
    auto re = super::Load(param);

    super::LoadComplete();
    return re;
}