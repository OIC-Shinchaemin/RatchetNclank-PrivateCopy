#include "BGMPlayer.h"


ratchet::game::audio::BGMPlayer::BGMPlayer() :
    _sounds(),
    _recieved_event(),
    _default_volume(0.2f) {
}

ratchet::game::audio::BGMPlayer::~BGMPlayer() {
}

void ratchet::game::audio::BGMPlayer::SetDefaultVolume(float volume) {
    this->_default_volume = volume;
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

    if (ptr) {
        ptr->SetVolume(_default_volume);
        ptr->SetLoop(true);
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
        if (event.command.stop) {
            sound->Stop();
        } // else if
        if (event.command.set_volume) {
            sound->SetVolume(event.command.volume);
        } // else if
        if (event.command.set_loop) {
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
    /*
    {
        auto e = const_cast<ratchet::game::audio::BGMEvent*>(&event);
        e->command.set_volume = true;;
        e->command.volume = _default_volume;
        e->command.set_loop = true;
        e->command.loop = true;
    }
    */

    _recieved_event.push_back(event);
    return true;
}