export module Night1:Door;

namespace Night1{

	class Door{
	public:
		void SetClosed(bool newState){
			closed = newState;
		}

		bool GetClosed(){
			return closed;
		}
	
	private:
		bool closed = false;

	};

}
