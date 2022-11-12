#include <catch.hpp>

#include "ShapeFactory.h"
#include "Designer.h"
#include "Painter.h"
#include "StreamCanvas.h"

TEST_CASE("Create picture draft from input stream with designer")
{
	std::ostringstream oss;
	Designer designer(std::make_unique<ShapeFactory>());
	Painter painter;
	auto canvas = std::make_unique<StreamCanvas>(oss);

	SECTION("Create draft with valid data of three shapes in input stream")
	{
		std::istringstream input("rectangle black 10 10 20 20\n"
								 "triangle pink 10 10 20 20 30 30\n"
								 "ellipse green 50 50 20 90\n");

		painter.DrawPicture(designer.CreateDraft(input), canvas.get());

		REQUIRE(oss.str() == "color was set to black\n"
							 "drawing line from 10,10 to 20,10 with color black\n"
							 "drawing line from 20,10 to 20,20 with color black\n"
							 "drawing line from 20,20 to 10,20 with color black\n"
							 "drawing line from 10,20 to 10,10 with color black\n"
							 "color was set to pink\n"
							 "drawing line from 10,10 to 20,20 with color pink\n"
							 "drawing line from 20,20 to 30,30 with color pink\n"
							 "drawing line from 30,30 to 10,10 with color pink\n"
							 "color was set to green\n"
							 "drawing ellipse with center in 50,50 width 20 height 90 with color green\n");
	}
}
