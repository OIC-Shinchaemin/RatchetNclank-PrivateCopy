#include "TextSystem.h"


bool ratchet::game::gamesystem::text::TextSystem::Load(const char* name) {
    //�Z�[�u�t�@�C�����J��
    FILE* fp = fopen(name, "rb");
    if (fp == NULL) {
        return false;
    }
    //���݂̏������
    _script.Release();
    _sprite_list.Release();
    //���s���̃X�N���v�g�̕ύX
    char sname[MAX_PATH];
    fread(sname, 1, MAX_PATH, fp);
    if (!_script.Load(sname)) {
        return false;
    }
    //�R�}���h�ʒu��ǂݍ���
    fread(&m_CommandNo, sizeof(int), 1, fp);
    //�t���O��Ԃ�ǂݍ���
    fread(m_Flag, sizeof(int), _flag_count, fp);
    //�\���̏�Ԃ�ǂݍ���
    fread(&_text_command.px, sizeof(float), 1, fp);
    fread(&_text_command.py, sizeof(float), 1, fp);
    fread(_text_command.Text, 1, 256, fp);
    fread(_line_buffer, 1, 256, fp);
    int cnt;
    fread(&cnt, sizeof(int), 1, fp);
    for (int i = 0; i < cnt; i++) {
        char tname[MAX_PATH];
        fread(tname, 1, MAX_PATH, fp);
        CSprite2D* pAdd = new CSprite2D(tname);
        fread(tname, 1, MAX_PATH, fp);
        pAdd->SetName(tname);
        fread(&pAdd->m_Position.x, sizeof(float), 1, fp);
        fread(&pAdd->m_Position.y, sizeof(float), 1, fp);
        fread(&pAdd->m_bShow, sizeof(int), 1, fp);
        _sprite_list.Add(&pAdd);
    }
    //�t�@�C�������
    fclose(fp);
    //�E�F�C�g�����܂ł����s
    m_bWait = false;
    StepCommand();
    return true;
}

bool ratchet::game::gamesystem::text::TextSystem::Save(const char* name) {
    //�Z�[�u�t�@�C�����J��
    FILE* fp = fopen(name, "wb");
    if (fp == NULL) {
        return false;
    }
    //���s���̃X�N���v�g�̕ۑ�
    fwrite(_script.GetFileName(), 1, MAX_PATH, fp);
    //�R�}���h�ʒu��ۑ��A�ǂݍ��ݎ��ɍēx���݂̃R�}���h�����s���邽�߂Ɉ�O�ɖ߂�
    int cmd = m_CommandNo - 1;
    fwrite(&cmd, sizeof(int), 1, fp);
    //�t���O��Ԃ�ۑ�
    fwrite(m_Flag, sizeof(int), _flag_count, fp);
    //�\���̏�Ԃ�ۑ�
    fwrite(&_text_command.px, sizeof(float), 1, fp);
    fwrite(&_text_command.py, sizeof(float), 1, fp);
    fwrite(_text_command.Text, 1, 256, fp);
    fwrite(_line_buffer, 1, 256, fp);
    int cnt = _sprite_list.GetArrayCount();
    fwrite(&cnt, sizeof(int), 1, fp);
    for (int i = 0; i < cnt; i++) {
        char tname[MAX_PATH];
        strcpy(tname, _sprite_list[i]->GetTexture()->GetName()->GetString());
        fwrite(tname, 1, MAX_PATH, fp);
        strcpy(tname, _sprite_list[i]->GetName()->GetString());
        fwrite(tname, 1, MAX_PATH, fp);
        fwrite(&_sprite_list[i]->m_Position.x, sizeof(float), 1, fp);
        fwrite(&_sprite_list[i]->m_Position.y, sizeof(float), 1, fp);
        fwrite(&_sprite_list[i]->m_bShow, sizeof(int), 1, fp);
    }
    //�t�@�C�������
    fclose(fp);
    return true;
}

bool ratchet::game::gamesystem::text::TextSystem::LoadScript(const char* name) {
    //���݂̏������
    _script.Release();
    _sprite_list.Release();
    m_CommandNo = 0;
    m_bWait = false;
    //�X�N���v�g�̓ǂݍ���
    if (!_script.Load(name)) {
        return false;
    }
    //�E�F�C�g�����܂ł����s
    StepCommand();
    return true;
}

