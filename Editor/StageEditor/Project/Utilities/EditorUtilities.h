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
		/// ウィンドウサイズ変更
		/// </summary>
		/// <returns>変更された場合変更後のウィンドウサイズが返る</returns>
		static std::optional<RECT> ChangeWindowSize(void);

		static bool ObserveWindowStyle(void);
		static long GetWindowStyle(void);

		static bool LoadWindowParam(void);
		static bool SaveWindowParam(void);

		/// <summary>
		/// 拡張子の取得
		/// </summary>
		/// <param name="path">ファイルパス</param>
		/// <returns>.を含む拡張子文字列</returns>
		static std::string GetExt(const std::string& path);

		/// <summary>
		/// ファイル名の取得
		/// </summary>
		/// <param name="path">ファイルパス</param>
		/// <returns>拡張子を含まないファイル名</returns>
		static std::string GetFileName(const std::string& path);
	};
}