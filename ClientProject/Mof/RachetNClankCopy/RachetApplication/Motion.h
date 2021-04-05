#ifndef MY_MOTION_H
#define MY_MOTION_H


#include <string>
#include <array>
#include <unordered_map>

#include <Mof.h>

#include "My/Core/Utility.h"

#include "GameDefine.h"
#include "MotionNames.h"


namespace my {
class Motion {
private:
    //! アニメーションデータ
    Mof::LPMeshMotionController _motion;
    //! 名前
    MotionNames _motion_names;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Motion() :
        _motion(),
        _motion_names() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Motion() {
    }
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetLPMeshMotionController(Mof::LPMeshMotionController ptr) {
        this->_motion = ptr;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    const char* GetMotionName(int type) {

        // check contains
        auto it = _motion_names.find(type);
        if (it != _motion_names.end()) {
            return it->second.c_str();
        } // id
        return nullptr;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::LPMeshMotionController GetMotionData(void) const {
        return this->_motion;
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEndMotion(void) const {
        return _motion->IsEndMotion();
    }
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    bool AddTimer(float time) {
        return _motion->AddTimer(time);
    }
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="type"></param>
    /// <param name="loop"></param>
    /// <param name="speed"></param>
    /// <param name="same"></param>
    /// <returns></returns>
    bool ChangeMotion(int type, bool loop = true, float speed = 1.0f, bool same = true) {
        if (_motion) {
            return _motion->ChangeMotionByName(this->GetMotionName(type), speed, loop, same);
        } // if
        return false;
    }
};
}
#endif // !MY_MOTION_H