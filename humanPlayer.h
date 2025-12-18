#ifndef __HUMANPLAYER_DEFINED__
#define __HUMANPLAYER_DEFINED__

class HumanPlayer : public Player
{
public:
	HumanPlayer(bool white);
	bool ChooseChip(LinesOfAction* ploa) override;
	bool ChooseTarget(LinesOfAction* ploa) override;
};


#endif // __HUMANPLAYER_DEFINED__
