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
    
    bool _active;
    BYTE _alpha = 0;
    CTexture _text_window_texture;
    CScript _script;
    CDynamicArray<CSprite2D*> _sprite_list;
    TEXTCOMMAND _text_command;
    char _line_buffer[256];
    int m_StrWait = 0;
    int	m_CommandNo = 0;
    COMMAND* m_pNowCommand;
    bool m_bWait = false;
    int	m_Flag[_flag_count];
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