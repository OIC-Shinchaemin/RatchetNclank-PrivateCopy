#ifndef RATCHET_ACTOR_GIMMICK_FENCE_H
#define RATCHET_ACTOR_GIMMICK_FENCE_H


#include "../Actor.h"


namespace ratchet::actor::gimmick {
	class Fence : public ratchet::actor::Actor {
		using super = ratchet::actor::Actor;
	private:
		//! ���b�V��
		Mof::CMeshContainer _mesh;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Fence();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~Fence();
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Update(float delta_time) override;
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		virtual bool Render(void) override;
	};
}
#endif // !RATCHET_ACTOR_GIMMICK_FENCE_H