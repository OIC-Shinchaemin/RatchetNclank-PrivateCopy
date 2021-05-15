#ifndef MY__BEZIER_CURVE_ANIMATION_H
#define MY__BEZIER_CURVE_ANIMATION_H


#include <cmath>
#include <vector>

#include "My/Core/Math.h"

#include <Mof.h>


namespace my {
enum class EaseType {
    Linear,
    EaseIn,
    EaseOut,
    EaseInOut,
};
struct AnimData {
    float value;
    float time;
    EaseType ease_type;
};
class BezierCurve {
private:
public:
    /// <summary>
    /// 補間
    /// </summary>
    /// <param name="time">timeは正規化されているものとする </param>
    /// <param name="prev"></param>
    /// <param name="next"></param>
    /// <param name="type"></param>
    /// <returns></returns>
    float Interpolation(float time, float prev, float next, my::EaseType type = my::EaseType::Linear) {
        switch (type) {
            case  EaseType::EaseInOut:
                time = 0.5f - 0.5f * std::cosf(math::kPi * time);
                break;
        } // switch

        float from = prev;
        float to = next;
        return from + (to - from) * time;
    }
    /// <summary>
    /// 補間計算
    /// </summary>
    /// <param name="normalized">アニメーションさせたい時間で割った値 最大値が1.0f</param>
    /// <param name="control">コントロールポイントの位置</param>
    /// <param name="type">イージング</param>
    /// <returns></returns>
    float InterpolationAnimData(float normalized, std::vector<float>& control, my::EaseType type = my::EaseType::Linear) {
        _ASSERT_EXPR(0.0 <= normalized, L"アニメーションの時間の閾値を超えています");
        if (control.size() > 2) {
            std::vector<float> anim_data;
            for (int i = 1; i < control.size(); i++) {
                float value = this->Interpolation(normalized, control.at(i - 1), control.at(i), type);
                anim_data.push_back(value);
            } // for
            return this->InterpolationAnimData(normalized, anim_data);
        } // if
        else if (control.size() == 2) {
            return this->Interpolation(normalized, control.at(0), control.at(1), type);
        } // else if
        return 0.0f;
    }
};

class BezierCurveAnimation {
private:
    //! コントロールポイント
    std::vector<float> _anim_data_x;
    //! コントロールポイント
    std::vector<float> _anim_data_y;
    //! コントロールポイント
    std::vector<float> _anim_data_z;
    //! アニメーション所要時間
    float _rate;
public:
    BezierCurveAnimation(float rate) :
        _anim_data_x(),
        _anim_data_y(),
        _anim_data_z(),
        _rate(rate) {
    };
    /// <summary>
    /// メモリ確保
    /// </summary>
    /// <param name="size"></param>
    void Reserve(uint32_t size) {
        _anim_data_x.reserve(size);
        _anim_data_y.reserve(size);
        _anim_data_z.reserve(size);
    }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="point"></param>
    void AddControlPoint(Mof::CVector3 point) {
        _anim_data_x.push_back(point.x);
        _anim_data_y.push_back(point.y);
        _anim_data_z.push_back(point.z);
    }
    /// <summary>
    /// 計算
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    Mof::CVector3 CalculatePointPosition(float time) {
        my::BezierCurve bezier_curve;
        Mof::CVector3 ret;
        ret.x = bezier_curve.InterpolationAnimData(time / _rate, _anim_data_x);
        ret.y = bezier_curve.InterpolationAnimData(time / _rate, _anim_data_y);
        ret.z = bezier_curve.InterpolationAnimData(time / _rate, _anim_data_z);
        return ret;
    }
};
}
#endif // !MY__BEZIER_CURVE_ANIMATION_H