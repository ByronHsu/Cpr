/****************************************************************************
  FileName   [ CprPlayer.cpp ]
  Author     [ Haowei Luan ]
  Synopsis   [ implement CprPlayer member functions ]
****************************************************************************/

#include "CprPlayer.h"
#include "CprHandMaster.h"
#include "CprHand.h"


CprPlayer::CprPlayer() {
	_score = 0;
}

CprPlayer::~CprPlayer() {
}

void CprPlayer::strategy() {
	// Note: please define CprCollection::finishSetting such that
	// all hands' type are determined, by calling CprHandMaster::DetermineType
	_collection.resetAllHands();
	playerStrategy();

	CprHandMaster::DetermineType(collection().hand(0));
	CprHandMaster::DetermineType(collection().hand(1));
	CprHandMaster::DetermineType(collection().hand(2));

}

void CprPlayer::setId(string str) {
	_id = str;
}

CprHand& CprPlayer::hand(int idx) {
	return _collection.hand(idx);
}

CprCollection & CprPlayer::collection() {
	return _collection;
}

const CprCollection & CprPlayer::collection() const {
	return _collection;
}
