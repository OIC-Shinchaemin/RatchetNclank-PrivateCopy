#include "PlayerCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../../State/PlayerActionStateDefine.h"
#include "../../Player/PlayerComponent.h"
#include "../../VelocityComponent.h"
#include "../../Player/PlayerStateComponent.h"
#include "WaterFlowCollisionComponent.h"


void ratchet::PlayerCollisionComponent::ChangeState(void) {
    if (auto state_com = _state_com.lock()) {
        for (auto& state : _next_status) {
            if (state_com->CanTransition(state)) {
                state_com->ChangeState(state);
                break;
            } // if
        } // for
    } // if
}

std::optional<Mof::CRay3D> ratchet::PlayerCollisionComponent::GetFrontRay(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if

    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    auto velocity = _velocity_com.lock()->GetVelocity() * def::kDeltaTime;
    auto dir = Mof::CVector3(velocity.x, 0.0f, velocity.z);
    pos -= dir;
    return Mof::CRay3D(pos, dir);
}

void ratchet::PlayerCollisionComponent::CollisionStageFrontRay(Mof::LPMeshContainer mesh, const StageObject& obj) {
    auto ray = this->GetFrontRay().value();
    Mof::COLLISIONOUTGEOMETRY info;
    float margin = -0.2f;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        auto velocity = _velocity_com.lock()->GetVelocity();
        velocity *= def::kDeltaTime;

        if (ray.CollisionGeometry(geometry, info)) {
            Mof::CVector3 up(0.0f, 1.0f, 0.0f);
            float angle = up.DotAngle(info.Normal);
            float slope_threshold_angle = 40.0f;
            if (angle > slope_threshold_angle) {
                continue;
            } // if

            if (info.d <= velocity.Length() + margin) {
                float dot = Mof::CVector3Utilities::Dot(velocity, info.Normal);
                dot = std::abs(dot);
                auto pos = super::GetOwner()->GetPosition();
                pos += ray.Direction * (info.d - dot + margin);
                pos += info.Normal * dot;
                super::GetOwner()->SetPosition(pos);
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for    
}

void ratchet::PlayerCollisionComponent::CollisionStageDownRay(Mof::LPMeshContainer mesh, const StageObject& obj) {
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;
    float margin = 0.1f;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        if (ray.CollisionGeometry(geometry, info)) {
            Mof::CVector3 up(0.0f, 1.0f, 0.0f);
            float angle = up.DotAngle(info.Normal);
            float slope_threshold_angle = 30.0f;
            if (angle > slope_threshold_angle) {
                continue;
            } // if

            float height = _player_com.lock()->GetHeight();
            if (info.d <= height + margin) {
                auto pos = super::GetOwner()->GetPosition();
                pos.y += height + margin - info.d;
                super::GetOwner()->SetPosition(pos);
                this->ChangeState();
            } // if
        } // if

        if (this->GetNextRay().value().CollisionGeometry(geometry, info)) {
            _player_com.lock()->SetNextTerrain("Ground");
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}

void ratchet::PlayerCollisionComponent::CollisionStageElevator(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info) {
    auto sphere = this->GetSphere().value();

    auto gimmick_pos = gimmick->GetPosition();
    auto gimmick_sphere_0 = gimmick->GetStartPositionSphere();
    auto gimmick_sphere_1 = gimmick->GetEndPositionSphere();
    if (gimmick_sphere_0.CollisionSphere(sphere) && !gimmick_sphere_0.CollisionPoint(gimmick->GetPosition()) ||
        (gimmick_sphere_1.CollisionSphere(sphere) && !gimmick_sphere_1.CollisionPoint(gimmick->GetPosition()))) {
        gimmick->ActionStart();
    } // if

    auto gimmick_move = gimmick->GetMoveValue();
    float time = gimmick->GetRequestTime();
    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * gimmick->GetWorldMatrix();
        geometry->SetMatrix(mat);



        float volume = _player_com.lock()->GetVolume();
        float height = _player_com.lock()->GetHeight();
        auto pos = super::GetOwner()->GetPosition();


        auto player_circle = Mof::CCircle(pos.x, pos.z, volume);
        auto gimmick_circle = Mof::CCircle(gimmick_pos.x, gimmick_pos.z, gimmick->GetVolume());
        float gimmick_top = gimmick_pos.y + gimmick->GetHeight() * 0.5f;
        float gimmick_bottom = gimmick_pos.y - gimmick->GetHeight() * 0.5f;
        if (gimmick_top > sphere.Position.y && gimmick_bottom < sphere.Position.y) {
            if (player_circle.CollisionCircle(gimmick_circle)) {
                Mof::CVector2 player_pos(player_circle.x, player_circle.y);
                Mof::CVector2 gimmick_pos(gimmick_circle.x, gimmick_circle.y);
                float direction = std::atan2(gimmick_pos.y - player_pos.y, gimmick_pos.x - player_pos.x) + math::kHalfPi;
                auto distance = Mof::CVector2Utilities::Distance(player_pos, gimmick_pos);
                float diff = (gimmick_circle.r + player_circle.r) - distance;
                
                auto add = math::Rotate(0.0f, diff, direction);
                auto pos = super::GetOwner()->GetPosition();
                pos.x += add.x;
                pos.z += add.y;
                super::GetOwner()->SetPosition(pos);
            } // if
        } // if




        // down ray
        if (ray.CollisionGeometry(geometry, info)) {
            float height = _player_com.lock()->GetHeight();
            if (info.d <= height) {
                auto pos = super::GetOwner()->GetPosition();
                pos += gimmick_move;
                pos.y += height - info.d;
                super::GetOwner()->SetPosition(pos);

                if (!_on_elevator) {
                    gimmick->ActionStart();
                } // if
                this->ChangeState();

                _on_elevator = true;
            } // if
            else {
                _on_elevator = false;
            } // else
        } // if

        if (this->GetNextRay().value().CollisionGeometry(geometry, info)) {
            _player_com.lock()->SetNextTerrain("Ground");
        } // if

        geometry->SetMatrix(default_matrix);
    } // for
}

void ratchet::PlayerCollisionComponent::CollisionStageBridge(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info) {
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

                this->ChangeState();

            } // if
        } // if
        if (this->GetNextRay().value().CollisionGeometry(geometry, info)) {
            _player_com.lock()->SetNextTerrain("Ground");
        } // if


        geometry->SetMatrix(default_matrix);
    } // for
}

