#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_H


#include <Mof.h>
#include "Menu.h"


namespace ratchet::game::gamesystem::text {
//�R�}���h�̒�`
enum tag_SCRIPTCOMMAND {
    CMD_TEXT,
    CMD_SPRITE,
    CMD_SETPOS,
    CMD_SETSHOW,
    CMD_LABEL,
    CMD_JUMP,
    CMD_NEXT,
    CMD_SELECT,
    CMD_FLAG,
    CMD_IF,

    CMD_COUNT,
};

typedef struct tag_COMMAND {
    int					Type;
    //delete���ɔh����̃f�X�g���N�^���Ăяo�����߂ɉ��z��`�����Ă���
    virtual ~tag_COMMAND() {}
}COMMAND;
//�e�L�X�g�\���R�}���h�̂��߂̍\����
#define		TEXTBUFFERSIZE			256
typedef struct tag_TEXTCOMMAND : public COMMAND {
    float				px;
    float				py;
    char				Text[TEXTBUFFERSIZE];

    tag_TEXTCOMMAND() {
        Type = CMD_TEXT;
        px = 0;
        py = 0;
        memset(Text, 0, TEXTBUFFERSIZE);
    }
}TEXTCOMMAND;
//�X�v���C�g�쐬�R�}���h�̂��߂̍\����
typedef struct tag_SPRITECOMMAND : public COMMAND {
    char				FName[256];
    char				Name[256];

    tag_SPRITECOMMAND() {
        Type = CMD_SPRITE;
        memset(FName, 0, 256);
        memset(Name, 0, 256);
    }
}SPRITECOMMAND;
//�X�v���C�g���W�ݒ�R�}���h�̂��߂̍\����
typedef struct tag_SETPOSCOMMAND : public COMMAND {
    float				px;
    float				py;
    char				Name[256];

    tag_SETPOSCOMMAND() {
        Type = CMD_SETPOS;
        px = 0;
        py = 0;
        memset(Name, 0, 256);
    }
}SETPOSCOMMAND;
//�X�v���C�g�\���ݒ�R�}���h�̂��߂̍\����
typedef struct tag_SETSHOWCOMMAND : public COMMAND {
    BOOL bShow;
    char Name[256];

    tag_SETSHOWCOMMAND() {
        Type = CMD_SETSHOW;
        bShow = false;
        memset(Name, 0, 256);
    }
}SETSHOWCOMMAND;
//���x���쐬�E�W�����v�E�t�@�C���ύX�R�}���h�̂��߂̍\����
typedef struct tag_NAMECOMMAND : public COMMAND {
    char				Name[256];

    tag_NAMECOMMAND(int cmd) {
        Type = cmd;
        memset(Name, 0, 256);
    }
}NAMECOMMAND;
//�I�����R�}���h�̂��߂̍\����
typedef struct tag_SELECTCOMMAND : public COMMAND {
    char				Name[256];
    int					Count;

    char** pItem;
    char** pLabel;

    CMenu				Select;

    /**
     * �R���X�g���N�^
     *
     */
    tag_SELECTCOMMAND() :
        Select() {
        Type = CMD_SELECT;
        memset(Name, 0, 256);
        Count = 0;
        pItem = NULL;
        pLabel = NULL;
    }

    /**
     * �f�X�g���N�^
     *
     */
    virtual ~tag_SELECTCOMMAND() {
        for (int i = 0; i < Count; i++) 		{
            free(pItem[i]);
            free(pLabel[i]);
        }
        free(pItem);
        free(pLabel);
        Select.Release();
    }
}SELECTCOMMAND;
//�t���O����̉��Z�q��`
enum tag_FLAGOP {
    OP_PLUS,				// +
    OP_MINUS,				// -
    OP_MULTIPLY,			// *
    OP_DIVISION,			// /
    OP_EQUAL,				// =

    OP_COUNT,
};
//�t���O����R�}���h�̂��߂̍\����
typedef struct tag_FLAGCOMMAND : public COMMAND {
    int					No;
    int					Op;
    int					Value;

    /**
     * �R���X�g���N�^
     *
     */
    tag_FLAGCOMMAND() {
        Type = CMD_FLAG;
        No = 0;
        Op = 0;
        Value = 0;
    }
}FLAGCOMMAND;
//��������̉��Z�q��`
enum tag_IFOP {
    CMP_GRATER,				// >
    CMP_GRATEREQUAL,		// >=
    CMP_EQUAL,				// =
    CMP_NOTEQUAL,			// !
    CMP_LESSEQUAL,			// <=
    CMP_LESS,				// <

    CMP_COUNT,
};
//��������R�}���h�̂��߂̍\����
typedef struct tag_IFCOMMAND : public COMMAND {
    int					No;
    int					Op;
    int					Value;
    char				Name[256];

    /**
     * �R���X�g���N�^
     *
     */
    tag_IFCOMMAND() {
        Type = CMD_IF;
        No = 0;
        Op = 0;
        Value = 0;
        memset(Name, 0, 256);
    }
}IFCOMMAND;

class CScript {
private:
    char							m_FileName[MAX_PATH];
    char* m_FileBuffer;
    CDynamicArray< COMMAND* >		m_CommandList;
public:
    CScript();
    ~CScript();
    bool Load(const char* name);
    void ParseCommand(int sCmd);
    void TextCommand(void);
    void SpriteCommand(void);
    void SetShowCommand(void);
    void SetPosCommand(void);
    void NameCommand(int sCmd);
    void SelectCommand(void);
    void FlagCommand(void);
    void IfCommand(void);
    bool LoadTextFile(const char* name);
    void Release(void);
    CDynamicArray< COMMAND* >& GetCommand(void) { return m_CommandList; }
    COMMAND* GetCommand(int n) { return m_CommandList[n]; }
    int GetCommandCount(void) { return m_CommandList.GetArrayCount(); }
    char* GetFileName(void) { return m_FileName; }
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_H