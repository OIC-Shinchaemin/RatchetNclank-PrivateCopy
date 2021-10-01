#include "TitleSceneInitializer.h"

#include "Base/Resource/ResourceFont.h"
#include "../Factory/FactoryManager.h"
#include "../Camera/FollowCameraController.h"
#include "../Game/Audio/AudioUtility.h"


ratchet::scene::TitleSceneInitializer::TitleSceneInitializer() {
}

bool ratchet::scene::TitleSceneInitializer::Execute(std::shared_ptr<ratchet::scene::TitleScene>& out) {
    out->_stage.Initialize();

    auto actor_param = ratchet::actor::Actor::Param();
    actor_param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
    actor_param.transform.position = Mof::CVector3(10.0f, -5.0f, -15.0f);
    out->_demo_actor = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Player>("builder/demo_player.json", &actor_param);

    // camera
    out->_stage_view_camera = (std::make_shared<ratchet::camera::Camera>());
    //////////////auto pos = math::vec3::kZero;
    auto pos = actor_param.transform.position;
    auto offset = math::vec3::kNegUnitZ;
    out->_stage_view_camera->SetPosition(pos - offset);
    out->_stage_view_camera->SetTarget(pos);
    out->_stage_view_camera->Initialize();
    out->_stage_view_camera->Update();
    out->_camera_controller.SetService(std::make_shared<ratchet::camera::FollowCameraController>());
    out->_camera_controller.GetService()->SetCamera(out->_stage_view_camera);
    out->_camera_controller.GetService()->RegisterGlobalCamera();
    out->_camera_controller.GetService()->SetAzimuth(0.0f);
    out->_camera_controller.GetService()->SetAltitude(-13.0f);
    out->_camera_controller.GetService()->SetDistance(10.0f);

    {
        if (auto r = out->_resource.lock()) {
            auto bgm_player = out->GetBGMPlayer();
            auto bgm = r->Get<std::shared_ptr<Mof::CStreamingSoundBuffer>>("../Resource/bgm/title.mp3");
            bgm_player->AddSound(ratchet::game::audio::BGMType::Title, bgm);
            bgm->SetLoop(true);
            //bgm->SetVolume(0.5f);

            auto se_player = out->GetSEPlayer();
            auto add_cound = game::audio::SEAddSound(se_player, r);
            add_cound.Add(ratchet::game::audio::SEType::SystemSelect, "../Resource/se/system_select.mp3");
            add_cound.Add(ratchet::game::audio::SEType::SystemEner, "../Resource/se/system_enter.mp3");
            add_cound.Add(ratchet::game::audio::SEType::SystemMenuOpen, "../Resource/se/system_menu_open.mp3");

            out->_logo.SetTexture(out->GetResource()->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/title_logo/image.png"));
        } // if

    }


    auto bgm_player = out->GetBGMPlayer();
    auto e = ratchet::game::audio::BGMEvent();
    e.type = decltype(e.type)::Title;
    e.command = decltype(e.command)::Play();
    out->GetBGMPlayer()->Recieve(e);
    return true;
}