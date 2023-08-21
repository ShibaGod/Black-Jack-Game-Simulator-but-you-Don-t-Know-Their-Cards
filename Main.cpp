#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>
#include <vector>

enum class CardRank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,
	rank_ace,
	max_card_rank

};

enum class CardSuit
{
	club,
	diamond,
	heart,
	spade,
	max_suit
};

struct Card
{
	CardRank rank{};
	CardSuit suit{};

};

void printCard(const Card& card)
{
	switch (card.rank)
	{
	case(CardRank::rank_2):
		std::cout << "2";
		break;
	case(CardRank::rank_3):
		std::cout << "3";
		break;
	case(CardRank::rank_4):
		std::cout << "4";
		break;
	case(CardRank::rank_5):
		std::cout << "5";
		break;
	case(CardRank::rank_6):
		std::cout << "6";
		break;
	case(CardRank::rank_7):
		std::cout << "7";
		break;
	case(CardRank::rank_8):
		std::cout << "8";
		break;
	case(CardRank::rank_9):
		std::cout << "9";
		break;
	case(CardRank::rank_10):
		std::cout << "T";
		break;
	case(CardRank::rank_jack):
		std::cout << "J";
		break;
	case(CardRank::rank_queen):
		std::cout << "Q";
		break;
	case(CardRank::rank_king):
		std::cout << "K";
		break;
	case(CardRank::rank_ace):
		std::cout << "A";
		break;
	default:
		std::cout << "ERROR";
	}

	switch (card.suit)
	{
	case(CardSuit::club):
		std::cout << "C";
		break;
	case(CardSuit::diamond):
		std::cout << "D";
		break;
	case(CardSuit::heart):
		std::cout << "H";
		break;
	case(CardSuit::spade):
		std::cout << "S";
		break;
	
	default:
		std::cout << "BAD";
	}
	
}

using Deck = std::array<Card, 52>;

Deck createDeck()
{

	Deck deck{};
	size_t count{ 0 };
	for (int i{}; i < static_cast<int>(CardRank::max_card_rank); ++i)
	{
		for (int j{}; j < static_cast<int>(CardSuit::max_suit); ++j)
		{
			
			deck[count].rank = static_cast<CardRank>(i);
			deck[count].suit = static_cast<CardSuit>(j);
			++count;
		}
		
	}

	return deck;
}

void printDeck(const Deck& deck)
{
	for (Card i : deck)
	{
		printCard(i);
	}
	std::cout << '\n';
}

void shuffleDeck(Deck& deck, std::mt19937 mt)
{
	std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(Card& card)
{

	switch (card.rank)
	{
	case(CardRank::rank_2):
		return 2;
		break;
	case(CardRank::rank_3):
		return 3;
		break;
	case(CardRank::rank_4):
		return 4;
		break;
	case(CardRank::rank_5):
		return 5;
		break;
	case(CardRank::rank_6):
		return 6;
		break;
	case(CardRank::rank_7):
		return 7;
		break;
	case(CardRank::rank_8):
		return 8;
		break;
	case(CardRank::rank_9):
		return 9;
		break;
	case(CardRank::rank_10):
		return 10;
		break;
	case(CardRank::rank_jack):
		return 10;
		break;
	case(CardRank::rank_queen):
		return 10;
		break;
	case(CardRank::rank_king):
		return 10;
		break;
	case(CardRank::rank_ace):
		return 11;
		break;
	default:
		return 00;
		break;
	}
}

struct Player
{
	std::vector<Card> hand{};
};

struct Dealer
{
	std::vector<Card> hand{};
};

Card dealCard(Deck& deck)
{
	static size_t count{0};
	return deck[count++];

}

int playerPlays(Deck& deck, Player player)
{
	size_t counter{};

	std::cout << "Your hand is: ";
	printCard(player.hand[counter++]);
	std::cout << " and ";
	printCard(player.hand[counter++]);
	std::cout << '\n';
	std::cout << "Would you like to hit or stand? Input 1 to hit and 2 to stand? ";
	int choice{};
	std::cin >> choice;

	int fSum{};
	while (choice == 1)
	{
		player.hand.push_back(dealCard(deck));
		std::cout << "Drawn card is ";
		printCard(player.hand[counter++]);
		std::cout << ". ";
		int sum{};
		for (Card i : player.hand)
		{
			int x = getCardValue(i);
			static int aceCounter{};
			if (x == 11)
				++aceCounter;
			sum += x;
			while (sum > 21 && aceCounter > 0)
			{
				sum -= 10;
				--aceCounter;
			}
			
			
		}
		fSum = sum;

		if (fSum > 21)
		{
			break;
		}

		std::cout << "Would you like to hit or stand? Input 1 to hit and 2 to stand? ";
		std::cin >> choice;
		
	}
	return fSum;

}

int dealerPlays(Deck& deck, Dealer dealer)
{
	size_t counter{};

	std::cout << "Dealer hand is: ";
	printCard(dealer.hand[counter++]);
	std::cout << ". ";
	int fSum{};
	while(fSum < 17)
	{
		dealer.hand.push_back(dealCard(deck));
		std::cout << "Drawn card is ";
		printCard(dealer.hand[counter++]);
		std::cout << ". ";
		int sum{};
		for (Card i : dealer.hand)
		{
			int x = getCardValue(i);
			static int dealerAceCounter{};
			if (x == 11)
				++dealerAceCounter;
			sum += x;
			while (sum > 21 && dealerAceCounter > 0)
			{
				sum -= 10;
				--dealerAceCounter;
			}


		}
		fSum = sum;
	}
	return fSum;

}

int playBlackJack(Deck& deck, Player player, Dealer dealer)
{
	dealer.hand.push_back(dealCard(deck));

	player.hand.push_back(dealCard(deck));
	player.hand.push_back(dealCard(deck));

	std::cout << '\n';

	int playerHand{ playerPlays(deck, player) };
	int dealerHand{ dealerPlays(deck, dealer) };

	if ( playerHand > 21)
	{
		return 1;
	}


	if (dealerHand > 21)
	{
		return 2;
	}

	if (playerHand > dealerHand)
	{
		return 2;
	}
	else if (dealerHand > playerHand)
	{
		return 1;
	}
	else
	{
		return 3;
	}

	
}


int main()
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	Deck deck{ createDeck()};

	shuffleDeck(deck,mt);


	Player player;
	Dealer dealer;

	switch (playBlackJack(deck, player, dealer))
	{
	case(1):
		std::cout << "You Lose!" << '\n';
		break;
	case(2):
		std::cout << "You Win!" << '\n';
		break;
	case(3):
		std::cout << "You Tie!" << '\n';
		break;
	}



	return 0;
}