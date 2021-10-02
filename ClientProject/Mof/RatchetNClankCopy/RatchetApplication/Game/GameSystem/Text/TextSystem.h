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

// ���N�G�X�g
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
    //! �\����
    bool _active;
    //! �\����
    BYTE _alpha = 0;
    //! �e�N�X�`��
    Mof::CTexture _text_window_texture;
    //! 
    CScript _script;
    //! 
    Mof::CDynamicArray<CSprite2D*> _sprite_list;
    //! 
    TEXTCOMMAND _text_command;
    //! �o�b�t�@
    char _line_buffer[256];
    //! �ҋ@
    int _str_wait = 0;
    //! �R�}���h
    int	_command_no = 0;
    //! �R�}���h
    COMMAND* _now_command;
    //! �ҋ@�t���O
    bool _wait = false;
    //! 
    int	_flags[_flag_count];
    //! �����\����
    int _wait_count_max = 3;
    //! �}�b�v
    std::unordered_map<TextEventType, std::string> _path_map;
    //! �ʒm�p
    TextSystemClosedMessageSubject _text_system_closed_message_subject;
    //! �ʒm�p
    TextSystemOpenMessageSubject _text_system_open_message_subject;
    //! �N���[�Y�C�x���g
    std::optional<TextSystemMessage::CloseEvent> _on_close;
    //! �v���C���[
    std::weak_ptr<ratchet::actor::Actor> _player;
    //! �v���C���[
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
    /// �R���X�g���N�^
    /// </summary>
    TextSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TextSystem();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const TextSystemMessage& message) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayer(const std::shared_ptr<ratchet::actor::Actor> ptr) {
        this->_player = ptr;
    }
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetScene(const std::shared_ptr<ratchet::scene::Scene> ptr) {
        this->_scene = ptr;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemClosedMessageSubject(void) {
        return &this->_text_system_closed_message_subject;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemOpenMessageSubject(void) {
        return &this->_text_system_open_message_subject;
    }
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// �L����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Activate(void);
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Load(void);
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
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_H