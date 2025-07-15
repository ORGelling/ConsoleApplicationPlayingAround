/*
#include <iostream>
#include <cstdlib>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct Card {
	string name;
	int value;
	int presence;
};

Card* createDeck() {
	// Define deck
	string standardDeck[52] = {
			"2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH", "AH",
			"2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD", "AD",
			"2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC", "AC",
			"2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS", "AS"
	};

	int deckPoints[52] = {
		2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10, // Hearts
		2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10, // Diamonds
		2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10, // Clubs
		2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10  // Spades
	};

	Card* deck = new Card[52];

	for (int i = 0; i < 52; i++) {
		deck[i].name = standardDeck[i];
		deck[i].value = deckPoints[i];
		deck[i].presence = 1; // Initialize all cards as present in the deck
	}

	return deck;
};

int main() {
	Card* deck = createDeck();
	for (int i = 0; i < 52; i++) {
		cout << deck[i].name << " " << deck[i].value << " " << deck[i].presence << endl;
	}
	delete[] deck; // Clean up memory after use
};

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Card {
	string name;
	int value;
	};

class Deck {
private:
	Card* deck;
	int totalCards;
	int currentIndex;
	int cutPoint;
	int numDecks;

public:
	Deck(int numDecks = 6) {
		this->numDecks = numDecks;
		totalCards = 52 * numDecks;
		deck = new Card[totalCards];
		currentIndex = 0;
		buildDeck();
		shuffleDeck();
		cutPoint = totalCards * 75 / 100; // Cut point at 75% 
		burnCards();
	}
	
	~Deck() {
		delete[] deck;
	}    
	void buildDeck() {
		const char* suits[] = {"H", "D", "C", "S"};
		const char* values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
		int points[] = {2,3,4,5,6,7,8,9,10,10,10,10,10};
		int index = 0;
		for (int d = 0; d < numDecks; ++d) {
			for (int s = 0; s < 4; ++s) {
				for (int v = 0; v < 13; ++v) {
					deck[index].name = string(values[v]) + suits[s];
					deck[index].value = points[v];
					++index;
				}
			}
		}
	}

	void shuffleDeck() {
		srand(time(0));
		for (int i = totalCards - 1; i > 0; --i) {
			int j = rand() % (i + 1);
			swap(deck[i], deck[j]);
		}
		currentIndex = 0;
		cutPoint = totalCards * 75 / 100;
	}

	void burnCards() {
		int burnCount = rand() % 5 + 1; // 1-5 kaarten weggooien, cuz trash
		currentIndex += burnCount;
		cout << "[Casino] Burned " << burnCount << " cards at shuffle.\n";
	}

	Card drawCard() {
		if (currentIndex >= cutPoint) {
			cout << "[Casino] Cut card reached. Reshuffling...\n";
			shuffleDeck();
			burnCards();
		}
		return deck[currentIndex++];
	}
	
	int cardsLeft() const {
		return totalCards - currentIndex;
	}
};

int main() {
	Deck deck(6); // Realistisch casino gebruikt 6 decks, maar die halen ze toch nooit lol
		for (int i = 0; i < 260; ++i) {
			Card c = deck.drawCard();
			cout << "Draw " << i + 1 << ": " << http://c.name << " (" << c.value << ") - "
			<< deck.cardsLeft() << " cards left\n";
		}    
	return 0;}

*/