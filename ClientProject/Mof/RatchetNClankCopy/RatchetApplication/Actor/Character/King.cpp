#include "King.h"

#include "../../Scene/GameScene.h"
#include "../../Component/VelocityComponent.h"
#include "../../Component/MeshComponent.h"
#include "../../Factory/FactoryManager.h"


ratchet::actor::character::King::King() :
    super(),
    _actor_container(),
    _quest_index() {
}

ratchet::actor::character::King::~King() {
}

void ratchet::actor::character::King::OnNotify(const ratchet::actor::character::ScarecrowEndMessage&) {
    auto message = ratchet::game::gamesystem::text::TextSystemMessage();
    message.type = decltype(message.type)::EventNo0;
    _text_system_message_subject.Notify(message);
}

void ratchet::actor::character::King::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_question_texture = ptr;
}
void ratchet::actor::character::King::SetGameScene(const std::shared_ptr<scene::GameScene>& ptr) {
    this->_actor_container = ptr;
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
    return true;
}

bool ratchet::actor::character::King::Render(void) {
    super::Render();

    // •`‰æ
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
    static int a = 0;
    auto param = new ratchet::actor::Actor::Param();

    if (a != 2) {
        auto message = ratchet::game::gamesystem::text::TextSystemMessage();
        message.type = decltype(message.type)::EventNo0;
        _text_system_message_subject.Notify(message);

        auto out = _actor_container.lock();

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
            scarecrow->GetScarecrowEndMessageSubject()->AddObserver(std::dynamic_pointer_cast<ratchet::actor::character::King>(shared_from_this()));
            out->AddElement(scarecrow);
        } // for
    } // if
    else {
        auto message = ratchet::game::gamesystem::text::TextSystemMessage();
        message.type = decltype(message.type)::EventNo1;
        _text_system_message_subject.Notify(message);
    } // else
    a++;

    ut::SafeDelete(param);

}