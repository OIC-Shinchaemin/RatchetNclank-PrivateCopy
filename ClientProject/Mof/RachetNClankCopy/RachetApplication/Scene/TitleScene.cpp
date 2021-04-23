#include "TitleScene.h"


bool my::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);

    if (auto tex = _backbround.lock()) {
        tex->Render(0.0f, 0.0f);
    } // if
    ::CGraphicsUtilities::RenderString(10.0, 10.0f, "%s", this->GetName().c_str());
    return true;
}

my::TitleScene::TitleScene() :
    super(),
    _resource(),
    _backbround() {
}

my::TitleScene::~TitleScene() {
}

void my::TitleScene::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}

void my::TitleScene::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

std::string my::TitleScene::GetName(void) {
    return my::SceneType::kTitleScene;
}

bool my::TitleScene::Load(std::shared_ptr<my::Scene::Param> param) {
    super::Load(param);
    if (auto resource = _resource.lock()) {
        _backbround = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/scene/title.png");
    } // if

    return true;
}

bool my::TitleScene::Update(float delta_time) {
    super::Update(delta_time);
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kGameScene, ""));
    } // if

    auto rect = Mof::CRectangle(0.0f, 0.0f, 256.0f, 128.0f);
    rect.Translation(Mof::CVector2(460.0f, 460.0f));
    ::CGraphicsUtilities::RenderFillRect(rect, def::color_rgba_u32::kRed);
    if (::g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
        Mof::CVector2 pos;
        ::g_pInput->GetMousePos(pos);
        if (rect.CollisionPoint(pos)) {
            _subject.Notify(my::SceneMessage(my::SceneType::kGameScene, ""));
        } // if
    } // if

    return true;
}