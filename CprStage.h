/****************************************************************************
  FileName   [ CprStage.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define each phase in a single stage ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprCollection.h"

class CprStage
{
    friend class CprGame;
public:
	CprStage(int,vector<CprPlayer*>&, int id);
	~CprStage();
	void start();
private:
	void dealingPhase();
	void strategyPhase();
	void checkXianggongPhase();
	void comparisonPhase();
	void shootingPhase();
	void printScores() const;

	vector<CprPlayer*>& _players;
	int _stageId;
	int T;
};

