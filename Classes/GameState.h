#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
};

#endif // __GAME_STATE_H__
