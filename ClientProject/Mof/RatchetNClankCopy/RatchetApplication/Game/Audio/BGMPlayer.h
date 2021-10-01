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
    //! サウンド
    std::unordered_map<ratchet::game::audio::BGMType, std::shared_ptr<Mof::CStreamingSoundBuffer>> _sounds;
    //! メッセージ
    std::vector<ratchet::game::audio::BGMEvent> _recieved_event;
    //! ボリューム
    float _default_volume;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BGMPlayer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BGMPlayer();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="volume"></param>
    void SetDefaultVolume(float volume);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(ratchet::game::audio::BGMType type) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool IsPlay(ratchet::game::audio::BGMType type) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="key"></param>
    /// <param name="ptr"></param>
    /// <returns></returns>
    bool AddSound(ratchet::game::audio::BGMType key, const std::shared_ptr<Mof::CStreamingSoundBuffer>& ptr);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
    /// <summary>
    /// クリア
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Clear(void);
    /// <summary>
    /// 受付
    /// </summary>
    /// <param name="event"></param>
    /// <returns></returns>
    bool Recieve(const ratchet::game::audio::BGMEvent& event);
};
}
#endif // !RATCHET_GAME_AUDIO_BGM_PLAYER_H