#include "TitleScene.h"
#include "../Gamepad.h"
#include "My/Resource/ResourceFont.h"
#include "../Factory/FactoryManager.h"
#include "../Camera/FollowCameraController.h"


bool my::TitleScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kGameScene, ""));
    } // if

    //_demo_actor->Update(delta_time);

    auto camera_info = my::CameraController::CameraInfo();

    auto pos = Mof::CVector3(10.0f, -2.0f, -15.0f);
    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(_camera_controller.GetService()->GetAzimuth()) + 0.2f);
    //_camera_controller.GetService()->SetCameraTarget(pos);
    camera_info.target = pos;
    _camera_controller.GetService()->Update(delta_time, camera_info);
    return true;
}

bool my::TitleScene::LoadingUpdate(float delta_time) {
    return true;
}

bool my::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);

    _demo_actor->Render();
    _stage.Render();


    ::g_pGraphics->SetDepthEnable(false);
    if (auto resource = _resource.lock()) {
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");
        auto text = "Please Press   Start Button or \n                          Enter Key !";
        font->RenderString(220.0, 400.0f, def::color_rgba_u32::kGreen, text);
    } // if
    return true;
}

bool my::TitleScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);
    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, def::color_rgba_u32::kRed, "Now Loading");
    return true;
}

my::TitleScene::TitleScene() :
    super(),
    _stage(),
    _stage_view_camera(),
    _camera_controller(),
    _demo_actor() {
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

    super::_load_thread = std::thread([&]() {
        if (!super::IsLoaded()) {
            ::CoInitialize(NULL);
            auto path = "../Resource/scene_resource/game_scene.txt";
            if (auto r = _resource.lock()) {
                r->Load(path);
            } // if
            // stage
            if (!_stage.Load("../Resource/stage/test.json")) {
            } // if
            _stage.Initialize();

            auto actor_param = my::Actor::Param();
            actor_param .transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
            actor_param .transform.position = Mof::CVector3(10.0f, -5.0f, -15.0f);
            _demo_actor = my::FactoryManager::Singleton().CreateActor<my::Player>("builder/player.json", &actor_param);

            ::CoUninitialize();            
            super::LoadComplete();

            // camera
            _stage_view_camera = (std::make_shared<my::Camera>());
            auto pos = math::vec3::kZero;
            auto offset = math::vec3::kNegUnitZ;
            _stage_view_camera->SetPosition(pos - offset);
            _stage_view_camera->SetTarget(pos);
            _stage_view_camera->Initialize();
            _stage_view_camera->Update();
            _camera_controller.SetService(std::make_shared<my::FollowCameraController>());
            _camera_controller.GetService()->SetCamera(_stage_view_camera);
            _camera_controller.GetService()->RegisterGlobalCamera();
            _camera_controller.GetService()->SetAzimuth(0.0f);
            _camera_controller.GetService()->SetAltitude(-10.0f);
            _camera_controller.GetService()->SetDistance(8.0f);
        } // if
    });

    return true;
}

bool my::TitleScene::Release(void) {
    super::Release();
    _stage.Release();
    return true;
}