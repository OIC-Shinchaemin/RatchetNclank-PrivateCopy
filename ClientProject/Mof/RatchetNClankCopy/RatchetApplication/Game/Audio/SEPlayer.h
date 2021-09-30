#ifndef RATCHET_GAME_AUDIO_SE_PLAYER_H
#define RATCHET_GAME_AUDIO_SE_PLAYER_H


#include <memory>
#include <unordered_map>

#include <Mof.h>

#include "SEDefine.h"


namespace ratchet::game::audio {
class SEPlayer {
private:
    //! サウンド
    std::unordered_map<ratchet::game::audio::SEType, std::shared_ptr<Mof::CSoundBuffer>> _sounds;
    //! メッセージ
    std::vector<ratchet::game::audio::SEEvent> _recieved_event;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SEPlayer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SEPlayer();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(ratchet::game::audio::SEType type) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool IsPlay(ratchet::game::audio::SEType type) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="key"></param>
    /// <param name="ptr"></param>
    /// <returns></returns>
    bool AddSound(ratchet::game::audio::SEType key, const std::shared_ptr<Mof::CSoundBuffer>& ptr);
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
    bool Recieve(const ratchet::game::audio::SEEvent& event);
};
}
#endif // !RATCHET_GAME_AUDIO_SE_PLAYER_H