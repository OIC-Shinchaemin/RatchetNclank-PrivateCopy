#ifndef MY_CAMERA_CONTROLLER_H
#define MY_CAMERA_CONTROLLER_H


#include <memory>

#include "My/Core/Math.h"
#include "Camera.h"
#include "CameraManager.h"


namespace my {
class CameraController {
public:
    struct CameraInfo {
        Mof::CVector3 position;
        Mof::CVector3 target;
    };
protected:
    //! マネージャ
    static std::weak_ptr<my::CameraManager> _manager;
    //! カメラ
    std::shared_ptr<my::Camera>_camera;
    //! ばね定数
    const float _spring;
    //! 減衰定数
    const float _dumping;
    //! 位置
    Mof::CVector3 _position;
    //! 対象
    Mof::CVector3 _target;
    // 距離
    float _distance;
    //! Z軸を中心とした方位角θ
    math::Radian _azimuth;
    //! XY平面空の符号付回転角度（仰角）φ
    math::Radian _altitude;
    //! 速度
    Mof::CVector3 _velocity;
    //! 対象
    Mof::CVector3 _preview_position;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(const std::shared_ptr<my::Camera>& camera);
    /// <summary>
    /// 球座標系→直行座標系
    /// </summary>
    /// <param name="camera"></param>
    Mof::CVector3 SphericalToCartesian(Mof::CVector3 spherical) const;
    Mof::CVector3 SphericalToCartesian(float x, float y, float z) const;
public:
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    static void SetCameraManager(const std::shared_ptr<my::CameraManager>& ptr);
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~CameraController();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetCamera(const std::shared_ptr<my::Camera>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetCameraPosition(Mof::CVector3 pos);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetCameraTarget(Mof::CVector3 pos);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetDistance(float value);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="azimuth"></param>
    void SetAzimuth(float degree);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="degree"></param>
    void SetAltitude(float degree);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Camera> GetCamera(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetCameraPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetViewFront(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetAzimuth(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetAltitude(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDefaultAzimuth(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDefaultAltitude(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetVelocity(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPreviewPosition(void) const;
    /// <summary>
    /// 回転
    /// </summary>
    /// <param name="degree"></param>
    virtual void AddAzimuth(float degree);
    /// <summary>
    /// 回転
    /// </summary>
    /// <param name="degree"></param>
    virtual void AddAltitude(float degree);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasValidCamara(void) const;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool RegisterGlobalCamera(void);
};
}
#endif // !MY_CAMERA_CONTROLLER_H