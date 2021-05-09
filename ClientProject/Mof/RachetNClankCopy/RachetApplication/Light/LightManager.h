#ifndef MY_LIGHT_MANAGER_H
#define MY_LIGHT_MANAGER_H


#include <Mof.h>


namespace my {
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
};
}
#endif // !MY_LIGHT_MANAGER_H