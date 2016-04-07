#include "InputManager.h"

bool InputManager::instanceFlag = false;
InputManager* InputManager::instance = NULL;

InputManager* InputManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new InputManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void InputManager::UpdateState()
{
	//Check for keys that were pressed in previous frame
	if (downKeys.size() > 0)
	{
		for each (sf::Keyboard::Key key in downKeys)
		{
			heldKeys.push_back(key);
		}
		downKeys.clear();
	}

	if (releasedKeys.size() > 0)
	{
		releasedKeys.clear();
	}

	//Check for mouse buttons that were clicked in previous frame
	if (downClicks.size() > 0)
	{
		for each (int button in downClicks)
		{
			heldClicks.push_back(button);
		}
		downClicks.clear();
	}

	if (releasedClicks.size() > 0)
	{
		releasedClicks.clear();
	}
}

void InputManager::UpdatePolledEvents(sf::Event e)
{
	//Key Input
	//if a new key was pressed
	if (!IsKeyHeld(e.key.code))
	{
		if (e.type == e.KeyPressed)
		{
			//std::cout << "Key Pressed\n";
			downKeys.push_back(e.key.code);
		}
	}

	//If a key was released
	if (e.type == e.KeyReleased)
	{
		//std::cout << "Key Released\n";
		heldKeys.remove(e.key.code);
		releasedKeys.push_back(e.key.code);
	}

	//Mouse Input
	//If a mouse button was clicked
	if (!IsMouseButtonHeld(e.mouseButton.button))
	{
		if (e.type == e.MouseButtonPressed)
		{
			downClicks.push_back(e.mouseButton.button);
		}
	}

	//if a mouse button was released
	if (e.type == e.MouseButtonReleased)
	{
		heldClicks.remove(e.mouseButton.button);
		releasedClicks.push_back(e.mouseButton.button);
	}

	//If the mouse cursor moves
	if (e.type == e.MouseMoved)
	{
		mousePos.x = e.mouseMove.x;
		mousePos.y = e.mouseMove.y;
		//std::cout << "MousePos: " << mousePos.x << "," << mousePos.y;
	}
}

bool InputManager::IsKeyDown(sf::Keyboard::Key key)
{
	std::list<sf::Keyboard::Key>::iterator iter = std::find(downKeys.begin(), downKeys.end(), key);

	if (iter != downKeys.end())
	{
		return true;
	}

	return false;
}

bool InputManager::IsKeyHeld(sf::Keyboard::Key key)
{
	std::list<sf::Keyboard::Key>::iterator iter = std::find(heldKeys.begin(), heldKeys.end(), key);

	if (iter != heldKeys.end())
	{
		return true;
	}
	return false;
}

bool InputManager::IsKeyReleased(sf::Keyboard::Key key)
{
	std::list<sf::Keyboard::Key>::iterator iter = std::find(releasedKeys.begin(), releasedKeys.end(), key);

	if (iter != releasedKeys.end())
	{
		return true;
	}
	return false;
}

bool InputManager::IsMouseButtonDown(int mouseButtonIndex)
{
	std::list<int>::iterator iter = std::find(downClicks.begin(), downClicks.end(), mouseButtonIndex);

	if (iter != downClicks.end())
	{
		return true;
	}
	return false;
}

bool InputManager::IsMouseButtonHeld(int mouseButtonIndex)
{
	std::list<int>::iterator iter = std::find(heldClicks.begin(), heldClicks.end(), mouseButtonIndex);

	if (iter != heldClicks.end())
	{
		return true;
	}
	return false;
}

bool InputManager::IsMouseButtonReleased(int mouseButtonIndex)
{
	std::list<int>::iterator iter = std::find(releasedClicks.begin(), releasedClicks.end(), mouseButtonIndex);

	if (iter != releasedClicks.end())
	{
		return true;
	}
	return false;
}

sf::Vector2f InputManager::GetMousePos()
{
	return mousePos;
}