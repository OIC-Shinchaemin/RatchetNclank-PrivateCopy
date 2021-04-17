#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// カメラ制御クラス
/// </summary>
// ********************************************************************************
class CameraController {
public:

    template<class T >
    struct Controll {
        bool    trigger_flag;
        T       move;
    };

    struct Controller {
        Controll<Vector3>   rotation;
        Controll<float>     zoom;
        Controll<Vector3>   track;
    };

private:

    //! 制御するカメラポインタ
    CCamera* _camera_pointer{ nullptr };

    //! カメラのズーム率
    float _zoom_ratio{ 1.0f };

    // ********************************************************************************
    /// <summary>
    /// カメラのパン(左右)とティルト(上下)処理
    /// </summary>
    /// <param name="rotation">回転量</param>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void PanTilt(const Controll<Vector3>& rotation);

    // ********************************************************************************
    /// <summary>
    /// カメラのズーム
    /// </summary>
    /// <param name="zoom">ズーム量</param>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void Zoom(const Controll<float>& zoom);

    // ********************************************************************************
    /// <summary>
    /// カメラのトラック
    /// </summary>
    /// <param name="track">移動量</param>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void Track(const Controll<Vector3>& track);

public:

    // ********************************************************************************
    /// <summary>
    /// カメラの設定
    /// </summary>
    /// <param name="camera_pointer">制御するカメラポインタ</param>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void SetCamera(CCamera* camera_pointer);

    // ********************************************************************************
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="camera_pointer">制御するカメラポインタ</param>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void Initialize(CCamera* camera_pointer);

    // ********************************************************************************
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="controller">制御データ</param>
    /// <created>いのうえ,2021/03/17</created>
    /// <changed>いのうえ,2021/03/17</changed>
    // ********************************************************************************
    void Update(const Controller& controller);

};

