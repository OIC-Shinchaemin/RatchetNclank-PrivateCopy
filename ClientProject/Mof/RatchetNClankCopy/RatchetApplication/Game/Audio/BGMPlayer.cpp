#include "BGMPlayer.h"


ratchet::game::audio::BGMPlayer::BGMPlayer() :
    _sounds(),
    _recieved_event() {
}

ratchet::game::audio::BGMPlayer::~BGMPlayer() {
}

float ratchet::game::audio::BGMPlayer::GetVolume(ratchet::game::audio::BGMType type) const {
    auto& sound = _sounds.at(type);
    return sound->GetVolume();
}

bool ratchet::game::audio::BGMPlayer::IsPlay(ratchet::game::audio::BGMType type) const {
    auto& sound = _sounds.at(type);
    return sound->IsPlay();
}

bool ratchet::game::audio::BGMPlayer::AddSound(ratchet::game::audio::BGMType key, const std::shared_ptr<Mof::CStreamingSoundBuffer>& ptr) {
    auto it = _sounds.find(key);
    if (it != _sounds.end()) {
        return false;
    } // if
    _sounds.emplace(key, ptr);
    return true;
}

bool ratchet::game::audio::BGMPlayer::Update(void) {
    for (auto& event : _recieved_event) {
        auto& sound = _sounds.at(event.type);
        if (event.command.play) {
            sound->Play();
        } // if
        else if (event.command.stop) {
            sound->Stop();
        } // else if
        else if (event.command.set_volume) {
            sound->SetVolume(event.command.volume);
        } // else if
        else if (event.command.set_loop) {
            sound->SetLoop(event.command.loop);
        } // else if
    } // for
    _recieved_event.clear();

    for (auto& sound : _sounds) {
        sound.second->Update();
    } // for
    return true;
}

bool ratchet::game::audio::BGMPlayer::Clear(void) {
    _sounds.clear();
    _recieved_event.clear();
    return true;
}

bool ratchet::game::audio::BGMPlayer::Recieve(const ratchet::game::audio::BGMEvent& event) {
//    _recieved_event.push_back(event);
    return true;
}