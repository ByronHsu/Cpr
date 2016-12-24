/****************************************************************************
FileName   [ CprFullHouseMaster.h ]
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

bool CprFullHouseMaster::compareDeeply(const CprHand& h1, const CprHand& h2) {
	//if h2>h1 return false
	int three_num1,three_num2,two_num1,two_num2;
	three_num1=h1.getCard(0).rankA();
	three_num2=h2.getCard(0).rankA();
	two_num1=h1.getCard(3).rankA();
	two_num2=h2.getCard(3).rankA();
	if(three_num1>three_num2){
		return 0;
	}
	else{
		if(three_num1==three_num2){
			if(two_num1>two_num2)
				return 0;
		}
	}
	return 1;
}
bool CprFullHouseMaster::determineMe(CprHand& hand) {
	if(hand.size()==3)
		return false;
	else{
		int three_num,two_num;//3排前面
		CardList three_numlist,two_numlist;
		//size=5
		hand.computeACR();
		CardList _ACR[15];

		for(int i=0;i<15;i++){
			_ACR[i]=hand.getACR()[i];
		}

		for(int i=1;i<=13;i++){
			//cout<<i<<"size="<<_ACR[i].size()<<endl;
			if(_ACR[i].size()==3){
				three_num=i;
				for(int j=0;j<3;j++){
					three_numlist.push_back(_ACR[i][j]);
				}
			}
			else
				if(_ACR[i].size()>=2){
					two_num=i;
					for(int j=0;j<2;j++){
						two_numlist.push_back(_ACR[i][j]);
					}				
				}
				else{
					if(_ACR[i].size()!=0)
						return false;
				}
		}
		CardList newlist;
		//cout<<"test"<<endl;
		for(int j=0;j<3;j++){
			newlist.push_back(three_numlist[j]);
		}
		//cout<<"pass"<<endl;
		for(int j=0;j<2;j++){
			newlist.push_back(two_numlist[j]);
		}		
		CprHand newhand(newlist);
		hand=newhand;//更新
		return true;
	}
}

bool CprFullHouseMaster::containsMe(const CprCollection& col, CprHand& res) {
	
	//開兩個vector 一個存 大於等於三張的所有數字 一個存 大於等於兩張的所有數字
	//把最大的那個數字從three_vector取出 如果他是two_vector的頭的話 取two_vector的第二個
	CardList _ACR[15];
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}
	vector<int> three_vector,two_vector;

	for(int i=2;i<=14;i++){
		if(_ACR[i].size()>=3){
			three_vector.push_back(i);
			two_vector.push_back(i);
		}else{
			if(_ACR[i].size()>=2){
				two_vector.push_back(i);
			}
		}
	}
	if((three_vector.size()==0)||(three_vector.size()==1&&two_vector.size()==1))
		return false;
	sort(three_vector.begin(),three_vector.end(),greater<int>());
	sort(two_vector.begin(),two_vector.end(),greater<int>());
	int three_num,two_num;
	three_num=three_vector[0];
	if(three_vector[0]==two_vector[0]){
		two_num=two_vector[1];
	}
	else{
		two_num=two_vector[0];
	}
	CardList newlist;
	//cout<<"test"<<endl;
	for(int j=0;j<3;j++){
		newlist.push_back(_ACR[three_num][j]);
	}
	//cout<<"test2"<<endl;
	for(int j=0;j<2;j++)
		newlist.push_back(_ACR[two_num][j]);
	CprHand newhand(newlist);
	res=newhand;
	return true;
}

bool CprFullHouseMaster::containsMeUnder(const CprCollection& col, const CprHand& uppHand, CprHand& res) {
	CardList _ACR[15];
	CardList newlist;
	for(int i=0;i<15;i++){
		_ACR[i]=col.getACR()[i];
	}

	for(int i1=14;i1>=2;i1--){
		if(_ACR[i1].size()==3){
			for(int j=0;j<3;j++)
				newlist.push_back(_ACR[i1][j]);
			for(int i2=14;i2>=2;i2--){
				if(_ACR[i2].size()>=2){
					for(int j=0;j<2;j++)
						newlist.push_back(_ACR[i2][j]);
					CprHand newhand(newlist);
					if(!compareDeeply(uppHand,newhand)){
						res=newhand;
						return 1;
					}
					newlist.pop_back();
					newlist.pop_back();		
				}
			}
			newlist.pop_back();
			newlist.pop_back();
			newlist.pop_back();
		}

	}

	return 0;	
}