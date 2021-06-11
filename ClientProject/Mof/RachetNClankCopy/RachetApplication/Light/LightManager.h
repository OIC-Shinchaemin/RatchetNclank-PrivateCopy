#ifndef RACHET_LIGHT_MANAGER_H
#define RACHET_LIGHT_MANAGER_H


#include <Mof.h>


namespace rachet {
class LightManager {
private:
    // 光源
    Mof::CDirectionalLight _simple_light;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LightManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~LightManager();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
};
}
#endif // !RACHET_LIGHT_MANAGER_H