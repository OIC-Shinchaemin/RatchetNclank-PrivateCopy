#ifndef MY_LIGHT_MANAGER_H
#define MY_LIGHT_MANAGER_H


#include <Mof.h>


namespace my {
class LightManager {
private:
    // ����
    Mof::CDirectionalLight _simple_light;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LightManager();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~LightManager();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
};
}
#endif // !MY_LIGHT_MANAGER_H