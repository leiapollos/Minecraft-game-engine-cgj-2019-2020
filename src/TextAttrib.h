#ifndef TEXTATTRIB_H
#define TEXTATTRIB_H
#include "vector2.h"
//#include "World/Block/BlockType.h"
class TextAttrib {
public:
	std::vector<Vector2> bottom;
	std::vector<Vector2> top;
	std::vector<Vector2> left;
	std::vector<Vector2> right;
	std::vector<Vector2> front;
	std::vector<Vector2> back;
	TextAttrib() = default;
	//TextAttrib(const BlockData&);
	~TextAttrib();

	//void updateTex(const BlockData&);
	void calculateTextDataBottom(int x, int y);
	void calculateTextDataTop(int x, int y);
	void calculateTextDataLeft(int x, int y);
	void calculateTextDataRight(int x, int y);
	void calculateTextDataFront(int x, int y);
	void calculateTextDataBack(int x, int y);

	void calculateTextDataBottom(const Vector2& v);
	void calculateTextDataTop(const Vector2& v);
	void calculateTextDataLeft(const Vector2& v);
	void calculateTextDataRight(const Vector2& v);
	void calculateTextDataFront(const Vector2& v);
	void calculateTextDataBack(const Vector2& v);

	const std::vector<Vector2>& getTextDataBottom() const;
	const std::vector<Vector2>& getTextDataTop() const;
	const std::vector<Vector2>& getTextDataLeft() const;
	const std::vector<Vector2>& getTextDataRight() const;
	const std::vector<Vector2>& getTextDataFront() const;
	const std::vector<Vector2>& getTextDataBack() const;



	std::vector<Vector2> getTextureFromAtlas(int x, int y);
};
#endif