/****************************************************************************
FileName   [ CprHighCardMaster.h ]
Author     [ Haowei Luan ]
Synopsis   [ implement HighCard master ]
****************************************************************************/

#include "CprEachMaster.h"
#include "CprCollection.h"
#include "CprHand.h"

// comparison function (to sort from high to low)
// static global function means that it's only visible in current file
// (which is a totally different concept from static member function)
static bool card_greater(const CprCard& c1, const CprCard& c2) {
	if (c1 <= c2 && c2 <= c1) {
		assert(c1.rank() == c2.rank());
		return c1.suit() < c2.suit();
	} else {
		return !(c1 <= c2);
	}
}

bool CprHighCardMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int h1Score = 0, h2Score = 0;
	for (int i = 0; i < h1.size(); ++i) {
		h1Score += h1.getCard(i).rankA() << 4 * (4 - i);
			// equivalent to h1Score += h1.getCard(i).rankA() * pow(2, 4 * (4 - i));
		h2Score += h2.getCard(i).rankA() << 4 * (4 - i);
	}
	return h1Score <= h2Score;
}
bool CprHighCardMaster::determineMe(CprHand& hand) {
	std::sort(hand._cards.begin(), hand._cards.end(), card_greater);
	return true;
}

bool CprHighCardMaster::containsMe(const CprCollection& col, CprHand& res) {
	CardList _ACR[15];
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	CardList newlist;
	for(int i=14;i>=2;i--){
		if(_ACR[i].size()){
			for(int j=0;j<_ACR[i].size();j++){
				newlist.push_back(_ACR[i][j]);
				if(newlist.size()==5){
					res=newlist;
					return 1;
				}
			}
		}
	}
}

bool CprHighCardMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res) {
	/*
	CardList cards = col.getAvailableCards();
	std::sort(cards.begin(), cards.end(), card_greater);
	int handSize = (col._cards.size() < 5) ? 3 : 5;
	res._cards.insert(res._cards.end(), cards.begin(), cards.begin() + handSize);
	res._type = HTHighCard;
	return true;
	*/
}