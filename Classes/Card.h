#ifndef __Card_H__
#define __Card_H__

#include <string>

enum class Suit
{
	Hearts,
	Diamonds,
	Clubs,
	Spades
};

class Card
{
public:
	Card(int value, Suit suit);
	std::string toString() const;
	int getValue() const;
	Suit getSuit() const;
	bool isJack() const;
	std::string getImagePath() const;

private:
	int value;
	Suit suit;
};

#endif // __Card_H__
