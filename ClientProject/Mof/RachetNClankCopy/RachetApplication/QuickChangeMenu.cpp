#include "QuickChangeMenu.h"

my::QuickChangeMenu::QuickChangeMenu(const char* name) :
    super(name) {
}

void my::QuickChangeMenu::OnNotify(const std::shared_ptr<my::QuickChangeSystem>& observable, const char* event) {
    if (event == "UpdateColor") {
        this->SetColor(observable->GetColor());
    } // if
}

bool my::QuickChangeMenu::Render(void) {
    auto circle = Mof::CCircle(_position, 128.0f);
    ::CGraphicsUtilities::RenderCircle(circle, _color.ToU32Color());
    return true;
}

my::QuickChangeMenuItem::QuickChangeMenuItem(const char* name) :
    super(name) {
}

bool my::QuickChangeMenuItem::Render(void) {
    return true;
}