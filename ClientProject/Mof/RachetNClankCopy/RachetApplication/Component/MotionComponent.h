#ifndef MY_MOTION_COMPONENT_H
#define MY_MOTION_COMPONENT_H


#include "UpdateComponent.h"

#include <string>

#include "../MotionNames.h"


namespace my {
class MotionComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! アニメーションデータ
    Mof::LPMeshMotionController _motion;
    //! モーション
    my::MotionNames _motion_names;
    //std::unordered_map<std::string, std::string> _motion_names;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    void GenerateMotionNames(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    MotionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    MotionComponent(const MotionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MotionComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    const char* GetMotionName(const std::string& type);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::LPMeshMotionController GetMotionData(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEndMotion(void) const;
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
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    /// <param name="loop"></param>
    /// <param name="speed"></param>
    /// <param name="same"></param>
    /// <returns></returns>
    bool ChangeMotionByName(const char* name, bool loop = true, float speed = 1.0f, bool same = true);
};
}
#endif // !MY_MOTION_COMPONENT_H