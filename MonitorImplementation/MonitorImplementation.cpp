// MonitorImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <mutex>
#include "Player.h"

using namespace std;

struct BoundedBuffer {
	string* buffer;
	int capacity;

	int front;
	int rear;
	int count;

	std::mutex lock;

	std::condition_variable not_full;
	std::condition_variable not_empty;

	BoundedBuffer(int capacity) : capacity(capacity), front(0), rear(0), count(0) {
		buffer = new string[capacity];
	}

	~BoundedBuffer() {
		delete[] buffer;
	}

	void deposit(string data) {
		std::unique_lock<std::mutex> l(lock);

		not_full.wait(l, [this]() {return count != capacity; });

		buffer[rear] = data;
		rear = (rear + 1) % capacity;
		++count;

		not_empty.notify_one();
	}

	string fetch() {
		std::unique_lock<std::mutex> l(lock);

		not_empty.wait(l, [this]() {return count != 0; });

		string result = buffer[front];
		front = (front + 1) % capacity;
		--count;

		not_full.notify_one();

		return result;
	}
};

void consumer(int id, BoundedBuffer& buffer) {
	for (int i = 0; i < 50; ++i) {
		string value = buffer.fetch();
		//cout << "Consumer " << id << " fetched " <<  value << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1400, 900, 32), "This Subject makes me want to quit college");

	Player* player = new Player();

	BoundedBuffer buffer(200);

	std::thread c1(consumer, 0, std::ref(buffer));
	std::thread c2(consumer, 1, std::ref(buffer));
	std::thread c3(consumer, 2, std::ref(buffer));

	c1.join();
	c2.join();
	c3.join();

	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			InputManager::GetInstance()->UpdatePolledEvents(Event);
			if (Event.type == sf::Event::Closed)
				window.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}
		player->Update();

		window.clear();
		player->Draw(window);
		window.display();
	}

	return 0;
}

