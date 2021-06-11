#ifndef RACHET_LIGHT_MANAGER_H
#define RACHET_LIGHT_MANAGER_H


#include <Mof.h>


namespace rachet {
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
#endif // !RACHET_LIGHT_MANAGER_H