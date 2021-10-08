//#ifndef RATCHET_GAME_AUDIO_SOUND_PLAYER_H
//#define RATCHET_GAME_AUDIO_SOUND_PLAYER_H
//
//
//#include <memory>
//#include <vector>
//#include <unordered_map>
//
//
//namespace ratchet::game::audio {
//template<typename SoundEvent, typename Sound>
//class SoundPlayer {
//public:
//    using Event = SoundEvent;
//private:
//    //! �T�E���h
//    std::unordered_map<Event::Type, std::shared_ptr<Sound>> _sounds;
//    //! ���b�Z�[�W
//    std::vector<Event> _recieved_event;
//public:
//    /// <summary>
//    /// �R���X�g���N�^
//    /// </summary>
//    SoundPlayer() :
//        _sounds(),
//        _recieved_event() {
//    }
//    /// <summary>
//    /// �f�X�g���N�^
//    /// </summary>
//    ~SoundPlayer() {
//    }
//    /// <summary>
//    /// �Q�b�^�[
//    /// </summary>
//    /// <param name=""></param>
//    /// <returns></returns>
//    float GetVolume(Event::Type type) const {
//        auto& sound = _sounds.at(type);
//        return sound->GetVolume();
//    }
//    /// <summary>
//    /// ����
//    /// </summary>
//    /// <param name="type"></param>
//    /// <returns></returns>
//    bool IsPlay(Event::Type type) const {
//        auto& sound = _sounds.at(type);
//        return sound->IsPlay();
//    }
//    /// <summary>
//    /// �ǉ�
//    /// </summary>
//    /// <param name="key"></param>
//    /// <param name="ptr"></param>
//    /// <returns></returns>
//    bool AddSound(Event::Type key, const std::shared_ptr<Sound>& ptr) {
//        auto it = _sounds.find(key);
//        if (it != _sounds.end()) {
//            return false;
//        } // if
//        _sounds.emplace(key, ptr);
//        return true;
//    }
//    /// <summary>
//    /// �X�V
//    /// </summary>
//    /// <param name=""></param>
//    /// <returns></returns>
//    bool Update(void) {
//        for (auto& event : _recieved_event) {
//            auto& sound = _sounds.at(event.type);
//            if (event.command.play) {
//                sound->Play();
//            } // if
//            else if (event.command.stop) {
//                sound->Stop();
//            } // else if
//            else if (event.command.set_volume) {
//                sound->SetVolume(event.command.volume);
//            } // else if
//            else if (event.command.set_loop) {
//                sound->SetLoop(event.command.loop);
//            } // else if
//        } // for
//        _recieved_event.clear();
//
//        for (auto& sound : _sounds) {
//            sound.second->Update();
//        } // for
//        return true;
//    }
//    /// <summary>
//    /// �N���A
//    /// </summary>
//    /// <param name=""></param>
//    /// <returns></returns>
//    bool Clear(void) {
//        _sounds.clear();
//        _recieved_event.clear();
//        return true;
//    }
//    /// <summary>
//    /// ��t
//    /// </summary>
//    /// <param name="event"></param>
//    /// <returns></returns>
//    bool Recieve(const Event& event) {
//        _recieved_event.push_back(event);
//    }
//};
//}
//#endif // !RATCHET_GAME_AUDIO_SOUND_PLAYER_H