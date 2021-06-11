#include "DescriptionScene.h"

#include "../Gamepad.h"


bool ratchet::DescriptionScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        //::g_pInput->IsKeyPush(MOFKEY_RETURN) ||
        //::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        ::g_pInput->IsKeyPush(MOFKEY_LSHIFT)) {
        _subject.Notify(scene::SceneMessage(ratchet::SceneType::kTitleScene, ""));
    } // if
    return true;
}

bool ratchet::DescriptionScene::LoadingUpdate(float delta_time) {
    return false;
}

bool ratchet::DescriptionScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    if (auto resource = _resource.lock()) {
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");

        const char* text;
        
        text = "ゲームの操作説明";
        ::CGraphicsUtilities::RenderString(400.0, 100.0f, text);

        text = " ◆ ESCAPEキーでゲーム終了\n\n \
◆ Zキーで攻撃\n\n \
◆ Xキーでジャンプ\n\n \
◆ Shiftキーで変更 武器選択はShift長押しで0~8キー\n\n \
◆ Vキーで武器が選択されていれば武器使用\n\n \
◆ WASDキーで移動\n\n \
◆ 十字キーでカメラ移動\n\n \
◆ Qキーでカメラ補正\n";
        //font->RenderString(400.0, 350.0f, text);
        ::CGraphicsUtilities::RenderString(130.0 + 1, 240.0f + 1, def::color_rgba_u32::kBlue, text);
        ::CGraphicsUtilities::RenderString(130.0, 240.0f, text);



        text = "Startボタン・Shiftキーでタイトルに戻る";
        ::CGraphicsUtilities::RenderString(460.0, 700.0f, text);
    } // if

    return true;
}

ratchet::DescriptionScene::DescriptionScene() {
}

ratchet::DescriptionScene::~DescriptionScene() {
}

void ratchet::DescriptionScene::OnNotify(const char* type, const std::shared_ptr<ratchet::Actor>& ptr) {
}

std::string ratchet::DescriptionScene::GetName(void) {
    return ratchet::SceneType::kDescriptionScene;
}

bool ratchet::DescriptionScene::Load(std::shared_ptr<ratchet::Scene::Param> param) {
    auto re = super::Load(param);

    super::LoadComplete();
    return re;
}