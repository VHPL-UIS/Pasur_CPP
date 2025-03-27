#include "GameScene.h"
#include "Card.h"

USING_NS_CC;

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

	initDeck();
	shuffleDeck();
	dealCards();

	showCards(playerHand, visibleSize.height / 4);
	showCards(cpuHand, visibleSize.height / 4 * 3.7, false);
	showCards(tableCards, visibleSize.height / 2 * 1.2);

	return true;
}

void GameScene::initDeck()
{
	deck.clear();

	for (int suit = static_cast<int>(Suit::Hearts); suit <= static_cast<int>(Suit::Spades); ++suit)
	{
		for (int value = 2; value <= 14; ++value)
		{
			deck.push_back(Card(value, static_cast<Suit>(suit)));
		}
	}
}

void GameScene::shuffleDeck()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void GameScene::dealCards()
{
	playerHand.clear();
	cpuHand.clear();
	tableCards.clear();

	for (int i = 0; i < 4; ++i)
	{
		playerHand.push_back(deck.back());
		deck.pop_back();
		cpuHand.push_back(deck.back());
		deck.pop_back();
	}

	for (int i = 0; i < 4; ++i)
	{
		Card card = deck.back();
		deck.pop_back();

		while (card.isJack())
		{
			deck.insert(deck.begin(), card);
			card = deck.back();
			deck.pop_back();
		}
		tableCards.push_back(card);
	}
}

void GameScene::showCard(const Card& card, const Vec2& position, bool showCardFace)
{
	auto cardSprite = Sprite::create(card.getImagePath(showCardFace));
	if (cardSprite == nullptr)
	{
		problemLoading(card.getImagePath().c_str());
		return;
	}
	else
	{
		cardSprite->setPosition(position);
		cardSprite->setScale(0.25f);
		printf("%f %f\n", cardSprite->getContentSize().width, cardSprite->getContentSize().height);
		this->addChild(cardSprite, 0);
	}
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

void GameScene::endGame()
{
	//GameManager::getInstance().changeState(std::make_unique<GameStateMenu>());
}