#include "TextAttrib.h"

TextAttrib::~TextAttrib() {}

/*TextAttrib::TextAttrib(const BlockData& bData) {
	updateTex(bData);
}

void TextAttrib::updateTex(const BlockData& bData) {
	calculateTextDataBottom(bData.getBlockData().texBottomCoord);
	calculateTextDataTop(bData.getBlockData().texTopCoord);
	calculateTextDataLeft(bData.getBlockData().texSideCoord);	
	calculateTextDataRight(bData.getBlockData().texSideCoord);
	calculateTextDataFront(bData.getBlockData().texSideCoord);
	calculateTextDataBack(bData.getBlockData().texSideCoord);
}*/

std::vector<Vector2> TextAttrib::getTextureFromAtlas(int x, int y) {
	float res = 0.0625;
	Vector2 uv01 = Vector2((float)(x - 1) * res, (float)y * res);
	Vector2 uv11 = Vector2((float)x * res, (float)y * res);
	Vector2 uv00 = Vector2((float)(x - 1) * res, (float)(y - 1) * res);
	Vector2 uv10 = Vector2((float)x * res, (float)(y - 1) * res);
	std::vector<Vector2> vector = { uv00, uv01, uv10, uv11 };
	return vector;
}

void TextAttrib::calculateTextDataBottom(int x, int y) {
	bottom = TextAttrib::getTextureFromAtlas(x, y);
}

void TextAttrib::calculateTextDataTop(int x, int y) {
	top = TextAttrib::getTextureFromAtlas(x, y);
}

void TextAttrib::calculateTextDataLeft(int x, int y) {
	left = TextAttrib::getTextureFromAtlas(x, y);
}

void TextAttrib::calculateTextDataRight(int x, int y) {
	right = TextAttrib::getTextureFromAtlas(x, y);
}

void TextAttrib::calculateTextDataFront(int x, int y) {
	front = TextAttrib::getTextureFromAtlas(x, y);
}

void TextAttrib::calculateTextDataBack(int x, int y) {
	back = TextAttrib::getTextureFromAtlas(x, y);
}


void TextAttrib::calculateTextDataBottom(const Vector2& v) {
	calculateTextDataBottom((int)v.x,(int)v.y);
}

void TextAttrib::calculateTextDataTop(const Vector2& v) {
	calculateTextDataTop((int)v.x,(int)v.y);
}

void TextAttrib::calculateTextDataLeft(const Vector2& v) {
	calculateTextDataLeft((int)v.x,(int)v.y);
}

void TextAttrib::calculateTextDataRight(const Vector2& v) {
	calculateTextDataRight((int)v.x,(int)v.y);
}

void TextAttrib::calculateTextDataFront(const Vector2& v) {
	calculateTextDataFront((int)v.x,(int)v.y);
}

void TextAttrib::calculateTextDataBack(const Vector2& v) {
	calculateTextDataBack((int)v.x,(int)v.y);
}

const std::vector<Vector2>& TextAttrib::getTextDataBottom() const {
	return bottom;
}

const std::vector<Vector2>& TextAttrib::getTextDataTop() const {
	return top;
}

const std::vector<Vector2>& TextAttrib::getTextDataLeft() const {
	return left;
}

const std::vector<Vector2>& TextAttrib::getTextDataRight() const {
	return right;
}

const std::vector<Vector2>& TextAttrib::getTextDataFront() const {
	return front;
}

const std::vector<Vector2>& TextAttrib::getTextDataBack() const {
	return back;
}

