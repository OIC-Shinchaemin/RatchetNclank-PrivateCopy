#ifndef MY_UPDATE_COMPONENT_H
#define MY_UPDATE_COMPONENT_H


#include "Component.h"


namespace my {
class UpdateComponent : public my::Component {
    using super = my::Component;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    UpdateComponent(int priority);
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
#ifdef _DEBUG
    virtual bool IsRender(void) const override;
#endif // !_DEBUG
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
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void);
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool End(void);
};
}
#endif // !MY_UPDATE_COMPONENT_H