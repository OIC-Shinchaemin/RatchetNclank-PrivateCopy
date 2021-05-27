#include "StageViewEvent.h"


my::StageViewEvent::StageViewEvent() :
    super(),
    _stage_view_camera(),
    _stage_view_camera_controller() {
}

my::StageViewEvent::~StageViewEvent() {
}
/*
void my::StageViewEvent::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}
*/

std::shared_ptr<my::Observable<const my::CameraController::CameraInfo&>> my::StageViewEvent::GetSubject(void) const {
    return std::dynamic_pointer_cast<my::AutoCameraController>(_stage_view_camera_controller.GetService());
}

bool my::StageViewEvent::Initialize(void) {
    _stage_view_camera = std::make_shared<my::Camera>();
    _stage_view_camera->Initialize();
    _stage_view_camera->Update();
    auto auto_camera_controller = std::make_shared<my::AutoCameraController>();
    _stage_view_camera_controller.SetService(auto_camera_controller);
    _stage_view_camera_controller.GetService()->SetCamera(_stage_view_camera);
    _stage_view_camera_controller.GetService()->RegisterGlobalCamera();
    //auto_camera_controller->AddObserver(player->GetComponent<my::CameraComponent>());
    return true;
}

bool my::StageViewEvent::Update(float delta_time) {
#ifdef _DEBUG
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        auto tmep = _stage_view_camera_controller.GetService();
        auto controller = std::dynamic_pointer_cast<my::AutoCameraController>(tmep);
        controller->ForceTick(controller->GetTimeMax());
    } // if
#endif // _DEBUG
    auto camera_info = my::CameraController::CameraInfo();
    _stage_view_camera_controller.GetService()->Update(delta_time, camera_info);
    return true;
}