#ifndef RACHET_GAMEPAD_H
#define RACHET_GAMEPAD_H


#include <memory>

#include <Mof.h>


namespace rachet {
class Gamepad {
private:
    //! �������t���O
    bool _initialized;
    //! �Q�[���p�b�h
    std::shared_ptr<Mof::CXGamePad>_gamepad;
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Gamepad();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Gamepad();
public:
    /// <summary>
    /// �V���O���g��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static rachet::Gamepad& GetInstance(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CXGamePad>GetGamepad(void) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Create(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void RefreshKey(void);
};
}
#define g_pGamepad rachet::Gamepad::GetInstance().GetGamepad()
#endif // !RACHET_GAMEPAD_H