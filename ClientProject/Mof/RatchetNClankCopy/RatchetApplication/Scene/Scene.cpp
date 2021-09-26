#include "Scene.h"

#include "Base/Core/Define.h"


bool ratchet::scene::Scene::IsLoaded(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    return this->_loaded;
}

void ratchet::scene::Scene::LoadComplete(void) {
    std::lock_guard<std::mutex> lock(_mutex);
    _loaded = true;
}

std::shared_ptr<ratchet::ResourceMgr> ratchet::scene::Scene::GetResource(void) const {
    if (auto ptr = _resource.lock()) {
        return ptr;
    } // if
    return nullptr;
}

std::shared_ptr<base::ui::UICanvas> ratchet::scene::Scene::GetUICanvas(void) const {
    if (auto ptr = _ui_canvas.lock()) {
        return ptr;
    } // if
    return nullptr;
}

std::shared_ptr<ratchet::light::LightManager> ratchet::scene::Scene::GetLightManager(void) const {
    if (auto ptr = _light_manager.lock()) {
        return ptr;
    } // if
    return nullptr;
}

Mof::LPRenderTarget ratchet::scene::Scene::GetDefaultRendarTarget(void) const {
    return this->_default;
}

bool ratchet::scene::Scene::LoadingUpdate(float delta_time) {
    return false;
}

bool ratchet::scene::Scene::SceneUpdate(float delta_time) {
    if (_effect.has_value()) {
        auto camera = ::CGraphicsUtilities::GetCamera();
        _effect.value().Update(delta_time);
        _effect.value().SetCamera(*camera);
        _effect.value().Enable();

        if (_effect.value().IsEnd()) {
            if (_transition_state == TransitionState::In) {
                _transition_state = TransitionState::None;
                _effect.reset();
                return true;
            } // if
            else if (_transition_state == TransitionState::None) {
                _transition_state = TransitionState::Out;
                return true;
            } // else if
            else if (_transition_state == TransitionState::Out) {
                _transition_state = TransitionState::End;
                _effect.reset();
                return true;
            } // else if
            else if (_transition_state == TransitionState::End) {
                return true;
            } // else if
        } // if
    } // if    
    return false;
}

bool ratchet::scene::Scene::PreRender(void) {
    // start
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetRenderTarget(_rendar_target.GetRenderTarget(), ::g_pGraphics->GetDepthTarget());
    return true;
}

bool ratchet::scene::Scene::LoadingRender(void) {
    return true;
}

bool ratchet::scene::Scene::SceneRender(void) {
    return false;
}

bool ratchet::scene::Scene::PostRender(void) {
    // end
    ::g_pGraphics->SetRenderTarget(_default, ::g_pGraphics->GetDepthTarget());
    ::g_pGraphics->SetDepthEnable(false);

    // complete prepare
    if (_effect.has_value()) {
        auto& shader = _effect.value().shader;
        ::CGraphicsUtilities::RenderTexture(
            0.0f, 0.0f, &_rendar_target,
            shader.value.get(), shader.bind.get());
    } // if
    else {
        ::CGraphicsUtilities::RenderTexture(0.0f, 0.0f, &_rendar_target);
        if (_transition_state == TransitionState::End) {
            auto width = ::g_pFramework->GetWindow()->GetWidth();
            auto height = ::g_pFramework->GetWindow()->GetHeight();
            ::CGraphicsUtilities::RenderFillRect(0.0f, 0.0f, width, height, def::color_rgba_u32::kBlack);
        } // if
    } // else
    return true;
}

ratchet::scene::Scene::Scene() :
    _state(this_type::State::Active),
    _transition_state(this_type::TransitionState::None),
    _rendar_target(),
    _default(),
    _effect(),
    _resource(),
    _ui_canvas(),
    _light_manager(),
    _loaded(false),
    _mutex(),
    _load_thread() {
}

ratchet::scene::Scene::~Scene() {
    if (_load_thread.has_value()) {
        _load_thread.value().join();
        _load_thread.reset();
    } // if
}

void ratchet::scene::Scene::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::scene::Scene::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void ratchet::scene::Scene::SetLightManager(std::weak_ptr<ratchet::light::LightManager> ptr) {
    this->_light_manager = ptr;
}

void ratchet::scene::Scene::SetState(const ratchet::scene::Scene::State state) {
    this->_state = state;
}

ratchet::scene::Scene::TransitionState ratchet::scene::Scene::GetTransitionState(void) const {
    return this->_transition_state;
}

void ratchet::scene::Scene::AddSceneObserver(const std::shared_ptr<base::core::Observer<const scene::SceneMessage&>>& ptr) {
    _subject.AddObserver(ptr);
}

bool ratchet::scene::Scene::Load(std::shared_ptr<ratchet::scene::Scene::Param> param) {
    _transition_state = TransitionState::In;
    _effect = ratchet::scene::SceneEffect();
    _effect.value().Load("../Resource/shader/fadein.hlsl");
    bool seccess = _effect.value().CreateShaderBuffer("cbSceneEffectParam", sizeof(ratchet::scene::cbSceneEffectParam));
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

bool ratchet::scene::Scene::Initialize(void) {
    _effect.value().time = 1.0f;
    return true;
}

bool ratchet::scene::Scene::Input(void) {
    return true;
}

bool ratchet::scene::Scene::Update(float delta_time) {
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

bool ratchet::scene::Scene::Render(void) {
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

bool ratchet::scene::Scene::Release(void) {
    return true;
}