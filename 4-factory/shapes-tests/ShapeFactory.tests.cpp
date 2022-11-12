#include <catch.hpp>

#include "ShapeFactory.h"
#include "PictureDraft.h"
#include "Painter.h"
#include "StreamCanvas.h"

TEST_CASE("Passing valid shape description in method CreateShape")
{
	std::ostringstream oss;

	ShapeFactory factory;
	PictureDraft draft;
	Painter painter;
	auto canvas = std::make_unique<StreamCanvas>(oss);

	SECTION("Passing valid rectangle shape description, drawing shape to ensure valid data")
	{
		draft.AddShape(factory.CreateShape("rectangle yellow 20 20 40 40"));

		painter.DrawPicture(draft, canvas.get());

		REQUIRE(oss.str() == "color was set to yellow\n"
							 "drawing line from 20,20 to 40,20 with color yellow\n"
							 "drawing line from 40,20 to 40,40 with color yellow\n"
							 "drawing line from 40,40 to 20,40 with color yellow\n"
							 "drawing line from 20,40 to 20,20 with color yellow\n");
	}

	SECTION("Passing valid triangle shape description, drawing shape to ensure valid data")
	{
		draft.AddShape(factory.CreateShape("triangle green 10 10 20 10 15 20"));

		painter.DrawPicture(draft, canvas.get());

		REQUIRE(oss.str() == "color was set to green\n"
							 "drawing line from 10,10 to 20,10 with color green\n"
							 "drawing line from 20,10 to 15,20 with color green\n"
							 "drawing line from 15,20 to 10,10 with color green\n");
	}

	SECTION("Passing valid ellipse shape description, drawing shape to ensure valid data")
	{
		draft.AddShape(factory.CreateShape("ellipse red 50 50 20 30"));

		painter.DrawPicture(draft, canvas.get());

		REQUIRE(oss.str() == "color was set to red\n"
							 "drawing ellipse with center in 50,50 width 20 height 30 with color red\n");
	}

	SECTION("Drawing single pentagon")
	{
		draft.AddShape(factory.CreateShape("polygon black 5 50 50 30"));

		painter.DrawPicture(draft, canvas.get());

		REQUIRE(oss.str() == "color was set to black\n"
							 "drawing line from 80,50 to 59,79 with color black\n"
							 "drawing line from 59,79 to 25,68 with color black\n"
							 "drawing line from 25,68 to 25,32 with color black\n"
							 "drawing line from 25,32 to 59,21 with color black\n"
							 "drawing line from 59,21 to 80,50 with color black\n");
	}
}

TEST_CASE("Passing invalid shapes data")
{
	std::ostringstream oss;

	ShapeFactory factory;

	SECTION("Passing invalid shape type, should cause exception")
	{
		REQUIRE_THROWS_AS(factory.CreateShape("ponimay purple 30 30 20"), std::invalid_argument);
		REQUIRE_THROWS_WITH(factory.CreateShape("ponimay purple 30 30 20"), "Invalid shape type");
	}

	SECTION("Passing invalid color string value, should cause exception")
	{
		REQUIRE_THROWS_AS(factory.CreateShape("rectangle nenorm 20 20 40 40"), std::invalid_argument);
		REQUIRE_THROWS_WITH(factory.CreateShape("rectangle nenorm 20 20 40 40"), "Invalid color string value");
	}

	SECTION("Passing valid shape type and color but invalid numeric data, should cause exception")
	{
		REQUIRE_THROWS_AS(factory.CreateShape("triangle blue 30 nu 20"), std::invalid_argument);
		REQUIRE_THROWS_WITH(factory.CreateShape("triangle blue 30 nu 20"), "Failed to read shape data");
	}
}
