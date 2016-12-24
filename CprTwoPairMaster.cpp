/****************************************************************************
FileName   [ CprTwoPairMaster.h ]
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

bool CprTwoPairMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int now_size=min(h1.size(),h2.size());
	for(int i=0;i<now_size;i++){
		if(i!=1&&i!=3){
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
bool CprTwoPairMaster::determineMe(CprHand& hand) {
	CardList newlist;
	hand.computeACR();
	CardList _ACR[15];
	for(int i=0;i<15;i++){
		_ACR[i]=hand.getACR()[i];
	}
	int numof2[2]={0};
	int numof2count=0;
	int index=0;
	for(int i=14;i>=2;i--){
		if(_ACR[i].size()==2)
			{
				numof2[index++]=i;
				numof2count++;
			}
	}

	if(numof2count<2)
		return false;
	for(int i=0;i<_ACR[numof2[0]].size();i++)
		newlist.push_back(_ACR[numof2[0]][i]);
	for(int i=0;i<_ACR[numof2[1]].size();i++)
		newlist.push_back(_ACR[numof2[1]][i]);

	for(int i=14;i>=2;i--){
		if(_ACR[i].size()>=1){
			newlist.push_back(_ACR[i][0]);
		}
	}
	CprHand newhand(newlist);
	hand=newhand;
	return true;

}

bool CprTwoPairMaster::containsMe(const CprCollection& col, CprHand& res) {
	CardList newlist;
	CardList _ACR[15];
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	int numof2[2]={0};
	int numof2count=0;
	int index=0;
	for(int i=14;i>=2;i--){
		if(_ACR[i].size()>=2)
			{
				numof2[index++]=i;
				numof2count++;
			}
		if(numof2count==2)
			break;
	}
	if(numof2count<2)
		return false;
	for(int i=0;i<2;i++)
		newlist.push_back(_ACR[numof2[0]][i]);
	for(int i=0;i<2;i++)
		newlist.push_back(_ACR[numof2[1]][i]);

	for(int i=14;i>=2;i--){
		if(_ACR[i].size()>=1){
			newlist.push_back(_ACR[i][0]);
		}
		if(newlist.size()==5)
			break;
	}
	CprHand newhand(newlist);
	res=newhand;
	return true;
}
bool CprTwoPairMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res) {
	CardList _ACR[15];
	CardList newlist;
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}

	for(int i1=14;i1>=2;i1--){
		if(_ACR[i1].size()==2){
			for(int j=0;j<2;j++)
				newlist.push_back(_ACR[i1][j]);
			for(int i2=i1-1;i2>=2;i2--){
				if(_ACR[i2].size()==2){
					for(int j=0;j<2;j++)
						newlist.push_back(_ACR[i2][j]);
					for(int i3=14;i3>=2;i3--){
						if(_ACR[i3].size()>=1){
							newlist.push_back(_ACR[i3][0]);
							CprHand newhand(newlist);
							if(!compareDeeply(uppHand,newhand)){
								res=newhand;
								return 1;
							}
							newlist.pop_back();						
						}
					}
					newlist.pop_back();
					newlist.pop_back();		
				}
			}
			newlist.pop_back();
			newlist.pop_back();
		}

	}

	return 0;
}