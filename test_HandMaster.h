#pragma once
#include <iostream>
#include "CprCollection.h"
using namespace std;

class CprHandMasterTest {
public:
	CprHandMasterTest() {}
	void run() {
		int type; cin >> type;
		if (type == 0) {
			readHand(5);
			readHand(5);
			readHand(3);
			determineTypes();
			compareHands();
		} else {
			readCollection();	
			getBestHand();
		}
	}
private:
	void readCollection() {
		CardList cards = readCards(13);
		std::sort(cards.begin(), cards.end());
		_col._cards = cards;
		_col._availCards = cards;
		_col.computeACR();
	}
	void readHand(int handSize) {
		CardList cards = readCards(handSize);
		if (handSize == 5) {
			if (_handA.empty()) {
				_handA._cards = cards;	
			} else {
				_handB._cards = cards;
			}
		} else {
			_smallHand._cards = cards;
		}
	}
	void determineTypes() {
		CprHandMaster::DetermineType(_handA);
		cout << CprHandMaster::TranslateType(_handA.getType()) << endl;
		CprHandMaster::DetermineType(_handB);
		cout << CprHandMaster::TranslateType(_handB.getType()) << endl;
		CprHandMaster::DetermineType(_smallHand);
		cout << CprHandMaster::TranslateType(_smallHand.getType()) << endl;
	}
	void compareHands() {
		cout << (_handB <= _handA) << endl;
		cout << (_smallHand <= _handB) << endl;
	}
	void getBestHand() {
		CprHand bestHand = CprHandMaster::GetBestHand(_col);
		CprHandMaster::DetermineType(bestHand);
		bestHand.print();
		cout << endl;
	}
	CardList readCards(int n) {
		CardList cards;
		for (int i = 0; i < n; ++i) {
			CprCard c;
			cin >> c;
			cards.push_back(c);
		}
		cin.clear();
		return cards;
	}
	CprCollection _col;
	CprHand _handA;
	CprHand _handB;
	CprHand _smallHand;
};

