#include "Enemy.h"

#include "../../Factory/FactoryManager.h"

#include "../../Component/Item/BoltActionStateComponent.h"
#include "../../Component/Item/BoltComponent.h"
#include "../../State/BoltActionStateDefine.h"
#include "../../Component/Item/BulletItem/BulletItemActionStateComponent.h"
#include "../../Component/Item/BulletItem/BulletItemComponent.h"
#include "../../State/BulletItemActionStateDefine.h"
#include "../../Component/Item/NanotechItem/NanotechItemActionStateComponent.h"
#include "../../Component/Item/NanotechItem/NanotechItemComponent.h"
#include "../../State/NanotechItemActionStateDefine.h"


void ratchet::actor::character::Enemy::Activate(void) {
	super::Activate();
}

ratchet::actor::character::Enemy::Enemy() :
	super(),
	_effect_container(),
	_effect_emitter() {
	super::SetTag("Enemy");
}

ratchet::actor::character::Enemy::~Enemy() {
}

void ratchet::actor::character::Enemy::SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr) {
	this->_effect_container = ptr;
	_effect_emitter = ptr->CreateEmitter();
}
/*
void ratchet::actor::character::Enemy::SetEffectEmitter(std::shared_ptr<ratchet::effect::EffectEmitter> ptr) {
	this->_effect_emitter = ptr;
}
*/
std::shared_ptr<ratchet::effect::EffectEmitter> ratchet::actor::character::Enemy::GetEffectEmitter(void) const {
	return this->_effect_emitter;
}

base::core::Observable<const ratchet::game::gamesystem::GameQuest&>* ratchet::actor::character::Enemy::GetQuestSubject(void) {
	return &this->_quest_subject;
}

void ratchet::actor::character::Enemy::End(void) {
	{
		this->GenerateDropItem();
	}

	{
		//auto param = ratchet::actor::item::BulletItem::Param();
		//param.transform.position = super::GetPosition();
		//param.transform.rotate = Mof::CVector3(0.0f, 0.0f, 0.0f);


		//float speed = 8.0f;
		//float angle_y = ut::GenerateRandomF(0.0f, math::kTwoPi);
		//Mof::CVector3 accele(0.0f, 0.0f, -speed);
		//accele.RotationY(angle_y);
		//param.speed.x = accele.x;
		//param.speed.y = speed;
		//param.speed.z = accele.z;
		//param.angle.x = param.speed.x;
		//param.angle.y = param.speed.y;
		//param.angle.z = param.speed.z;
		//param.type = static_cast <ratchet::actor::item::BulletItem::Type>(ut::GenerateRandom(0, static_cast<int>(ratchet::actor::item::BulletItem::Type::CountMax) - 1));
		//param.count = ut::GenerateRandom(0.0f, 10);

		//auto item = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::item::BulletItem>("../Resource/builder/bullet_item.json", &param);
		//item->GetComponent<ratchet::component::item::bulletitem::BulletItemActionStateComponent>()->ChangeState(state::BulletItemActionType::kMoved);
		//Observable::Notify("AddRequest", item);
	}


	{
		//auto param = ratchet::actor::item::NanotechItem::Param();
		//param.transform.position = super::GetPosition();
		//param.transform.rotate = Mof::CVector3(0.0f, 0.0f, 0.0f);

		//float speed = 8.0f;
		//float angle_y = ut::GenerateRandomF(0.0f, math::kTwoPi);
		//Mof::CVector3 accele(0.0f, 0.0f, -speed);
		//accele.RotationY(angle_y);
		//param.speed.x = accele.x;
		//param.speed.y = speed;
		//param.speed.z = accele.z;
		//param.angle.x = param.speed.x;
		//param.angle.y = param.speed.y;
		//param.angle.z = param.speed.z;


		//auto item = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::item::NanotechItem>("../Resource/builder/nanotech.json", &param);
		//item->GetComponent<ratchet::component::item::nanotechitem::NanotechItemActionStateComponent>()->ChangeState(state::NanotechItemActionType::kMoved);
		//Observable::Notify("AddRequest", item);
	}



	_quest_subject.Clear();
	Observable::Notify("EnemyDead", shared_from_this());
	super::End();
}

void ratchet::actor::character::Enemy::GenerateDropItem(void) {
	auto param = ratchet::actor::item::Bolt::Param();
	for (int i = 0, n = ut::GenerateRandom(3, 4); i < n; i++) {
		param.transform.position = super::GetPosition();
		param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);

		float speed = 8.0f;
		float angle_y = ut::GenerateRandomF(0.0f, math::kTwoPi);
		Mof::CVector3 accele(0.0f, 0.0f, -speed);
		accele.RotationY(angle_y);

		param.speed.x = accele.x;
		param.speed.y = speed;
		param.speed.z = accele.z;
		param.angle.x = param.speed.x;
		param.angle.y = param.speed.y;
		param.angle.z = param.speed.z;

		auto bolt = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::item::Bolt>("../Resource/builder/bolt.json", &param);
		bolt->GetComponent<ratchet::component::item::BoltActionStateComponent>()->ChangeState(state::BoltActionType::kMoved);
		Observable::Notify("AddRequest", bolt);
	} // for
}