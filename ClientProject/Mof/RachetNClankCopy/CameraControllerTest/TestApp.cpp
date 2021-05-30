#include "TestApp.h"

#include "My/Core/Define.h"
#include "Gamepad.h"
#include "Camera/CameraController.h"
#include "Camera/FollowCameraController.h"
#include "Camera/FirstPersonCameraController.h"
#include "Camera/DebugCameraController.h"


void test::CGameApp::InputFollow(std::shared_ptr<my::CameraController> controller) {
    if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
        controller->AddAzimuth(1.0f);
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
        controller->AddAzimuth(-1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
        controller->AddAltitude(1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
        controller->AddAltitude(-1.0f);
    } // else if

    if (::g_pInput->IsKeyPush(MOFKEY_Q)) {
        auto eye_pos = _transform.position;
        eye_pos.y += 1.0f;

        auto prev_pos = _controller_map.at(_current_mode)->GetCameraPosition();
        auto front = _controller_map.at(_current_mode)->GetViewFront();

        _current_mode = my::CameraController::CameraMode::FirstPerson;
        auto con = _controller_map.at(_current_mode);

        auto info = my::CameraController::CameraInfo();
        info.start_position = prev_pos;
        info.camera_front = front;
        info.ideal_position = eye_pos;
        con->SetInfo(info);
        _camera_controller.SetService(con);
    } // if
}

void test::CGameApp::InputFirstPerson(std::shared_ptr<my::CameraController> controller) {
    if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
        controller->AddAzimuth(1.0f);
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
        controller->AddAzimuth(-1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
        controller->AddAltitude(1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
        controller->AddAltitude(-1.0f);
    } // else if

    if (::g_pInput->IsKeyHold(MOFKEY_Q)) {
        auto camera_pos = _controller_map.at(_current_mode)->GetCameraPosition();
        auto eye_pos = _transform.position;
        eye_pos.y += 1.0f;

        float diff = std::fabs(camera_pos.Length() - eye_pos.Length());
        if (diff < 0.1f) {
            auto camera_front = _controller_map.at(_current_mode)->GetViewFront();

            float angle_y = std::atan2(-camera_front.z, camera_front.x) - math::kHalfPi;
            auto angle = Mof::CVector3(0.0f, angle_y, 0.0f);

            _transform.rotate = angle;
        } // if
    } // if

    else if (::g_pInput->IsKeyPull(MOFKEY_Q)) {
        auto prev_pos = _controller_map.at(_current_mode)->GetCameraPosition();

        _current_mode = my::CameraController::CameraMode::Follow;
        float ideal_angle_y = _transform.rotate.y + math::kHalfPi;
        auto info = my::CameraController::CameraInfo();
        info.start_position = prev_pos;

        auto con = _controller_map.at(_current_mode);
        con->SetAzimuth(math::ToDegree(ideal_angle_y));
        con->SetInfo(info);
        _camera_controller.SetService(con);
    } // else if
}

void test::CGameApp::UpdateFollow(float delta_time, std::shared_ptr<my::CameraController> controller) {
    auto info = my::CameraController::CameraInfo();
    info.target_position = _transform.position;
    _camera_controller.GetService()->Update(delta_time, info);
}

void test::CGameApp::UpdateFirstPerson(float delta_time, std::shared_ptr<my::CameraController> controller) {
    auto info = my::CameraController::CameraInfo();
    auto pos = _transform.position;
    pos.y += 1.0f;
    info.ideal_position = pos;
    _camera_controller.GetService()->Update(delta_time, info);
}

MofBool test::CGameApp::Initialize(void) {
    ::CUtilities::SetCurrentDirectory("TestResource");
//    bool loaded = _gizmo.Load("gizmo.mom");
    bool loaded = _gizmo.Load("bolt/scene02.mom");

    my::Gamepad::GetInstance().Create();
    _camera_manager = std::make_shared<my::CameraManager>();
    my::CameraController::SetCameraManager(_camera_manager);


    using Mode = my::CameraController::CameraMode;
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

    auto pos = _transform.position;
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
        _transform.position.x += move;
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_D)) {
        _transform.position.x -= move;
    } // else if
    if (::g_pInput->IsKeyHold(MOFKEY_W)) {
        _transform.position.z -= move;
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_S)) {
        _transform.position.z += move;
    } // else if

    if (::g_pInput->IsKeyHold(MOFKEY_E)) {
        _transform.rotate.y -= move;
    } // if
    if (::g_pInput->IsKeyHold(MOFKEY_R)) {
        _transform.rotate.y += move;
    } // if


    // camera
    auto controller = _camera_controller.GetService();
    using Mode = my::CameraController::CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            this->InputFollow(controller);
            break;
        case Mode::FirstPerson:
            this->InputFirstPerson(controller);
            break;
    } // switch
    return TRUE;
}

MofBool test::CGameApp::Update(void) {
    this->Input();

    float delta_time = 1.0f / 60.0f;
    auto controller = _camera_controller.GetService();
    using Mode = my::CameraController::CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            this->UpdateFollow(delta_time, controller);
            break;
        case Mode::FirstPerson:
            this->UpdateFirstPerson(delta_time, controller);
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
    _gizmo.Render(_transform.Matrix());
    _gizmo.Render(Mof::CMatrix44());


    ::CGraphicsUtilities::RenderGrid(2, 20, MOF_COLOR_WHITE, PLANEAXIS_ALL);

    ::g_pGraphics->SetDepthEnable(false);

    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "Camera Controller Test Application ");
    ::CGraphicsUtilities::RenderString(10.0f, 30.0f, "FPS = %d", ::CUtilities::GetFPS());
    using Mode = my::CameraController::CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            ::CGraphicsUtilities::RenderString(10.0f, 50.0f, "Mode = Follow");
            break;
        case Mode::FirstPerson:
            ::CGraphicsUtilities::RenderString(10.0f, 50.0f, "Mode = FirstPerson");
            break;
    } // switch

    auto actor_pos = _transform.position;
    auto camera_pos = _camera_controller.GetService()->GetCameraPosition();
    ::CGraphicsUtilities::RenderString(10.0f, 100.0f, "actor_pos.x = %f", actor_pos.x);
    ::CGraphicsUtilities::RenderString(10.0f, 120.0f, "actor_pos.y = %f", actor_pos.y);
    ::CGraphicsUtilities::RenderString(10.0f, 140.0f, "actor_pos.z = %f", actor_pos.z);
    ::CGraphicsUtilities::RenderString(10.0f, 160.0f, "camera_pos.x = %f", camera_pos.x);
    ::CGraphicsUtilities::RenderString(10.0f, 180.0f, "camera_pos.y = %f", camera_pos.y);
    ::CGraphicsUtilities::RenderString(10.0f, 200.0f, "camera_pos.z = %f", camera_pos.z);


    ::g_pGraphics->RenderEnd();
    return TRUE;
}

MofBool test::CGameApp::Release(void) {
    _camera_manager.reset();
    my::Gamepad::GetInstance().Release();
    return TRUE;
}