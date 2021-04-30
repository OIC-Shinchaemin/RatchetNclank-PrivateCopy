#include "PlayerCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../Player/PlayerComponent.h"
#include "../../Player/PlayerJumpComponent.h"
#include "../../VelocityComponent.h"


bool my::PlayerCollisionComponent::CollisionStageFrontRay(Mof::LPMeshContainer mesh, const StageObject& obj) {
    auto velocity_com = _velocity_com.lock();

    //接触情報
    COLLISIONOUTGEOMETRY gout;
    //進行方向へのレイ
    auto pos = super::GetOwner()->GetPosition();
    auto velocity = velocity_com->GetVelocity();

    // ステージ上の障害物との当たり判定　
    float offset = 0.5f;
    Mof::CRay3D mray(pos, velocity); // 進行方向へのレイ
    mray.Position.y += offset;
    if (mray.CollisionMesh(mesh, gout)) {
        float radius = 1.0f;
        if (gout.d <= velocity.Length() + radius) {
            float nd = Mof::CVector3Utilities::Dot(velocity, gout.Normal);
            nd = MOF_ABS(nd);
            // 進んだ方向に対して埋まった値の分だけ元に戻してやる
//			m_Move = (m_Move + gout.Normal * -2 * m_Move.Dot(gout.Normal)) * 0.5f;
            pos += mray.Direction * (gout.d - (radius - nd));
            pos += gout.Normal * nd;
        } // if
    } // if
    super::GetOwner()->SetPosition(pos);

    return true;
}

my::PlayerCollisionComponent::PlayerCollisionComponent(int priority) :
    super(priority),
    _player_com() {
}

my::PlayerCollisionComponent::PlayerCollisionComponent(const PlayerCollisionComponent& obj) :
    super(obj._priority),
    _player_com(),
    _velocity_com() {
}

my::PlayerCollisionComponent::~PlayerCollisionComponent() {
}

std::string my::PlayerCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent;
}

std::optional<Mof::CSphere> my::PlayerCollisionComponent::GetSphere(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CSphere(pos, _player_com.lock()->GetVolume());
}

std::optional<Mof::CBoxAABB> my::PlayerCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::PlayerCollisionComponent::GetRay(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> my::PlayerCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::PlayerCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::PlayerCollisionComponent::Initialize(void) {
    super::Initialize();
    _player_com = super::GetOwner()->GetComponent<my::PlayerComponent>();
    _jump_com = super::GetOwner()->GetComponent<my::PlayerJumpComponent >();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    return true;
}

std::shared_ptr<my::Component> my::PlayerCollisionComponent::Clone(void) {
    return std::make_shared<my::PlayerCollisionComponent>(*this);
}

void my::PlayerCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);

        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        if (ray.CollisionGeometry(geometry, info)) {
            float height = _player_com.lock()->GetHeight();
            if (info.d <= height) {
                auto pos = super::GetOwner()->GetPosition();
                pos.y += height - info.d;
                super::GetOwner()->SetPosition(pos);
                _jump_com.lock()->End();
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}

void my::PlayerCollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);

        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * gimmick->GetWorldMatrix();
        geometry->SetMatrix(mat);

        if (ray.CollisionGeometry(geometry, info)) {
            float height = _player_com.lock()->GetHeight();
            if (info.d <= height) {
                auto pos = super::GetOwner()->GetPosition();
                pos.y += height - info.d;
                super::GetOwner()->SetPosition(pos);
                gimmick->ActionStart();
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}