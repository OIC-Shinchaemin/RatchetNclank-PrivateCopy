#include "EnemyHpBillboardComponent.h"

#include "../../Game/Graphics/RenderBillboardCommand.h"


ratchet::component::enemy::EnemyHpBillboardComponent::EnemyHpBillboardComponent(int priority) :
	super(priority),
	_path2(),
	_texture(),
	_color(),
	_offset_position(),
	_offset_rotation(),
	_hp_com(),
	_type_com() {
}

ratchet::component::enemy::EnemyHpBillboardComponent::EnemyHpBillboardComponent(const ratchet::component::enemy::EnemyHpBillboardComponent& obj) :
	super(obj),
	_path2(obj._path2),
	_texture(obj._texture),
	_texture_hp_guage(obj._texture_hp_guage),
	_color(obj._color),
	_offset_position(),
	_offset_rotation(),
	_hp_com(),
	_type_com() {
}

ratchet::component::enemy::EnemyHpBillboardComponent::~EnemyHpBillboardComponent() {
}

void ratchet::component::enemy::EnemyHpBillboardComponent::SetParam(const rapidjson::Value& param) {
	super::SetParam(param);
	{
		const char* path = "path";
		_ASSERT_EXPR(param.HasMember(path), L"指定のパラメータがありません");
		_ASSERT_EXPR(param[path].IsString(), L"パラメータの指定された型でありません");
		auto p = param[path].GetString();
		auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<Mof::CTexture>>(p);
		this->SetTexture(temp);
	}
	{
		const char* path2 = "path2";
		_ASSERT_EXPR(param.HasMember("path2"), L"指定された型がありません");
		_ASSERT_EXPR(param["path2"].IsString(), L"指定された型でありません");
		this->_path2 = param["path2"].GetString();

		auto p = param[path2].GetString();
		auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<Mof::CTexture>>(p);
		_texture_hp_guage = temp;
	}

	const char* color = "color";
	if (param.HasMember(color)) {
		_ASSERT_EXPR(param[color].IsArray(), L"パラメータの指定された型でありません");
		for (int i = 0, n = param[color].GetArray().Size(); i < n; i++) {
			_color.fv[i] = param[color].GetArray()[i].GetFloat();
		} // for
	} // if
	else {
		_color = math::vec4::kOne;
	} // else
}

void ratchet::component::enemy::EnemyHpBillboardComponent::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
	this->_texture = ptr;
}

void ratchet::component::enemy::EnemyHpBillboardComponent::SetColor(const Mof::CVector4& value) {
	this->_color = value;
}

void ratchet::component::enemy::EnemyHpBillboardComponent::SetOffsetPosition(const Mof::CVector3& value) {
	this->_offset_position = value;
}

void ratchet::component::enemy::EnemyHpBillboardComponent::SetOffsetRotation(const Mof::CVector3& value) {
	this->_offset_rotation = value;
}

std::string ratchet::component::enemy::EnemyHpBillboardComponent::GetType(void) const {
	return "EnemyHpBillboardComponent";
}

std::shared_ptr<Mof::CTexture> ratchet::component::enemy::EnemyHpBillboardComponent::GetTexture(void) const {
	return this->_texture.lock();
}

Mof::CVector4 ratchet::component::enemy::EnemyHpBillboardComponent::GetColor(void) const {
	return this->_color;
}

bool ratchet::component::enemy::EnemyHpBillboardComponent::Initialize(void)
{
	super::Initialize();
	super::Activate();

	_hp_com = super::GetOwner()->GetComponent<component::HpComponent>();
	_type_com = super::GetOwner()->GetComponent<component::enemy::EnemyComponent>();

	_offset_position.y += _type_com.lock()->GetHeight() * 1.3f;
	return true;
}

bool ratchet::component::enemy::EnemyHpBillboardComponent::Render(void) {
	if (!super::GetOwner()->InCameraRange()) {
		return false;
	} // if

	auto owner = super::GetOwner();
	// ベース
	if (auto tex = this->GetTexture(); tex) {
		Mof::CMatrix44 scale, rotate, translate;
		Mof::CQuaternion quat;

		scale.Scaling(owner->GetScale(), scale);
		quat.ConvertMatrixTranspose(rotate);
		translate.Translation(this->_offset_position + owner->GetPosition(), translate);

		Mof::CMatrix44 world = scale * rotate * translate;
		auto camera = ::CGraphicsUtilities::GetCamera();
		//tex->Render(camera->GetBillBoardMatrix() * world, _color.ToU32Color());
	} // if
	// ゲージ
	if (auto tex = _texture_hp_guage.lock(); tex) {
		Mof::CMatrix44 scale, rotate, translate;
		Mof::CQuaternion quat;

		quat.ConvertMatrixTranspose(rotate);

		auto pos = this->_offset_position + owner->GetPosition();
		{
			auto camera_pos = CGraphicsUtilities::GetCamera()->GetViewPosition();
			auto diff = Mof::CVector3(camera_pos - pos);
			diff.Normal(diff);
			pos += diff * 1.0f;
		}
		translate.Translation(pos, translate);

		auto camera = ::CGraphicsUtilities::GetCamera();

		float hp_per = 
			static_cast<float>(_hp_com.lock()->GetHp()) / 
			static_cast<float>(_hp_com.lock()->GetHpMax());

		float width = static_cast<float>(tex->GetWidth());
		float height = static_cast<float>(tex->GetHeight());
		auto rect = Mof::CRectangle(0.0f, 0.0f, width, height);

		{
			auto s = owner->GetScale();
			s.x = hp_per;
			scale.Scaling(s, scale);
		}
		Mof::CMatrix44 world = rotate * translate;

		tex->Render(scale * camera->GetBillBoardMatrix() * world, rect);
	} // if
	return true;
}

bool ratchet::component::enemy::EnemyHpBillboardComponent::Render(std::shared_ptr<ratchet::game::graphics::RenderCommandTask> out) {
	if (!super::GetOwner()->InCameraRange()) {
		return false;
	} // if

	auto owner = super::GetOwner();
	// 描画
	if (auto tex = this->GetTexture(); tex) {
		Mof::CMatrix44 scale, rotate, translate;
		Mof::CQuaternion quat;

		scale.Scaling(owner->GetScale(), scale);
		quat.ConvertMatrixTranspose(rotate);
		translate.Translation(this->_offset_position + owner->GetPosition(), translate);

		Mof::CMatrix44 world = scale * rotate * translate;
		auto camera = ::CGraphicsUtilities::GetCamera();
		auto command = std::make_shared<ratchet::game::graphics::RenderBillboardCommand>(tex, camera->GetBillBoardMatrix() * world, _color);
		out->Push(command, _target_layer);
	} // if
	return true;
}

bool ratchet::component::enemy::EnemyHpBillboardComponent::Release(void) {
	super::Release();
	_texture.reset();
	return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::enemy::EnemyHpBillboardComponent::Clone(void) {
	return std::make_shared<ratchet::component::enemy::EnemyHpBillboardComponent>(*this);
}