void ratchet::game::gamesystem::text::TextSystem::InitializeScript(void) {
    //m_bEnd = false;
    _alpha = 0;
}

void ratchet::game::gamesystem::text::TextSystem::UpdateAlpha(void) {
    //�I����ԂȂ�t�F�[�h�A�E�g
    if (false) {
        if (_alpha - ALPHA_SPEED <= 0) {
            _alpha = 0;
        }
        else {
            _alpha -= ALPHA_SPEED;
        }
    }
    else {
        if (_alpha + ALPHA_SPEED >= 255) {
            _alpha = 255;
        }
        else {
            _alpha += ALPHA_SPEED;
        }
    }

    //�X�v���C�g�̃A���t�@�l���V�[���̃A���t�@�l�Ɠ����ɂ���
    //�X�v���C�g�̃A���t�@�����o��0.0f �` 1.0f�ɂȂ邽��255�Ŋ������l��ݒ肷��B
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->m_Color.a = _alpha / 255.0f;
    }
}

bool ratchet::game::gamesystem::text::TextSystem::UpdateScript(void) {
    //�A���t�@�l�̍X�V
    UpdateAlpha();

    //�J�ڒ��͂���ȍ~�̏����͂��Ȃ�
    //if (m_bEnd || gScene != gChangeScene) 	{
        //return;
    //}

    //���j���[�̍X�V
    if (m_SaveMenu.IsShow()) {
    }
    //�X�N���v�g�ɂ��X�V
    else if (m_bWait) {
        //�R�}���h�̃^�C�v�ɂ���ĕ���
        switch (m_pNowCommand->Type) {
            case CMD_TEXT:
                TextCommand();
                break;
            case CMD_SELECT:
                SelectCommand();
                break;
        }
    }
    //�N���b�N�Ŏ��̃R�}���h������s���ĊJ
    else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
        StepCommand();
    }

    //�X�v���C�g�̃��X�g���X�V����
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->Update();
    } // for
    //F2�L�[�Ń^�C�g����ʂ�
    if (g_pInput->IsKeyPush(MOFKEY_F2)) {
        //m_bEnd = true;
        //gChangeScene = SCENENO_TITLE;
    }
    //F3�L�[�ŕۑ���ʂ�
    else if (g_pInput->IsKeyPush(MOFKEY_F3)) {
        //m_bEnd = true;
        //gChangeScene = SCENENO_SAVE;
        //gSaveScene.SetState(SCENENO_GAME, true);
    }


    if (_sprite_list.GetArrayCount() == 0) {
        this->_active = false;
        return false;
    } // if
}

void ratchet::game::gamesystem::text::TextSystem::StepCommand(void) {
    //���ׂẴR�}���h�����s���邩�ҋ@�����ɓ���܂Ń��[�v���s
    while (m_CommandNo < _script.GetCommandCount() && !m_bWait) {
        //���s�R�}���h���o��
        m_pNowCommand = _script.GetCommand(m_CommandNo);
        //�R�}���h�̃^�C�v�ɂ���ĕ���
        switch (m_pNowCommand->Type) {
            case CMD_TEXT:
                _text_command = *((TEXTCOMMAND*)m_pNowCommand);
                memset(_line_buffer, 0, TEXTBUFFERSIZE);
                m_StrWait = 0;
                m_bWait = true;
                break;
            case CMD_SPRITE:
                SpriteCommand((SPRITECOMMAND*)m_pNowCommand);
                break;
            case CMD_SETPOS:
                SetPosCommand((SETPOSCOMMAND*)m_pNowCommand);
                break;
            case CMD_SETSHOW:			//�X�v���C�g�̕\���ݒ�R�}���h
                SetShowCommand((SETSHOWCOMMAND*)m_pNowCommand);
                break;
            case CMD_JUMP:				//�W�����v�R�}���h
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)m_pNowCommand;
                JumpCommand(pNameCommand->Name);
                break;
            }
            case CMD_NEXT:				//�t�@�C���ύX�R�}���h
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)m_pNowCommand;
                //�V�����X�N���v�g���J���ƌÂ���񂪏����Ă��܂��̂ŕ���������o��
                char name[256];
                strcpy(name, pNameCommand->Name);
                //�X�N���v�g��ǂݍ���
                LoadScript(name);
                //�������I��������
                return;
            }
            case CMD_SELECT:
            {
                SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)m_pNowCommand;
                pSelCommand->Select.Show(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f);
                m_bWait = true;
                break;
            }
            case CMD_FLAG:				//�t���O����R�}���h
                FlagCommand((FLAGCOMMAND*)m_pNowCommand);
                break;
            case CMD_IF:				//����R�}���h
                IfCommand((IFCOMMAND*)m_pNowCommand);
                break;
            default:					//��`����Ă��Ȃ��R�}���h
                break;
        }
        //���̃R�}���h��
        m_CommandNo++;
    }
}

