#include "Queen.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::character::Queen::Queen() :
    super() {
}

ratchet::actor::character::Queen::~Queen() {
}

bool ratchet::actor::character::Queen::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);

    auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
    velocity->Inactivate();
    velocity->SetUseGravity(false);
    return true;
}

bool ratchet::actor::character::Queen::Update(float delta_time) {
    super::Update(delta_time);
    //auto camera = _scarecrow_view_camera_controller.GetService();
    //auto info = camera::CameraController::CameraInfo();
    //info.ideal_position = super::GetPosition();
    //camera->Update(delta_time, info);
    return true;
}

void ratchet::actor::character::Queen::Talk(void) {
    auto param = new ratchet::actor::Actor::Param();
    //auto out = _actor_container.lock();
    //auto player = _player.lock();

    auto message = ratchet::game::gamesystem::text::TextSystemMessage();
    /*
    if (_free_talk_index == 0) {
        message.type = decltype(message.type)::ItemCollectionCompleteEvent;

        message.on_close = [&]() {
            // event fire
            return true;
        };
        _free_talk_index++;
    } // if
    else {
       message.type = decltype(message.type)::KingFreeTalkTextEvent;
    } // else
    */

    message.type = decltype(message.type)::QueenFreeTalkTextEvent;
    _text_system_message_subject.Notify(message);




  //if (_quest_index < _quest_count) {
  //    auto message = ratchet::game::gamesystem::text::TextSystemMessage();
  //    auto type_temp = static_cast<int>(decltype(message.type)::TutorialEventNo0) + _quest_index;
  //    message.type = static_cast<decltype(message.type)>(type_temp);
  //    message.on_close = [&]() {
  //        _event_icon_show = false;
  //        _player_view_camera_controller->GetService()->RegisterGlobalCamera();

  //        auto target = Mof::CVector3(-12.0f, -5.0f, -4.0f);
  //        auto player_camera = _player_view_camera_controller->GetService();
  //        auto dir = target - _player.lock()->GetPosition();
  //        player_camera->SetAzimuth(math::ToDegree(std::atan2(-dir.z, dir.x)));

  //        return true;
  //    };
  //    _text_system_message_subject.Notify(message);

  //    if (!_event_active) {
  //        if (message.type == decltype(message.type)::TutorialEventNo1) {
  //            this->BarricadeCreate(param, out);
  //        } // if

  //        auto& scarecrow_transforms = _scarecrow_generate_datas.at(_quest_index);
  //        // create
  //        param->tag = "scarecrow";
  //        for (auto& position : scarecrow_transforms.position) {
  //            param->transform.position = position;
  //            auto scarecrow = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::character::Scarecrow>("../Resource/builder/scarecrow.json", param);
  //            auto emitter = effect->CreateEmitter();
  //            scarecrow->SetEffectEmitter(emitter);
  //            scarecrow->GetScarecrowEndMessageSubject()->AddObserver(std::dynamic_pointer_cast<ratchet::actor::character::King>(shared_from_this()));
  //            out->AddElement(scarecrow);
  //            _created_scarecrows.push_back(scarecrow);
  //        } // for

  //        auto player_camera = _player_view_camera_controller->GetService();
  //        auto dir = super::GetPosition() - player->GetPosition();
  //        player_camera->SetAzimuth(math::ToDegree(std::atan2(-dir.z, dir.x)));
  //        this->PlayerActionLiberate();
  //        ut::SafeDelete(param);
  //        _quest_index++;
  //    } // if
  //    _event_active = true;
  //} // if
  //else {
  //    auto message = ratchet::game::gamesystem::text::TextSystemMessage();
  //    if (_free_talk_index == 0) {
  //        message.type = decltype(message.type)::KingTextEvent;

  //        message.on_close = [&]() {
  //            tutorial::TutorialManager::GetInstance().Complete();

  //            _player_view_camera_controller->GetService()->SetAzimuth(10);
  //            _player_view_camera_controller->GetService()->SetAltitude(20);

  //            if (auto help_desk = _help_desk.lock()) {
  //                help_desk->Show();
  //            } // if
  //            auto hp_com = _player.lock()->GetComponent<component::HpComponent>();
  //            if (hp_com) {
  //                hp_com->RegisterUI();
  //            } // if
  //            return true;
  //        };

  //        _free_talk_index++;
  //    } // if
  //    else {
  //        message.type = decltype(message.type)::KingFreeTalkTextEvent;
  //    } // else
  //    _text_system_message_subject.Notify(message);
  //} // else
}
