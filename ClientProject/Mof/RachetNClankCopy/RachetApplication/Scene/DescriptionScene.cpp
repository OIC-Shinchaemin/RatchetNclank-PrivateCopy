#include "DescriptionScene.h"

#include "../Gamepad.h"


bool my::DescriptionScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN) ||
        ::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
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
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");

        auto text = "スタートボタン・スペースキー・エンターキーでタイトルに戻る";
        ::CGraphicsUtilities::RenderString(260.0, 300.0f, text);

        text = "ゲームの操作説明\nESCAPEキーでゲーム終了\nZキーで攻撃\nXキーでジャンプ\nShiftキーで変更 武器選択はShift長押しで0~8キー\nVキーで武器が選択されていれば武器使用\n \WASDキーで移動\n十字キーでカメラ移動\nQキーでカメラ補正\n";
        //font->RenderString(400.0, 350.0f, text);
        ::CGraphicsUtilities::RenderString(400.0, 350.0f, text);
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