#include "TextSystem.h"

#include "../../../DebugManager.h"
#include "../../../Component/Player/PlayerStateComponent.h"
#include "../../../State/PlayerActionStateDefine.h"


bool ratchet::game::gamesystem::text::TextSystem::Load(const char* name) {
    //セーブファイルを開く
    std::FILE* fp = std::fopen(name, "rb");
    if (fp == NULL) {
        return false;
    }
    //現在の情報を解放
    _script.Release();
    _sprite_list.Release();
    //実行中のスクリプトの変更
    char sname[MAX_PATH];
    std::fread(sname, 1, MAX_PATH, fp);
    if (!_script.Load(sname)) {
        return false;
    } // if
    //コマンド位置を読み込み
    std::fread(&_command_no, sizeof(int), 1, fp);
    //フラグ状態を読み込み
    std::fread(_flags, sizeof(int), _flag_count, fp);
    //表示の状態を読み込み
    std::fread(&_text_command.px, sizeof(float), 1, fp);
    std::fread(&_text_command.py, sizeof(float), 1, fp);
    std::fread(_text_command.Text, 1, 256, fp);
    std::fread(_line_buffer, 1, 256, fp);
    int cnt;
    std::fread(&cnt, sizeof(int), 1, fp);
    for (int i = 0; i < cnt; i++) {
        char tname[MAX_PATH];
        std::fread(tname, 1, MAX_PATH, fp);
        CSprite2D* pAdd = new CSprite2D(tname);
        std::fread(tname, 1, MAX_PATH, fp);
        pAdd->SetName(tname);
        std::fread(&pAdd->m_Position.x, sizeof(float), 1, fp);
        std::fread(&pAdd->m_Position.y, sizeof(float), 1, fp);
        std::fread(&pAdd->m_bShow, sizeof(int), 1, fp);
        _sprite_list.Add(&pAdd);
    }
    //ファイルを閉じる
    std::fclose(fp);
    //ウェイト処理までを実行
    _wait = false;
    this->StepCommand();
    return true;
}
/*
bool ratchet::game::gamesystem::text::TextSystem::Save(const char* name) {
    //セーブファイルを開く
    std::FILE* fp = std::fopen(name, "wb");
    if (fp == NULL) {
        return false;
    }
    //実行中のスクリプトの保存
    std::fwrite(_script.GetFileName(), 1, MAX_PATH, fp);
    //コマンド位置を保存、読み込み時に再度現在のコマンドを実行するために一つ前に戻す
    int cmd = _command_no - 1;
    std::fwrite(&cmd, sizeof(int), 1, fp);
    //フラグ状態を保存
    std::fwrite(_flags, sizeof(int), _flag_count, fp);
    //表示の状態を保存
    std::fwrite(&_text_command.px, sizeof(float), 1, fp);
    std::fwrite(&_text_command.py, sizeof(float), 1, fp);
    std::fwrite(_text_command.Text, 1, 256, fp);
    std::fwrite(_line_buffer, 1, 256, fp);
    int cnt = _sprite_list.GetArrayCount();
    std::fwrite(&cnt, sizeof(int), 1, fp);
    for (int i = 0; i < cnt; i++) {
        char tname[MAX_PATH];
        std::strcpy(tname, _sprite_list[i]->GetTexture()->GetName()->GetString());
        std::fwrite(tname, 1, MAX_PATH, fp);
        std::strcpy(tname, _sprite_list[i]->GetName()->GetString());
        std::fwrite(tname, 1, MAX_PATH, fp);
        std::fwrite(&_sprite_list[i]->m_Position.x, sizeof(float), 1, fp);
        std::fwrite(&_sprite_list[i]->m_Position.y, sizeof(float), 1, fp);
        std::fwrite(&_sprite_list[i]->m_bShow, sizeof(int), 1, fp);
    } // for
    //ファイルを閉じる
    std::fclose(fp);
    return true;
}
*/
bool ratchet::game::gamesystem::text::TextSystem::LoadScript(const char* name) {
    //現在の情報を解放
    _script.Release();
    _sprite_list.Release();
    _command_no = 0;
    _wait = false;
    //スクリプトの読み込み
    if (!_script.Load(name)) {
        return false;
    }
    //ウェイト処理までを実行
    this->StepCommand();
    return true;
}

void ratchet::game::gamesystem::text::TextSystem::InitializeScript(void) {
    _alpha = 0;
}

void ratchet::game::gamesystem::text::TextSystem::UpdateAlpha(void) {
    //終了状態ならフェードアウト
    if (false) {
        if (_alpha - ALPHA_SPEED <= 0) {
            _alpha = 0;
        } // if
        else {
            _alpha -= ALPHA_SPEED;
        } // else
    } // if
    else {
        if (_alpha + ALPHA_SPEED >= 255) {
            _alpha = 255;
        } // if
        else {
            _alpha += ALPHA_SPEED;
        } // else
    } // else

    // スプライトのアルファ値をシーンのアルファ値と同じにする
    // スプライトのアルファメンバは0.0f ～ 1.0fになるため255で割った値を設定する。
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->m_Color.a = _alpha / 255.0f;
    } // for
}

