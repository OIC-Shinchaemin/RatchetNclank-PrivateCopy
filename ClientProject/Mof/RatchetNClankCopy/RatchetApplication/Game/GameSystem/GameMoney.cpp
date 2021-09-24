#include "GameMoney.h"

#include "Base/Core/Utility.h"
#include "../../UI/GameMoneyMenu.h"
#include "../../Event/EventReferenceTable.h"
#include "../../Event/BridgeEvent.h"
#include "../../Event/EnemyViewEvent.h"
#include "../../Actor/Character/Player.h"


ratchet::game::gamesystem::GameMoney::GameMoney() :
	_value(),
	_value_max(40),
	_subject(),
	_resource(),
	_ui_canvas(),
	_event_manager(),
	_text_system_message_subject(),
	_text_system() {
}

ratchet::game::gamesystem::GameMoney::~GameMoney() {
	_resource.reset();
	_ui_canvas.reset();
	_event_manager.reset();
}

void ratchet::game::gamesystem::GameMoney::OnNotify(int add_money) {
	this->_value += add_money;
	if (this->_value < 0) {
		this->_value = 0;
	} // if

	auto message = game::gamesystem::GameMoneyMessage();
	message.money = _value;
	message.money_max = _value_max;

	if (message.money > message.money_max) {
		//if (auto e = _event_manager.lock()) {
		//	auto bridge_event = e->CreateGameEvent<ratchet::event::BridgeEvent>();
		//	bridge_event->Initialize();
		//} // if

		auto message = ratchet::game::gamesystem::text::TextSystemMessage();
		message.type = decltype(message.type)::ItemCollectionCompleteEvent;
		message.on_close = [&]() {
			// enemy view event
			//if (ratchet::event::EventReferenceTable::Singleton().Exist("player")) {
//				player->Sleep();
//				player_event->GetPlayerActionAfterGettingOffElevatorEventEndSubject()->AddObserver(player);
//				player_event->Start();
//			} // if


			auto player = ratchet::event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player>>("player");
			auto e = ratchet::event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::event::EventManager>>("EventManager");
			auto view_event = e->CreateGameEvent<ratchet::event::EnemyViewEvent>();
			//view_event->GetEnemyViewEventMessageSubject()->AddObserver(player_event);
			view_event->SetStartPosition(player->GetPosition());
			view_event->SetPlayerCamera(player->GetComponent<component::CameraComponent>()->GetCameraController());
			view_event->GetCameraObservable()->AddObserver(player->GetComponent<component::CameraComponent>());
			view_event->Initialize();
			view_event->GetTextSystemMessageSubject()->AddObserver(_text_system.lock());
			//view_event->GetTextSystemMessageSubject()
			//view_event->GetTextSystemMessageSubject()->
			return true;
		};

		_text_system_message_subject.Notify(message);
	} // if
	_subject.Notify(message);
}

void ratchet::game::gamesystem::GameMoney::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
	this->_resource = ptr;
}

void ratchet::game::gamesystem::GameMoney::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
	this->_ui_canvas = ptr;
}

void ratchet::game::gamesystem::GameMoney::SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr) {
	this->_event_manager = ptr;
}

void ratchet::game::gamesystem::GameMoney::SetTextSystem(std::weak_ptr<ratchet::game::gamesystem::text::TextSystem> ptr)
{
	this->_text_system = ptr;
}

std::uint32_t ratchet::game::gamesystem::GameMoney::GetValue(void) const {
	return this->_value;
}

bool ratchet::game::gamesystem::GameMoney::Load(ratchet::game::gamesystem::save::SaveData& in) {
	_value = in.GetMoney();
	return true;
}

bool ratchet::game::gamesystem::GameMoney::Initialize(void) {
	_ASSERT_EXPR(!_resource.expired(), L"無効なポインタを保持しています");
	_ASSERT_EXPR(!_ui_canvas.expired(), L"無効なポインタを保持しています");

	if (auto canvas = _ui_canvas.lock()) {
		canvas->RemoveElement("GameMoneyMenu");
	} // if
	auto menu = std::make_shared< ratchet::ui::GameMoneyMenu>("GameMoneyMenu");
	_subject.AddObserver(menu);
	menu->SetColor(def::color_rgba::kCyan);
	menu->SetResourceManager(_resource);
	menu->Initialize();
	if (auto canvas = _ui_canvas.lock()) {
		canvas->AddElement(menu);
	} // if
	return true;
}

bool ratchet::game::gamesystem::GameMoney::Release(void) {
	if (auto canvas = _ui_canvas.lock()) {
		canvas->RemoveElement("GameMoneyMenu");
	} // if
	return false;
}