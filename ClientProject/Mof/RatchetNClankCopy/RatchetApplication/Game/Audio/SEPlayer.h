#ifndef RATCHET_GAME_AUDIO_SE_PLAYER_H
#define RATCHET_GAME_AUDIO_SE_PLAYER_H


#include <memory>
#include <unordered_map>

#include <Mof.h>

#include "SEDefine.h"


namespace ratchet::game::audio {
class SEPlayer {
private:
    //! �T�E���h
    std::unordered_map<ratchet::game::audio::SEType, std::shared_ptr<Mof::CSoundBuffer>> _sounds;
    //! ���b�Z�[�W
    std::vector<ratchet::game::audio::SEEvent> _recieved_event;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SEPlayer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SEPlayer();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(ratchet::game::audio::SEType type) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool IsPlay(ratchet::game::audio::SEType type) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="key"></param>
    /// <param name="ptr"></param>
    /// <returns></returns>
    bool AddSound(ratchet::game::audio::SEType key, const std::shared_ptr<Mof::CSoundBuffer>& ptr);
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
    bool Recieve(const ratchet::game::audio::SEEvent& event);
};
}
#endif // !RATCHET_GAME_AUDIO_SE_PLAYER_H