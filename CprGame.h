/****************************************************************************
  FileName   [ CprGame.h ]
  Author     [ Haowei Luan ]
  Synopsis   [ define the start of Chinese Poker Game ]
****************************************************************************/

#pragma once
#include "CprDef.h"
#include "CprPlayer.h"

class CprGame
{
public:
	CprGame();
	~CprGame();
	void setting();
	void Tsetting();
	void start();
	void Tstart();
	void end();
private:
	vector<CprPlayer*> _players;
};

