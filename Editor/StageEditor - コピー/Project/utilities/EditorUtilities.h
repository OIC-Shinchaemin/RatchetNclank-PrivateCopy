#pragma once
#include <Mof.h>
#include <filesystem>
#include <optional>
#undef   GetWindowStyle

namespace editor {
	class EditorUtilities {
	private:
		static long _style;
		static long _pos[2];
	public:
		EditorUtilities(void) = delete;
		~EditorUtilities(void) = delete;

		/// <summary>
		/// �E�B���h�E�T�C�Y�ύX
		/// </summary>
		/// <returns>�ύX���ꂽ�ꍇ�ύX��̃E�B���h�E�T�C�Y���Ԃ�</returns>
		static std::optional<RECT> ChangeWindowSize(void);

		static bool ObserveWindowStyle(void);
		static long GetWindowStyle(void);

		static bool LoadWindowParam(void);
		static bool SaveWindowParam(void);
	};
}