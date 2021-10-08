#ifndef BASE_CORE_TWEEN_H
#define BASE_CORE_TWEEN_H


#include <memory>


namespace base {
	namespace core {
		enum class EaseType {
			Linear,
		};
		template<typename Type>
		class Tween {
		private:
			//! �K�p����
			float _duration;
			//! �J�n
			Type _from;
			//! �I��
			Type _to;
			//! �C�[�W���O
			EaseType _type;


			Type OutputLinear(float time) {
				return _from + (_to - _from) * (time / _duration);
			}
		public:
			Tween() :
				_duration(),
				_from(),
				_to(),
				_type() {
			}
			~Tween() {
			}
			/// <summary>
			/// �J�n
			/// </summary>
			/// <param name=""></param>
			void Start(Type from, Type to, float duration, EaseType type) {
				this->_duration = duration;
				this->_from = from;
				this->_to = to;
				this->_type = type;
			}
			/// <summary>
			/// �o��
			/// </summary>
			Type Output(float time) {
				switch (_type) {
				case base::core::EaseType::Linear:
					return this->OutputLinear(time);
				default:
					break;
				} // switch
				return Type();
			}
		};
	}
}
#endif // !BASE_CORE_TWEEN_H