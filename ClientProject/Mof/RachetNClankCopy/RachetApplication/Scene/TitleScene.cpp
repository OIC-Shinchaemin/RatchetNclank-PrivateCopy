#include "TitleScene.h"
#include "../Gamepad.h"
#include "My/Resource/ResourceFont.h"


bool my::TitleScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START) ||
        ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kGameScene, ""));
    } // if


    auto pos = Mof::CVector3(10.0f, -2.0f, -15.0f);

    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(_camera_controller.GetService()->GetAzimuth()) + 0.2f);
    _camera_controller.GetService()->SetCameraTarget(pos);

    _camera_controller.GetService()->Update();
    return true;
}

bool my::TitleScene::LoadingUpdate(float delta_time) {
    return true;
}

bool my::TitleScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);


    if (auto resource = _resource.lock()) {
        auto mesh = resource->Get<std::shared_ptr<Mof::CMeshContainer>>("../Resource/mesh/Chara/Chr_01_ion_mdl_01.mom");


        _motion->ChangeMotionByName("bse_wait_lp");
        _motion->AddTimer(1.0f);

        Mof::CMatrix44 scale, rotate, translate;
        scale.Scaling(math::vec3::kOne, scale);
        rotate.RotationZXY(Mof::CVector3(0.0f, -math::kHalfPi, 0.0f));
        translate.Translation(Mof::CVector3(10.0f, -5.0f, -15.0f), translate);
        auto world = scale * rotate * translate;

        _motion->RefreshBoneMatrix(world);
        mesh->Render(_motion);
    } // if

    _stage.Render();


    Mof::CMatrix44 scale, rotate, translate;
    scale.Scaling(math::vec3::kOne * 128.0f, scale);
    rotate.RotationZXY(math::vec3::kZero);
    translate.Translation(math::vec3::kZero, translate);
    auto world = scale * rotate * translate;

    _uv_scroll += Mof::CVector2(0.0001f, 0.005f);

    gShaderBind.SetCamera(::CGraphicsUtilities::GetCamera());
    gShaderBind.SetDirectionalLight(::CGraphicsUtilities::GetDirectionalLight());
    gShaderBind.GetShaderBuffer(0)->SetBuffer(&_uv_scroll);
    //_plane->Render(world, def::color_rgba::kWhite * 0.5f, &gShader, &gShaderBind);



    ::g_pGraphics->SetDepthEnable(false);
    if (auto resource = _resource.lock()) {
        auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");
        auto text = "Please Press   Start Button or \n                          Enter Key !";
        font->RenderString(220.0, 400.0f, def::color_rgba_u32::kGreen, text);
    } // if

    return true;
}

bool my::TitleScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);
    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, def::color_rgba_u32::kRed, "Now Loading");
    return true;
}

my::TitleScene::TitleScene() :
    super(),
    _stage(),
    _stage_view_camera(),
    _camera_controller(),
    _mock(),
    _plane(),
    _scroll(),
    _uv_scroll(),
    gShader(),
    gShaderBind(),
    _simple_light(),
    _motion() {
}

my::TitleScene::~TitleScene() {
}

void my::TitleScene::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
}

std::string my::TitleScene::GetName(void) {
    return my::SceneType::kTitleScene;
}

bool my::TitleScene::Load(std::shared_ptr<my::Scene::Param> param) {
    super::Load(param);

    super::_load_thread = std::thread([&]() {
        if (!super::IsLoaded()) {
            ::CoInitialize(NULL);
            auto path = "../Resource/scene_resource/game_scene.txt";
            if (auto r = _resource.lock()) {
                r->Load(path);
            } // if
            // stage
            if (!_stage.Load("../Resource/stage/test.json")) {
            } // if
            _stage.Initialize();

            _plane = Mof::CGraphicsUtilities::CreatePlaneGeometry(
                1.0f, 1.0f, 1.0f, 1.0f, true, math::vec3::kZero
            );

            //_mock.Load("../Resource/texture/water/water0.jpg");
            if (auto resource = _resource.lock()) {
                auto tex = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/water/water0.jpg");
                _plane->GetMaterial()->GetTextureArray()->Add(tex.get());
            } // if
            //_plane->GetMaterial()->GetTextureArray()->Add(&_mock);


            //シェーダーの読み込み
            gShader.Load("../Resource/shader/water.hlsl");
            gShaderBind.Create(&gShader);
            gShaderBind.CreateShaderBuffer("cbUVScrollParam", sizeof(cbUVScrollParam));

            // light
            _simple_light.SetDirection(-math::vec3::kOne);
            _simple_light.SetDiffuse(def::color_rgba::kWhite);
            _simple_light.SetAmbient(def::color_rgba::kWhite * 0.8f);
            ::CGraphicsUtilities::SetDirectionalLight(&_simple_light);


            super::LoadComplete();

            if (auto resource = _resource.lock()) {
                auto mesh = resource->Get<std::shared_ptr<Mof::CMeshContainer>>("../Resource/mesh/Chara/Chr_01_ion_mdl_01.mom");

                _motion = mesh->CreateMotionController();
            } // if
            ::CoUninitialize();
        } // if
    });



    // camera
    _stage_view_camera = (std::make_shared<my::Camera>());
    auto pos = math::vec3::kZero;
    auto offset = math::vec3::kNegUnitZ;
    _stage_view_camera->SetPosition(pos - offset);
    _stage_view_camera->SetTarget(pos);
    _stage_view_camera->Initialize();
    _stage_view_camera->Update();
    _camera_controller.SetService(std::make_shared<my::CameraController>());
    _camera_controller.GetService()->SetCamera(_stage_view_camera);
    _camera_controller.GetService()->RegisterGlobalCamera();
    _camera_controller.GetService()->SetAzimuth(0.0f);
    _camera_controller.GetService()->SetAltitude(-10.0f);
    _camera_controller.GetService()->SetDistance(8.0f);
    return true;
}

bool my::TitleScene::Release(void) {
    super::Release();
    _stage.Release();

    gShaderBind.Release();
    gShader.Release();
    ut::SafeDelete(_motion);

    return false;
}