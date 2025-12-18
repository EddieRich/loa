#ifndef __LOA_DEFINED__
#define __LOA_DEFINED__

class LinesOfAction
{
private:
	bool (LinesOfAction::* state)();


	void SetTargetFlag(int bx, int by);
	bool IsTarget(int bx, int by);
	void ClearPlayers();
	bool ChipAt(int bx, int by);
	int ChipIndexAt(int bx, int by);
	bool LegalMove(int ci, int dx, int dy, int count);
	int GetLineCount(int x, int y, int dx, int dy);

public:
	bool requires_render;
	unsigned long long int target;		// 64 bit-flags

	Chip chip[24];
	Player* player[2];
	int pi;

	Texture2D texSquare;

	LinesOfAction();
	~LinesOfAction();

	void Shutdown();

	void SetTargetsFor(int chip_index);

	bool NewGame();
	bool PlayerChooseChip();
	bool PlayerChooseTarget();

	bool Update(float elapsed);
	void Render();
};

#endif // __LOA_DEFINED__
