#include "Game.h"
#include <algorithm>
#include <random>
#include <chrono>

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
	tableCards.push_back(card);
	if (onCardPlayed)
	{
		onCardPlayed(card, true);
	}
	collectCards(card, true);
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
		for (auto it = tableCards.begin(); it != tableCards.end();)
		{
			if (it->getValue() != 12 || it->getValue() != 13)
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
		for (auto it = tableCards.begin(); it != tableCards.end();)
		{
			if (it->getValue() == value)
			{
				collectedCards.push_back(*it);
				it = tableCards.erase(it);
				break;
			}
			else
			{
				++it;
			}
		}
	}
	else
	{
		int target = 11 - value;
		if (value == 14)
		{
			value = 1;
		}
		int n = tableCards.size();
		std::vector<int> bestIndices;

		for (int mask = 1; mask < (1 << n); ++mask)
		{
			int sum = 0;
			std::vector<int> indices;
			for (int i = 0; i < n; ++i)
			{
				if (mask & (1 << i))
				{
					sum += tableCards[i].getValue();
					indices.push_back(i);
				}
			}
			if (sum == target && indices.size() > bestIndices.size())
			{
				bestIndices = indices;
			}
		}

		for (int i = bestIndices.size() - 1; i >= 0; --i)
		{
			int idx = bestIndices[i];
			collectedCards.push_back(tableCards[idx]);
			tableCards.erase(tableCards.begin() + idx);
		}
	}

	if (!collectedCards.empty())
	{
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

	if (collectedCards.empty())
	{
		tableCards.push_back(playedCard);
	}
}
