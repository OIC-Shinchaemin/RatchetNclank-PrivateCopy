#include "Scene.h"

#include "Base/Core/Define.h"


bool ratchet::Scene::IsLoaded(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    return this->_loaded;
}

void ratchet::Scene::LoadComplete(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    _loaded = true;
}

std::shared_ptr<ratchet::ResourceMgr> ratchet::Scene::GetResource(void) const {
    if (auto ptr = _resource.lock()) {
        return ptr;
    } // if
    return nullptr;
}

std::shared_ptr<base::ui::UICanvas> ratchet::Scene::GetUICanvas(void) const {
    if (auto ptr = _ui_canvas.lock()) {
        return ptr;
    } // if
    return nullptr;
}

Mof::LPRenderTarget ratchet::Scene::GetDefaultRendarTarget(void) const {
    return this->_default;
}

bool ratchet::Scene::LoadingUpdate(float delta_time) {
    return false;
}

bool ratchet::Scene::SceneUpdate(float delta_time) {
    if (_effect.has_value()) {
        _effect.value().Update(delta_time);

        if (_effect.value().IsEnd()) {
            _effect.reset();
        } // if
    } // if    
    return true;
}

bool ratchet::Scene::PreRender(void) {
    // start
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetRenderTarget(_rendar_target.GetRenderTarget(), ::g_pGraphics->GetDepthTarget());
    return true;
}

bool ratchet::Scene::LoadingRender(void) {
    return true;
}

bool ratchet::Scene::SceneRender(void) {
    return false;
}

bool ratchet::Scene::PostRender(void) {
    // end
    ::g_pGraphics->SetRenderTarget(_default, ::g_pGraphics->GetDepthTarget());
    ::g_pGraphics->SetDepthEnable(false);
    if (_effect.has_value()) {
        auto camera = ::CGraphicsUtilities::GetCamera();
        _effect.value().SetCamera(*camera);
        _effect.value().Enable();
    } // if

    // complete prepare
    if (_effect.has_value()) {
        auto& shader = _effect.value().shader;
        ::CGraphicsUtilities::RenderTexture(
            0.0f, 0.0f, &_rendar_target,
            shader.value.get(), shader.bind.get());
    } // if
    else {
        ::CGraphicsUtilities::RenderTexture(0.0f, 0.0f, &_rendar_target);
    } // else
    return true;
}

ratchet::Scene::Scene() :
    _state(this_type::State::Active),
    _rendar_target(),
    _default(),
    _effect(),
    _resource(),
    _ui_canvas(),
    _loaded(false),
    _mutex(),
    _load_thread() {
}

ratchet::Scene::~Scene() {
    if (_load_thread.has_value()) {
        _load_thread.value().join();
        _load_thread.reset();
    } // if
}

void ratchet::Scene::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::Scene::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void ratchet::Scene::AddSceneObserver(const std::shared_ptr<base::core::Observer<const scene::SceneMessage&>>& ptr) {
    _subject.AddObserver(ptr);
}

bool ratchet::Scene::Load(std::shared_ptr<ratchet::Scene::Param> param) {
    _effect = ratchet::SceneEffect();
    _effect.value().Load("../Resource/shader/fadein.hlsl");
    bool seccess = _effect.value().CreateShaderBuffer("cbSceneEffectParam", sizeof(ratchet::cbSceneEffectParam));
    _effect.value().time = 1.0f;

    _default = ::g_pGraphics->GetRenderTarget();
    // ì¬
    MofU32 sw = g_pGraphics->GetTargetWidth();
    MofU32 sh = g_pGraphics->GetTargetHeight();
    if (!_rendar_target.CreateTarget(sw, sh,
                                     PIXELFORMAT_R8G8B8A8_UNORM,
                                     BUFFERACCESS_GPUREADWRITE)) {
        return true;
    } // if
    return true;
}

bool ratchet::Scene::Initialize(void) {
    _effect.value().time = 1.0f;
    return true;
}

bool ratchet::Scene::Input(void) {
    return true;
}

bool ratchet::Scene::Update(float delta_time) {
    if (this->IsLoaded()) {
        if (_load_thread.has_value()) {
            _load_thread.value().join();
            _load_thread.reset();
        } // if

        this->SceneUpdate(delta_time);
    } // if
    else {
        this->LoadingUpdate(delta_time);
    } // else
    return true;
}

bool ratchet::Scene::Render(void) {
    if (this->IsLoaded()) {
        this->PreRender();
        this->SceneRender();
        this->PostRender();
    } // if
    else {
        this->LoadingRender();
    } // else
    return true;
}

bool ratchet::Scene::Release(void) {
    return true;
}