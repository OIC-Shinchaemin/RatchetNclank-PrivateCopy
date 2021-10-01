#include "SEPlayer.h"


ratchet::game::audio::SEPlayer::SEPlayer() :
	_sounds(),
	_recieved_event(),
	_default_volume(0.05f){
}

ratchet::game::audio::SEPlayer::~SEPlayer() {
}

void ratchet::game::audio::SEPlayer::SetDefaultVolume(float volume) {
	this->_default_volume = volume;
}

float ratchet::game::audio::SEPlayer::GetVolume(ratchet::game::audio::SEType type) const {
	auto& sound = _sounds.at(type);
	return sound->GetVolume();
}

bool ratchet::game::audio::SEPlayer::IsPlay(ratchet::game::audio::SEType type) const {
	auto& sound = _sounds.at(type);
	return sound->IsPlay();
}

bool ratchet::game::audio::SEPlayer::AddSound(ratchet::game::audio::SEType key, const std::shared_ptr<Mof::CSoundBuffer>& ptr) {
	auto it = _sounds.find(key);
	if (it != _sounds.end()) {
		return false;
	} // if

	{
		ptr->SetVolume(_default_volume);
	}
	_sounds.emplace(key, ptr);
	return true;
}

bool ratchet::game::audio::SEPlayer::Update(void) {
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

bool ratchet::game::audio::SEPlayer::Clear(void) {
	_sounds.clear();
	_recieved_event.clear();
	return true;
}

bool ratchet::game::audio::SEPlayer::Recieve(const ratchet::game::audio::SEEvent& event) {
	_recieved_event.push_back(event);
	return true;
}