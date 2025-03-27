#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Card.h"
#include <vector>

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	std::vector<Card> deck;
	std::vector<Card> playerHand;
	std::vector<Card> cpuHand;
	std::vector<Card> tableCards;

	void initDeck();
	void shuffleDeck();
	void dealCards();

	void showCard(const Card& card, const cocos2d::Vec2& position, bool showCardFace = true);
	void showCards(const std::vector<Card>& cards, float yPosition, bool showCardFace = true);
	void endGame();
};

#endif // __GAMESCENE_H__