ratchet::PlayerCollisionComponent::PlayerCollisionComponent(int priority) :
    super(priority),
    _player_com(),
    _velocity_com(),
    _state_com(),
    _on_elevator(false) {
}

ratchet::PlayerCollisionComponent::PlayerCollisionComponent(const PlayerCollisionComponent& obj) :
    super(obj),
    _player_com(),
    _velocity_com(),
    _state_com(),
    _on_elevator(false) {
    _next_status.push_back(state::PlayerActionStateType::kPlayerActionJumpLandingState);
    _next_status.push_back(state::PlayerActionStateType::kPlayerActionIdleState);
}

ratchet::PlayerCollisionComponent::~PlayerCollisionComponent() {
}

std::string ratchet::PlayerCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kPlayerCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::PlayerCollisionComponent::GetSphere(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CSphere(pos, _player_com.lock()->GetVolume());
}

std::optional<Mof::CBoxAABB> ratchet::PlayerCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::PlayerCollisionComponent::GetRay(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::CRay3D> ratchet::PlayerCollisionComponent::GetNextRay(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto player_com = _player_com.lock();
    auto offset = Mof::CVector3(0.0f, 0.0f, -player_com->GetVolume() * 2.0f);
    offset.RotationY(super::GetOwner()->GetRotate().y);

    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    return Mof::CRay3D(pos + offset, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::PlayerCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::PlayerCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::PlayerCollisionComponent::Initialize(void) {
    super::Initialize();
    _player_com = super::GetOwner()->GetComponent<ratchet::PlayerComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerCollisionComponent>(*this);
}

void ratchet::PlayerCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    bool execute = false;
    auto check_sphere = this->GetSphere().value();
    check_sphere.r *= 2.0f;
    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        if (check_sphere.CollisionSphere(obj.GetGeometrySphere(i))) {
            execute = true;
            break;
        } // if
    } // for

    if (!execute) {
        return;
    } // if
    this->CollisionStageFrontRay(mesh, obj);
    this->CollisionStageDownRay(mesh, obj);
}

void ratchet::PlayerCollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    auto ray = this->GetRay().value();
    Mof::COLLISIONOUTGEOMETRY info;
    if (gimmick->GetType() == StageObjectType::Elevator) {
        this->CollisionStageElevator(mesh, gimmick, ray, info);
    } // if
    else if (gimmick->GetType() == StageObjectType::Bridge) {
        this->CollisionStageBridge(mesh, gimmick, ray, info);
    } // else if
}