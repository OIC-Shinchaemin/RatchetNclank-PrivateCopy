#include "TitleScene.h"
#include "../Gamepad.h"
#include "My/Resource/ResourceFont.h"


bool my::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);

    ::g_pGraphics->SetDepthEnable(true);
    _stage.Render();

    ::g_pGraphics->SetDepthEnable(false);
    if (auto resource = _resource.lock()) {
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-�A�i���O�e���r�t�H���g");
        auto text = "Please Press   Start Button or \n                          Enter Key !";
        font->RenderString(220.0, 400.0f, text);
    } // if
    return true;
}

my::TitleScene::TitleScene() :
    super() {
}

my::TitleScene::~TitleScene() {
}

void my::TitleScene::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}

std::string my::TitleScene::GetName(void) {
    return my::SceneType::kTitleScene;
}

bool my::TitleScene::Load(std::shared_ptr<my::Scene::Param> param) {
    super::Load(param);
    if (auto r = _resource.lock()) {
        r->Load(param->resource.c_str());
    } // if
    // stage
    if (!_stage.Load("../Resource/stage/test.json")) {
        return false;
    } // if

    // camera
    _stage_view_camera = (std::make_shared<my::Camera>());
    auto pos = math::vec3::kZero;
    auto offset = math::vec3::kNegUnitZ;
    _stage_view_camera->SetPosition(pos - offset);
    _stage_view_camera->SetTarget(pos);
    _stage_view_camera->Initialize();
    _stage_view_camera->Update();
    _camera_controller.SetService(std::make_shared<my::CameraController>());
    _camera_controller.GetService()->SetCamera(_stage_view_camera);
    _camera_controller.GetService()->RegisterGlobalCamera();
    _camera_controller.GetService()->SetAzimuth(0.0f);
    _camera_controller.GetService()->SetAltitude(35.0f);
    _camera_controller.GetService()->SetDistance(70.0f);
    return true;
}

bool my::TitleScene::Update(float delta_time) {
    super::Update(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kGameScene, ""));
    } // if

    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(_camera_controller.GetService()->GetAzimuth()) + 0.2f);
    _camera_controller.GetService()->Update();
    return true;
}

bool my::TitleScene::Release(void) {
    super::Release();
    _stage.Release();
    return false;
}