#ifndef MY_CAMERA_CONTROLLER_H
#define MY_CAMERA_CONTROLLER_H


#include <memory>

#include "My/Core/Math.h"
#include "Camera.h"
#include "CameraManager.h"


namespace my {
class CameraController {
public:
    struct Param {
        //! Z軸を中心とした方位角θ
        math::Radian azimuth;
        //! XY平面空の符号付回転角度（仰角）φ
        math::Radian altitude;
        // 距離
        float distance;
        //! ばね定数
        float spring;
        //! 減衰定数
        float dumping;
        //! 速度
        Mof::CVector3 velocity;
    };
    struct CameraInfo {
        Mof::CVector3 position;
        Mof::CVector3 target;
        Mof::CVector3 rotate;

        CameraInfo() :
            position(),
            target() {
        }
        CameraInfo(Mof::CVector3 pos, Mof::CVector3 tar) :
            position(pos),
            target(tar) {
        }
    };
protected:
    //! マネージャ
    static std::weak_ptr<my::CameraManager> _manager;
    //! カメラ
    std::shared_ptr<my::Camera>_camera;
    //! 位置
    Mof::CVector3 _position;
    //! 対象
    Mof::CVector3 _target;
    //! 位置
    Mof::CVector3 _preview_position;
    //! パラメータ
    my::CameraController::Param _param;
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
    /// カメラ所有判定
    /// </summary>
    /// <param name=""></param>
    operator bool(void) const;
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
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const my::CameraController::CameraInfo& info);
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