#ifndef RATCHET_GAME_AUDIO_AUDIO_UTILITY_H
#define RATCHET_GAME_AUDIO_AUDIO_UTILITY_H


#include <memory>
#include <unordered_map>

#include <Mof.h>

#include "BGMDefine.h"
#include "SEDefine.h"
#include "SEPlayer.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"


namespace ratchet::game::audio {
struct SEAddSound {
    std::shared_ptr<ratchet::game::audio::SEPlayer> player;
    std::shared_ptr<ratchet::ResourceMgr> resource;

    SEAddSound(const std::shared_ptr<ratchet::game::audio::SEPlayer>& se_player,
               const std::shared_ptr<ratchet::ResourceMgr>& resource) :
        player(se_player),
        resource(resource) {
    }
    ~SEAddSound() {
        player.reset();
        resource.reset();
    }

    bool Add(ratchet::game::audio::SEEvent::Type type, const char* path) {
        auto ptr = resource->Get<std::shared_ptr<Mof::CSoundBuffer>>(path);
        return player->AddSound(type, ptr);
    }
    bool Add(ratchet::game::audio::SEEvent::Type type, const char* path, bool loop) {
        auto ptr = resource->Get<std::shared_ptr<Mof::CSoundBuffer>>(path);
        ptr->SetLoop(false);
        return player->AddSound(type, ptr);
    }
    bool Add(ratchet::game::audio::SEEvent::Type type, const char* path, float volume) {
        auto ptr = resource->Get<std::shared_ptr<Mof::CSoundBuffer>>(path);
        ptr->SetVolume(volume);
        return player->AddSound(type, ptr);
    }
    bool Add(ratchet::game::audio::SEEvent::Type type, const char* path, bool loop, float volume) {
        auto ptr = resource->Get<std::shared_ptr<Mof::CSoundBuffer>>(path);
        ptr->SetLoop(loop);
        ptr->SetVolume(volume);
        return player->AddSound(type, ptr);
    }

};
}
#endif // !RATCHET_GAME_AUDIO_AUDIO_UTILITY_H