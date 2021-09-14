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
    fread(&_command_no, sizeof(int), 1, fp);
    //�t���O��Ԃ�ǂݍ���
    fread(_flags, sizeof(int), _flag_count, fp);
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
    _wait = false;
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
    int cmd = _command_no - 1;
    fwrite(&cmd, sizeof(int), 1, fp);
    //�t���O��Ԃ�ۑ�
    fwrite(_flags, sizeof(int), _flag_count, fp);
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
    _command_no = 0;
    _wait = false;
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
    else if (_wait) {
        //�R�}���h�̃^�C�v�ɂ���ĕ���
        switch (_now_command->Type) {
            case CMD_TEXT:
                TextCommand();
                break;
            case CMD_SELECT:
                SelectCommand();
                break;
        }
    }
    //�N���b�N�Ŏ��̃R�}���h������s���ĊJ
    //else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
    else if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
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
        auto message = TextSystemClosedMessage();
        message.close = true;
        _text_system_closed_message_subject.Notify(message);
        return false;
    } // if

    return true;
}

void ratchet::game::gamesystem::text::TextSystem::StepCommand(void) {
    //���ׂẴR�}���h�����s���邩�ҋ@�����ɓ���܂Ń��[�v���s
    while (_command_no < _script.GetCommandCount() && !_wait) {
        //���s�R�}���h���o��
        _now_command = _script.GetCommand(_command_no);
        //�R�}���h�̃^�C�v�ɂ���ĕ���
        switch (_now_command->Type) {
            case CMD_TEXT:
                _text_command = *((TEXTCOMMAND*)_now_command);
                memset(_line_buffer, 0, TEXTBUFFERSIZE);
                _str_wait = 0;
                _wait = true;
                break;
            case CMD_SPRITE:
                SpriteCommand((SPRITECOMMAND*)_now_command);
                break;
            case CMD_SETPOS:
                SetPosCommand((SETPOSCOMMAND*)_now_command);
                break;
            case CMD_SETSHOW:			//�X�v���C�g�̕\���ݒ�R�}���h
                SetShowCommand((SETSHOWCOMMAND*)_now_command);
                break;
            case CMD_JUMP:				//�W�����v�R�}���h
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)_now_command;
                JumpCommand(pNameCommand->Name);
                break;
            }
            case CMD_NEXT:				//�t�@�C���ύX�R�}���h
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)_now_command;
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
                SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)_now_command;
                pSelCommand->Select.Show(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f);
                _wait = true;
                break;
            }
            case CMD_FLAG:				//�t���O����R�}���h
                FlagCommand((FLAGCOMMAND*)_now_command);
                break;
            case CMD_IF:				//����R�}���h
                IfCommand((IFCOMMAND*)_now_command);
                break;
            default:					//��`����Ă��Ȃ��R�}���h
                break;
        }
        //���̃R�}���h��
        _command_no++;
    }
}

void ratchet::game::gamesystem::text::TextSystem::TextCommand(void) {
        //�\�����̃e�L�X�g�ƁA�\������e�L�X�g�̒������擾
    int nl = strlen(_line_buffer);
    int tl = strlen(_text_command.Text);
    //�܂��S���\������ĂȂ�
    if (nl < tl) {
        //�N���b�N�őS�����ꊇ�\��
        //if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
        if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
            _wait = false;
            strcpy(_line_buffer, _text_command.Text);
        } // if
        else {
            //��莞�Ԃ��ƂɈꕶ��������Ă���
            _str_wait++;
            if (_str_wait >= 10) {
                _str_wait = 0;
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
                    _wait = false;
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
                _now_command = pCommand;
                _command_no = cmd;
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
    SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)_now_command;
    //���j���[�̍X�V
    if (pSelCommand->Select.IsShow()) {
        pSelCommand->Select.Update();
        if (pSelCommand->Select.IsEnter()) {
            pSelCommand->Select.Hide();
            _wait = false;
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
        case OP_PLUS:		_flags[pFlagCommand->No] += pFlagCommand->Value;		break;
        case OP_MINUS:		_flags[pFlagCommand->No] -= pFlagCommand->Value;		break;
        case OP_MULTIPLY:	_flags[pFlagCommand->No] *= pFlagCommand->Value;		break;
        case OP_DIVISION:	_flags[pFlagCommand->No] /= pFlagCommand->Value;		break;
        case OP_EQUAL:		_flags[pFlagCommand->No] = pFlagCommand->Value;			break;
    }
}

void ratchet::game::gamesystem::text::TextSystem::IfCommand(IFCOMMAND* pIfCommand) {
    if (pIfCommand->No >= _flag_count) {
        return;
    } // if
    switch (pIfCommand->Op) {
        case CMP_GRATER:			// >
            if (_flags[pIfCommand->No] > pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_GRATEREQUAL:		// >=
            if (_flags[pIfCommand->No] >= pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_EQUAL:				// =
            if (_flags[pIfCommand->No] == pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_NOTEQUAL:			// !
            if (_flags[pIfCommand->No] != pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_LESSEQUAL:			// <=
            if (_flags[pIfCommand->No] <= pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
        case CMP_LESS:				// <
            if (_flags[pIfCommand->No] < pIfCommand->Value) {
                JumpCommand(pIfCommand->Name);
            } // if
            break;
    }
}

ratchet::game::gamesystem::text::TextSystem::TextSystem() :
    _active(false),
    _text_system_closed_message_subject(){
    ::memset(_line_buffer, 0, TEXTBUFFERSIZE);

    _path_map.emplace(TextEventType::EventNo0, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo1, "script/test2.txt");
    _path_map.emplace(TextEventType::EventNo2, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo3, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo4, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo5, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo6, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo7, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo8, "script/test.txt");
    _path_map.emplace(TextEventType::EventNo9, "script/test.txt");
}

ratchet::game::gamesystem::text::TextSystem::~TextSystem() {
}

void ratchet::game::gamesystem::text::TextSystem::OnNotify(const TextSystemMessage& message) {
    //�t���O�̏�����
    ::memset(_flags, 0, sizeof(int) * _flag_count);
    //�X�N���v�g��ǂݍ���
    //if (!this->LoadScript("script/test.txt")) {
    
    auto path = _path_map.at(message.type);
    if (!this->LoadScript(path.c_str())) {
        return;
    } // if
    this->Activate();
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
    ::memset(_flags, 0, sizeof(int) * _flag_count);
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
    if (_now_command->Type == CMD_SELECT) {
        //�R�}���h���o��
        SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)_now_command;
        //�I��`��
        pSelCommand->Select.Render();
    } // if

    //�\���e�L�X�g�̉��ɘg��\������
    _text_window_texture.Render(16, 568);
    //�\���e�L�X�g��`�悷��
    ::CGraphicsUtilities::RenderString(_text_command.px, _text_command.py, MOF_ARGB(_alpha, 255, 255, 255), _line_buffer);

    // debug 
    ::CGraphicsUtilities::RenderString(10, 10, MOF_ARGB(_alpha, 255, 0, 0), "�R�}���h���s�ʒu [%d]", _command_no);
    return false;
}

bool ratchet::game::gamesystem::text::TextSystem::Release(void) {
    _text_window_texture.Release();
    _script.Release();
    _sprite_list.Release();
    return true;
}