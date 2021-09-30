#include "RenderBillboardCommand.h"

ratchet::game::graphics::RenderBillboardCommand::RenderBillboardCommand(const std::shared_ptr<Mof::CTexture> ptr, const Mof::CMatrix44& matrix, const Mof::CVector4 color) :
	_texture(ptr),
	_matrix(matrix),
	_color(color)
{
}

bool ratchet::game::graphics::RenderBillboardCommand::Execute(void) {
	if (auto tex = _texture.lock()) {
		tex->Render(_matrix);
	} // if
	return true;
}
