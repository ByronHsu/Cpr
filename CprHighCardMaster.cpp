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
	CardList _ACR[15];
	CardList newlist;
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}

	for(int i1=14;i1>=2;i1--){
		if(_ACR[i1].size()){
			for(int j=0;j<1;j++)
				newlist.push_back(_ACR[i1][j]);
			for(int i2=i1-1;i2>=2;i2--){
				if(_ACR[i2].size()){
					for(int j=0;j<1;j++)
						newlist.push_back(_ACR[i2][j]);
					for(int i3=i2-1;i3>=2;i3--){
						if(_ACR[i3].size()){
							for(int j=0;j<1;j++)
								newlist.push_back(_ACR[i3][j]);
							for(int i4=i3-1;i4>=2;i4--){
								if(_ACR[i4].size()){
									for(int j=0;j<1;j++)
										newlist.push_back(_ACR[i4][j]);
									for(int i5=i4-1;i5>=2;i5--){
										if(_ACR[i5].size()){
											for(int j=0;j<1;j++)
												newlist.push_back(_ACR[i5][j]);
											CprHand newhand(newlist);
											if(!compareDeeply(uppHand,newhand)){
												res=newhand;
												return 1;
											}
											newlist.pop_back();	
										}
									}
									newlist.pop_back();	
								}
							}
							newlist.pop_back();	
						}
					}
					newlist.pop_back();	
				}
			}
			newlist.pop_back();
		}
	}

	return 0;
}