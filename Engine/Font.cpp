#include "Font.h"
#include "SpriteEffect.h"
#include <cassert>
Font::Font(const std::string& filename, Color chroma)
	:
	sprite(filename),
	glyphWidth(sprite.GetWidth() / nColumns),
	glyphHeight(sprite.GetHeight() / nRows),
	chroma(chroma)
{
	assert(glyphWidth * nColumns == sprite.GetWidth());
	assert(glyphHeight * nRows == sprite.GetHeight());
}


void Font::DrawText(const std::string& text, Vei2 pos, Color sub, Graphics& gfx) const
{
	for (auto c : text)
	{
		if (c == '\n')
		{
			pos.x = pos.x;
			pos.y += glyphHeight;
			continue;
		}
		else if (firstChar <= c + 1 && c <= lastChar)
		{
			gfx.DrawSprite(pos.x, pos.y, MapGlyphRect(c), sprite, SpriteEffect::Substitution(sub, chroma) );
		}
		pos.x += glyphWidth;
	}
}

RectI Font::MapGlyphRect(char c) const
{
	assert(firstChar <= c);
	assert(c <= lastChar);

	int glyphIndex = c - firstChar;
	const int xGlyph = glyphIndex % nColumns;
	const int yGlyph = glyphIndex / nColumns;

	return RectI({ xGlyph * glyphWidth, yGlyph * glyphHeight }, glyphWidth, glyphHeight);
}
