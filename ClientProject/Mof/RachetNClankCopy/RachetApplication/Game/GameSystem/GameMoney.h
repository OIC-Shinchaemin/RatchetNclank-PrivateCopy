#ifndef MY_GAME_MONEY_H
#define MY_GAME_MONEY_H


#include <memory>
#include <string>

#include <Mof.h>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "Save/SaveData.h"


namespace my {
class GameMoney : public std::enable_shared_from_this<my::GameMoney>, public my::Observer<int> {
private:
    //! ����
    std::uint32_t _value;
    //! �ʒm�p
    my::Observable<int> _subject;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameMoney();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameMoney();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(int add_money) override;
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
    std::uint32_t GetValue(void) const;
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Load(my::SaveData& in);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_GAME_MONEY_H