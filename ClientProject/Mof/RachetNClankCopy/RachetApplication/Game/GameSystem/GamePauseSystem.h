#ifndef MY_GAME_PAUSE_SYSTEM_H
#define MY_GAME_PAUSE_SYSTEM_H


#include "GameSystem.h"

#include <optional>
#include <memory>
#include <vector>


namespace my {
class GamePauseSystemMenu;
class GamePauseSystemItem : public std::enable_shared_from_this<my::GamePauseSystemItem> {
    using this_type = my::GamePauseSystemItem;
private:
    //! �e�L�X�g
    std::string _text;
    //! ���s�֐�
    std::function<bool(void)> _on_enter;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GamePauseSystemItem();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GamePauseSystemItem(std::function<bool(void)> lambda);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GamePauseSystemItem();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="text"></param>
    void SetText(const char* text);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetText(void) const;
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Execute(void);
};
class GamePauseSystem : public my::GameSystem {
    using super = my::GameSystem;
    using this_type = my::GamePauseSystem;
    using ElemType = my::GamePauseSystemItem;
public:
    struct Info {
        bool enable = false;
        //bool enter = false;
        //bool exit = false;
        //bool push_item = false;
        std::optional<int> index = 0;
        std::vector<std::shared_ptr<ElemType>>* items;
        void Reset(void) {
            enable = false;
            //enter = false;
            //exit = false;
            //push_item = false;
            index.reset();
            ///items = nullptr;
        }
    };
private:
private:
    //! ���
    this_type::Info _infomation;
    //! �ʒm�p
    base::core::Observable<const this_type::Info&> _info_subject;
    //! �q��
    std::vector<std::shared_ptr<ElemType>> _items;
    //! �q��
    std::vector<std::shared_ptr<ElemType>> _execute_list;
    //! �C���f�b�N�X
    //std::optional<int> _item_index;
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
    base::core::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="elem"></param>
    /// <returns></returns>
    void AddItem(const std::shared_ptr<ElemType>& elem);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    void Inactive(void);
    /// <summary>
    /// �N���A
    /// </summary>
    /// <param name=""></param>
    void Clear(void);
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