bool ratchet::game::gamesystem::text::TextSystem::UpdateScript(void) {
    //アルファ値の更新
    this->UpdateAlpha();

    //メニューの更新
    //if (m_SaveMenu.IsShow()) {
    if (false) {
    }
    //スクリプトによる更新
    else if (_wait) {
        //コマンドのタイプによって分岐
        switch (_now_command->Type) {
            case CMD_TEXT:
                TextCommand();
                break;
            case CMD_SELECT:
                SelectCommand();
                break;
        } // switch
    } // else if
    //クリックで次のコマンドから実行を再開
    else if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        StepCommand();
    } // else if

    //スプライトのリストを更新する
    for (int i = 0; i < _sprite_list.GetArrayCount(); i++) {
        _sprite_list[i]->Update();
    } // for
    if (_sprite_list.GetArrayCount() == 0) {
        this->_active = false;
        auto message = TextSystemClosedMessage();
        message.close = true;
        if (_on_close.has_value()) {
            _on_close.value()();
        } // if
        _text_system_closed_message_subject.Notify(message);
        return false;
    } // if
    return true;
}

void ratchet::game::gamesystem::text::TextSystem::StepCommand(void) {
    // すべてのコマンドを実行するか待機処理に入るまでループ実行
    while (_command_no < _script.GetCommandCount() && !_wait) {
        _now_command = _script.GetCommand(_command_no);
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
            case CMD_SETSHOW:
                SetShowCommand((SETSHOWCOMMAND*)_now_command);
                break;
            case CMD_JUMP:
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)_now_command;
                JumpCommand(pNameCommand->Name);
                break;
            }
            case CMD_NEXT:
            {
                NAMECOMMAND* pNameCommand = (NAMECOMMAND*)_now_command;
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
                SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)_now_command;
                pSelCommand->Select.Show(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f);
                _wait = true;
                break;
            }
            case CMD_FLAG:
                FlagCommand((FLAGCOMMAND*)_now_command);
                break;
            case CMD_IF:
                IfCommand((IFCOMMAND*)_now_command);
                break;
            default:
                break;
        }
        _command_no++;
    }
}

void ratchet::game::gamesystem::text::TextSystem::TextCommand(void) {
    //表示中のテキストと、表示するテキストの長さを取得
    int nl = std::strlen(_line_buffer);
    int tl = std::strlen(_text_command.Text);
    //まだ全部表示されてない
    if (nl < tl) {
        //クリックで全文を一括表示
        if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
            _wait = false;
            std::strcpy(_line_buffer, _text_command.Text);
        } // if
        else {
            //一定時間ごとに一文字ずつ入れていく
            _str_wait++;
            if (_str_wait >= _wait_count_max) {
                _str_wait = 0;
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
                    _wait = false;
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
                _now_command = pCommand;
                _command_no = cmd;
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
    SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)_now_command;
    //メニューの更新
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
    _text_system_closed_message_subject() {
    ::memset(_line_buffer, 0, TEXTBUFFERSIZE);

    _path_map.emplace(TextEventType::TutorialEventNo0, "script/tutorial_event_0_start.txt");
    _path_map.emplace(TextEventType::TutorialEventNo1, "script/tutorial_event_2_start.txt");
    _path_map.emplace(TextEventType::TutorialEventNo0End, "script/tutorial_event_0_end.txt");
    _path_map.emplace(TextEventType::TutorialEventNo1End, "script/tutorial_event_2_end.txt");
    _path_map.emplace(TextEventType::KingTextEvent, "script/king_text_event.txt");
    _path_map.emplace(TextEventType::KingFreeTalkTextEvent, "script/king_free_talk_text_event.txt");
    _path_map.emplace(TextEventType::ItemCollectionCompleteEvent, "script/item_collection_complete_event.txt");
    _path_map.emplace(TextEventType::TeachPlazaEvent, "script/teach_plaza_event.txt");
    _path_map.emplace(TextEventType::QueenTextEvent, "script/queen_text_event.txt");
    _path_map.emplace(TextEventType::QueenFreeTalkTextEvent, "script/queen_free_talk_text_event.txt");
}

ratchet::game::gamesystem::text::TextSystem::~TextSystem() {
}

void ratchet::game::gamesystem::text::TextSystem::OnNotify(const TextSystemMessage& message) {
    if (auto player = _player.lock()) {
        player->Sleep();
        //auto state = player->GetComponent<component::ActionStateComponent>();
        //state->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if



    //フラグの初期化
    ::memset(_flags, 0, sizeof(int) * _flag_count);
    //スクリプトを読み込む
    auto path = _path_map.at(message.type);
    if (!this->LoadScript(path.c_str())) {
        return;
    } // if
    this->Activate();
    _on_close = message.on_close;
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
    ::memset(_flags, 0, sizeof(int) * _flag_count);
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
    if (_now_command->Type == CMD_SELECT) {
        //コマンド取り出し
        SELECTCOMMAND* pSelCommand = (SELECTCOMMAND*)_now_command;
        //選択描画
        pSelCommand->Select.Render();
    } // if

    //表示テキストの下に枠を表示する
    _text_window_texture.Render(16, 568);
    //表示テキストを描画する
    ::CGraphicsUtilities::RenderString(_text_command.px, _text_command.py, MOF_ARGB(_alpha, 255, 255, 255), _line_buffer);


    // debug 
    if (debug::DebugManager::GetInstance().IsDebugMode()) {
        ::CGraphicsUtilities::RenderString(10, 10, MOF_ARGB(_alpha, 255, 0, 0), "コマンド実行位置 [%d]", _command_no);
    } // if

    return false;
}

bool ratchet::game::gamesystem::text::TextSystem::Release(void) {
    _text_window_texture.Release();
    _script.Release();
    _sprite_list.Release();
    return true;
}