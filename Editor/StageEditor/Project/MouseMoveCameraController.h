#pragma once
#include "CameraController.h"

// ********************************************************************************
/// <summary>
/// カメラ制御クラスのマウスで操作するクラス
/// </summary>
// ********************************************************************************
class MouseMoveCameraController : public CameraController {
private:

    // ********************************************************************************
    /// <summary>
    /// マウスでの操作情報を返す
    /// </summary>
    /// <returns>コントロール情報</returns>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    Controller MouseMoveController(void);

    Controller ModeHand(void);
    Controller ModeEye(void);
    Controller ModeInstObject(void);


public:
    // ********************************************************************************
    /// <summary>
    /// 更新
    /// </summary>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void Update(void);
};

