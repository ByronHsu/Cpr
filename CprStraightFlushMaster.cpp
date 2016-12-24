/****************************************************************************
FileName   [ CprStraightFlushMaster.h ]
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

bool CprStraightFlushMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	int num1,num2;
	num1=h1.getCard(4).rankA();
	num2=h2.getCard(4).rankA();
	if(num1>num2)
		return false;
	else{
		return true;
	}
}
bool CprStraightFlushMaster::determineMe(CprHand& hand) {
	if(hand.size()==3)
		return false;
	else{
		CardList newlist;
		hand.computeACR();
		CardList _ACR[15];

		for(int i=0;i<15;i++){
			_ACR[i]=hand.getACR()[i];
		}
		//10JQKA > 910JQK > ... > 23456 > A2345
		for(int i=10;i>=1;i--){
			for(int ii=0;ii<_ACR[i].size();ii++){
				int nowsuit=_ACR[i][ii].suit();
				for(int j=0;j<=4;j++){
					int index=i+j;
					if(i+j>13)
						index%=13;
					if(_ACR[index].size()==0){
						break;
					}
					else{
						bool b=0;
						for(int jj=0;jj<_ACR[index].size();jj++){
							if(_ACR[index][jj].suit()==nowsuit)
								b=1;
						}
					
						if(b==0)
							break;
						//success
						if(j==4){
						
							for(int k=0;k<=4;k++){
								int index2=i+k;
								if(i+k>13)
									index%=13;
								for(int kk=0;kk<_ACR[index2].size();kk++)
									if(_ACR[index2][kk].suit()==nowsuit)
										newlist.push_back(_ACR[index2][kk]);
							}
							hand=newlist;
							return true;
						}
					}

				}
			}
			
		}
		return false;
	}
}

bool CprStraightFlushMaster::containsMe(const CprCollection& col, CprHand& res) {
	CardList newlist;
	CardList _ACR[15];

	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	//10JQKA > 910JQK > ... > 23456 > A2345
	for(int i=10;i>=1;i--){
		for(int ii=0;ii<_ACR[i].size();ii++){
			int nowsuit=_ACR[i][ii].suit();
			for(int j=0;j<=4;j++){
				int index=i+j;
				if(i+j>13)
					index%=13;
				if(_ACR[index].size()==0){
					break;
				}
				else{
					bool b=0;
					for(int jj=0;jj<_ACR[index].size();jj++){
						if(_ACR[index][jj].suit()==nowsuit)
							b=1;
					}
				
					if(b==0)
						break;
					//success
					if(j==4){
					
						for(int k=0;k<=4;k++){
							int index2=i+k;
							if(i+k>13)
								index%=13;
							for(int kk=0;kk<_ACR[index2].size();kk++)
								if(_ACR[index2][kk].suit()==nowsuit)
									newlist.push_back(_ACR[index2][kk]);
						}
						res=newlist;
						return true;
					}
				}

			}
		}
		
	}
	return false;
}
bool CprStraightFlushMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res) {
	CardList newlist;
	CardList _ACR[15];

	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	//10JQKA > 910JQK > ... > 23456 > A2345
	for(int i=10;i>=1;i--){
		for(int ii=0;ii<_ACR[i].size();ii++){
			int nowsuit=_ACR[i][ii].suit();
			for(int j=0;j<=4;j++){
				int index=i+j;
				if(i+j>13)
					index%=13;
				if(_ACR[index].size()==0){
					break;
				}
				else{
					bool b=0;
					for(int jj=0;jj<_ACR[index].size();jj++){
						if(_ACR[index][jj].suit()==nowsuit)
							b=1;
					}
				
					if(b==0)
						break;
					//success
					if(j==4){
					
						for(int k=0;k<=4;k++){
							int index2=i+k;
							if(i+k>13)
								index%=13;
							for(int kk=0;kk<_ACR[index2].size();kk++)
								if(_ACR[index2][kk].suit()==nowsuit)
									newlist.push_back(_ACR[index2][kk]);
						}
						CprHand newhand(newlist);
						if(!compareDeeply(uppHand,newhand)){
							res=newhand;
							return 1;
						}
						newlist.clear();
					}
				}

			}
		}
		
	}
	return false;
}