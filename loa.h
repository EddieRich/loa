#ifndef __LOA_DEFINED__
#define __LOA_DEFINED__

class LinesOfAction
{
private:
	bool (LinesOfAction::* state)();

	void ClearPlayers();

public:
	bool requires_render;

	Chip chip[24];
	Player* player[2];
	int pi;

	LinesOfAction();
	~LinesOfAction();

	bool NewGame();
	bool PlayerChooseChip();
	bool PlayerChooseTarget();

	bool Update(float elapsed);
	void Render();
};

#endif // __LOA_DEFINED__
