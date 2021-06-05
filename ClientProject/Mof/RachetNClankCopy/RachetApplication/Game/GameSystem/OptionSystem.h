#ifndef MY_OPTION_SYSTEM_H
#define MY_OPTION_SYSTEM_H


#include "GameSystem.h"

#include <stack>

#include "../../Scene/SceneDefine.h"


namespace my {
class OptionSystemItem : public std::enable_shared_from_this<my::OptionSystemItem> {
    using this_type = my::OptionSystemItem;
private:
    //! �e�L�X�g
    std::string _text;
    //! ���s�֐�
    std::function<bool(void)> _on_enter;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    OptionSystemItem();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    OptionSystemItem(std::function<bool(void)> func);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~OptionSystemItem();
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


class OptionSystem : public my::GameSystem
//    ,
//    public my::Observer<const  std::shared_ptr<my::OptionSystem >&> 
{
    using super = my::GameSystem;
    using this_type = my::OptionSystem;
    using ElemType = my::OptionSystemItem;
public:
    struct Info {
        bool enter = false;
        bool exit = false;
        std::vector<std::shared_ptr<ElemType>>* items = nullptr;
    };
private:
    //! ���
    this_type::Info _infomation;
    //! �ʒm�p
    my::Observable<const this_type::Info&> _info_subject;
    //! �q��
    std::vector<std::shared_ptr<ElemType>> _item;
    //! �q��
    std::vector<std::shared_ptr<ElemType>> _execute_list;
    //! �C���f�b�N�X
    int _item_index;
    //! ��
    //std::stack <std::shared_ptr<this_type>> _next;
    //! �ʒm�p
    //my::Observable<const  std::shared_ptr<my::OptionSystem >&> option_system_subject;
    //! �ʒm�p
    my::Observable<const scene::SceneMessage&> _scene_message_subject;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    OptionSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~OptionSystem();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="pop"></param>
    //virtual void OnNotify(const std::shared_ptr<my::OptionSystem>& pop);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const my::scene::SceneMessage&>* GetSceneMessageSubject(void);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="next"></param>
    /// <returns></returns>
    //void PushSystem(const std::shared_ptr<my::OptionSystem>& next);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="elem"></param>
    /// <returns></returns>
    void AddItem(const std::shared_ptr<ElemType>& elem);
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
#endif // !MY_OPTION_SYSTEM_H