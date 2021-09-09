#include "TitleInfoMenu.h"


ratchet::ui::TitleInfoMenu::TitleInfoMenu(const char* name) :
	super(name),
	_show(true),
	_resource(),
	_ui_canvas(),
	_show_timer(),
	_start(false),
	_blinking_on_timer(),
	_blinking_off_timer(),
	_blinking_on(false),
	_texture_path("../Resource/texture/ui/text/press_button_text.png"){
	super::_position = Mof::CVector2(260.0f, 720.0f);
	_blinking_on_timer.Initialize(2.0f, true);
	_blinking_off_timer.Initialize(0.5f, true);

	//_text_elements.reserve(static_cast<std::size_t>(TextType::CountMax));
	//_text_elements.push_back(TextElem(TextType::Press,
	//	"../Resource/texture/ui/text/press.png",
	//	Mof::CVector2()));
	//_text_elements.push_back(TextElem(TextType::Start,
	//	"../Resource/texture/ui/text/start.png",
	//	Mof::CVector2()));
	//_text_elements.push_back(TextElem(TextType::Button,
	//	"../Resource/texture/ui/text/button.png",
	//	Mof::CVector2()));
	//_text_elements.push_back(TextElem(TextType::Or,
	//	"../Resource/texture/ui/text/or.png",
	//	Mof::CVector2()));
	//_text_elements.push_back(TextElem(TextType::Enter,
	//	"../Resource/texture/ui/text/enter.png",
	//	Mof::CVector2()));
	//_text_elements.push_back(TextElem(TextType::Key,
	//	"../Resource/texture/ui/text/key.png",
	//	Mof::CVector2()));
	//_text_elements.push_back(TextElem(TextType::ExclamationMark,
	//	"../Resource/texture/ui/text/ex_mark.png",
	//	Mof::CVector2()));
}

ratchet::ui::TitleInfoMenu::~TitleInfoMenu() {
}

void ratchet::ui::TitleInfoMenu::OnNotify(bool show) {
	if (show) {
		super::Notify(shared_from_this(), "Enable");
		_start = false;
		_show_timer.Initialize(3.0f, false);
	} // if
	_show = show;
}

void ratchet::ui::TitleInfoMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
	this->_resource = ptr;
}

void ratchet::ui::TitleInfoMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
	this->_ui_canvas = ptr;
}

bool ratchet::ui::TitleInfoMenu::Initialize(void) {
	super::Initialize();
	//auto pos = _position;
	//for (auto& elem : _text_elements) {
	//	if (auto resource = _resource.lock()) {
	//		elem.position = pos;
	//		auto tex = resource->Get<std::shared_ptr < Mof::CTexture >>(elem.path.c_str());
	//		auto size = Mof::CVector2(tex->GetWidth(), tex->GetHeight());
	//		pos.x += size.x;
	//	} // if
	//} // for
	return true;
}

bool ratchet::ui::TitleInfoMenu::Update(float delta_time) {
	if (_show_timer.Tick(delta_time)) {
		_start = true;

	} // if

	if (_blinking_on && _blinking_on_timer.Tick(delta_time)) {
		_blinking_on = false;
	} // if
	else if (!_blinking_on && _blinking_off_timer.Tick(delta_time)) {
		_blinking_on = true;
	} // else if
	return true;
}

bool ratchet::ui::TitleInfoMenu::Render(void) {
	if (!_show) {
		return false;
	} // if

	if (_start) {
		if (_blinking_on) {
			super::Render();
			if (auto resource = _resource.lock()) {
				auto center = Mof::CVector2(::g_pFramework->GetWindow()->GetWidth() * 0.5f, ::g_pFramework->GetWindow()->GetHeight() * 0.5f);
				float scale = 0.45f;
				auto tex = resource->Get<std::shared_ptr< Mof::CTexture>>(_texture_path.c_str());
				auto size = Mof::CVector2(tex->GetWidth(), tex->GetHeight()) * scale;
				auto half_size = size * 0.5f;
				_position = Mof::CVector2(center.x - half_size.x, _position.y);
				tex->RenderScale(_position.x, _position.y, scale, Mof::TextureAlignment::TEXALIGN_BOTTOMLEFT);
				/*
			for (auto& elem : _text_elements) {
				auto tex = resource->Get<std::shared_ptr< Mof::CTexture>>(elem.path.c_str());
				auto pos = elem.position;
				tex->Render(pos.x, pos.y);

				auto rect = Mof::CRectangle(pos.x, pos.y, pos.x + tex->GetWidth(), pos.y + tex->GetHeight());
				Mof::CGraphicsUtilities::RenderRect(rect, def::color_rgba_u32::kRed);
			} // for
				*/
			} // if
		} // if
	} // if
	return true;
}