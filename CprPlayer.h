/****************************************************************************
  FileName   [ CprPlayer.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define CprPlayer class ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCollection.h"
#include "CprStage.h"

class CprPlayer
{
    friend class CprGame;
	friend CprDealer;
	friend CprStage;
public:
	CprPlayer();
	~CprPlayer();
	void strategy();
	void setId(string);
	CprHand & hand(int idx);
	int& getScore() { return _score; }


protected:
	CprCollection _collection;
	CprCollection& collection();
	const CprCollection& collection() const;
	string _id;

private:
	int _score;
	virtual void playerStrategy() = 0;
};

