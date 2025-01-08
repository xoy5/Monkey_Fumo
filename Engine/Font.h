#pragma once
#include <string>
#include "Rect.h"
#include "Surface.h"
#include "Vec2.h"
#include "Graphics.h"

class Font
{
public:
	Font(const std::string & filename, Color chroma = Colors::White);
	void DrawText(const std::string & text, Vei2 pos, Color sub, Graphics& gfx) const;
private:
	RectI MapGlyphRect(char c) const;
private:
	Surface sprite;
	Color chroma;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	int glyphWidth;
	int glyphHeight;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};