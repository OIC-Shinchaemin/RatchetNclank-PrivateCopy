#ifndef RACHET_GAME_SYSTEM_H
#define RACHET_GAME_SYSTEM_H


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


namespace rachet {
class GameSystem : public std::enable_shared_from_this<rachet::GameSystem>,
    public base::core::Observer<bool> {
    using this_type = rachet::GameSystem;
private:
    //! �ʒm�p
    base::core::Observable<const std::shared_ptr<this_type>&> _subject;
    //! ���\�[�X
    std::weak_ptr<rachet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<rachet::ResourceMgr> GetResource(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<base::ui::UICanvas> GetUICanvas(void) const;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GameSystem();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const std::shared_ptr<this_type>&>* GetSubject(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Update(float delta_time);
};
}
#endif // !RACHET_GAME_SYSTEM_H