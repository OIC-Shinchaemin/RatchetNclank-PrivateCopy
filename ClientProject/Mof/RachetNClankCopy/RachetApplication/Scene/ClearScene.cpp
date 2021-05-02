#include "ClearScene.h"


bool my::ClearScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    ::CGraphicsUtilities::RenderString(10.0, 10.0f, "%s", this->GetName().c_str());
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

bool my::ClearScene::Update(float delta_time) {
    super::Update(delta_time);
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kTitleScene, ""));
    } // if
    return true;
}