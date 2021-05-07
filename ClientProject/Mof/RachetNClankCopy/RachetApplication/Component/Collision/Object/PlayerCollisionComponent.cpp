#include "PlayerCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../Player/PlayerComponent.h"
#include "../../VelocityComponent.h"
#include "../../Player/PlayerStateComponent.h"


std::optional<Mof::CRay3D> my::PlayerCollisionComponent::GetFrontRay(void) {
    _ASSERT_EXPR(!_player_com.expired(), L"無効なポインタを保持しています");
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if

    auto pos = super::GetOwner()->GetPosition();
    pos.y += _player_com.lock()->GetHeight();
    auto velocity = _velocity_com.lock()->GetVelocity() * 1.0f / 60.0f;
    auto dir = Mof::CVector3(velocity.x, 0.0f, velocity.z);
    pos -= dir;
    return Mof::CRay3D(pos, dir);
}

void my::PlayerCollisionComponent::CollisionStageFrontRay(Mof::LPMeshContainer mesh, const StageObject& obj) {
    auto ray = this->GetFrontRay().value();
    Mof::COLLISIONOUTGEOMETRY info;
    float margin = -0.2f;

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
        geometry->SetMatrix(mat);

        auto velocity = _velocity_com.lock()->GetVelocity();
        velocity *= 1.0f / 60.0f;

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

void my::PlayerCollisionComponent::CollisionStageDownRay(Mof::LPMeshContainer mesh, const StageObject& obj) {
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

                if (auto state_com = _state_com.lock()) {
                    if (state_com->CanTransition(state::PlayerActionStateType::kPlayerActionJumpLandingState)) {
                        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionJumpLandingState);
                    } // if
                } // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}

void my::PlayerCollisionComponent::CollisionStageElevator(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info) {
    auto sphere = this->GetSphere().value();

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

        if (ray.CollisionGeometry(geometry, info)) {
            float height = _player_com.lock()->GetHeight();

            if (info.d <= height) {
                auto pos = super::GetOwner()->GetPosition();
                if (auto velocity_com = _velocity_com.lock()) {
                    auto add = Mof::CVector3(std::log10(time) * gimmick_move.x * 60.0f,
                                             std::log10(time) * gimmick_move.y * 60.0f,
                                             std::log10(time) * gimmick_move.z * 60.0f);
                    velocity_com->AddVelocityForce(add);
                } // if
                pos.y += height - info.d;
                super::GetOwner()->SetPosition(pos);

                if (!_on_elevator) {
                    gimmick->ActionStart();
                } // if
                if (auto state_com = _state_com.lock()) {
                    if (state_com->CanTransition(state::PlayerActionStateType::kPlayerActionJumpLandingState)) {
                        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionJumpLandingState);
                    } // if
                } // if
                _on_elevator = true;
            } // if
            else {
                _on_elevator = false;
            } // else
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}

void my::PlayerCollisionComponent::CollisionStageBridge(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info) {
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

                if (auto state_com = _state_com.lock()) {
                    if (state_com->CanTransition(state::PlayerActionStateType::kPlayerActionJumpLandingState)) {
                        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionJumpLandingState);
                    } // if
                } // if
            } // if
        } // if
        geometry->SetMatrix(default_matrix);
    } // for
}

my::PlayerCollisionComponent::PlayerCollisionComponent(int priority) :
    super(priority),
    _player_com(),
    _velocity_com(),
    _state_com(),
    _on_elevator(false) {
}

my::PlayerCollisionComponent::PlayerCollisionComponent(const PlayerCollisionComponent& obj) :
    super(obj._priority),
    _player_com(),
    _velocity_com(),
    _state_com(),
    _on_elevator(false) {
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
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
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

void my::PlayerCollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
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