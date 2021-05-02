#include "TitleScene.h"
#include "../Gamepad.h"


bool my::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);

    ::g_pGraphics->SetDepthEnable(true);
    _stage.Render();


    //Mof::CMatrix44 world, scale, rotate, translate;
    //_water_surface.Render();


    ::g_pGraphics->SetDepthEnable(false);
    auto text = "Please Press   Start Button or \n               Enter Key !";
    ::CGraphicsUtilities::RenderString(320.0, 400.0f, "%s", text);
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
        resource->Load(param->resource.c_str());
        this->LoadComplete();
    } // if

    bool s = _water_surface.Load("../Resource/texture/water/water.jpg");
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