#include "PlayerCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../Player/PlayerComponent.h"
#include "../../VelocityComponent.h"
#include "../../Player/PlayerStateComponent.h"


bool my::PlayerCollisionComponent::CollisionStageFrontRay(Mof::LPMeshContainer mesh, const StageObject& obj) {
    return true;
}

my::PlayerCollisionComponent::PlayerCollisionComponent(int priority) :
    super(priority),
    _player_com(),
    _velocity_com(),
    _state_com(),
    _on_elevator(false){
}

my::PlayerCollisionComponent::PlayerCollisionComponent(const PlayerCollisionComponent& obj) :
    super(obj._priority),
    _player_com(),
    _velocity_com(),
    _state_com() ,
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

void my::PlayerCollisionComponent::CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) {
    if (!this->GetRay().has_value()) {
        return;
    } // if
    auto ray = this->GetRay().value();
    auto sphere = this->GetSphere().value();
    Mof::COLLISIONOUTGEOMETRY info;


    if (gimmick->GetType() == StageObjectType::Elevator) {
        auto gimmick_pos = gimmick->GetPosition();
        auto gimmick_pre_pos = gimmick->GetPreviewPosition();
        auto gimmick_move = gimmick_pos - gimmick_pre_pos;

        auto gimmick_sphere_0 = Mof::CSphere(20.0, -5.0f, -12.0f, 35.0f);
        auto gimmick_sphere_1 = Mof::CSphere(65.0, -29.0f, 10.0f, 15.0f);

        if (gimmick_sphere_0.CollisionSphere(sphere) && !gimmick_sphere_0.CollisionPoint(gimmick_pos)) {
            gimmick->ActionStart();
        } // if
        else if (gimmick_sphere_1.CollisionSphere(sphere) && !gimmick_sphere_1.CollisionPoint(gimmick_pos)) {
            gimmick->ActionStart();
        } // else if


        for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
            auto geometry = mesh->GetGeometry(i);

            auto default_matrix = geometry->GetMatrix();
            Mof::CMatrix44 mat = default_matrix * gimmick->GetWorldMatrix();
            geometry->SetMatrix(mat);

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
    } // if
    else if (gimmick->GetType() == StageObjectType::Bridge) {
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
    } // else if

}