#ifndef RATCHET_COMPONENT_SIGHT_RECOGNITION_COMPONENT_H
#define RATCHET_COMPONENT_SIGHT_RECOGNITION_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>
#include <vector>

#include "../Effect/EffectEmitter.h"

struct ContactEnemyMessage {
};
using ContactEnemyMessageSubject = base::core::Observable<const ContactEnemyMessage&>;
using ContactEnemyMessageListener = base::core::Observer<const  ContactEnemyMessage&>;

struct FindEnemyMessage {
};
using FindEnemyMessageSubject = base::core::Observable<const FindEnemyMessage&>;
using FindEnemyMessageListener = base::core::Observer<const  FindEnemyMessage&>;


namespace ratchet::component::player { class PlayerComponent; }
namespace ratchet::component::enemy { class EnemyComponent; }
namespace ratchet::component {
class SightRecognitionComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! 視野
    float _range;
    //! 認識
    std::vector<std::weak_ptr<ratchet::actor::Actor>> _recognized;
    //! 認識中
    int _recognizing_count;
    //std::vector<std::string> _recognizing;
    //! キャラ
    std::weak_ptr<ratchet::component::player::PlayerComponent> _player_com;
    //! キャラ
    std::weak_ptr<ratchet::component::enemy::EnemyComponent> _ENEMY_com;
    //! エフェクト
    //std::shared_ptr<effect::EffectEmitter> _effect_emitter;
    //! 会敵
    bool _contact_enemy;
    //! 通知
    ContactEnemyMessageSubject _contact_enemy_message_subject;
    //! 通知
    FindEnemyMessageSubject _find_enemy_message_subject;
    /// <summary>
    /// 発生
    /// </summary>
    /// <param name=""></param>
    void SenseEffectEmit(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority">優先度</param>
    SightRecognitionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    SightRecognitionComponent(const SightRecognitionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SightRecognitionComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto  GetContactEnemyMessageSubject(void) {
        return &this->_contact_enemy_message_subject;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetFindEnemyMessageSubject(void) {
        return &this->_find_enemy_message_subject;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<std::weak_ptr<ratchet::actor::Actor>>& GetRecognized(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_SIGHT_RECOGNITION_COMPONENT_H