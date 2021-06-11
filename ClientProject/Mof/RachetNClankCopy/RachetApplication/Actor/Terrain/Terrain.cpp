#include "Terrain.h"

#include "Base/Core/Math.h"
#include "../../Factory/Builder/IBuilder.h"


my::Terrain::Terrain() :
    super(),
    _plane(),
    _uv_scroll(),
    _scroll_increase(0.00001f, 0.0005f),
    _shader(),
    _shader_bind() {
}

my::Terrain::~Terrain() {
}

void my::Terrain::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    _resource = ptr;
}

bool my::Terrain::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    _plane = Mof::CGraphicsUtilities::CreatePlaneGeometry(1.0f, 1.0f, 1.0f, 1.0f, true, math::vec3::kZero);
    if (auto resource = _resource.lock()) {
        auto tex = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/water/water0.jpg");
        _plane->GetMaterial()->GetTextureArray()->Add(tex.get());
    } // if

    // shader
    _shader.Load("../Resource/shader/water.hlsl");
    _shader_bind.Create(&_shader);
    _shader_bind.CreateShaderBuffer("cbUVScrollParam", sizeof(my::cbUVScrollParam));
    return true;
}

bool my::Terrain::Update(float delta_time) {
    return false;
}

bool my::Terrain::Render(void) {
    Mof::CMatrix44 scale, rotate, translate;
    scale.Scaling(super::GetScale(), scale);
    rotate.RotationZXY(math::vec3::kZero);
    translate.Translation(super::GetPosition(), translate);
    auto world = scale * rotate * translate;

    _uv_scroll += _scroll_increase;
    _shader_bind.SetCamera(::CGraphicsUtilities::GetCamera());
    _shader_bind.SetDirectionalLight(::CGraphicsUtilities::GetDirectionalLight());
    _shader_bind.GetShaderBuffer(0)->SetBuffer(&_uv_scroll);

    _plane->Render(world, def::color_rgba::kWhite, &_shader, &_shader_bind);
    return true;
}

bool my::Terrain::Release(void) {
    super::Release();

    auto work = _plane->GetMaterial()->GetTextureArray();
    for (int i = 0, n = work->GetArrayCount(); i < n; i++) {
        work->GetData(i) = nullptr;
    } // for
    _plane->Release();
    delete _plane;

    _resource.reset();
    _shader_bind.Release();
    _shader.Release();
    return true;
}