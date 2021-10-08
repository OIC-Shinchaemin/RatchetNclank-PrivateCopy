#include "RenderAnimationMeshCommand.h"

ratchet::game::graphics::RenderAnimationMeshCommand::RenderAnimationMeshCommand(const std::shared_ptr<Mof::CMeshContainer> ptr, Mof::LPMeshMotionController motion, const Mof::CVector4& color) :
	_mesh(ptr),
	_motion(motion),
	_color(color) {
}

bool ratchet::game::graphics::RenderAnimationMeshCommand::Execute(void) {
	// •`‰æ
	if (auto mesh = _mesh.lock()) {
		mesh->Render(_motion, _color);
	} // if
	return true;
}
