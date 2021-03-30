#ifndef MY_QUICK_CHANGE_SYSTEM_H
#define MY_QUICK_CHANGE_SYSTEM_H


#include "../ResourceLocator.h"
#include "My/Core/Observable.h"
#include "MY/UI/CanvasLocator.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "WeaponSystem.h"


namespace my {
class QuickChangeItem {
private:
    //! �ʒu
    Mof::CVector2 _position;
    //! ��`
    Mof::CRectangle _rectangle;
    //! �e�N�X�`��
    std::weak_ptr<Mof::CTexture> _texture;
    //! ���L
    std::string _weapon;
public:
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector2 pos);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="rect"></param>
    void SetRectangle(Mof::CRectangle rect);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
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
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(Mof::CVector4 color);
};
class QuickChangeSystem : public std::enable_shared_from_this<my::QuickChangeSystem>, public my::ResourceLocator, public my::CanvasLocator, public Observable<Mof::CVector4> {
    using Observable = my::Observable<Mof::CVector4>;
    enum class State {
        Enter,
        Exit
    };
private:
    //! �ʒu
    Mof::CVector2 _position;
    //! �F
    Mof::CVector4 _color;
    //! ���
    State _state;
    //! �A���t�@
    float _alpha;
    //! ���a
    float _distance;
    //! ����
    std::vector<int> _angles;
    //! ����
    std::optional<float> _current_angle;
    //! �A�C�e��
    std::unordered_map<int, my::QuickChangeItem> _items;
    //! �p�X
    std::unordered_map<std::string, std::string> _tex_names;

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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector4 GetColor(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    bool Initialize(Mof::CVector2 pos, const std::shared_ptr<my::WeaponSystem>& weapon_system);
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
    bool Update(void);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_QUICK_CHANGE_SYSTEM_H