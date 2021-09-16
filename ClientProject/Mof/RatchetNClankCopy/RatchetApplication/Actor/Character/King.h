#ifndef RATCHET_ACTOR_CHARACTER_KING_H
#define RATCHET_ACTOR_CHARACTER_KING_H


#include "../Actor.h"

#include "../../Game/GameSystem/Text/TextSystem.h"
#include "Scarecrow.h"
#include "../../Camera/CameraController.h"
#include "../../Component/CameraComponent.h"
#include "../../Effect/EffectContainer.h"


namespace ratchet::scene {
class GameScene;
}
namespace ratchet::actor::character {
class Player;
class King :
    public actor::Actor,
    public ratchet::actor::character::ScarecrowEndMessageListener {
    using super = actor::Actor;
private:
    //! ハテナ
    std::weak_ptr<Mof::CTexture> _question_texture;
    //! 通知用
    ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
    //! 通知用
    base::core::Observable<const ratchet::camera::CameraController::CameraInfo&> _player_camera_subject;
    //! カカシ追加先ゲームシーン
    std::weak_ptr<ratchet::scene::GameScene> _actor_container;
    //! 回数
    int _quest_index;
    //! 回数
    int _quest_count;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::camera::CameraController> _scarecrow_view_camera_controller;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::camera::CameraController>* _player_view_camera_controller;
    //! 視点
    Mof::CVector3 _scarecrow_view_position;
    //! エフェクト
    std::weak_ptr<effect::EffectContainer>_effect_container;
    //! エフェクト
    std::weak_ptr<ratchet::actor::character::Player> _player;
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
    void SetGameScene(const std::shared_ptr<scene::GameScene>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEffectContainer(const std::shared_ptr<effect::EffectContainer>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayer(const std::shared_ptr<ratchet::actor::character::Player>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCameraontroller(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemMessageSubject(void) {
        return &this->_text_system_message_subject;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetPlayerCameraSubject(void) {
        return &this->_player_camera_subject;
    }
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
#endif // !RATCHET_ACTOR_CHARACTER_KING_H