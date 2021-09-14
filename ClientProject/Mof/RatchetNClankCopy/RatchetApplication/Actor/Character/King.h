#ifndef RATCHET_ACTOR_CHARACTER_KING_H
#define RATCHET_ACTOR_CHARACTER_KING_H


#include "../Actor.h"

#include "../../Game/GameSystem/Text/TextSystem.h"
#include "Scarecrow.h"


namespace ratchet::actor::character {
	class King :
		public actor::Actor,
		public ratchet::actor::character::ScarecrowEndMessageListener {
		using super = actor::Actor;
	private:
		//! ハテナ
		std::weak_ptr<Mof::CTexture> _question_texture;
		//! 通知用
		ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		King();
		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~King();
		/// <summary>
		/// 通知
		/// </summary>
		/// <param name="message"></param>
		virtual void OnNotify(const ratchet::actor::character::ScarecrowEndMessage& message);
		/// <summary>
		/// セッター
		/// </summary>
		/// <param name="ptr"></param>
		void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);

		auto GetTextSystemMessageSubject(void) {
			return &this->_text_system_message_subject;
		}
		/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="param"></param>
	/// <returns></returns>
		virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Update(float delta_time) override;

		/// <summary>
	/// 描画
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
		virtual bool Render(void) override;
		/// <summary>
		/// 会話
		/// </summary>
		void Talk(void);
	};
}
#endif // !RATCHET_ACTOR_CHARACTER_KING_H