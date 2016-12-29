/****************************************************************************
  FileName   [ CprDealer.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define/implement a dealer in dealing phase ]
****************************************************************************/

#pragma once
#include "CprCollection.h"
#include "CprPlayer.h"


class RandCardFiller {
public:
    RandCardFiller() {
        //srand(time(0));
    }
    void fill(CprCard* cards) {   
        // TODO: given an CprCard array with size 52
        // Fill in it with 52 different cards randomly
        bool b[53]={0};
        b[0]=1;
        for(int i=0;i<52;i++){
            int index=0;
            while(b[index]){
                index=rand()%52+1;
            }
            b[index]=1;
            CprCard c(index);
            cards[i]=c;
        }
    }
 
/*
    You might need to define some data members to help you
*/
};
class CprDealer
{
public:
	CprDealer() {}
	~CprDealer() {}

	void deal(PlayerList& players) {
        for(int i=0;i<4;i++){
            players[i]->_collection._availCards.clear();
            players[i]->_collection._cards.clear();
        }
		CprCard cards[52];
		RandCardFiller filler;
		filler.fill(cards);
		for (int i = 0; i < 52; ++i) {
			(players[i%4]->_collection)._cards.push_back(cards[i]);
			(players[i%4]->_collection)._availCards.push_back(cards[i]);
		}

		for (int j = 0; j < 4; ++j) {
			std::sort((players[j]->_collection)._cards.begin(), (players[j]->_collection)._cards.end());
			std::sort((players[j]->_collection)._availCards.begin(), (players[j]->_collection)._availCards.end());
			(players[j]->_collection).computeACR();
		}

	}
};

