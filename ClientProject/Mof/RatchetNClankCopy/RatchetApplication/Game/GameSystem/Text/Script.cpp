#include "Script.h"

//コマンド解析文字列定義
const char* gScriptCommand[] = {
    "text",
    "sprite",
    "setpos",
    "setshow",
    "label",
    "jump",
    "next",
    "select",
    "flag",
    "if",

    "",
};

//演算子解析文字列定義
const char* gScriptOp[] = {
    "+",
    "-",
    "*",
    "/",
    "=",

    "",
};

//演算子解析文字列定義
const char* gScriptCmp[] = {
    ">",
    ">=",
    "=",
    "!",
    "<=",
    "<",

    "",
};

char* Trim(char* s) {
    // 引数の文字列がない
    if (!s) {
        return NULL;
    }
    // 文字列の後ろから空白以外を見つけた次の位置に\0（終端）を設定する
    int length = std::strlen(s);
    while (--length >= 0) {
        if (s[length] != '\t' && s[length] != '\r' && 
            s[length] != '\n' && s[length] != ' ') {
            break;
        }
    }
    s[length + 1] = '\0';
    // 先頭から空白以外を見つけた位置のポインタを返す
    int p = 0;
    while (p < length) {
        if (s[p] != '\t' && s[p] != '\r' && s[p] != '\n' && s[p] != ' ') {
            return &s[p];
        }
        p++;
    }
    return s;
}

ratchet::game::gamesystem::text::Script::Script() :
    m_FileBuffer(NULL),
    m_CommandList() {
    memset(m_FileName, 0, MAX_PATH);
}

ratchet::game::gamesystem::text::Script::~Script() {
}

bool ratchet::game::gamesystem::text::Script::Load(const char* name) {
    //テキストファイルを開く
    if (!LoadTextFile(name)) {
        return false;
    } // if

    //スクリプトの解析を行う
    char* fb = m_FileBuffer;
    while (TRUE) {
        //指定の行の最初の，までがコマンドの指定
        char* cmd = strtok(fb, ",");
        fb = NULL;
        if (!cmd) {
            break;
        } // if
        //コマンドの前後に空白などがあるなら除去をする
        cmd = Trim(cmd);
        
        //コマンドの識別
        int sCmd = 0;
        for (sCmd = 0; 
             sCmd < CMD_COUNT && stricmp(cmd, gScriptCommand[sCmd]) != 0; 
             sCmd++);
        //コマンドの解析
        this->ParseCommand(sCmd);
    } // while
    return true;
}

void ratchet::game::gamesystem::text::Script::ParseCommand(int sCmd) {
    //コマンドに必要なパラメータの解析
    switch (sCmd) {
        case CMD_TEXT:				//テキストの表示コマンド
            TextCommand();
            break;
        case CMD_SPRITE:			//スプライトの作成コマンド
            SpriteCommand();
            break;
        case CMD_SETPOS:			//スプライトの座標設定コマンド
            SetPosCommand();
            break;
        case CMD_SETSHOW:			//スプライトの表示設定コマンド
            SetShowCommand();
            break;
        //同一の引数のためコマンド解析を共通化
        case CMD_LABEL:				//ラベル設定コマンド
        case CMD_JUMP:				//ジャンプコマンド
        case CMD_NEXT:				//ファイル変更コマンド
            NameCommand(sCmd);
            break;
        case CMD_SELECT:			//選択肢コマンド
            SelectCommand();
            break;
        case CMD_FLAG:				//フラグ操作コマンド
            FlagCommand();
            break;
        case CMD_IF:				//分岐コマンド
            IfCommand();
            break;
        default:					//定義されていないコマンド
            break;
    }
}

