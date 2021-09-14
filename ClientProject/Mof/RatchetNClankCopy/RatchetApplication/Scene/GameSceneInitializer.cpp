#include "GameSceneInitializer.h"

#include "../Gamepad.h"
#include "../Factory/FactoryManager.h"
#include "../Actor/Character/Enemy.h"
#include "../Actor/Character/Player.h"
#include "../Actor/Character/King.h"
#include "../Actor/Character/Scarecrow.h"
#include "../Actor/Facility/Shop.h"
#include "../Actor//Terrain/Terrain.h"
#include "../Actor/Gimmick/Wall.h"
#include "../Actor/Gimmick/Fence.h"
#include "../Component/CameraComponent.h"
#include "../Stage/Gimmick/Bridge.h"
#include "../Event/BridgeEvent.h"
#include "../Event/ShipEvent.h"
#include "../Event/StageViewEvent.h"
#include "../Event/TextSystemStartEvent.h"
#include "../Stage/Gimmick/Bridge.h"


ratchet::scene::GameSceneInitializer::GameSceneInitializer() {
}

bool ratchet::scene::GameSceneInitializer::Execute(std::shared_ptr<ratchet::game::GameManager>& game, std::shared_ptr<ratchet::event::EventManager>& event, std::shared_ptr<ratchet::scene::GameScene>& out) {
	out->_stage.Initialize();
	ratchet::event::EventReferenceTable::Singleton().Reset();

	std::shared_ptr<ratchet::event::BridgeEvent> bridge_event;
	std::shared_ptr<ratchet::event::ShipEvent> ship_event;
	std::shared_ptr<ratchet::event::StageViewEvent> stage_view_event;
	auto shared_this = out;

	out->_text_system->GetTextSystemClosedMessageSubject()->Clear();

	if (auto e = event) {
		e->InitializeGameEvent();
		bridge_event = e->CreateGameEvent<ratchet::event::BridgeEvent>();
		ship_event = e->CreateGameEvent<ratchet::event::ShipEvent>();
		stage_view_event = e->CreateGameEvent<ratchet::event::StageViewEvent>();
		stage_view_event->SetGameScene(shared_this);
		stage_view_event->SetTextSystem(out->_text_system);
		stage_view_event->GetStageViewEventMessageSubject()->AddObserver(shared_this);
	} // if

	bridge_event->SetStage(&out->_stage);
	bridge_event->Initialize();
	ship_event->Initialize();
	stage_view_event->Initialize();

	bridge_event->GetCameraSubject()->AddObserver(ship_event);
	ship_event->GetShipEventSubject()->AddObserver(out);

	for (auto gimmick : out->_stage.GetGimmickArray()) {
		auto temp = std::dynamic_pointer_cast<Bridge>(gimmick);
		if (temp) {
			temp->AddObserver(ship_event);
		} // if
	} // for


	auto param = new ratchet::actor::Actor::Param();

	// player
	param->transform.position = Mof::CVector3(5.0f, 5.0f, -5.0f);
	param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
	auto player = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Player>("../Resource/builder/player.json", param);
	out->AddElement(player);
	out->_text_system->GetTextSystemClosedMessageSubject()->AddObserver(player);
	stage_view_event->GetCameraObservable()->AddObserver(player->GetComponent<ratchet::component::CameraComponent>());

	{
		param->transform.position = Mof::CVector3(15.0f, -5.0f, 7.0f);
		param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
		auto shop = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::facility::Shop >("../Resource/builder/shop.json", param);
		out->AddElement(shop);
	}
	{
		param->name = "weapon";
		param->tag = "OmniWrench";
		auto omniwrench = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::weapon::OmniWrench>("builder/omni_wrench.json", param);
		player->AddChild(omniwrench);
		out->AddElement(omniwrench);
	}


	// game system
	//if (auto game = _game.lock()) 
	{
		auto pause_system = game->GetGamePauseSystem();
		auto weapon_system = game->GetWeaponSystem();
		auto quick_change = game->GetQuickChange();
		auto help_desk = game->GetHelpDesk();
		auto game_money = game->GetGameMoney();
		auto shop_system = game->GetShopSystem();

		shop_system->GetInfoSubject()->AddObserver(shared_this);
		player->GetShopSystemSubject()->AddObserver(game->GetShopSystem());
		player->GetQuickChangeSubject()->AddObserver(game->GetQuickChange());
		player->PushNotificationableSubject("QuickChange");
		player->GetQuestSubject()->AddObserver(help_desk);

		// game system
		weapon_system->Initialize(shared_this);
		quick_change->Initialize(weapon_system);
		game_money->Initialize();
		help_desk->Initialize();
		shop_system->Initialize();
		pause_system->Initialize();

		auto quest = ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::ToFront);
		help_desk->OnNotify(quest);
		stage_view_event->SetHelpDesk(help_desk);
		bridge_event->GetQuestSubject()->AddObserver(help_desk);
		weapon_system->AddMechanicalWeaponObserver(player);
		quick_change->AddWeaponObserver(weapon_system);
		quick_change->AddInfoObserver(player);
		out->_pause_menu_subject.AddObserver(pause_system);

		auto weapons = weapon_system->GetWeaponMap();
		for (auto& pair : weapons) {
			player->AddChild(pair.second);
		} // for
	} // if


	auto help_desk = game->GetHelpDesk();
	// enemy
	for (auto enemy_spawn : out->_stage.GetEnemySpawnArray()) {
		auto event_sphere = Mof::CSphere(180.0f, -30.0f, 25.0f, 40.0f);
		_ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"Œ^‚ªˆê’v‚µ‚Ü‚¹‚ñ");
		auto builder = enemy_spawn.first.c_str();
		param->name = enemy_spawn.second->GetName();
		param->transform.position = enemy_spawn.second->GetPosition();
		auto enemy = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Enemy>(builder, param);
		out->AddElement(enemy);
		enemy->GetQuestSubject()->AddObserver(help_desk);

		if (event_sphere.CollisionPoint(param->transform.position)) {
			bridge_event->AddTriggerActor(enemy);
		} // if
	} // for

	// terrain
	def::Transform terrain_transforms[]{
		def::Transform(Mof::CVector3(0.0f, -31.2f, 0.0f), Mof::CVector3(), Mof::CVector3(540.0f, 1.0f, 540.0f)),
	};
	for (auto& transform : terrain_transforms) {
		param->transform.scale = transform.scale;
		param->transform.position = transform.position;
		auto terrain = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::terrain::Terrain>("../Resource/builder/water_flow.json", param);
		out->AddElement(terrain);
	} // for


	{
		// wall
		def::Transform wall_transforms[]{
			def::Transform(Mof::CVector3(43.0f, -4.0f, -13.0f)),
			def::Transform(Mof::CVector3(-3.0f, -4.0f, -51.0f)),
		};
		param->tag = "wall";
		param->name = "wall_1";
		for (auto& transform : wall_transforms) {
			param->transform.position = transform.position;
			param->transform.scale = transform.scale;
			auto gimmick = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::gimmick::Wall >("../Resource/builder/wall.json", param);
			out->AddElement(gimmick);
			param->name = "wall_2";
		} // for
	}



	{
		// fence
		def::Transform wall_transforms[]{
			def::Transform(Mof::CVector3(-13.0f, -5.0f, 3.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
			def::Transform(Mof::CVector3(-13.0f, -5.0f, -13.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
			def::Transform(Mof::CVector3(-8.0f, -5.0f, -13.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
			def::Transform(Mof::CVector3(-3.0f, -5.0f, -13.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
			def::Transform(Mof::CVector3(3.0f, -5.0f, -13.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
		};
		param->tag = "fence";
		param->name = "fence";
		int index = 0;
		for (auto& transform : wall_transforms) {
			param->transform.position = transform.position;
			param->transform.rotate = transform.rotate;
			param->transform.scale = transform.scale;
			auto fence = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::gimmick::Fence>("../Resource/builder/fence.json", param);
			out->AddElement(fence);
			param->name = std::string("fence") + std::to_string(index);
			index++;
		} // for
	}



	std::vector<ratchet::actor::character::ScarecrowEndMessageSubject*> scarecrow_end_message_subjects;
	{
		// npc
		def::Transform scarecrow_transforms[]{
			def::Transform(Mof::CVector3(-12.0f, -5.0f, -4.0f)),
		};
		param->tag = "scarecrow";
		param->name = "scarecrow_1";
		for (auto& transform : scarecrow_transforms) {
			param->transform.position = transform.position;
			param->transform.rotate = transform.rotate;
			param->transform.scale = transform.scale;
			auto scarecrow = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::character::Scarecrow>("../Resource/builder/scarecrow.json", param);
			scarecrow_end_message_subjects.push_back(scarecrow->GetScarecrowEndMessageSubject());
			out->AddElement(scarecrow);
		} // for
	}

	// npc
	{
		def::Transform npc_transforms[]{
			def::Transform(Mof::CVector3(8.0f, -5.0f, -2.0f), Mof::CVector3(0.0f, 45.0f , 0.0f)),
		};
		param->tag = "king";
		param->name = "king";
		for (auto& transform : npc_transforms) {
			param->transform.position = transform.position;
			param->transform.rotate = transform.rotate;
			param->transform.scale = transform.scale;
			auto king = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::character::King >("../Resource/builder/king.json", param);
			auto tex = out->GetResource()->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/ui/icon/question.png");
			king->SetTexture(tex);
			king->GetTextSystemMessageSubject()->AddObserver(out->_text_system);
			out->AddElement(king);

			for (auto subject : scarecrow_end_message_subjects) {
				subject->AddObserver(king);
			} // for
		} // for
	}



	ut::SafeDelete(param);


	return true;
}