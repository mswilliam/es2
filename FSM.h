enum eState{Quiet = 0x00, Ring = 0X01, StateMax = 0x02};
enum eInput{InputOff = 0x00, InputOn = 0x01, InputMAX = 0x02};

struct TState {
  void (*functionOut) (void); 
  enum eState Next[InputMAX];
};

typedef struct TFsm{
	struct TState transitionGraph[StateMax];
	enum eState currentState;
	enum eInput input;
} Fsm;
