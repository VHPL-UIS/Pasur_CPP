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

	game->onCardPlayed = [this](const Card& card, bool isPlayer)
	{
		renderCards();
	};

	game->start();

	renderCards();

	return true;
}

void GameScene::renderCards()
{
	for (auto* card : playerHandCards)
	{
		if (card != nullptr)
		{
			card->removeFromParent();
		}
	}
	playerHandCards.clear();

	for (auto* card : cpuHandCards)
	{
		if (card != nullptr)
		{
			card->removeFromParent();
		}
	}
	cpuHandCards.clear();

	for (auto* card : tableCards)
	{
		if (card != nullptr)
		{
			card->removeFromParent();
		}
	}
	tableCards.clear();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	showCards(game->getPlayerHand(), visibleSize.height / 4);
	showCards(game->getCpuHand(), visibleSize.height / 4 * 3.7, false, false);
	showCards(game->getTableCards(), visibleSize.height / 2 * 1.2, true, false);
}

void GameScene::showCards(const std::vector<Card>& cards, float yPosition, bool showCardFace, bool isPlayerHand)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	const float spacing = 10.0f;
	const int numCards = cards.size();

	auto sampleSprite = Sprite::create(cards[0].getImagePath());
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
		Vec2 position = Vec2(xPosition, yPosition);
		auto cardButton = Button::create(cards[i].getImagePath(showCardFace), cards[i].getImagePath(showCardFace));
		if (cardButton == nullptr)
		{
			problemLoading(cards[i].getImagePath().c_str());
			return;
		}
		else
		{
			cardButton->setPosition(position);
			cardButton->setScale(0.25f);
			this->addChild(cardButton, 0);
			if (!showCardFace)
			{
				cpuHandCards.push_back(cardButton);
			}
			else
			{
				if (isPlayerHand)
				{
					playerHandCards.push_back(cardButton);
				}
				else
				{
					tableCards.push_back(cardButton);
				}
			}
		}

		cardButton->addClickEventListener([=](Ref* sender)
		{
			game->playerPlay(i);
			CCLOG("Card clicked: %s", cards[i].toString().c_str());
		});
		xPosition += cardWidth + spacing;
	}
}