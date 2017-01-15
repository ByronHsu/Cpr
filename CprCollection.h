/****************************************************************************
  FileName   [ CprCollection.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define cards held by players ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprHand.h"
class CprCollection
{
	FRIEND_ALL;
	friend class CprHanmoOuJrAi;
	friend class CprStage;
	friend class CprGame;
	friend class CprStupidAi;
	friend class CprGreedyAi;
	friend class CprHandMaster;
public:
	CprCollection();
	~CprCollection();
	/* setting methods */
	bool settingHand(int, const CprHand &);
	bool settingHand(int, const CardList&);
	void resetAllHands();
	/* access methods */
	CprHand& hand(int);
	const CprHand& getHand(int) const;
	const CardList& getAvailableCards() const;
	void computeACR();
	void computeMAX();
	const CardList* getACR() const;
    const CardList * getMAX() const;
	/* other methods */
	void printByRank() const;
	void printBySuit() const;
	void showCollection() const;
	bool isValidSet() ;

private:
	CardList _cards;
	CardList _availCards;
	HandList _hands;
	CardList _ACR[15];	// availableCardsWithRank
    CardList _MAX[4];
	/* helper */
	int isCardAvailable(const CprCard&) const;
};