void ratchet::game::gamesystem::text::Script::TextCommand(void) {
    TEXTCOMMAND* pCmd = new TEXTCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->px = atof(pstr);
    pstr = strtok(NULL, ",");
    pCmd->py = atof(pstr);
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Text, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

void ratchet::game::gamesystem::text::Script::SpriteCommand(void) {
    SPRITECOMMAND* pCmd = new SPRITECOMMAND();
    char* pstr = strtok(NULL, ",");
    strcpy(pCmd->Name, Trim(pstr));
    pstr = strtok(NULL, ";");
    strcpy(pCmd->FName, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

void ratchet::game::gamesystem::text::Script::SetPosCommand(void) {
    SETPOSCOMMAND* pCmd = new SETPOSCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->px = atof(pstr);
    pstr = strtok(NULL, ",");
    pCmd->py = atof(pstr);
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

void ratchet::game::gamesystem::text::Script::SetShowCommand(void) {
    SETSHOWCOMMAND* pCmd = new SETSHOWCOMMAND();
    char* pstr = strtok(NULL, ",");
    Trim(pstr);
    if (stricmp(pstr, "true") == 0) {
        pCmd->bShow = true;
    }
    else if (stricmp(pstr, "false") == 0) {
        pCmd->bShow = false;
    }
    else {
        pCmd->bShow = atoi(pstr);
    }
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

void ratchet::game::gamesystem::text::Script::NameCommand(int sCmd) {
    NAMECOMMAND* pCmd = new NAMECOMMAND(sCmd);
    char* pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

void ratchet::game::gamesystem::text::Script::SelectCommand(void) {
    SELECTCOMMAND* pCmd = new SELECTCOMMAND();
    char* pstr = strtok(NULL, ",");
    strcpy(pCmd->Name, Trim(pstr));
    pstr = strtok(NULL, ",");
    pCmd->Count = atoi(pstr);
    pCmd->pItem = (char**)malloc(sizeof(char*) * pCmd->Count);
    pCmd->pLabel = (char**)malloc(sizeof(char*) * pCmd->Count);
    for (int i = 0; i < pCmd->Count; i++) {
        //選択文字列読み込み
        pstr = strtok(NULL, ",");
        pstr = Trim(pstr);
        pCmd->pItem[i] = (char*)malloc(strlen(pstr) + 1);
        strcpy(pCmd->pItem[i], pstr);
        //移動先ラベル読み込み
        //最後のラベルのみ区切りが,から;に変更
        pstr = strtok(NULL, ((i == pCmd->Count - 1) ? ";" : ","));
        pstr = Trim(pstr);
        pCmd->pLabel[i] = (char*)malloc(strlen(pstr) + 1);
        strcpy(pCmd->pLabel[i], pstr);
    }
    pCmd->Select.Create(pCmd->Name, pCmd->pItem, pCmd->Count);
    m_CommandList.Add((COMMAND**)&pCmd);
}

void ratchet::game::gamesystem::text::Script::FlagCommand(void) {
    FLAGCOMMAND* pCmd = new FLAGCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->No = atoi(pstr);
    pstr = strtok(NULL, ",");
    Trim(pstr);
    for (pCmd->Op = 0; pCmd->Op < OP_COUNT && strcmp(pstr, gScriptOp[pCmd->Op]) != 0; pCmd->Op++);
    pstr = strtok(NULL, ";");
    pCmd->Value = atoi(pstr);
    m_CommandList.Add((COMMAND**)&pCmd);
}

void ratchet::game::gamesystem::text::Script::IfCommand(void) {
    IFCOMMAND* pCmd = new IFCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->No = atoi(pstr);
    pstr = strtok(NULL, ",");
    Trim(pstr);
    for (pCmd->Op = 0; pCmd->Op < CMP_COUNT && strcmp(pstr, gScriptCmp[pCmd->Op]) != 0; pCmd->Op++);
    pstr = strtok(NULL, ",");
    pCmd->Value = atoi(pstr);
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

bool ratchet::game::gamesystem::text::Script::LoadTextFile(const char* name) {
    //テキストファイルを開く
    FILE* fp = fopen(name, "rt");
    if (fp == NULL) {
        return false;
    }
    //ファイルの全容量を調べる
    //一度ファイルの終端に移動して、その位置を調べることでサイズがわかる
    //調べ終わった後はファイルの先頭に移動して戻しておく
    //ただしこの方法でも正常なサイズを読み込むことはできない
    fseek(fp, 0, SEEK_END);
    long fSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    //ファイルサイズ分だけのメモリを確保する
    //終端を含めるため＋１しておく
    m_FileBuffer = (char*)malloc(fSize + 1);
    //ファイルを全てバッファに読み込む
    //ここで実際に読み込めたサイズを調べてその終端に\0を入る
    fSize = fread(m_FileBuffer, 1, fSize, fp);
    m_FileBuffer[fSize] = '\0';
    //ファイル名の保存
    strcpy(m_FileName, name);
    //ファイルを閉じる
    fclose(fp);
    return true;
}

void ratchet::game::gamesystem::text::Script::Release(void) {
    if (m_FileBuffer) {
        free(m_FileBuffer);
        m_FileBuffer = NULL;
    }
    m_CommandList.Release();
}