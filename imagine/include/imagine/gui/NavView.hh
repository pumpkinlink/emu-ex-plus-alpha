/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#pragma once

#include <memory>
#include <imagine/engine-globals.h>
#include <imagine/gfx/GfxText.hh>
#include <imagine/gfx/GeomRect.hh>
#include <imagine/gfx/GfxLGradient.hh>
#include <imagine/gfx/Texture.hh>
#include <imagine/util/rectangle2.h>
#include <imagine/input/Input.hh>

class NavView
{
public:
	IG::WindowRect leftBtn{}, rightBtn{}, textRect{};
	Gfx::Text text{};
	IG::WindowRect viewRect{};
	bool hasBackBtn = false, leftBtnActive = false, hasCloseBtn = false, rightBtnActive = false;

	constexpr NavView() {}
	virtual void onLeftNavBtn(Input::Event e) {};
	virtual void onRightNavBtn(Input::Event e) {};
	void setLeftBtnActive(bool on) { leftBtnActive = on; }
	void setRightBtnActive(bool on) { rightBtnActive = on; }
	void setTitle(const char *title) { text.setString(title); }
	void init(ResourceFace *face);
	virtual void deinit() = 0;
	void deinitText();
	virtual void place(const Gfx::ProjectionPlane &projP);
	void inputEvent(Input::Event e);
	virtual void draw(const Base::Window &win, const Gfx::ProjectionPlane &projP) = 0;
};

class BasicNavView : public NavView
{
public:
	Gfx::Sprite leftSpr{}, rightSpr{};
	Gfx::LGradient bg{};
	std::unique_ptr<Gfx::LGradientStopDesc[]> gradientStops{};

	BasicNavView() {}
	void init(ResourceFace *face, Gfx::PixmapTexture *leftRes, Gfx::PixmapTexture *rightRes);
	void setBackImage(Gfx::PixmapTexture *img);
	void setBackgroundGradient(const Gfx::LGradientStopDesc *gradStop, uint gradStops);

	template <size_t S>
	void setBackgroundGradient(const Gfx::LGradientStopDesc (&gradStop)[S])
	{
		setBackgroundGradient(gradStop, S);
	}

	void draw(const Base::Window &win, const Gfx::ProjectionPlane &projP) override;
	void place(const Gfx::ProjectionPlane &projP) override;
	void deinit() override;
};