void ratchet::game::gamesystem::text::TextSystem::TextCommand(void) {
        //�\�����̃e�L�X�g�ƁA�\������e�L�X�g�̒������擾
    int nl = strlen(_line_buffer);
    int tl = strlen(_text_command.Text);
    //�܂��S���\������ĂȂ�
    if (nl < tl) {
        //�N���b�N�őS�����ꊇ�\��
        if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
            m_bWait = false;
            strcpy(_line_buffer, _text_command.Text);
        } // if
        else {
            //��莞�Ԃ��ƂɈꕶ��������Ă���
            m_StrWait++;
            if (m_StrWait >= 10) {
                m_StrWait = 0;
                //�S�p�����̔�����s��
                if (IsDBCSLeadByte(_text_command.Text[nl])) {
                    //�S�p�����̏ꍇ�Q�o�C�g���ňꕶ���ɂȂ�
                    _line_buffer[nl] = _text_command.Text[nl];
                    nl++;
                    _line_buffer[nl] = _text_command.Text[nl];
                    nl++;
                    _line_buffer[nl] = '\0';
                } // if
                else {
                    _line_buffer[nl] = _text_command.Text[nl];
                    nl++;
                    _line_buffer[nl] = '\0';
                }
                //�S���̕\�����I��
                if (nl >= tl) {
                    m_bWait = false;
                } // if
            }
        }
    }
}

void ratchet::game::gamesystem::text::TextSystem::SpriteCommand(SPRITECOMMAND* pSpriteCommand) {
    LPSprite2D* pSprite = _sprite_list.Find(pSpriteCommand->Name);
    //�X�v���C�g���Ȃ��ꍇ�͐V�K�쐬���ă��X�g�ɓo�^
    if (!pSprite) {
        CSprite2D* pAdd = new CSprite2D(pSpriteCommand->FName);
        pAdd->SetName(pSpriteCommand->Name);
        _sprite_list.Add(&pAdd);
    } // if
    //�X�v���C�g������ꍇ�Â�����j�����ĐV�����e�N�X�`���t�@�C���ɍ����ւ�
    else {
        (*pSprite)->Release();
        (*pSprite)->CreateSprite(pSpriteCommand->FName);
        (*pSprite)->SetName(pSpriteCommand->Name);
    }
}

void ratchet::game::gamesystem::text::TextSystem::SetPosCommand(SETPOSCOMMAND* pSpriteCommand) {
    LPSprite2D* pSprite = _sprite_list.Find(pSpriteCommand->Name);
    if (!pSprite) {
        return;
    } // if
    (*pSprite)->m_Position.x = pSpriteCommand->px;
    (*pSprite)->m_Position.y = pSpriteCommand->py;

}

void ratchet::game::gamesystem::text::TextSystem::SetShowCommand(SETSHOWCOMMAND* pSpriteCommand) {
    LPSprite2D* pSprite = _sprite_list.Find(pSpriteCommand->Name);
    if (!pSprite) {
        return;
    } // if
    (*pSprite)->m_bShow = pSpriteCommand->bShow;
}

bool ratchet::game::gamesystem::text::TextSystem::JumpCommand(const char* label) {
    //���ׂẴR�}���h�����s���邩�ҋ@�����ɓ���܂Ń��[�v���s
    int cmd = 0;
    while (cmd < _script.GetCommandCount()) {
        //���s�R�}���h���o��
        COMMAND* pCommand = _script.GetCommand(cmd);
        if (pCommand->Type == CMD_LABEL) {
            NAMECOMMAND* pNameCommand = (NAMECOMMAND*)pCommand;
            if (stricmp(pNameCommand->Name, label) == 0) {
                m_pNowCommand = pCommand;
                m_CommandNo = cmd;
                return true;
            } // if
        } // if
        //���̃R�}���h��
        cmd++;
    }
    return false;
}

