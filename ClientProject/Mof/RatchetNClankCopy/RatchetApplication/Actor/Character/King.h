#ifndef RATCHET_ACTOR_CHARACTER_KING_H
#define RATCHET_ACTOR_CHARACTER_KING_H


#include "Character.h"

#include "Scarecrow.h"
#include "../../Camera/CameraController.h"
#include "../../Component/CameraComponent.h"
#include "../../Effect/EffectContainer.h"
#include "../../Game/GameSystem/HelpDesk.h"
#include "../../Scene/Scene.h"


namespace ratchet::actor::character {
class Player;
class King :
    public ratchet::actor::character::Character,
    public ratchet::actor::character::ScarecrowEndMessageListener {
    using super = ratchet::actor::character::Character;

    struct ScarecrowGenerateData {
        std::vector<Mof::CVector3> position;
    };
private:
    //! ハテナ
    std::weak_ptr<Mof::CTexture> _question_texture;
    //! カカシ追加先ゲームシーン
    std::weak_ptr<ratchet::scene::Scene> _actor_container;
    //! 回数
    int _quest_index;
    //! 回数
    int _quest_count;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::camera::CameraController> _scarecrow_view_camera_controller;
    //! 視点
    Mof::CVector3 _scarecrow_view_position;
    //! エフェクト
    std::weak_ptr<effect::EffectContainer>_effect_container;
    //! テキストイベント
    int _free_talk_index;
    //! テキストイベントアイコン
    bool _event_icon_show;
    //! テキストイベントアイコン
    bool _event_active;
    //! 生成情報
    std::vector<ScarecrowGenerateData> _scarecrow_generate_datas;
    //! かかし
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _created_scarecrows;
    //! バリケード
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _created_barricade;
    //! 表示
    std::weak_ptr<ratchet::game::gamesystem::HelpDesk> _help_desk;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void PlayerActionLiberate(void);
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    void BarricadeCreate(ratchet::actor::Actor::Param* param, std::shared_ptr<ratchet::scene::Scene> out);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    King();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~King();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::actor::character::ScarecrowEndMessage& message);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameScene(const std::shared_ptr<scene::Scene>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    void SetHelpDesk(const std::shared_ptr<ratchet::game::gamesystem::HelpDesk>& ptr);
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
    virtual void Talk(void) override;
};
}
#endif // !RATCHET_ACTOR_CHARACTER_KING_H