#include "CprGreedyAi.h"

CprGreedyAi::CprGreedyAi() {
}

CprGreedyAi::~CprGreedyAi() {
}

void CprGreedyAi::playerStrategy() {
    //_collection.resetAllHands();
    //_collection.printByRank();
	CprHandMaster master;
	CprHand h1=master.GetBestHand(_collection);
	_collection.settingHand(2, h1._cards);
	//_collection._hands[2].print();
	CprHand h2=master.GetBestHand(_collection);
	_collection.settingHand(1, h2._cards);
	//_collection._hands[1].print();
	CprHand h3=master.GetBestHand(_collection);
	_collection.settingHand(0, h3._cards);
	//_collection._hands[0].print();

}
