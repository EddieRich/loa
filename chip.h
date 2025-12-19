#ifndef __CHIP_DEFINED__
#define __CHIP_DEFINED__

class Chip
{
public:
	static Texture2D texChip;

	int bx, by;		// board x and y
	int px, py;		// pixel position (animated)
	int fx, tx;		// lerp from
	int fy, ty;		// lerp to
	float t;			// lerp t
	bool selected;
	Color color;

	bool visited;	// used during CheckForWinner

	Chip();
	void SetRandomOffScreen(bool move_to = false);

	bool Update(float elapsed);
	void Render(void) const;

	bool Contains(Vector2 pt);
	void MoveTo(int nx, int ny);
};

#endif // __CHIP_DEFINED__
