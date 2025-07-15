// ConsoleApplicationPlayingAround.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>
using namespace std;

struct Card {
	string rank;
	string suit;
	int points; // Points for blackjack
	int sort;
};

/*
enum class Rank {
	Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
};
enum class Suit {
	Clubs, Diamonds, Hearts, Spades
};


//Trying to wrap all of this in classes now. WIP.

// Forward declarations for classes

class Deck {

private:
	int numDecks;
	int totalCards;
	Card* deck;

public:
	Deck(int numDecks = 1) : numDecks(numDecks), totalCards(52 * numDecks) {
		deck = createDeck(numDecks);
	}
	~Deck() {
		delete[] deck; // Clean up memory
	}
	Card* getDeck() {
		return deck;
	}
	int getTotalCards() const {
		return totalCards;
	}
}

class Hand {

private:
	Card* hand;
	int handSize;

public:
	Hand(int size) : handSize(size) {
		hand = drawHand(handSize); // Initialize hand with the specified size
	}
	~Hand() {
		delete[] hand; // Clean up memory
	}
	void addCard(const Card& card, int index) {
		if (index < handSize) {
			hand[index] = card; // Add card to the hand at the specified index
		}
	}
	void show() const {
		for (int i = 0; i < handSize; i++) {
			cout << hand[i].rank << hand[i].suit << " ";
		}
		cout << endl;
	}
	int getScore() const {
		int score = 0;
		for (int i = 0; i < handSize; i++) {
			score += hand[i].points; // Sum the points of each card in the hand
		}
		return score;
}
*/

Card* createDeck(int numDecks = 1) {
	const char* ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	const char* suits[] = { "C", "D", "H", "S" };
	int points[] = { 2,3,4,5,6,7,8,9,10,10,10,10,10 }; // Points for blackjack

	int totalCards = 52 * numDecks;
	Card* newDeck = new Card[totalCards];

	int index = 0; // Index to fill the new deck
	for (int d = 0; d < numDecks; ++d) {
		int sortindex = 0;
		for (int s = 0; s < 4; ++s) {
			for (int p = 0; p < 13; ++p) {
				newDeck[index].rank = ranks[p];
				newDeck[index].suit = suits[s];
				newDeck[index].points = points[p];
				newDeck[index].sort = sortindex; // Assign sort value
				++index;
				++sortindex;
			}
		}
	}

	return newDeck;
};

void sortHand(Card* hand, int handSize) {
	//easy sort lmao
	sort(hand, hand + handSize, [](const Card& a, const Card& b) {
		return a.sort < b.sort;
		});
}

Card* drawHand(Card** currentDeck, int& deckSize, int handSize) {

	Card* hand = new Card[handSize]; // Initialize hand with the specified size

	for (int i = 0; i < handSize; i++) {
		int cardPick = rand() % deckSize; // Randomly pick a card from the deck
		hand[i] = (*currentDeck)[cardPick]; // Add the picked card to the hand

		Card* newDeck = new Card[deckSize-1]; // Create a new deck without the picked card
		for (int j = 0, k = 0; j < deckSize; j++) {
			if (j != cardPick) { // Skip the picked card
				newDeck[k++] = (*currentDeck)[j]; // Copy the remaining cards to the new deck
			}
		}
		delete[] *currentDeck; // Clean up memory for the old deck
		*currentDeck = newDeck; // Update the deck to the new deck without the picked card
		deckSize--; // Decrease deck size after picking a card
	}
	sortHand(hand, handSize); // Sort the hand after drawing cards
	return hand;
}

