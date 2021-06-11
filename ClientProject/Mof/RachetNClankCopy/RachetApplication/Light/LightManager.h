#ifndef RATCHET_LIGHT_MANAGER_H
#define RATCHET_LIGHT_MANAGER_H


#include <Mof.h>


namespace ratchet {
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
#endif // !RATCHET_LIGHT_MANAGER_H