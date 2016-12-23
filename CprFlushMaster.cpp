/****************************************************************************
FileName   [ CprFlushMaster.h ]
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

bool CprFlushMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	for(int i=0;i<5;i++){
		if(h1.getCard(i).rankA()>h2.getCard(i).rankA()){
			return false;
		}
		if(h1.getCard(i).rankA()<h2.getCard(i).rankA()){
			return true;
		}
	}
	return true;
}
bool CprFlushMaster::determineMe(CprHand& hand) {
	CardList newlist;
	CardList _ACR[15];
	hand.computeACR();
	for(int i=0;i<15;i++){
		_ACR[i]=hand.getACR()[i];
	}
	int successhead=0;
	for(int i=14;i>=2;i--){
		if(i<successhead)
			break;
		for(int ii=0;ii<_ACR[i].size();ii++){
			int nowsuit=_ACR[i][ii].suit();
			newlist.push_back(_ACR[i][ii]);
			int nownumcount=1;
			for(int j=i-1;j>=2;j--){
				for(int jj=0;jj<_ACR[j].size();jj++){
					if(_ACR[j][jj].suit()==nowsuit){
						newlist.push_back(_ACR[j][jj]);
						nownumcount++;
					}
				if(nownumcount==5){
					successhead=i;
					CprHand newhand(newlist);
					hand=newhand;
					return 1;
				}
				}
			}
			newlist.clear();
		}
	}
	return 0;
}

bool CprFlushMaster::containsMe(const CprCollection& col, CprHand& res) {
	CardList newlist;
	CardList _ACR[15];

	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	int successhead=0;
	for(int i=14;i>=2;i--){
		if(i<successhead)
			break;
		for(int ii=0;ii<_ACR[i].size();ii++){
			int nowsuit=_ACR[i][ii].suit();
			newlist.push_back(_ACR[i][ii]);
			int nownumcount=1;
			for(int j=i-1;j>=2;j--){
				for(int jj=0;jj<_ACR[j].size();jj++){
					if(_ACR[j][jj].suit()==nowsuit){
						newlist.push_back(_ACR[j][jj]);
						nownumcount++;
					}
				if(nownumcount==5){
					successhead=i;
					CprHand newhand(newlist);
					if(!res.size()||(res.size()&&!compareDeeply(newhand,res))){
						res=newhand;
					}
				}
				}
			}
			newlist.clear();
		}
	}
	if(res.size()==5)
		return 1;
	return 0;
}
bool CprFlushMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res) {

}