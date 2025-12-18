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
	virtual bool ChooseTarget(LinesOfAction* ploa) = 0;
};

#endif // __PLAYER_DEFINED__
