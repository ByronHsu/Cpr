#include "CprStupidAi.h"

CprStupidAi::CprStupidAi() {
}

CprStupidAi::~CprStupidAi() {
}

void CprStupidAi::playerStrategy() {
	// Note: It's just an example showing you how to create Cpr*Ai 
	// by implementing Cpr*Ai::playerStrategy

    _collection.resetAllHands();

	const CardList& availCards = _collection.getAvailableCards();
	CardList cards1 = CardList(availCards.begin(), availCards.begin() + 3);
		// set the 1st hand by the first 3 available cards
	CardList cards2 = CardList(availCards.begin() + 3, availCards.begin() + 8);
	CardList cards3 = CardList(availCards.begin() + 8, availCards.end());
		// set the 3rd hand by the last  5 available cards
	_collection.settingHand(0, cards1);
	_collection.settingHand(1, cards2);
	_collection.settingHand(2, cards3);

}
