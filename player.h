#ifndef __PLAYER_DEFINED__
#define __PLAYER_DEFINED__

class LinesOfAction;

class Player
{
public:
	bool isWhite;

	Player(bool white);
	virtual ~Player();
	virtual bool ChooseChip(LinesOfAction* ploa) = 0;
	// return -1=go back, 0 = not yet, 1 = target chosen
	virtual int ChooseTarget(LinesOfAction* ploa) = 0;
};

#endif // __PLAYER_DEFINED__
