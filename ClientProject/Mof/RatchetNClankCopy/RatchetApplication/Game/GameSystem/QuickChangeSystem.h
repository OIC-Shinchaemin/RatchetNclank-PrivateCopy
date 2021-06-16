#ifndef RATCHET_GAME_GAME_SYSTEM_QUICK_CHANGE_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_QUICK_CHANGE_SYSTEM_H


#include "GameSystem.h"
#include "Base/Core/Observable.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "WeaponSystem.h"
#include "Base/UI/UICanvas.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"


namespace ratchet {
namespace game {
namespace gamesystem {

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
    public ratchet::game::gamesystem::GameSystem {
    using super = ratchet::game::gamesystem::GameSystem;
    using This = ratchet::game::gamesystem::QuickChangeSystem;
    using Observable = base::core::Observable<Mof::CVector4>;
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
    //base::core::Observable<const std::shared_ptr<This>&> _subject;
    //! ���
    State _state;
    //! �A���t�@
    float _alpha;
    //! ���a
    float _distance;
    //! ����
    std::vector<int> _angles;
    //! �A�C�e��
    std::unordered_map<int, ratchet::game::gamesystem::QuickChangeItem> _items;
    //! �ʒm�p
    base::core::Observable<const std::string&> _current;
    //! ���\�[�X
    //std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    //std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! �Ď��Ώ�
    base::core::Observable<const This::Info&> _info_subject;
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
    //void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    //void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ///base::core::Observable<const std::shared_ptr<This>&>* GetSubject(void);
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
    void AddWeaponObserver(const std::shared_ptr<base::core::Observer<const std::string&>>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddInfoObserver(const std::shared_ptr<base::core::Observer<const ratchet::game::gamesystem::QuickChangeSystem::Info&>>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="weapon_system"></param>
    /// <returns></returns>
    bool Initialize(const std::shared_ptr<ratchet::game::gamesystem::WeaponSystem>& weapon_system);
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
}
}
#endif // !RATCHET_GAME_GAME_SYSTEM_QUICK_CHANGE_SYSTEM_H