#ifndef INPUTMANAGER
#define INPUTMANAGER
#include <list>
#include "SFML\Graphics.hpp"
class InputManager
{
public:
	//Functions
	static InputManager* GetInstance();
	~InputManager()
	{
		instanceFlag = false;
	}

	void UpdateState();
	void UpdatePolledEvents(sf::Event e);
	bool IsKeyDown(sf::Keyboard::Key key);
	bool IsKeyHeld(sf::Keyboard::Key key);
	bool IsKeyReleased(sf::Keyboard::Key key);

	bool IsMouseButtonDown(int mouseButtonIndex);
	bool IsMouseButtonHeld(int mouseButtonIndex);
	bool IsMouseButtonReleased(int mouseButtonIndex);
	sf::Vector2f GetMousePos();

	//Variables

private:
	//Functions
	InputManager()
	{
		//private constructor
		downKeys = std::list<sf::Keyboard::Key>();
		heldKeys = std::list<sf::Keyboard::Key>();
		releasedKeys = std::list<sf::Keyboard::Key>();

		downClicks = std::list<int>();
		heldClicks = std::list<int>();
		releasedClicks = std::list<int>();
	}

	//Variables
	std::list<sf::Keyboard::Key> downKeys;
	std::list<sf::Keyboard::Key> heldKeys;
	std::list<sf::Keyboard::Key> releasedKeys;

	std::list<int> downClicks;
	std::list<int> heldClicks;
	std::list<int> releasedClicks;
	sf::Vector2f mousePos;

	static bool instanceFlag;
	static InputManager *instance;
};

#endif