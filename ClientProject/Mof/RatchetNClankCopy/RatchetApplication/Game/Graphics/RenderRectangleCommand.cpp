#include "RenderRectangleCommand.h"


ratchet::game::graphics::RenderRectangleCommand::RenderRectangleCommand(float l, float t, float r, float b, unsigned int col) :
    _rectangle(l, t, r, b), _color(col) {
}

ratchet::game::graphics::RenderRectangleCommand::RenderRectangleCommand(const Mof::CRectangle& rect, unsigned int col) :
    _rectangle(rect),
    _color(col) {
}

bool ratchet::game::graphics::RenderRectangleCommand::Execute(void) {
    ::CGraphicsUtilities::RenderFillRect(_rectangle, _color);
    return true;
}
