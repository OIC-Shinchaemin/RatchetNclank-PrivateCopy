#include "RenderMeshCommand.h"

ratchet::game::graphics::RenderMeshCommand::RenderMeshCommand(const std::shared_ptr<Mof::CMeshContainer> ptr, const Mof::CMatrix44& world, const Mof::CVector4& color) :
	_mesh(ptr),
	_world(world),
	_color(color) {
}

bool ratchet::game::graphics::RenderMeshCommand::Execute(void) {
    if (auto mesh = _mesh.lock()) {
        mesh->Render(_world);
		return true;
	} // if
	return false;
}