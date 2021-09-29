#include	"Menu.h"


ratchet::game::gamesystem::text::CMenu::CMenu() :
    _position(),
    _space(),
    _count(0),
    _title(NULL),
    _item(NULL),
    _select(0),
    _show(false),
    _enter(false),
    _rectangle(),
    _header_rectangle(),
    _drag(false) {
    _space.x = 12.0f;
    _space.y = 8.0f;

}

ratchet::game::gamesystem::text::CMenu::~CMenu() {
    Release();
}

void ratchet::game::gamesystem::text::CMenu::Create(char* pTitle, char** pItem, int cnt) {
    this->Release();
    //引数の文字列を保存
    _count = cnt;
    _title = (char*)malloc(strlen(pTitle) + 1);
    strcpy(_title, pTitle);
    _item = (char**)malloc(sizeof(char*) * cnt);
    for (int i = 0; i < _count; i++) {
        _item[i] = (char*)malloc(strlen(pItem[i]) + 1);
        strcpy(_item[i], pItem[i]);
    }
    //メニューの文字列の最大、最少矩形を求める
    CRectangle trec;
    CGraphicsUtilities::CalculateStringRect(0, 0, _title, trec);
    _rectangle.Right = MOF_MAX(_rectangle.Right, trec.Right + _space.x * 2);
    _rectangle.Bottom += trec.Bottom + _space.y * 2;
    _header_rectangle = _rectangle;
    for (int i = 0; i < _count; i++) {
        CGraphicsUtilities::CalculateStringRect(0, 0, _item[i], trec);
        _header_rectangle.Right = _rectangle.Right = MOF_MAX(_rectangle.Right, trec.Right + _space.x * 2);
        _rectangle.Bottom += trec.Bottom + _space.y;
    }
    _rectangle.Bottom += _space.y;
}

void ratchet::game::gamesystem::text::CMenu::Release(void) {
    if (_title) {
        free(_title);
        _title = NULL;
    }
    if (_item) {
        for (int i = 0; i < _count; i++) {
            free(_item[i]);
        }
        free(_item);
        _item = NULL;
        _count = 0;
    }
    _rectangle = CRectangle(0, 0, 0, 0);
}

void ratchet::game::gamesystem::text::CMenu::Show(float cx, float cy) {
    _position.x = cx;
    _position.y = cy;
    _show = true;
    _enter = false;
    _drag = false;
    _select = 0;
    float w = _rectangle.GetWidth();
    float h = _rectangle.GetHeight();
    _rectangle.Top = _position.y - h * 0.5f;
    _rectangle.Bottom = _rectangle.Top + h;
    _rectangle.Left = _position.x - w * 0.5f;
    _rectangle.Right = _rectangle.Left + w;
    _header_rectangle.Bottom = _rectangle.Top + _header_rectangle.GetHeight();
    _header_rectangle.Top = _rectangle.Top;
    _header_rectangle.Right = _rectangle.Left + _header_rectangle.GetWidth();
    _header_rectangle.Left = _rectangle.Left;
}

void ratchet::game::gamesystem::text::CMenu::Update(void) {
    if (!_show) {
        return;
    }
    //マウス位置で選択
    float px, py;
    g_pInput->GetMousePos(px, py);
    CRectangle trec;
    CRectangle hrec = _header_rectangle;
    _select = -1;
    for (int i = 0; i < _count; i++) {
        CGraphicsUtilities::CalculateStringRect(0, 0, _item[i], trec);
        hrec.Top = hrec.Bottom;
        hrec.Bottom += trec.Bottom + _space.y * 2;
        if (hrec.CollisionPoint(px, py)) {
            _select = i;
        }
    }
    //左クリックで決定
    if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
        //ヘッダーのドラッグで移動させる
        if (_header_rectangle.CollisionPoint(px, py)) {
            _drag = true;
        }
        else if (_select >= 0 && _select < _count) {
            _enter = true;
        }
    }
    //ドラッグ移動
    if (_drag && g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON)) {
        float mx, my;
        g_pInput->GetMouseMove(mx, my);
        char str[128];
        sprintf(str, "%f / %f\n", mx, my);
        OutputDebugString(str);
        _position.x += mx;
        _position.y += my;
        _rectangle.Left += mx;
        _rectangle.Right += mx;
        _rectangle.Top += my;
        _rectangle.Bottom += my;
        _header_rectangle.Left += mx;
        _header_rectangle.Right += mx;
        _header_rectangle.Top += my;
        _header_rectangle.Bottom += my;
    }
    else {
        _drag = false;
    }
}

void ratchet::game::gamesystem::text::CMenu::Render(void) {
    if (!_show) {
        return;
    }
    //メニューの背景描画
    CGraphicsUtilities::RenderFillRect(_rectangle, MOF_ARGB(200, 0, 0, 0));
    CGraphicsUtilities::RenderFillRect(_header_rectangle, MOF_ARGB(200, 64, 64, 64));
    //項目の文字を描画する
    CRectangle trec;
    float py = _rectangle.Top + _space.y;
    CGraphicsUtilities::CalculateStringRect(0, 0, _title, trec);
    CGraphicsUtilities::RenderString(_position.x - trec.GetWidth() * 0.5f, py, MOF_COLOR_WHITE, _title);
    py += trec.Bottom + _space.y;
    for (int i = 0; i < _count; i++) {
        CGraphicsUtilities::CalculateStringRect(0, 0, _item[i], trec);
        CGraphicsUtilities::RenderString(_position.x - trec.GetWidth() * 0.5f, py + _space.y, ((_select == i) ? MOF_XRGB(255, 255, 255) : MOF_XRGB(128, 128, 128)), _item[i]);
        py += trec.Bottom + _space.y;
    }
}