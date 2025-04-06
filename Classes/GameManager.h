#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <memory>

class GameState;

class GameManager
{
public:
	static GameManager& getInstance() {
		static GameManager instance;
		return instance;
	}

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	void changeState(std::unique_ptr<GameState> newState);

	void update(float deltaTime);

	void render();

private:
	GameManager() = default;
	~GameManager() = default;

	std::unique_ptr<GameState> currentState;
};

#endif // __GAME_MANAGER_H__

