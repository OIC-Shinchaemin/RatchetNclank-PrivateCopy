#ifndef MY_QUICK_CHANGE_SYSTEM_H
#define MY_QUICK_CHANGE_SYSTEM_H


#include "GameSystem.h"
#include "My/Core/Observable.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "WeaponSystem.h"
#include "MY/UI/UICanvas.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"


namespace my {
class QuickChangeItem {
private:
    //! ���L
    std::string _weapon;
public:
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="name"></param>
    void SetWeapon(const char* name);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetWeapon(void) const;
};

class QuickChangeSystem :
    public my::GameSystem {
    using super = my::GameSystem;
    using This = my::QuickChangeSystem;
    using Observable = my::Observable<Mof::CVector4>;
    enum class State {
        Enter,
        Exit
    };
public:
    struct Info {
        //! �\���F
        Mof::CVector4 color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.0f);
        //! ����
        std::optional<int> current_index;
    };
private:
    //! �F
    This::Info _infomation;
    //! �ʒm�p
    //my::Observable<const std::shared_ptr<This>&> _subject;
    //! ���
    State _state;
    //! �A���t�@
    float _alpha;
    //! ���a
    float _distance;
    //! ����
    std::vector<int> _angles;
    //! �A�C�e��
    std::unordered_map<int, my::QuickChangeItem> _items;
    //! �ʒm�p
    my::Observable<const std::string&> _current;
    //! ���\�[�X
    //std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    //std::weak_ptr<my::UICanvas> _ui_canvas;
    //! �Ď��Ώ�
    my::Observable<const This::Info&> _info_subject;
    /// <summary>
    /// �J��
    /// </summary>
    /// <param name=""></param>
    void Open(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void Close(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    QuickChangeSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~QuickChangeSystem();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    //void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    //void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ///my::Observable<const std::shared_ptr<This>&>* GetSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector4 GetColor(void) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddWeaponObserver(const std::shared_ptr<my::Observer<const std::string&>>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddInfoObserver(const std::shared_ptr<my::Observer<const my::QuickChangeSystem::Info&>>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="weapon_system"></param>
    /// <returns></returns>
    bool Initialize(const std::shared_ptr<my::WeaponSystem>& weapon_system);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_QUICK_CHANGE_SYSTEM_H