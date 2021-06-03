#ifndef MY_GAME_SYSTEM_H
#define MY_GAME_SYSTEM_H


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
class GameSystem : public std::enable_shared_from_this<my::GameSystem>,
    public my::Observer<bool> {
    using This = my::GameSystem;
private:
    //! �ʒm�p
    my::Observable<const std::shared_ptr<This>&> _subject;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;

protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::ResourceMgr> GetResource(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::UICanvas> GetUICanvas(void) const;
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
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const std::shared_ptr<This>&>* GetSubject(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
};
}
#endif // !MY_GAME_SYSTEM_H