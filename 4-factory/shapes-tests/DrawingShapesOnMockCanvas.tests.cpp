#include <catch.hpp>
#include <sstream>

#include "Painter.h"
#include "Designer.h"

#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

#include "StreamCanvas.h"

TEST_CASE("Drawing from existed picture draft on mock canvas")
{
	std::ostringstream oss;
	CanvasPtr canvas = std::make_unique<StreamCanvas>(oss);
	Painter painter;
	PictureDraft draft;

	SECTION("Drawing single rectangle")
	{
		ShapePtr rectangle = std::make_unique<Rectangle>(Point{ 10, 10 }, Point{ 20, 40 }, Color::Pink);

		draft.AddShape(std::move(rectangle));
		painter.DrawPicture(draft, canvas);

		REQUIRE(oss.str() == "color was set to pink\n"
							 "drawing line from 10,10 to 20,10 with color pink\n"
							 "drawing line from 20,10 to 20,40 with color pink\n"
							 "drawing line from 20,40 to 10,40 with color pink\n"
							 "drawing line from 10,40 to 10,10 with color pink\n");
	}

	SECTION("Drawing single triangle")
	{
		ShapePtr triangle = std::make_unique<Triangle>(Point{ 10, 10 }, Point{ 20, 10 }, Point{ 15, 20 }, Color::Green);

		draft.AddShape(std::move(triangle));
		painter.DrawPicture(draft, canvas);

		REQUIRE(oss.str() == "color was set to green\n"
							 "drawing line from 10,10 to 20,10 with color green\n"
							 "drawing line from 20,10 to 15,20 with color green\n"
							 "drawing line from 15,20 to 10,10 with color green\n");
	}

	SECTION("Drawing single ellipse")
	{
		ShapePtr ellipse = std::make_unique<Ellipse>(Point{ 50, 50 }, 20, 30, Color::Red);

		draft.AddShape(std::move(ellipse));
		painter.DrawPicture(draft, canvas);

		REQUIRE(oss.str() == "color was set to red\n"
							 "drawing ellipse with center in 50,50 width 20 height 30 with color red\n");
	}

	SECTION("Drawing single pentagon")
	{
		ShapePtr pentagon = std::make_unique<RegularPolygon>(5, Point{ 50, 50 }, 30, Color::Black);

		draft.AddShape(std::move(pentagon));
		painter.DrawPicture(draft, canvas);

		REQUIRE(oss.str() == "color was set to black\n"
							 "drawing line from 80,50 to 59,79 with color black\n"
							 "drawing line from 59,79 to 25,68 with color black\n"
							 "drawing line from 25,68 to 25,32 with color black\n"
							 "drawing line from 25,32 to 59,21 with color black\n"
							 "drawing line from 59,21 to 80,50 with color black\n");
	}

	SECTION("Drawing all shapes together")
	{
		ShapePtr rectangle = std::make_unique<Rectangle>(Point{ 10, 10 }, Point{ 20, 40 }, Color::Pink);
		ShapePtr triangle = std::make_unique<Triangle>(Point{ 10, 10 }, Point{ 20, 10 }, Point{ 15, 20 }, Color::Green);
		ShapePtr ellipse = std::make_unique<Ellipse>(Point{ 50, 50 }, 20, 30, Color::Red);
		ShapePtr pentagon = std::make_unique<RegularPolygon>(5, Point{ 50, 50 }, 30, Color::Black);

		draft.AddShape(std::move(rectangle))
			.AddShape(std::move(triangle))
			.AddShape(std::move(ellipse))
			.AddShape(std::move(pentagon));

		painter.DrawPicture(draft, canvas);

		REQUIRE(oss.str() == "color was set to pink\n"
							 "drawing line from 10,10 to 20,10 with color pink\n"
							 "drawing line from 20,10 to 20,40 with color pink\n"
							 "drawing line from 20,40 to 10,40 with color pink\n"
							 "drawing line from 10,40 to 10,10 with color pink\n"
							 "color was set to green\n"
							 "drawing line from 10,10 to 20,10 with color green\n"
							 "drawing line from 20,10 to 15,20 with color green\n"
							 "drawing line from 15,20 to 10,10 with color green\n"
							 "color was set to red\n"
							 "drawing ellipse with center in 50,50 width 20 height 30 with color red\n"
							 "color was set to black\n"
							 "drawing line from 80,50 to 59,79 with color black\n"
							 "drawing line from 59,79 to 25,68 with color black\n"
							 "drawing line from 25,68 to 25,32 with color black\n"
							 "drawing line from 25,32 to 59,21 with color black\n"
							 "drawing line from 59,21 to 80,50 with color black\n");
	}
}
