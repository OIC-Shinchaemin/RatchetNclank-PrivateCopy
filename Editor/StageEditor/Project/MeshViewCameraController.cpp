#include "MeshViewCameraController.h"
#include "ParameterMap.h"

MeshViewCameraController::Controller MeshViewCameraController::MeshViewController(void) {
	Controller controller;
	static float rotation = 0.0f;
	float* zoom = ParameterMap<float>::GetInstance().Get("mesh_view_zoom");
	controller.track.trigger_flag    = false;
	controller.rotation.trigger_flag = true;
	controller.rotation.move         = Vector3(0.01f, 0, 0);
	controller.zoom.trigger_flag     = (_prev_zoom != *zoom);
	controller.zoom.move             = (*zoom - _prev_zoom);
	return controller;
}

void MeshViewCameraController::Update(void) {
	CameraController::Update(MeshViewController());
}
