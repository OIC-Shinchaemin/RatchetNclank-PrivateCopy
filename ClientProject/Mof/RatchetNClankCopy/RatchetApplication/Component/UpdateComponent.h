#ifndef RATCHET_UPDATE_COMPONENT_H
#define RATCHET_UPDATE_COMPONENT_H


#include "Component.h"


namespace ratchet {
class UpdateComponent : public ratchet::Component {
    using super = ratchet::Component;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    UpdateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    UpdateComponent(const UpdateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~UpdateComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// 描画判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsUpdate(void) const override;
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
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_UPDATE_COMPONENT_H