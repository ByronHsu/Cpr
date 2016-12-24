/****************************************************************************
FileName   [ CprOnePairMaster.h ]
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

bool CprOnePairMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int now_size=min(h1.size(),h2.size());
	for(int i=0;i<now_size;i++){
		if(i!=1){
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
bool CprOnePairMaster::determineMe(CprHand& hand) {
	CardList newlist;
	hand.computeACR();
	CardList _ACR[15];
	for(int i=0;i<15;i++){
		_ACR[i]=hand.getACR()[i];
	}
	int numof2=0;

	for(int i=2;i<=14;i++){
		if(numof2&&_ACR[i].size()>1){
			return false;
		}
		if(_ACR[i].size()==2)
			numof2=i;
	}
	if(numof2==0)
		return false;
	for(int i=0;i<_ACR[numof2].size();i++)
		newlist.push_back(_ACR[numof2][i]);
	for(int i=14;i>=2;i--){
		if(i!=numof2&&_ACR[i].size()==1){
			newlist.push_back(_ACR[i][0]);
		}
	}
	CprHand newhand(newlist);
	hand=newhand;
	return true;

}

bool CprOnePairMaster::containsMe(const CprCollection& col, CprHand& res) {
	CardList _ACR[15];
	CardList newlist;
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	bool has2num=0;
	for(int i=14;i>=2;i--){
		if(_ACR[i].size()==2){
			has2num=1;
			for(int j=0;j<2;j++)
				newlist.push_back(_ACR[i][j]);
			break;
		}
	}
	if(!has2num)
		return false;
	for(int i=14;i>=2;i--){
		if(_ACR[i].size()==1){
			newlist.push_back(_ACR[i][0]);
		}
		if(newlist.size()==5){
			break;
		}
	}
	CprHand newhand(newlist);
	res=newhand;
	return true;
}
//Done
bool CprOnePairMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res) {
	CardList _ACR[15];
	CardList newlist;
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}

	for(int i=14;i>=2;i--){
		if(_ACR[i].size()==2){
			for(int j=0;j<2;j++)
				newlist.push_back(_ACR[i][j]);
			for(int j1=14;j1>=2;j1--){
				if(_ACR[j1].size()==1){
					newlist.push_back(_ACR[j1][0]);
					for(int j2=j1-1;j2>=2;j2--){
						if(_ACR[j2].size()==1){
							newlist.push_back(_ACR[j2][0]);
							for(int j3=j2-1;j3>=2;j3--){
								if(_ACR[j3].size()==1){
									newlist.push_back(_ACR[j3][0]);
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
			newlist.pop_back();
		}

	}

	return 0;
}