#include "TextSystem.h"


bool ratchet::game::gamesystem::text::TextSystem::Load(const char* name) {
    //セーブファイルを開く
    FILE* fp = fopen(name, "rb");
    if (fp == NULL) {
        return false;
    }
    //現在の情報を解放
    _script.Release();
    _sprite_list.Release();
    //実行中のスクリプトの変更
    char sname[MAX_PATH];
    fread(sname, 1, MAX_PATH, fp);
    if (!_script.Load(sname)) {
        return false;
    }
    //コマンド位置を読み込み
    fread(&m_CommandNo, sizeof(int), 1, fp);
    //フラグ状態を読み込み
    fread(m_Flag, sizeof(int), _flag_count, fp);
    //表示の状態を読み込み
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
    //ファイルを閉じる
    fclose(fp);
    //ウェイト処理までを実行
    m_bWait = false;
    StepCommand();
    return true;
}

bool ratchet::game::gamesystem::text::TextSystem::Save(const char* name) {
    //セーブファイルを開く
    FILE* fp = fopen(name, "wb");
    if (fp == NULL) {
        return false;
    }
    //実行中のスクリプトの保存
    fwrite(_script.GetFileName(), 1, MAX_PATH, fp);
    //コマンド位置を保存、読み込み時に再度現在のコマンドを実行するために一つ前に戻す
    int cmd = m_CommandNo - 1;
    fwrite(&cmd, sizeof(int), 1, fp);
    //フラグ状態を保存
    fwrite(m_Flag, sizeof(int), _flag_count, fp);
    //表示の状態を保存
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
    //ファイルを閉じる
    fclose(fp);
    return true;
}

bool ratchet::game::gamesystem::text::TextSystem::LoadScript(const char* name) {
    //現在の情報を解放
    _script.Release();
    _sprite_list.Release();
    m_CommandNo = 0;
    m_bWait = false;
    //スクリプトの読み込み
    if (!_script.Load(name)) {
        return false;
    }
    //ウェイト処理までを実行
    StepCommand();
    return true;
}

void ratchet::game::gamesystem::text::TextSystem::InitializeScript(void) {
    //m_bEnd = false;
    _alpha = 0;
}

void ratchet::game::gamesystem::text::TextSystem::UpdateAlpha(void) {
    //終了状態ならフェードアウト
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

    //スプライトのアルファ値をシーンのアルファ値と同じにする
    //スプライトのアルファメンバは0.0f ～ 1.0fになるため255で割った値を設定する。
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->m_Color.a = _alpha / 255.0f;
    }
}

bool ratchet::game::gamesystem::text::TextSystem::UpdateScript(void) {
    //アルファ値の更新
    UpdateAlpha();

    //遷移中はこれ以降の処理はしない
    //if (m_bEnd || gScene != gChangeScene) 	{
        //return;
    //}

    //メニューの更新
    if (m_SaveMenu.IsShow()) {
    }
    //スクリプトによる更新
    else if (m_bWait) {
        //コマンドのタイプによって分岐
        switch (m_pNowCommand->Type) {
            case CMD_TEXT:
                TextCommand();
                break;
            case CMD_SELECT:
                SelectCommand();
                break;
        }
    }
    //クリックで次のコマンドから実行を再開
    else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
        StepCommand();
    }

    //スプライトのリストを更新する
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->Update();
    } // for
    //F2キーでタイトル画面へ
    if (g_pInput->IsKeyPush(MOFKEY_F2)) {
        //m_bEnd = true;
        //gChangeScene = SCENENO_TITLE;
    }
    //F3キーで保存画面へ
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
    //すべてのコマンドを実行するか待機処理に入るまでループ実行
    while (m_CommandNo < _script.GetCommandCount() && !m_bWait) {
        //実行コマンド取り出し
        m_pNowCommand = _script.GetCommand(m_CommandNo);
        //コマンドのタイプによって分岐
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
            case CMD_SETSHOW:			//スプライトの表示設定コマンド
                SetShowCommand((SETSHOWCOMMAND*)m_pNowCommand);
                break;
            case CMD_JUMP:				//ジャンプコマンド
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)m_pNowCommand;
                JumpCommand(pNameCommand->Name);
                break;
            }
            case CMD_NEXT:				//ファイル変更コマンド
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)m_pNowCommand;
                //新しいスクリプトを開くと古い情報が消えてしまうので文字列を取り出す
                char name[256];
                strcpy(name, pNameCommand->Name);
                //スクリプトを読み込む
                LoadScript(name);
                //処理を終了させる
                return;
            }
            case CMD_SELECT:
            {
                SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)m_pNowCommand;
                pSelCommand->Select.Show(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f);
                m_bWait = true;
                break;
            }
            case CMD_FLAG:				//フラグ操作コマンド
                FlagCommand((FLAGCOMMAND*)m_pNowCommand);
                break;
            case CMD_IF:				//分岐コマンド
                IfCommand((IFCOMMAND*)m_pNowCommand);
                break;
            default:					//定義されていないコマンド
                break;
        }
        //次のコマンドへ
        m_CommandNo++;
    }
}

