#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Game.h"
#include "ui/CocosGUI.h"
#include <memory>

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	std::unique_ptr<Game> game;

	void showCards(const std::vector<Card>& cards, float yPosition, bool showCardFace = true, bool isPlayerHand = true);
	
	void renderCards();

	std::vector<cocos2d::ui::Button*> playerHandCards;
	std::vector<cocos2d::ui::Button*> cpuHandCards;
	std::vector<cocos2d::ui::Button*> tableCards;
};

#endif // __GAMESCENE_H__