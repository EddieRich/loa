#ifndef __COMPUTERPLAYER_DEFINED__
#define __COMPUTERPLAYER_DEFINED__

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(bool black);
	bool ChooseChip(LinesOfAction* ploa) override;
	int ChooseTarget(LinesOfAction* ploa) override;
};

#endif // __COMPUTERPLAYER_DEFINED__
