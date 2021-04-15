#include "QuickChangeMenu.h"


my::QuickChangeMenu::QuickChangeMenu(const char* name) :
    super(name) {
}

void my::QuickChangeMenu::OnNotify(Mof::CVector4 color) {
    this->SetColor(color);
}
void my::QuickChangeMenu::AddWeaponObserver(const std::shared_ptr<my::Observer<std::string>>& ptr) {
    _weapon.AddObserver(ptr);
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