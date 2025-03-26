#include "Card.h"

Card::Card(int value, Suit suit)
	: value(value), suit(suit)
{
}

std::string Card::toString() const
{
	std::string suitString;
	switch (suit)
	{
	case Suit::Hearts:
		suitString = "Hearts";
		break;
	case Suit::Diamonds:
		suitString = "Diamonds";
		break;
	case Suit::Clubs:
		suitString = "Clubs";
		break;
	case Suit::Spades:
		suitString = "Spades";
		break;
	}

	std::string rank;
	switch (value)
	{
	case 11:
		rank = "Jack";
		break;
	case 12:
		rank = "Queen";
		break;
	case 13:
		rank = "King";
		break;
	case 14:
		rank = "Ace";
		break;
	default:
		rank = std::to_string(value);
		break;
	}

	return rank + "_of_" + suitString;
}

int Card::getValue() const
{
	return value;
}

Suit Card::getSuit() const
{
	return suit;
}

bool Card::isJack() const
{
	return value == 11;
}

std::string Card::getImagePath() const
{
	return "cards/" + toString() + ".png";
}
