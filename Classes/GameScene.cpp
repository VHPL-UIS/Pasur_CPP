#include "GameScene.h"
#include "Card.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto backgroundSprite = Sprite::create("carpet_blur.png");
	if (!backgroundSprite)
	{
		problemLoading("carpet_blur.png");
	}
	else
	{
		backgroundSprite->setPosition(visibleSize / 2);
		this->addChild(backgroundSprite, -1);
	}

	game = std::make_unique<Game>();
	if (!game)
	{
		problemLoading("Game");
		return false;
	}

	game->start();

	showCards(game->getPlayerHand(), visibleSize.height / 4);
	showCards(game->getCpuHand(), visibleSize.height / 4 * 3.7, false);
	showCards(game->getTableCards(), visibleSize.height / 2 * 1.2);

	return true;
}

void GameScene::showCard(const Card& card, const Vec2& position, bool showCardFace)
{
	auto cardButton = Button::create(card.getImagePath(showCardFace), card.getImagePath(showCardFace));
	if (cardButton == nullptr)
	{
		problemLoading(card.getImagePath().c_str());
		return;
	}
	else
	{
		cardButton->setPosition(position);
		cardButton->setScale(0.25f);
		this->addChild(cardButton, 0);
	}

	cardButton->addClickEventListener([=](Ref* sender)
	{
		CCLOG("Card clicked: %s", card.toString().c_str());
		printf("%s\n", card.toString().c_str());
	});
}

void GameScene::showCards(const std::vector<Card>& cards, float yPosition, bool showCardFace)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	const float spacing = 10.0f;
	const int numCards = cards.size();

	auto sampleSprite = Sprite::create(cards[0].getImagePath());
	printf("%f %f\n", sampleSprite->getContentSize().width, sampleSprite->getContentSize().height);
	if (!sampleSprite)
	{
		problemLoading(cards[0].getImagePath().c_str());
		return;
	}

	float cardWidth = sampleSprite->getContentSize().width / 4;
	float totalWidth = numCards * cardWidth + (numCards - 1) * spacing;
	float xPosition = (visibleSize.width - totalWidth) / 2 + cardWidth / 2;
	for (int i = 0; i < numCards; ++i)
	{
		showCard(cards[i], Vec2(xPosition, yPosition), showCardFace);
		xPosition += cardWidth + spacing;
	}
}