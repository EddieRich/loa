#ifndef __CHIP_DEFINED__
#define __CHIP_DEFINED__

class Chip
{
public:
	int px, py;		// pixel position
	int fx, tx;		// lerp from
	int fy, ty;		// lerp to
	float t;			// lerp t

	bool selected;

	Color color;

	Chip();
	void SetRandomOffScreen(void);

	bool Update(float elapsed);
	void Render(void) const;

	bool Contains(Vector2 pt);
	void MoveTo(int nx, int ny);
};

#endif // __CHIP_DEFINED__
