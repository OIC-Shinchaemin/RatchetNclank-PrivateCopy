#include "TestApp.h"

#include "My/Core/Define.h"
#include "Gamepad.h"
#include "Camera/CameraController.h"
#include "Camera/FollowCameraController.h"
#include "Camera/FirstPersonCameraController.h"
#include "Camera/DebugCameraController.h"


void test::CGameApp::UpdateFollow(float delta_time, std::shared_ptr<my::CameraController> controller) {
    if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
        _camera_controller.GetService()->AddAzimuth(1.0f);
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
        _camera_controller.GetService()->AddAzimuth(-1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
        _camera_controller.GetService()->AddAltitude(1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
        _camera_controller.GetService()->AddAltitude(-1.0f);
    } // else if
    // chara front
    /*
    if (::g_pInput->IsKeyPush(MOFKEY_Q)) {
        auto pos = super::GetOwner()->GetPosition();
        pos.y += 1.0f;

        auto prev_pos = _controller_map.at(_current_mode)->GetCameraPosition();
        auto front = _controller_map.at(_current_mode)->GetViewFront();

        _current_mode = CameraMode::FirstPerson;
        auto con = _controller_map.at(_current_mode);

        auto info = my::CameraController::CameraInfo();
        info.start_position = prev_pos;
        info.camera_front = front;
        info.ideal_position = pos;
        con->SetInfo(info);
        _camera_controller.SetService(con);
    } // if
    */

    auto info = my::CameraController::CameraInfo();
    info.target = _player.Position;
    controller->Update(delta_time, info);
}

MofBool test::CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("Resource");
    bool loaded = _gizmo.Load("test/gizmo.mom");

    my::Gamepad::GetInstance().Create();
    _camera_manager = std::make_shared<my::CameraManager>();
    my::CameraController::SetCameraManager(_camera_manager);


    using Mode = test::CameraMode;
    _camera = std::make_shared<my::Camera>();
    _camera->Initialize();
    _controller_map.clear();
    auto follow = std::make_shared<my::FollowCameraController>();
    auto first_person = std::make_shared<my::FirstPersonCameraController>();
    _controller_map.emplace(Mode::Follow, follow);
    _controller_map.emplace(Mode::FirstPerson, first_person);
    _controller_map.at(Mode::Follow)->SetCamera(_camera);
    _controller_map.at(Mode::FirstPerson)->SetCamera(_camera);
    _camera_controller.SetService(_controller_map.at(Mode::Follow));
    _camera_controller.GetService()->RegisterGlobalCamera();

    auto pos = _player.Position;
    auto offset = Mof::CVector3(math::vec3::kNegUnitZ);
    offset.RotateAround(math::vec3::kZero, math::vec3::kZero);

    _camera_controller.GetService()->SetAzimuth(90.0f);
    _camera_controller.GetService()->SetAltitude(20.0f);
    _camera_controller.GetService()->SetDistance(10.0f);
    return TRUE;
}

MofBool test::CGameApp::Input(void) {
    ::g_pInput->RefreshKey();
    ::g_pGamepad->RefreshKey();

    if (::g_pInput->IsKeyPush(MOFKEY_ESCAPE) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_BACK)) {
        ::PostQuitMessage(0);
        return false;
    } // if


    float speed = 2.0f;
    float move = 1.0f / 60.0f * speed;
    if (::g_pInput->IsKeyHold(MOFKEY_A)) {
        _player.x += move;
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_D)) {
        _player.x -= move;
    } // else if
    if (::g_pInput->IsKeyHold(MOFKEY_W)) {
        _player.z -= move;
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_S)) {
        _player.z += move;
    } // else if
    return TRUE;
}

MofBool test::CGameApp::Update(void) {
    this->Input();

    float delta_time = 1.0f / 60.0f;
    auto controller = _camera_controller.GetService();
    using Mode = CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            this->UpdateFollow(delta_time, controller);
            break;
        case Mode::FirstPerson:
            break;
    } // switch
    _camera_manager->Update();

    return TRUE;
}

MofBool test::CGameApp::Render(void) {
    ::g_pGraphics->RenderStart();
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetRenderTarget(::g_pGraphics->GetRenderTarget(), ::g_pGraphics->GetDepthTarget());
    ::g_pGraphics->SetDepthEnable(true);
    _gizmo.Render(Mof::Matrix44());
    ::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);


    ::CGraphicsUtilities::RenderSphere(_player, def::color_rgba::kRed);

    ::g_pGraphics->SetDepthEnable(false);

    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "Camera Controller Test Application ");
    ::CGraphicsUtilities::RenderString(10.0f, 30.0f, "FPS = %d", ::CUtilities::GetFPS());

    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool test::CGameApp::Release(void) {
    _camera_manager.reset();
    my::Gamepad::GetInstance().Release();
    return TRUE;
}