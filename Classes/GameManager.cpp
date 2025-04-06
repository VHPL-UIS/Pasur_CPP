#include "GameManager.h"
#include "GameState.h"

void GameManager::changeState(std::unique_ptr<GameState> newState)
{
	currentState = std::move(newState);
}

void GameManager::update(float deltaTime)
{
	if (currentState)
	{
		currentState->update(deltaTime);
	}
}

void GameManager::render()
{
	if (currentState)
	{
		currentState->render();
	}
}