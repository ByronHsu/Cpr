/****************************************************************************
  FileName   [ CprStage.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement each phase in a single stage ]
****************************************************************************/

#include "CprStage.h"
#include "CprPlayer.h"
#include "CprDealer.h"
#include "CprHand.h"
#include<cstdio>
#include<iomanip>
#include<string>

void print_type(int num){
	if(num==10)
		cout<<"StraightFlush"<<endl;
	if(num==9)
		cout<<"FourOfAKind"<<endl;
	if(num==8)
		cout<<"FullHouse"<<endl;
	if(num==7)
		cout<<"Flush"<<endl;
	if(num==6)
		cout<<"Straight"<<endl;
	if(num==5)
		cout<<"ThreeOfAKind"<<endl;
	if(num==4)
		cout<<"TwoPair"<<endl;
	if(num==3)
		cout<<"OnePair"<<endl;
	if(num==2)
		cout<<"HighCard"<<endl;
	if(num==1)
		cout<<"Xianggong"<<endl;
	if(num==0)
		cout<<"Undefined"<<endl;
}
CprStage::CprStage(int t,vector<CprPlayer *>& players, int id)
	: _players(players), _stageId(id) {
	    T=t;
}

CprStage::~CprStage() {
}

void CprStage::start() {
	if(!T)
	cout<<endl;
	if(!T)
	cout << "== Stage " << _stageId << " start!" << endl;
	dealingPhase();
	strategyPhase();
	checkXianggongPhase();
	comparisonPhase();
	shootingPhase();
	printScores();
	if(!T)
	cout << "== Stage " << _stageId << " end" << endl << endl;
	if(!T)
	cout << endl;
}

void CprStage::dealingPhase() {
	// TODO: call CprDealer to distribute cards to players
	/*
		e.g.
		CprDealer dealer;
	 	dealer.deal(_players);
	*/
	CprDealer Dealer;
	Dealer.deal(_players);

}

void CprStage::strategyPhase() {
	// DONE
	for (unsigned i = 0; i < _players.size(); ++i) {
		CprPlayer *py = _players.at(i);
		py->strategy();
	}
}

void CprStage::checkXianggongPhase() {
	//DONE
	//cout<<"xx"<<endl;
	vector<CprPlayer*>::iterator it=_players.begin();
	for (;it < _players.end();it++) {
		if (!CprHandMaster::Compare((*it)->hand(0), (*it)->hand(1)) || !CprHandMaster::Compare((*it)->hand(1), (*it)->hand(2))) {
			cout<<"Xianggong Alert"<<endl;
			((*it)->hand(0)).print();
			((*it)->hand(1)).print();
			((*it)->hand(2)).print();
			((*it)->hand(0)).setXianggong();
			((*it)->hand(1)).setXianggong();
			((*it)->hand(2)).setXianggong();
			getchar();
			getchar();
		}
	}
	//cout<<"xxok"<<endl;
}

void CprStage::comparisonPhase() {
	CprHandMaster master;
	// TODO: compare players' hands and print them with tricks num
	for(int i=0;i<=3;i++){
		for(int j=0;j<3;j++)
			_players[i]->hand(j).Handsort();
	}
	for (int ridx = 1; ridx <= 3; ++ridx) {
	if(!T)
		cout<<endl;
	if(!T)
		cout << "= Round " << ridx << ".." << endl;
		for(int player=0;player<=3;player++){
			int pg=0;
			for(int pnum=0;pnum<=3;pnum++){
				if(player==pnum)continue;
				if(_players[player]->hand(ridx-1)<=_players[pnum]->hand(ridx-1))pg--;
				if(_players[player]->hand(ridx-1)>=_players[pnum]->hand(ridx-1))pg++;
			}
            if(!T)
			cout<<setw(8)<<_players[player]->_id<<":";
			if(!T)
			_players[player]->hand(ridx-1).print();
            if(!T)
			cout<<"type:";
			if(!T)
			print_type(_players[player]->hand(ridx-1)._type);
            if(!T)
			cout<<"score:"<<pg<<endl;
			_players[player]->_score+=pg;
		}
	}
}

void print_rank(int rank){
	switch(rank){
		case 3:
			cout<<" (1st)";
			break;
		case 2:
			cout<<" (2nd)";
			break;
		case 1:
			cout<<" (3rd)";
			break;
		case 0:
			cout<<" (4th)";
			break;
	}
}

void CprStage::shootingPhase() {
	// TODO: check if someone shoots another
    if(!T)
	cout<<endl;
    if(!T)
	cout << "= Check shooting.." << endl;
	for(int player=0;player<=3;player++){
		for(int player2=0;player2<=3;player2++){
			if(player==player2)continue;
			if(_players[player]->hand(0)>_players[player2]->hand(0)
				&&_players[player]->hand(1)>_players[player2]->hand(1)
				 &&_players[player]->hand(2)>_players[player2]->hand(2))
			{
                if(!T)
				cout<<_players[player]->_id<<"<+3> shoots "<<_players[player2]->_id<<"<-3>"<<endl;
				_players[player]->_score+=3;
				_players[player2]->_score-=3;
			}
		}
	}
}


void CprStage::printScores() const {
	// TODO: print all players' scores
    if(!T)
	cout<<endl;
    if(!T)
	cout << "== Stage "<< _stageId << " scores.." << endl;
	for(int player=0;player<=3;player++){
        if(!T)
		cout<<_players[player]->_id<<" "<<setw(23-(_players[player]->_id).length())<<setw(4)<<_players[player]->_score;
		int sum = 0;
		for(int i = 0; i <= 3; i++){
			if(_players[player] -> _score >= _players[i] -> _score && i != player)
				sum += 1;
		}
		if(!T)
		print_rank(sum);
		if(!T)
		cout<<endl;
	}
    if(!T)
	cout<<endl;
    if(!T)
	cout<<"Press Enter To Continue"<<endl;
    if(!T)
	getchar();
}



















