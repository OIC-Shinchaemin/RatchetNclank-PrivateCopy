#ifndef RATCHET_GAME_AUDIO_BGM_PLAYER_H
#define RATCHET_GAME_AUDIO_BGM_PLAYER_H


#include <memory>
#include <string>
#include <unordered_map>

#include <Mof.h>

#include "BGMDefine.h"


namespace ratchet::game::audio {
class BGMPlayer {
private:
    //! �T�E���h
    std::unordered_map<ratchet::game::audio::BGMType, std::shared_ptr<Mof::CStreamingSoundBuffer>> _sounds;
    //! ���b�Z�[�W
    std::vector<ratchet::game::audio::BGMEvent> _recieved_event;
    //! �{�����[��
    float _default_volume;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BGMPlayer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BGMPlayer();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="volume"></param>
    void SetDefaultVolume(float volume);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(ratchet::game::audio::BGMType type) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool IsPlay(ratchet::game::audio::BGMType type) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="key"></param>
    /// <param name="ptr"></param>
    /// <returns></returns>
    bool AddSound(ratchet::game::audio::BGMType key, const std::shared_ptr<Mof::CStreamingSoundBuffer>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
    /// <summary>
    /// �N���A
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Clear(void);
    /// <summary>
    /// ��t
    /// </summary>
    /// <param name="event"></param>
    /// <returns></returns>
    bool Recieve(const ratchet::game::audio::BGMEvent& event);
};
}
#endif // !RATCHET_GAME_AUDIO_BGM_PLAYER_H