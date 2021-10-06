#include "BoltCollisionComponent.h"

#include "../CollisionComponentDefine.h"
#include "../../VelocityComponent.h"
#include "../../Item/BoltActionStateComponent.h"


ratchet::component::collision::BoltCollisionComponent::BoltCollisionComponent(int priority) :
	super(priority),
	_height(0.2f),
	_volume(_height),
	_state_com() {
}

ratchet::component::collision::BoltCollisionComponent::BoltCollisionComponent(const BoltCollisionComponent& obj) :
	super(obj),
	_height(obj._height),
	_volume(obj._volume),
	_state_com() {
}

ratchet::component::collision::BoltCollisionComponent::~BoltCollisionComponent() {
}

std::string ratchet::component::collision::BoltCollisionComponent::GetType(void) const {
	return ratchet::component::collision::CollisionComponentType::kBoltCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::BoltCollisionComponent::GetSphere(void) {
	if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
		return std::optional<Mof::CSphere>();
	} // if
	auto pos = super::GetOwner()->GetPosition();
	pos.y += _height;
	return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BoltCollisionComponent::GetBox(void) {
	return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BoltCollisionComponent::GetRay(void) {
	if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
		return std::optional<Mof::CRay3D>();
	} // if
	auto pos = super::GetOwner()->GetPosition();
	pos.y += _height;

	auto dir = _velocity_com.lock()->GetVelocity()* def::kDeltaTime;
	return Mof::CRay3D(pos, dir);
}

std::optional<Mof::CRay3D> ratchet::component::collision::BoltCollisionComponent::GetNextRay(void) {
	return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BoltCollisionComponent::GetMesh(void) {
	return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BoltCollisionComponent::GetSightObject(void) {
	return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BoltCollisionComponent::Initialize(void) {
	super::Initialize();

	_state_com = super::GetOwner()->GetComponent<ratchet::component::item::BoltActionStateComponent>();
	_velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
	return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BoltCollisionComponent::Clone(void) {
	return std::make_shared<ratchet::component::collision::BoltCollisionComponent>(*this);
}

void ratchet::component::collision::BoltCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
	if (!this->GetRay().has_value()) {
		return;
	} // if
	if (_state_com.lock()->IsEqual(state::BoltActionType::kGravitate)) {
		return;
	} // if

	//auto sphere = this->GetSphere().value();
	auto ray = this->GetRay().value();
	Mof::COLLISIONOUTGEOMETRY info;

	for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
		auto geometry = mesh->GetGeometry(i);
		//auto default_matrix = geometry->GetMatrix();
		//Mof::CMatrix44 mat = default_matrix * obj.GetWorldMatrix();
		Mof::CMatrix44 mat = obj.GetWorldMatrix();
		//geometry->SetMatrix(mat);

		//auto inverse = Mof::CMatrix44();
		//mat.Inverse(inverse);

		auto rayLocal = ray;
		rayLocal.ToLocal(mat);
		if (rayLocal.CollisionGeometry(geometry, info)) {
			if (info.d <= _height) {
				auto pos = super::GetOwner()->GetPosition();
				pos.y += _height - info.d;
				super::GetOwner()->SetPosition(pos);
				_state_com.lock()->ChangeState(state::BoltActionType::kDefault);
			} // if
		} // if
		//geometry->SetMatrix(default_matrix);
	} // for
}