// This is just drawCard but without a returnvalue as all of this can just be done inside the function
void drawCard(Card** currentHand, int& handSize, Card** currentDeck, int& deckSize, int draws = 1) {

	if (deckSize < draws) {
		cout << "Not enough cards left in the deck!" << endl;
		return; // Don't change the hand if no cards are left in the deck
	}

	Card* newHand = new Card[handSize + draws]; // Create a new hand with one more card
	for (int i = 0; i < handSize; i++) {
		newHand[i] = (*currentHand)[i]; // Copy existing cards to the new hand
	}

	for (int i = 0; i < draws; i++) {
		int cardPick = rand() % deckSize; // Randomly pick a card from the deck
		Card card = (*currentDeck)[cardPick]; // Create card as a temporary variable

		newHand[handSize + i] = card; // Add the picked card to the new hand

		Card* newDeck = new Card[deckSize - 1]; // Create a new deck without the picked card
		for (int j = 0, k = 0; j < deckSize; j++) {
			if (j != cardPick) { // Skip the picked card
				newDeck[k++] = (*currentDeck)[j]; // Copy the remaining cards to the new deck
			}
		}
		delete[] * currentDeck; // Clean up memory for the old deck
		*currentDeck = newDeck; // Update the deck to the new deck without the picked card
		deckSize--; // Decrease deck size after picking a card
	}

	delete[] * currentHand; // Clean up memory for the old hand
	*currentHand = newHand; // Update the hand to the new hand with the picked cards
	handSize += draws; // Increase hand size after picking a card
	sortHand(*currentHand, handSize); // Sort the hand after drawing cards
	return;
}

void showHand(Card* hand, int handSize) {
	for (int i = 0; i < handSize; i++) {
		cout << hand[i].rank << hand[i].suit << " ";
	}
}

void showScore(Card* hand, int handSize) {
	int score = 0;
	for (int i = 0; i < handSize; i++) {
		score += hand[i].points; // Sum the points of each card in the hand
	}
	cout << "\n" << score << endl; // Display the total score
}


int getScore(Card* hand, int handSize) {
	int score = 0;
	for (int i = 0; i < handSize; i++) {
		score += hand[i].points; // Sum the points of each card in the hand
	}
	return score; // Return the total score
}

void showHandSplit(Card* hand, int handSize) {
	for (int i = 0; i < handSize; i++) {
		cout << hand[i].rank << hand[i].suit << " ";
		if (hand[i].suit != hand[i + 1].suit) {
			cout << endl; // Print a new line if the suit changes
		}
	}
}