void ratchet::game::gamesystem::text::TextSystem::SelectCommand(void) {
    //�R�}���h���o��
    SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)m_pNowCommand;
    //���j���[�̍X�V
    if (pSelCommand->Select.IsShow()) {
        pSelCommand->Select.Update();
        if (pSelCommand->Select.IsEnter()) {
            pSelCommand->Select.Hide();
            m_bWait = false;
            JumpCommand(pSelCommand->pLabel[pSelCommand->Select.GetSelect()]);
            StepCommand();
        } // if
    } // if
}

void ratchet::game::gamesystem::text::TextSystem::FlagCommand(FLAGCOMMAND* pFlagCommand) {
    if (pFlagCommand->No >= _flag_count) {
        return;
    } // if
    switch (pFlagCommand->Op) {
        case OP_PLUS:		m_Flag[pFlagCommand->No] += pFlagCommand->Value;		break;
        case OP_MINUS:		m_Flag[pFlagCommand->No] -= pFlagCommand->Value;		break;
        case OP_MULTIPLY:	m_Flag[pFlagCommand->No] *= pFlagCommand->Value;		break;
        case OP_DIVISION:	m_Flag[pFlagCommand->No] /= pFlagCommand->Value;		break;
        case OP_EQUAL:		m_Flag[pFlagCommand->No] = pFlagCommand->Value;			break;
    }
}

void ratchet::game::gamesystem::text::TextSystem::IfCommand(IFCOMMAND* pIfCommand) {
    if (pIfCommand->No >= _flag_count) {
        return;
    } // if
    switch (pIfCommand->Op) {
        case CMP_GRATER:			// >
            if (m_Flag[pIfCommand->No] > pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_GRATEREQUAL:		// >=
            if (m_Flag[pIfCommand->No] >= pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_EQUAL:				// =
            if (m_Flag[pIfCommand->No] == pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_NOTEQUAL:			// !
            if (m_Flag[pIfCommand->No] != pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_LESSEQUAL:			// <=
            if (m_Flag[pIfCommand->No] <= pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_LESS:				// <
            if (m_Flag[pIfCommand->No] < pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
    }
}

ratchet::game::gamesystem::text::TextSystem::TextSystem() :
    _active(false) {
    ::memset(_line_buffer, 0, TEXTBUFFERSIZE);
}

ratchet::game::gamesystem::text::TextSystem::~TextSystem() {
}

bool ratchet::game::gamesystem::text::TextSystem::IsActive(void) const {
    return this->_active;
}

bool ratchet::game::gamesystem::text::TextSystem::Activate(void) {
    _active = true;
    return true;
}

bool ratchet::game::gamesystem::text::TextSystem::Load(void) {
        //�t���O�̏�����
    ::memset(m_Flag, 0, sizeof(int) * _flag_count);
    //�X�N���v�g��ǂݍ���
    if (!this->LoadScript("script/test.txt")) {
        return false;
    } // if
    //�e�L�X�g�\���p�̃E�C���h�E��ǂݍ���
    if (!_text_window_texture.Load("TexWin.png")) {
        //return false;
    } // if
    return false;
}

bool ratchet::game::gamesystem::text::TextSystem::Update(void) {
    return this->UpdateScript();
}

bool ratchet::game::gamesystem::text::TextSystem::Render(void) {
    //�X�v���C�g�̃��X�g��`�悷��
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->Render();
    } // if
    //���j���[�̏ꍇ�͑I��`��
    if (m_pNowCommand->Type == CMD_SELECT) {
        //�R�}���h���o��
        SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)m_pNowCommand;
        //�I��`��
        pSelCommand->Select.Render();
    } // if

    //�\���e�L�X�g�̉��ɘg��\������
    _text_window_texture.Render(16, 568);
    //�\���e�L�X�g��`�悷��
    ::CGraphicsUtilities::RenderString(_text_command.px, _text_command.py, MOF_ARGB(_alpha, 255, 255, 255), _line_buffer);

    // debug 
    ::CGraphicsUtilities::RenderString(10, 10, MOF_ARGB(_alpha, 255, 0, 0), "�R�}���h���s�ʒu [%d]", m_CommandNo);
    return false;
}

bool ratchet::game::gamesystem::text::TextSystem::Release(void) {
    _text_window_texture.Release();
    _script.Release();
    _sprite_list.Release();
    return true;
}