#ifndef __CHIP_DEFINED__
#define __CHIP_DEFINED__

class Chip
{
public:
	int px, py;		// pixel position
	int fx, tx;		// lerp from
	int fy, ty;		// lerp to
	float t;			// lerp t

	Color color;

	Chip();
	void SetRandomOffScreen(void);

	bool Update(float elapsed);
	void Render(void) const;

	void MoveTo(int nx, int ny);
};

#endif // __CHIP_DEFINED__
