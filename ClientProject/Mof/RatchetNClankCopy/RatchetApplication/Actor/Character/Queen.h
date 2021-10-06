#ifndef RATCHET_ACTOR_CHARACTER_QUEEN_H
#define RATCHET_ACTOR_CHARACTER_QUEEN_H


#include "Character.h"
#include "../../Light/LightPillar.h"


namespace ratchet::actor::character {
class Queen:
    public actor::character::Character {
    using super = actor::character::Character;
private:
    //! イベント発火済み
    bool _event_activated;
    //! 光
    std::weak_ptr<ratchet::light::LightPillar> _light_pillar;
    //! 簡易影
    std::shared_ptr<actor::Actor> _shadow_child_actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Queen();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Queen();
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
    /// <summary>
    /// 会話
    /// </summary>
    void Talk(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_QUEEN_H