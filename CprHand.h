/****************************************************************************
  FileName   [ CprHand.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define a 3-card or 5-card Hand ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCard.h"
#include "CprHandType.h"
#include "CprHandMaster.h"
class CprHand
{
	FRIEND_ALL;
	friend class CprCollection;
	friend class CprStage;
	friend class CprGreedyAi;
public:
	CprHand();
	CprHand(const CardList&);
	CprHand(const CardList&, HandType);
	~CprHand();
	bool operator <= (const CprHand& hand) const;
	bool operator >= (const CprHand& hand) const;
	bool operator > (const CprHand& hand) const;
	const CardList& getCards() const;
	void setXianggong();
	void print() const;
	HandType getType() const;

	/* convenient methods */
	int size() const;
	bool empty() const;
	const CprCard getCard(int idx) const;
	const CardList* getACR() const;//new
	void computeACR();//new
	void Handsort();
	void printByRank() const;//new
	
private:
	CardList _cards;
	HandType _type;
	CardList _ACR[15];//><
	int isCardAvailable(const CprCard&) const;//new
};

