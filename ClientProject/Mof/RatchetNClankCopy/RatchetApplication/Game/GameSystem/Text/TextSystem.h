#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H


#include "Base/UI/UICanvas.h"
#include "../../../ResourceManager.h"
#include "Menu.h"
#include "Save.h"
#include "Script.h"
#include "SpriteSet.h"


namespace ratchet::game::gamesystem::text {
class TextSystem {
private:
    static const int _flag_count = 256;
    //! 表示中
    bool _active;
    //! 表示中
    BYTE _alpha = 0;
    CTexture _text_window_texture;
    CScript _script;
    CDynamicArray<CSprite2D*> _sprite_list;
    TEXTCOMMAND _text_command;
    char _line_buffer[256];
    int _str_wait = 0;
    int	_command_no = 0;
    COMMAND* _now_command;
    bool _wait = false;
    int	_flags[_flag_count];
    CMenu m_SaveMenu;

    bool Load(const char* name);
    bool Save(const char* name);
    bool LoadScript(const char* name);
    void InitializeScript(void);
    void UpdateAlpha(void);
    bool UpdateScript(void);
    void StepCommand(void);
    void TextCommand(void);
    void SpriteCommand(SPRITECOMMAND* pSpriteCommand);
    void SetPosCommand(SETPOSCOMMAND* pSpriteCommand);
    void SetShowCommand(SETSHOWCOMMAND* pSpriteCommand);
    bool JumpCommand(const char* label);
    void SelectCommand(void);
    void FlagCommand(FLAGCOMMAND* pFlagCommand);
    void IfCommand(IFCOMMAND* pIfCommand);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TextSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TextSystem();

    bool IsActive(void) const;
    bool Activate(void);
 
    bool Load(void);
    bool Update(void);
    bool Render(void);
    bool Release(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_ELEMENT_H