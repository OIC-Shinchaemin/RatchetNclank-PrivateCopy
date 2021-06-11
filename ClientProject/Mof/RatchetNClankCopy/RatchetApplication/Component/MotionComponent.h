#ifndef RATCHET_MOTION_COMPONENT_H
#define RATCHET_MOTION_COMPONENT_H


#include "UpdateComponent.h"

#include <string>

#include <Mof.h>

#include "../MotionNames.h"


namespace ratchet {
class MotionComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! モーション
    Mof::LPMeshMotionController	_motion;
    //! モーション名
    std::weak_ptr<ratchet::MotionNames> _motion_names;
    //! パス
    std::string _path;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    /// <param name="speed"></param>
    /// <param name="loop"></param>
    /// <param name="same"></param>
    /// <returns></returns>
    bool ChangeMotionByName(const char* name, float speed = 1.0f, bool loop = true, bool same = true);
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
    const std::shared_ptr<ratchet::MotionNames> GetMotionInfoMap(void) const;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
    /// <summary>
    /// 変更
    /// </summary>
    /// <typeparam name="Enum"></typeparam>
    /// <param name="type"></param>
    /// <param name="speed"></param>
    /// <param name="loop"></param>
    /// <param name="same"></param>
    /// <returns></returns>
    template<typename Enum>
    bool ChangeMotion(Enum type, float speed = 1.0f, bool loop = true, bool same = true) {
        if (auto motion_names = _motion_names.lock()) {
            return this->ChangeMotionByName(
                motion_names->At(type),
                speed, loop, same);
        } // if
        return false;
    }
    /// <summary>
    /// 時間
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    bool AddTimer(float time);
};
}
#endif // !RATCHET_MOTION_COMPONENT_H