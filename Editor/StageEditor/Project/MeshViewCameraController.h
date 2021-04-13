#pragma once
#include "CameraController.h"
class MeshViewCameraController : public CameraController {
private:

	float _prev_zoom{ 1.0f };

	Controller MeshViewController(void);

public:

	void Update(void);

};

