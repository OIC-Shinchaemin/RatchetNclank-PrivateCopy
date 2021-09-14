#ifndef RATCHET_UI_GAME_PAUSE_SYSTEM_MENU_H
#define RATCHET_UI_GAME_PAUSE_SYSTEM_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/GamePauseSystem.h"


namespace ratchet::ui {
class GamePauseSystemMenuItem : public base::ui::UIItem {
    using super = base::ui::UIItem;
private:
    //! �\���e�L�X�g
    std::string _text;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    GamePauseSystemMenuItem(const char* name);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GamePauseSystemMenuItem();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="text"></param>
    void SetText(const std::string& text);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector2 GetSize(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CTexture> GetTexture(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
class GamePauseSystemMenu : public base::ui::UIPanel,
    public base::core::Observer<const ratchet::game::gamesystem::GamePauseSystem::Info&> {
    using super = base::ui::UIPanel;
    using ElemType = ratchet::ui::GamePauseSystemMenuItem;
private:
    //! ���
    ratchet::game::gamesystem::GamePauseSystem::Info _infomation;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    GamePauseSystemMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::GamePauseSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CTexture> GetTexture(const std::string& type);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="in"></param>
    void AddItem(const ratchet::game::gamesystem::GamePauseSystemItem& in);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_GAME_PAUSE_SYSTEM_MENU_H