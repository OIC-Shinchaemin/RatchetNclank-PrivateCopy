#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H


#include "Base/UI/UICanvas.h"
#include "../../../ResourceManager.h"
#include "Menu.h"
#include "Save.h"
#include "Script.h"
#include "SpriteSet.h"
#include "../../../Actor/Actor.h"
#include "../../../Scene/Scene.h"


namespace ratchet::game::gamesystem::text {
enum class TextEventType {
    TutorialEventNo0,
    TutorialEventNo1,
    TutorialEventNo0End,
    TutorialEventNo1End,
    KingTextEvent,
    KingFreeTalkTextEvent,
    QueenTextEvent,
    QueenFreeTalkTextEvent,

    TeachPlazaEvent,
    ItemCollectionCompleteEvent,
};

// リクエスト
struct TextSystemMessage {
    using CloseEvent = std::function<bool(void)>;
    TextEventType type;
    std::optional<CloseEvent> on_close;
};
using TextSystemMessageSubject = base::core::Observable<const TextSystemMessage&>;
using TextSystemMessageListener = base::core::Observer<const TextSystemMessage&>;

struct TextSystemClosedMessage {
    bool close = false;
};
//using TextSystemClosedMessageSubject = base::core::Observable<const TextSystemClosedMessage&>;
//using TextSystemClosedMessageListener = base::core::Observer<const TextSystemClosedMessage&>;
struct TextSystemClosedMessageSubject : public base::core::Observable<const TextSystemClosedMessage&> {
    using Message = const TextSystemClosedMessage&;
};
struct TextSystemClosedMessageListener : public base::core::Observer<const TextSystemClosedMessage&> {
    using Message = const TextSystemClosedMessage&;
};





struct TextSystemOpenMessage {
};
struct TextSystemOpenMessageSubject : public base::core::Observable<const TextSystemOpenMessage&> {
    using Message = const TextSystemOpenMessage&;
};
struct TextSystemOpenMessageListener : public base::core::Observer<const TextSystemOpenMessage&> {
    using Message = const TextSystemOpenMessage&;
};

class TextSystem : public TextSystemMessageListener {
private:
    static const int _flag_count = 256;
    //! 表示中
    bool _active;
    //! 表示中
    BYTE _alpha = 0;
    //! テクスチャ
    Mof::CTexture _text_window_texture;
    //! 
    CScript _script;
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
    TextSystemOpenMessageSubject _text_system_open_message_subject;
    //! クローズイベント
    std::optional<TextSystemMessage::CloseEvent> _on_close;
    //! プレイヤー
    std::weak_ptr<ratchet::actor::Actor> _player;
    //! プレイヤー
    std::weak_ptr<ratchet::scene::Scene> _scene;


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
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayer(const std::shared_ptr<ratchet::actor::Actor> ptr) {
        this->_player = ptr;
    }
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetScene(const std::shared_ptr<ratchet::scene::Scene> ptr) {
        this->_scene = ptr;
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemOpenMessageSubject(void) {
        return &this->_text_system_open_message_subject;
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