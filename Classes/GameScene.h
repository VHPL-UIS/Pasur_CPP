#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Game.h"
#include <memory>

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	std::unique_ptr<Game> game;

	void showCard(const Card& card, const cocos2d::Vec2& position, bool showCardFace = true);
	void showCards(const std::vector<Card>& cards, float yPosition, bool showCardFace = true);
};

#endif // __GAMESCENE_H__