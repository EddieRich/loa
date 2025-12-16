class LinesOfAction
{
public:
	Chip chip[24];

	LinesOfAction();
	~LinesOfAction();

	bool Update(float elapsed);
	void Render();
};
