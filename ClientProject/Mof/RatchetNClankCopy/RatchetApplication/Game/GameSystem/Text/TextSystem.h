#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H


#include <memory>
#include <vector>

#include "Base/UI/UICanvas.h"
#include "../../../ResourceManager.h"
#include "Script.h"
#include "TextSystemDefine.h"


namespace ratchet::game::gamesystem::text {
class TextSystem : public TextSystemMessageListener {
private:
    //! 状態フラグ
    static const int _flag_count = 256;
    //! 位置
    Mof::CVector2 _window_position;
    //! 表示中
    bool _active;
    //! 表示中
    BYTE _alpha = 0;
    //! テクスチャ
    Mof::CTexture _text_window_texture;
    //! 
    Script _script;
    //! 
    Mof::CDynamicArray<CSprite2D*> _sprite_list;
    //! 
    TEXTCOMMAND _text_command;
    //! バッファ
    char _line_buffer[256];
    //! 待機
    int _str_wait = 0;
    //! コマンド
    int	_command_no = 0;
    //! コマンド
    COMMAND* _now_command;
    //! 待機フラグ
    bool _wait = false;
    //! 
    int	_flags[_flag_count];
    //! 文字表示速
    int _wait_count_max = 3;
    //! マップ
    std::unordered_map<TextEventType, std::string> _path_map;
    //! 通知用
    TextSystemClosedMessageSubject _text_system_closed_message_subject;
    //! 通知用
    std::shared_ptr<TextSystemOpenMessageSubject> _text_system_open_message_subject;
    //! クローズイベント
    std::optional<TextSystemMessage::CloseEvent> _on_close;
    //! フォント
    Mof::CFont _text_font;
    int ALPHA_SPEED = 15;

    bool Load(const char* name);
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
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const TextSystemMessage& message) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemOpenMessageSubject(void) {
        return this->_text_system_open_message_subject;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemClosedMessageSubject(void) {
        return &this->_text_system_closed_message_subject;
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Activate(void);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Load(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H