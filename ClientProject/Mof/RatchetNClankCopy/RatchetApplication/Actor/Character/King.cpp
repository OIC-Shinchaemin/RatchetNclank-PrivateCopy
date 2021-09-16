#include "King.h"

#include "../../Scene/GameScene.h"
#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"
#include "../../Factory/FactoryManager.h"
#include "../../Camera/FollowCameraController.h"
#include "../Character/Player.h"


ratchet::actor::character::King::King() :
    super(),
    _actor_container(),
    _quest_index(0),
    _quest_count(3),
    _text_system_message_subject(),
    _player_camera_subject(),
    _scarecrow_view_camera_controller(),
    _scarecrow_view_position(3.0f, -3.0f, 0.0f),
    _player_view_camera_controller(),
    _effect_container(),
    _player() {

    auto con = std::make_shared<ratchet::camera::FollowCameraController>();
    auto camera = std::make_shared<ratchet::camera::Camera>();
    camera->Initialize();
    con->SetCamera(camera);
    _scarecrow_view_camera_controller.SetService(con);
}

ratchet::actor::character::King::~King() {
}

void ratchet::actor::character::King::OnNotify(const ratchet::actor::character::ScarecrowEndMessage&) {
    auto message = ratchet::game::gamesystem::text::TextSystemMessage();
    auto type_temp = static_cast<int>(decltype(message.type)::TutorialEventNo0End) + _quest_index - 1;
    message.type = static_cast<decltype(message.type)>(type_temp);
    _text_system_message_subject.Notify(message);
}

void ratchet::actor::character::King::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_question_texture = ptr;
}
void ratchet::actor::character::King::SetGameScene(const std::shared_ptr<scene::GameScene>& ptr) {
    this->_actor_container = ptr;
}

void ratchet::actor::character::King::SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr) {
    this->_effect_container = ptr;
}

void ratchet::actor::character::King::SetPlayer(const std::shared_ptr<ratchet::actor::character::Player>& ptr) {
    this->_player = ptr;
}

void ratchet::actor::character::King::SetPlayerCameraontroller(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr) {
    this->_player_view_camera_controller = ptr;
}

bool ratchet::actor::character::King::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);

    auto velocity = super::GetComponent<ratchet::component::VelocityComponent>();
    velocity->Inactivate();
    velocity->SetUseGravity(false);

    auto mesh = super::GetComponent<ratchet::component::MeshComponent>();
    auto motion = mesh->GetMeshContainer()->CreateMotionController();
    auto count = motion->GetMotionCount();
    return true;
}

bool ratchet::actor::character::King::Update(float delta_time) {
    super::Update(delta_time);
    auto camera = _scarecrow_view_camera_controller.GetService();
    auto info = camera::CameraController::CameraInfo();
    info.ideal_position = super::GetPosition();
    camera->Update(delta_time, info);
    return true;
}

bool ratchet::actor::character::King::Render(void) {
    super::Render();

    // �`��
    auto pos = super::GetPosition();
    float height = 2.4f;
    auto transform = def::Transform(Mof::CVector3(pos.x, pos.y + height, pos.z));
    if (auto tex = _question_texture.lock(); tex) {
        Mof::CMatrix44 scale, rotate, translate;
        Mof::CQuaternion quat; quat.Rotation(transform.rotate);

        scale.Scaling(transform.scale, scale);
        quat.ConvertMatrixTranspose(rotate);
        translate.Translation(transform.position, translate);

        Mof::CMatrix44 world = scale * rotate * translate;
        auto camera = ::CGraphicsUtilities::GetCamera();
        tex->Render(camera->GetBillBoardMatrix() * world);

        //CGraphicsUtilities::RenderTexture();
        //tex->Render(world, _rectangle.value());
    } // if
    return true;
}

void ratchet::actor::character::King::Talk(void) {
    auto param = new ratchet::actor::Actor::Param();
    auto out = _actor_container.lock();
    auto effect = _effect_container.lock();
    auto player = _player.lock();

    if (_quest_index < _quest_count) {
        auto message = ratchet::game::gamesystem::text::TextSystemMessage();
        auto type_temp = static_cast<int>(decltype(message.type)::EventNo0) + _quest_index;
        message.type = static_cast<decltype(message.type)>(type_temp);
        message.on_close = [&]() {
            _player_view_camera_controller->GetService()->RegisterGlobalCamera();

            auto target = Mof::CVector3(-12.0f, -5.0f, -4.0f);
            auto player_camera = _player_view_camera_controller->GetService();
            auto dir = target - _player.lock()->GetPosition();
            player_camera->SetAzimuth(math::ToDegree(std::atan2(-dir.z, dir.x)));
            return true;
        };
        _text_system_message_subject.Notify(message);


        // create
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
            scarecrow->GetScarecrowEndMessageSubject()->AddObserver(std::dynamic_pointer_cast<ratchet::actor::character::King>(shared_from_this()));
            auto emitter = effect->CreateEmitter();
            scarecrow->SetEffectEmitter(emitter);
            out->AddElement(scarecrow);

            // camera
            //auto info = camera::CameraController::CameraInfo();
            //info.target_position = super::GetPosition();
            //info.ideal_position = ::CGraphicsUtilities::GetCamera()->GetViewPosition();
            //info.start_position = ::CGraphicsUtilities::GetCamera()->GetViewPosition();
            //info.camera_front = Mof::CVector3(0.0f, 0.0f, 0.0f);
            //auto con = _scarecrow_view_camera_controller.GetService();

            //float angle_y = std::atan2(-(info.target_position.z - info.start_position.z),
            //                           (info.target_position.x - info.start_position.x)) -
            //    math::kHalfPi;
            //auto angle = Mof::CVector3(0.0f, angle_y, 0.0f);
            //con->SetAzimuth(angle_y);
            //con->SetAltitude(20.0f);
            //con->SetDistance(3.0f);
            //con->RegisterGlobalCamera();
            //con->SetInfo(info);

            auto player_camera = _player_view_camera_controller->GetService();
            //player->GetPosition();
            //auto player_pos = player->GetPosition();
            //auto pos = super::GetPosition();
            auto dir = super::GetPosition() - player->GetPosition();
            player_camera->SetAzimuth(math::ToDegree(std::atan2(-dir.z, dir.x)));
        } // for

        ut::SafeDelete(param);
        _quest_index++;

    } // if
    else {
        auto message = ratchet::game::gamesystem::text::TextSystemMessage();
        message.type = decltype(message.type)::KingTextEvent;
        _text_system_message_subject.Notify(message);
    } // else
    //a++;


}