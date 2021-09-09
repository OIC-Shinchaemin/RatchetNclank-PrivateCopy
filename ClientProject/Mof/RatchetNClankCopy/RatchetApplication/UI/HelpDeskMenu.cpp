#include "HelpDeskMenu.h"

#include <cmath>


ratchet::ui::HelpDeskMenu::HelpDeskMenu(const char* name) :
	super(name),
	_blinking_on_timer(),
	_blinking_off_timer(),
	_blinking_on(false),
	_slide_on(false),
	_move_source(-250.0f, 10.0f),
	_move_destination(10.0f, 10.0f),
	_move_time(),
	_move_time_max(1.0f),
	_tween_pos_x(){
	_blinking_on_timer.Initialize(2.0f, true);
	_blinking_off_timer.Initialize(0.5f, true);
	super::_position = Mof::CVector2(10.0f, 10.0f);

	_tween_pos_x.Start(_move_source.x, _move_destination.x, _move_time_max, base::core::EaseType::Linear);
}

void ratchet::ui::HelpDeskMenu::OnNotify(const ratchet::game::gamesystem::HelpDesk::Info& info) {
	super::Notify(shared_from_this(), "Enable");
	if (info.show) {
		_slide_on = true;
	} // if
	else {
		_infomation = info;
	} // else
}

void ratchet::ui::HelpDeskMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
	this->_resource = ptr;
}

bool ratchet::ui::HelpDeskMenu::Update(float delta_time) {
	// ˆê’èŽžŠÔ•\Ž¦‚µ‚½‚çfalse‚ð•Ô‚·
	super::_position.x++;

	if (_blinking_on && _blinking_on_timer.Tick(delta_time)) {
		_blinking_on = false;
	} // if
	else if (!_blinking_on && _blinking_off_timer.Tick(delta_time)) {
		_blinking_on = true;
	} // else if

	if (_slide_on) {
		_move_time += delta_time;
		_move_time = std::clamp(_move_time, 0.0f, _move_time_max);
	} // if
	return true;
}

bool ratchet::ui::HelpDeskMenu::Render(void) {
	if (_blinking_on) {
		auto pos = super::_position;
		//pos.x = this->Lerp(_move_time, _move_time_max, _move_destination.x, _move_source.x);
		pos.x = _tween_pos_x.Output(_move_time);
		
		auto text = _infomation.text.c_str();
		::CGraphicsUtilities::RenderString(pos.x + 1, pos.y + 1, def::color_rgba_u32::kBlack, "%s", text);
		::CGraphicsUtilities::RenderString(pos.x, pos.y, def::color_rgba_u32::kWhite, "%s", text);
	} // if
	return true;
}