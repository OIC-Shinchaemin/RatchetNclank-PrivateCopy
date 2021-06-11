#ifndef RATCHET_CAMERA_H
#define RATCHET_CAMERA_H


#include <Mof.h>


namespace ratchet {
class Camera {
private:
    //! カメラ
    Mof::CCamera _camera;
    //! 位置
    Mof::CVector3 _position;
    //! 対象
    Mof::CVector3 _target;
    //! 上向き
    Mof::CVector3 _up;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Camera();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Camera();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Mof::CVector3 position);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="target"></param>
    void SetTarget(Mof::CVector3 target);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    Mof::CVector3 GetPosition(void) ;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetTarget(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetViewFront(void) ;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    bool Update(void);
    /// <summary>
    /// グローバルカメラに登録
    /// </summary>
    /// <param name=""></param>
    void RegisterGlobalCamera(void);
};
}
#endif // !RATCHET_CAMERA_H