#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <functional>
#include "Card.h"

class Game
{
public:
	Game();

	void start();
	void playerPlay(int cardIndex);
	void cpuPlay();

	const std::vector<Card>& getPlayerHand() const;
	const std::vector<Card>& getCpuHand() const;
	const std::vector<Card>& getTableCards() const;

	void collectCards(const Card& playedCard, bool isPlayer);

	//int getPlayerScore() const;
	//int getCpuScore() const;

	std::function<void()> onNewRound;
	std::function<void(const Card&, bool isPlayer)> onCardPlayed;
	std::function<void(int playerScore, int cpuScore)> onScoreUpdated;
	std::function<void(std::string winner)> onGameEnded;

private:
	std::vector<Card> deck;
	std::vector<Card> playerHand;
	std::vector<Card> cpuHand;
	std::vector<Card> tableCards;
	std::vector<Card> playerCollectedCards;
	std::vector<Card> cpuCollectedCards;
	int playerScore;
	int cpuScore;
	void initDeck();
	void shuffleDeck();
	void dealCards();
	void revealTableCards();
	//void checkEndRound();
	//void checkEndGame();
	//void calculateScore();
};

#endif	// __GAME_H__