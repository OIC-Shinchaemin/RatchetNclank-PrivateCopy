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
    //! ��ԃt���O
    static const int _flag_count = 256;
    //! �ʒu
    Mof::CVector2 _window_position;
    //! �\����
    bool _active;
    //! �\����
    BYTE _alpha = 0;
    //! �e�N�X�`��
    Mof::CTexture _text_window_texture;
    //! 
    Script _script;
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
    std::shared_ptr<TextSystemOpenMessageSubject> _text_system_open_message_subject;
    //! �N���[�Y�C�x���g
    std::optional<TextSystemMessage::CloseEvent> _on_close;
    //! �t�H���g
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemOpenMessageSubject(void) {
        return this->_text_system_open_message_subject;
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