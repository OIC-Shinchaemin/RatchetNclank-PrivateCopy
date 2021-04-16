#ifndef MY_CAMERA_COMPONENT_H
#define MY_CAMERA_COMPONENT_H


#include "UpdateComponent.h"

#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


namespace my {
class CameraComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! 対象
    Mof::CVector3 _target;
    //! カメラ
    std::shared_ptr<my::Camera> _player_view_camera;
    //! カメラコントローラ
    my::CameraController _camera_controller;
    /// <summary>
    /// 操作
    /// </summary>
    /// <param name=""></param>
    void ControllByKeyboard(void);
    /// <summary>
    /// 操作
    /// </summary>
    /// <param name=""></param>
    void ControllByGamepad(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    CameraComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    CameraComponent(const CameraComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CameraComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetTarget(Mof::CVector3 pos);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
};
}
#endif // !MY_CAMERA_COMPONENT_H