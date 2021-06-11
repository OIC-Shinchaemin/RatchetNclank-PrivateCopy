#ifndef RATCHET_SIGHT_RECOGNITION_COMPONENT_H
#define RATCHET_SIGHT_RECOGNITION_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>
#include <vector>

namespace ratchet {
class SightRecognitionComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! 視野
    float _range;
    //! 認識
    std::vector<std::weak_ptr<ratchet::actor::Actor>> _recognized;
    //! キャラ
    std::weak_ptr<class PlayerComponent> _player_com;
    //! キャラ
    std::weak_ptr<class EnemyComponent> _ENEMY_com;
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
#endif // !RATCHET_SIGHT_RECOGNITION_COMPONENT_H