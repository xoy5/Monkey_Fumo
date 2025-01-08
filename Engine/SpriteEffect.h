#pragma once
#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Copy
	{
	public:
		void operator()(Color src, int x, int y, Graphics& gfx) const
		{
			gfx.PutPixel(x, y, src);
		}
	};

	class Chroma
	{
	public:
		Chroma(Color chroma = Colors::Magenta)
			:
			chroma(chroma)
		{}
		void operator ()(Color src, int x, int y, Graphics& gfx) const
		{
			if (src != chroma)
			{
				gfx.PutPixel(x, y, src);
			}
		}
	private:
		Color chroma;
	};
	
	class Substitution
	{
	public:
		Substitution(Color sub, Color chroma = Colors::Magenta)
			:
			sub(sub),
			chroma(chroma)
		{}
		void operator()(Color src, int x, int y, Graphics& gfx)
		{
			if (src != chroma)
			{
				gfx.PutPixel(x, y, sub);
			}
		}
	private:
		Color sub;
		Color chroma;
	};

	class SubstitutionButSingleColor
	{
	public:
		SubstitutionButSingleColor(Color sub, Color single, Color chroma = Colors::Magenta)
			:
			sub(sub),
			single(single),
			chroma(chroma)
		{}
		void operator()(Color src, int x, int y, Graphics& gfx)
		{
			if (src != chroma)
			{
				if (src == single)
				{
					gfx.PutPixel(x, y, sub);
				}
				else
				{
					gfx.PutPixel(x, y, src);
				}
			}
		}
	private:
		Color sub;
		Color single;
		Color chroma;
	};

	class Ghost
	{
	public:
		Ghost(Color chroma = Colors::Magenta)
			:
			chroma(chroma)
		{}
		void operator()(Color src, int x, int y, Graphics& gfx) const
		{
			if (src != chroma)
			{
				Color dest = gfx.GetPixel(x, y);
				Color blend = Color((src.GetR() + dest.GetR()) / 2,
									(src.GetG() + dest.GetG()) / 2,
									(src.GetB() + dest.GetB()) / 2);
				gfx.PutPixel(x, y, blend);
			}
		}
	private:
		Color chroma;
	};
}