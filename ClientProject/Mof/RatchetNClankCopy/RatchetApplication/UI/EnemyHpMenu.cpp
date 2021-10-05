//#include "EnemyHpMenu.h"
//
//
//ratchet::ui::EnemyHpMenu::EnemyHpMenu(const char* name) :
//	super(name),
//	_hp_max(4),
//	_hp(_hp_max),
//	_resource_manager(),
//	_ui_canvas(),
//	_scale(ratchet::kWindowPerXGA) {
//	this->SetPosition(Mof::CVector2(1580.0f, 60.0f));
//}
//
//void ratchet::ui::EnemyHpMenu::OnNotify(int hp) {
//	super::Notify(shared_from_this(), "Enable");
//	this->_hp = hp;
//}
//
//void ratchet::ui::EnemyHpMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
//	this->_resource_manager = ptr;
//}
//
//void ratchet::ui::EnemyHpMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
//	this->_ui_canvas = ptr;
//}
//
//bool ratchet::ui::EnemyHpMenu::Initialize(int max_value, int hp)
//{
//	this->_hp_max = max_value;
//	this->_hp = hp;
//	return true;
//}
//
//bool ratchet::ui::EnemyHpMenu::Update(float delta_time) {
//	if (_hp < 0) {
//		return false;
//	} // if
//	return true;
//}
//
//bool ratchet::ui::EnemyHpMenu::Render(void) {
//	auto pos = super::_position;
//	std::shared_ptr<Mof::CTexture> tex;
//	std::shared_ptr<Mof::CTexture> empty_tex;
//	if (auto r = _resource_manager.lock()) {
//		tex = r->Get<std::shared_ptr<Mof::CTexture> >("../Resource/texture/nanotech/nanotech.png");
//		empty_tex = r->Get<std::shared_ptr<Mof::CTexture> >("../Resource/texture/nanotech/nanotech_empty.png");
//	} // if
//	tex->RenderScale(pos.x, pos.y, _scale);
//	return true;
//}