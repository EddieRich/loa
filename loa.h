class LinesOfAction
{
private:
	bool (LinesOfAction::* state)();

public:
	bool requires_render;

	Chip chip[24];

	LinesOfAction();
	~LinesOfAction();

	bool NewGame();
	bool PlayerChooseChip();
	bool PlayerChooseTarget();

	bool Update(float elapsed);
	void Render();
};
