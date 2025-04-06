#include "Game.h"
#include <algorithm>
#include <random>
#include <chrono>
#include "cocos2d.h"

USING_NS_CC;

Game::Game()
{
	playerScore = cpuScore = 0;
	initDeck();
	shuffleDeck();
	revealTableCards();
}

void Game::start()
{
	dealCards();
	if (onNewRound)
	{
		onNewRound();
	}
}

void Game::initDeck()
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

void Game::shuffleDeck()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void Game::dealCards()
{
	playerHand.clear();
	cpuHand.clear();

	for (int i = 0; i < 4; ++i)
	{
		playerHand.push_back(deck.back());
		deck.pop_back();
		cpuHand.push_back(deck.back());
		deck.pop_back();
	}
}

void Game::revealTableCards()
{
	tableCards.clear();
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

void Game::playerPlay(int cardIndex)
{
	Card card = playerHand[cardIndex];
	playerHand.erase(playerHand.begin() + cardIndex);
	collectCards(card, true);
	if (onCardPlayed)
	{
		onCardPlayed(card, true);
	}
	cpuPlay();
}

void Game::cpuPlay()
{
}

const std::vector<Card>& Game::getPlayerHand() const
{
	return playerHand;
}

const std::vector<Card>& Game::getCpuHand() const
{
	return cpuHand;
}

const std::vector<Card>& Game::getTableCards() const
{
	return tableCards;
}

void Game::collectCards(const Card& playedCard, bool isPlayer)
{
	std::vector<Card> collectedCards;
	int value = playedCard.getValue();
	if (value == 11)
	{
		if (tableCards.size() < 1)
		{
			tableCards.push_back(playedCard);
			return;
		}

		for (auto it = tableCards.begin(); it != tableCards.end();)
		{
			if (it->getValue() != 12 && it->getValue() != 13)
			{
				collectedCards.push_back(*it);
				it = tableCards.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	else if (value == 12 || value == 13)
	{
		std::vector<Card> multipleCards;
		for (auto it = tableCards.begin(); it != tableCards.end();)
		{
			if (it->getValue() == value)
			{
				multipleCards.push_back(*it);
			}
			else
			{
				++it;
			}
		}

		if (!multipleCards.empty())
		{
			bool hasClubs = false;
			for (auto it = multipleCards.begin(); it != multipleCards.end();)
			{
				if (it->getSuit() == Suit::Clubs)
				{
					collectedCards.push_back(*it);
					it = tableCards.erase(it);
					hasClubs = true;
					break;
				}
				else
				{
					++it;
				}
			}
			if (!hasClubs)
			{
				auto it = multipleCards.begin();
				collectedCards.push_back(*it);
				it = tableCards.erase(it);
			}
		}
	}
	else
	{
		if (value == 14)
		{
			value = 1;
		}

		int target = 11 - value;

		std::vector<Card> combination;
		std::vector<std::vector<Card>> results;

		findCombinationSum(tableCards, target, 0, combination, results);

		if (results.empty())
		{
			CCLOG("No valid combinaiton found!");
		}
		else
		{
			CCLOG("valid combinations:\n");
			for (auto& comb : results)
			{
				for (auto& card : comb)
				{
					CCLOG("Card: %s", card.toString().c_str());
				}
			}

			if (results.size() > 1)
			{
				// a pop up to select the combination and add it to the collected cards
			}
			else
			{
				for (auto& card : results[0])
				{
					for (auto it = tableCards.begin(); it != tableCards.end(); )
					{
						if (card.getValue() == it->getValue())
						{
							collectedCards.push_back(*it);
							it = tableCards.erase(it);
						}
						else
						{
							++it;
						}
					}
				}
			}
		}
	}

	if (!collectedCards.empty())
	{
		collectedCards.push_back(playedCard);
		if (isPlayer)
		{
			for (const Card& card : collectedCards)
			{
				playerCollectedCards.push_back(card);
			}
		}
		else
		{
			for (const Card& card : collectedCards)
			{
				cpuCollectedCards.push_back(card);
			}
		}

		if (onScoreUpdated)
		{
			onScoreUpdated(playerScore, cpuScore);
		}
	}
	else 
	{
		tableCards.push_back(playedCard);
	}
}

void Game::findCombinationSum(const std::vector<Card>& tableCards, int target, int start, std::vector<Card>& combination, std::vector<std::vector<Card>>& results)
{
	if (target == 0)
	{
		results.push_back(combination);
		return;
	}
	for (int i = start; i < tableCards.size(); ++i)
	{
		int cardValue = tableCards[i].getValue();
		if (cardValue == 14)
		{
			cardValue = 1;
		}
		if (cardValue <= target)
		{
			combination.push_back(tableCards[i]);
			findCombinationSum(tableCards, target - cardValue, i + 1, combination, results);
			combination.pop_back();
		}
	}
}