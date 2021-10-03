#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_MENU_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_MENU_H


#include <Mof.h>


namespace ratchet::game::gamesystem::text {
class TextMenu {
private:
    Mof::CVector2 _position;
    Mof::CVector2 _space;
    int _count;
    char* _title;
    char** _item;
    int	_select;
    bool _drag;
    bool _show;
    bool _enter;

    Mof::CRectangle _rectangle;
    Mof::CRectangle _header_rectangle;
public:
    TextMenu();
    ~TextMenu();
    int GetSelect(void) { return _select; }
    int GetCount(void) { return _count; }
    bool IsShow(void) { return _show; }
    bool IsEnter(void) { return _enter; }

    void Create(char* pTitle, char** pItem, int cnt);
    void Update(void);
    void Render(void);
    void Release(void);
    void Show(float cx, float cy);
    void Hide(void) {
        _show = false;
    }
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_MENU_H