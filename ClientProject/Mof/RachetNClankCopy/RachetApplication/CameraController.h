#ifndef MY_CAMERA_CONTROLLER_H
#define MY_CAMERA_CONTROLLER_H


#include <memory>

#include "Define.h"

#include "My/Core/Observer.h"
#include "My/Core/Utility.h"
#include "My/Core/Math.h"


namespace my {
class CameraController {
private:
    //! ばね定数
    const float kSpring; 
    //! 減衰定数
    const float kDumping; 
    //! カメラ
    std::weak_ptr<class Camera>_camera;
    //! 対象
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
    void SetCamera(const std::shared_ptr<class Camera>& ptr);
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
    /// 回転
    /// </summary>
    /// <param name="degree"></param>
    void AddAzimuth(float degree);
    /// <summary>
    /// 回転
    /// </summary>
    /// <param name="degree"></param>
    void AddAltitude(float degree);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasValidCamara(void) const;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !MY_CAMERA_CONTROLLER_H