void ratchet::game::gamesystem::text::TextSystem::TextCommand(void) {
        //表示中のテキストと、表示するテキストの長さを取得
    int nl = strlen(_line_buffer);
    int tl = strlen(_text_command.Text);
    //まだ全部表示されてない
    if (nl < tl) {
        //クリックで全文を一括表示
        if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
            m_bWait = false;
            strcpy(_line_buffer, _text_command.Text);
        } // if
        else {
            //一定時間ごとに一文字ずつ入れていく
            m_StrWait++;
            if (m_StrWait >= 10) {
                m_StrWait = 0;
                //全角文字の判定を行う
                if (IsDBCSLeadByte(_text_command.Text[nl])) {
                    //全角文字の場合２バイト分で一文字になる
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
                //全文の表示が終了
                if (nl >= tl) {
                    m_bWait = false;
                } // if
            }
        }
    }
}

void ratchet::game::gamesystem::text::TextSystem::SpriteCommand(SPRITECOMMAND* pSpriteCommand) {
    LPSprite2D* pSprite = _sprite_list.Find(pSpriteCommand->Name);
    //スプライトがない場合は新規作成してリストに登録
    if (!pSprite) {
        CSprite2D* pAdd = new CSprite2D(pSpriteCommand->FName);
        pAdd->SetName(pSpriteCommand->Name);
        _sprite_list.Add(&pAdd);
    } // if
    //スプライトがある場合古い情報を破棄して新しいテクスチャファイルに差し替え
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
    //すべてのコマンドを実行するか待機処理に入るまでループ実行
    int cmd = 0;
    while (cmd < _script.GetCommandCount()) {
        //実行コマンド取り出し
        COMMAND* pCommand = _script.GetCommand(cmd);
        if (pCommand->Type == CMD_LABEL) {
            NAMECOMMAND* pNameCommand = (NAMECOMMAND*)pCommand;
            if (stricmp(pNameCommand->Name, label) == 0) {
                m_pNowCommand = pCommand;
                m_CommandNo = cmd;
                return true;
            } // if
        } // if
        //次のコマンドへ
        cmd++;
    }
    return false;
}

void ratchet::game::gamesystem::text::TextSystem::SelectCommand(void) {
    //コマンド取り出し
    SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)m_pNowCommand;
    //メニューの更新
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
        //フラグの初期化
    ::memset(m_Flag, 0, sizeof(int) * _flag_count);
    //スクリプトを読み込む
    if (!this->LoadScript("script/test.txt")) {
        return false;
    } // if
    //テキスト表示用のウインドウを読み込む
    if (!_text_window_texture.Load("TexWin.png")) {
        //return false;
    } // if
    return false;
}

bool ratchet::game::gamesystem::text::TextSystem::Update(void) {
    return this->UpdateScript();
}

bool ratchet::game::gamesystem::text::TextSystem::Render(void) {
    //スプライトのリストを描画する
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->Render();
    } // if
    //メニューの場合は選択描画
    if (m_pNowCommand->Type == CMD_SELECT) {
        //コマンド取り出し
        SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)m_pNowCommand;
        //選択描画
        pSelCommand->Select.Render();
    } // if

    //表示テキストの下に枠を表示する
    _text_window_texture.Render(16, 568);
    //表示テキストを描画する
    ::CGraphicsUtilities::RenderString(_text_command.px, _text_command.py, MOF_ARGB(_alpha, 255, 255, 255), _line_buffer);

    // debug 
    ::CGraphicsUtilities::RenderString(10, 10, MOF_ARGB(_alpha, 255, 0, 0), "コマンド実行位置 [%d]", m_CommandNo);
    return false;
}

bool ratchet::game::gamesystem::text::TextSystem::Release(void) {
    _text_window_texture.Release();
    _script.Release();
    _sprite_list.Release();
    return true;
}