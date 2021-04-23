#include "EditorUtilities.h"

using namespace editor;

long EditorUtilities::_style = NULL;
long EditorUtilities::_pos[] = { 0L, 0L };

std::optional<RECT> editor::EditorUtilities::ChangeWindowSize(void) {
    RECT rect, pos;
    HWND hWnd = g_pMainWindow->GetWindowHandle();
    GetWindowRect(hWnd, &pos);
    GetClientRect(hWnd, &rect);
    int prev_window_width  = g_pGraphics->GetTargetWidth();
    int prev_window_height = g_pGraphics->GetTargetHeight();
    int now_width          = rect.right;
    int now_height         = rect.bottom;
    if (pos.left != _pos[0] || pos.top != _pos[1]) {
        _pos[0] = pos.left;
        _pos[1] = pos.top;
    }
    if (prev_window_width != now_width || prev_window_height != now_height) {
        g_pGraphics->SetScreenSize(now_width, now_height);
        g_pGraphics->SetBackBufferSize(now_width, now_height);
        return rect;
    }
    return std::nullopt;
}

bool editor::EditorUtilities::ObserveWindowStyle(void) {
    HWND hWnd = g_pMainWindow->GetWindowHandle();
    long s    = GetWindowLong(hWnd, GWL_STYLE);
    if (s == _style) {
        return false;
    }
    _style = s;
    return true;
}

long editor::EditorUtilities::GetWindowStyle(void) {
    return _style;
}

bool editor::EditorUtilities::LoadWindowParam(void) {
    long w, h, s;
    FILE* file_pointer = fopen("settings.bin", "rb");
    if (file_pointer == NULL) {
        return false;
    }
    fread(&w, sizeof(long), 1, file_pointer);
    fread(&h, sizeof(long), 1, file_pointer);
    fread(&s, sizeof(long), 1, file_pointer);
    fread(&_pos[0], sizeof(long), 1, file_pointer);
    fread(&_pos[1], sizeof(long), 1, file_pointer);
    fclose(file_pointer);

    HWND hWnd = g_pMainWindow->GetWindowHandle();
    g_pGraphics->SetScreenSize(w, h);
    g_pGraphics->SetBackBufferSize(w, h);
    SetWindowLong(hWnd, GWL_STYLE, s);
    SetWindowPos(hWnd, NULL, _pos[0], _pos[1], 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    return true;
}

bool editor::EditorUtilities::SaveWindowParam(void) {
    FILE* file_pointer = fopen("settings.bin", "wb");
    if (file_pointer == NULL) {
        return false;
    }
    long w = g_pGraphics->GetTargetWidth();
    long h = g_pGraphics->GetTargetHeight();
    fwrite(&w, sizeof(long), 1, file_pointer);
    fwrite(&h, sizeof(long), 1, file_pointer);
    fwrite(&_style, sizeof(long), 1, file_pointer);
    fwrite(&_pos[0], sizeof(long), 1, file_pointer);
    fwrite(&_pos[1], sizeof(long), 1, file_pointer);
    fclose(file_pointer);
    return true;
}