//Blackjack
int Blackjack() {
	// Seed the random number generator
	srand((unsigned int)time(nullptr));  // C++11 style seed the random number generator with current time

	cout << "\n----------------------------- Blackjack. -----------------------------" << endl;
	int decks = 2; // Amount of decks to use
	/*
	cout << "How many decks do you want to use?" << endl;
	cin >> decks;
	if (decks <= 0) {
		cout << "Invalid number of decks. Exiting the game." << endl;
		return 0; // Exit the game if invalid input
	}
	*/
	cout << "\nLet's begin." << endl;

	int deckSize = 52 * decks; // Total number of cards in the deck
	Card* deck = createDeck(decks);

	int startingHandSize = 2; // Size of the hand to draw

	int playerHandSize = startingHandSize; // Initialize hand size
	Card* playerHand = drawHand(&deck, deckSize, playerHandSize); // Draw a hand of 3 cards from the deck
	int playerScore = getScore(playerHand, playerHandSize); // Calculate initial player score

	int dealerScore = 0;
	int dealerHandSize = startingHandSize; // Initialize dealer hand size
	Card* dealerHand = drawHand(&deck, deckSize, dealerHandSize); // Draw a hand of 2 cards for the dealer
	dealerScore = getScore(dealerHand, dealerHandSize); // Calculate initial dealer score

	getchar(); // Wait for user input before showing hands
	cout << "\nYour hand and score are: \n" << endl;
	showHand(playerHand, playerHandSize); // Show the initial hand
	cout << "\n" << playerScore << "\n" << endl;

	// Loop drawcard until player goes bust
	bool bust = false;
	while (!bust) {

		int move;
		cout << "?????????????????????? What do you wish to do? ???????????????????????\n\n1: Draw Card\n2: Pass" << endl;
		cin >> move;

		switch (move)
		{
		case 1: // Draw Card
		{
			cout << "\nYou chose to draw a card.\n" << endl;
			drawCard(&playerHand, playerHandSize, &deck, deckSize); // Draw a card from the deck
			showHand(playerHand, playerHandSize); // Show the updated hand
			playerScore = getScore(playerHand, playerHandSize); // Update player score
			cout << "\n" << playerScore << "\n" << endl;
			//getchar();
			if (playerScore > 21) {
				cout << "!!!!!!!!!!!!!!!!!!!!!! You busted! Dealer wins. !!!!!!!!!!!!!!!!!!!!!!\n" << endl;
				bust = true; // End game
			}
			break;
		}
		case 2: // Pass, dealer's turn
		{
			cout << "You passed with a score of: " << playerScore << endl;
			getchar(); // Wait for user input before dealer's turn

			cout << "\n-------------------- Now it's the dealer's turn ----------------------\n" << endl;

			cout << "Dealer's hand is:\n" << endl;
			showHand(dealerHand, dealerHandSize); // Show dealer's hand
			showScore(dealerHand, dealerHandSize); // Show dealer's score

			while (dealerScore <= 16) { // Dealer must draw until score is at least 17
				cout << "\nDealer draws a card\n" << endl;
				drawCard(&dealerHand, dealerHandSize, &deck, deckSize); // Draw a card for the dealer
				dealerScore = getScore(dealerHand, dealerHandSize); // Update dealer score
				showHand(dealerHand, dealerHandSize); // Show updated dealer hand
				showScore(dealerHand, dealerHandSize); // Show dealer score
			}

			cout << "\nYour score: " << playerScore << "\nDealer's score: " << dealerScore << endl;
			
			cout << endl;
			if (playerScore > dealerScore) {
				cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ You win! $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
			}
			else if (dealerScore > playerScore && dealerScore <= 21) {
				cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!! Dealer wins! !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;
			}
			else if (dealerScore > 21) {
				cout << "$$$$$$$$$$$$$$$$$$$$$$ Dealer busted! You win! $$$$$$$$$$$$$$$$$$$$$$$\n" << endl;
			}
			else if (playerScore == dealerScore) {
				cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!! It's a tie! !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << endl;
			}
			bust = true; // End game after dealer's turn
			break;
		}
		default:
			/*
			cout << "Restart game? \n1: Yes\n0: No" << endl;
			int restart;
			cin >> restart;
			if (restart == 1) {
				Blackjack(); // Restart the game
			}
			else {
				cout << "Thank you for playing. Goodbye!" << endl;
				return 0; // Exit the game
			}
			*/
			return 0;
		};
	};
	cout << "Restart game? \n\n1: Yes\n0: No" << endl;
	int restart;
	cin >> restart;
	if (restart == 1) {
		Blackjack(); // Restart the game
	}
	else {
		cout << "Thank you for playing. Goodbye!" << endl;
		return 0; // Exit the game
	}
	delete[] deck;
	delete[] playerHand;
	delete[] dealerHand; // Clean up memory for the decks and hands

	return 0;
}

//More games
int Poker() {
	cout << "Poker is not implemented yet." << endl;
	return 0; // Placeholder for future implementation
}

int War() {
	cout << "War is not implemented yet." << endl;
	return 0; // Placeholder for future implementation
}

int MagicTrick() {
	cout << "Magic Trick is not implemented yet." << endl;
	return 0; // Placeholder for future implementation
}

int main () {

	srand((unsigned int)time(nullptr));  // C++11 style seed the random number generator with current time

	cout << "Welcome to the Console Application: Playing Around!" << endl;
	cout << "\nWe are going to be playing some card games!" << endl;

	bool quit = false; // Variable to control the game loop
	while (!quit) {
		cout << "\nPlease select a game to play:\n\n 1: Blackjack\n 2: Poker\n 3: War\n 4: Magic Trick\n 0: Quit" << endl;
		int game;
		cin >> game;
		switch (game)
		{
		case 1: // Blackjack
		{
			Blackjack();
			break;
		}
		case 2: // Poker
		{
			Poker();
			break;
		}
		case 3: // War
		{
			War();
			break;
		}
		case 4: // Magic Trick
		{
			MagicTrick();
			break;
		}
		case 0: // Quit
		{
			cout << "\nThank you for playing. Goodbye!" << endl;
			quit = true; // Set quit to true to exit the loop
			break;
		}
		default:
			cout << "\nInvalid game selection" << endl;
			//quit = true; // Set quit to true to exit the loop
			break;
		};
	};
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

//srand(time(0)); // Seed the random number generator

