#ifndef MY_GAME_PAUSE_SYSTEM_H
#define MY_GAME_PAUSE_SYSTEM_H


#include "GameSystem.h"


namespace my {
class GamePauseSystemMenu;
class GamePauseSystem : public my::GameSystem {
    using super = my::GameSystem;
    using this_type = my::GamePauseSystem;
public:
    struct Info {
        bool enter = false;
        bool exit = false;
        int index = 0;
    };
private:
    //! ���
    this_type::Info _infomation;
    //! �ʒm�p
    my::Observable<const this_type::Info&> _info_subject;
    //! �C���f�b�N�X
    int _item_index;
    //! UI�n��
    my::UICreator<class GamePauseSystemMenu> _ui_creator;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GamePauseSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GamePauseSystem();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_GAME_PAUSE_SYSTEM_H