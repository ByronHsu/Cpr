/****************************************************************************
FileName   [ CprThreeOfAKindMaster.h ]
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

bool CprThreeOfAKindMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	for(int i=0;i<5;i++){
		if(i!=1&&i!=2){
			if(h1.getCard(i).rankA()>h2.getCard(i).rankA()){
				return false;
			}
			if(h1.getCard(i).rankA()<h2.getCard(i).rankA()){
				return true;
			}
		}
	}
	return true;
}
bool CprThreeOfAKindMaster::determineMe(CprHand& hand) {
	CardList newlist;
	hand.computeACR();
	CardList _ACR[15];
	for(int i=0;i<15;i++){
		_ACR[i]=hand.getACR()[i];
	}
	int numof3=0;

	for(int i=2;i<=14;i++){
		if(_ACR[i].size()==3)
			numof3=i;
	}
	if(numof3==0)
		return false;
	for(int i=0;i<_ACR[numof3].size();i++)
		newlist.push_back(_ACR[numof3][i]);
	for(int i=14;i>=2;i--){
		if(i!=numof3&&_ACR[i].size()==1){
			newlist.push_back(_ACR[i][0]);
		}
	}
	CprHand newhand(newlist);
	hand=newhand;
	return true;

}

bool CprThreeOfAKindMaster::containsMe(const CprCollection& col, CprHand& res) {
	CardList newlist;
	CardList _ACR[15];
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	int numof3=0;

	for(int i=14;i>=2;i--){
		if(_ACR[i].size()==3){
			numof3=i;
			break;
		}
	}
	if(numof3==0)
		return false;
	for(int i=0;i<_ACR[numof3].size();i++)
		newlist.push_back(_ACR[numof3][i]);
	for(int i=14;i>=2;i--){
		if(i!=numof3&&_ACR[i].size()==1){
			newlist.push_back(_ACR[i][0]);
		}
		if(newlist.size()==5)
			break;
	}
	CprHand newhand(newlist);
	res=newhand;
	return true;
}
bool CprThreeOfAKindMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res) {

}