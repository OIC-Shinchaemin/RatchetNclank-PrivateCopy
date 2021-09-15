#ifndef RATCHET_ACTOR_CHARACTER_SCARECROW_H
#define RATCHET_ACTOR_CHARACTER_SCARECROW_H


#include "../Actor.h"


namespace ratchet::actor::character {
struct ScarecrowEndMessage {
    bool end;
};
using ScarecrowEndMessageSubject = base::core::Observable<const ScarecrowEndMessage&>;
using ScarecrowEndMessageListener = base::core::Observer<const ScarecrowEndMessage&>;

class Scarecrow : public actor::Actor {
    using super = actor::Actor;
private:
    //! 終了時通知用
    ratchet::actor::character::ScarecrowEndMessageSubject _end_message_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Scarecrow();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Scarecrow();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetScarecrowEndMessageSubject(void) {
        return &this->_end_message_subject;
    }
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_ACTOR_CHARACTER_SCARECROW_H