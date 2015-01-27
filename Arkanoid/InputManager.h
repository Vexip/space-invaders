// InputManager.h

#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

// forward declares
class Keyboard;

class InputManager
{
	friend class Engine;

public:
	InputManager();
	~InputManager();


	Keyboard* GetKeyboard();

private:
	
	void SetKeyboard(int key, bool state);

private:
	
	Keyboard* m_keyboard;
};

#endif // INPUTMANAGER_H_INCLUDED
