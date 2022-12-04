#include <catch.hpp>
#include <sstream>

#include "ModernGraphicsRendererAdapter.h"
#include "shape_drawing_lib.hpp"

TEST_CASE("Adapt CModernGraphicsRenderer to ICanvas and draw shapes using shape_drawing_lib")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(oss);
	ModernGraphicsRendererAdapter adapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(adapter);

	SECTION("Draw triangle")
	{
		shape_drawing_lib::CTriangle triangle({ 1, 1 }, { 2, 2 }, { 3, 3 }, 0xFF00FF);
		painter.Draw(triangle);

		CHECK(oss.str() == "<draw>\n"
						   "  <line fromX=\"1\" fromY=\"1\" toX=\"2\" toY=\"2\">\n"
						   "    <color r=\"1\" g=\"0\" b=\"1\" a=\"1\" />\n"
						   "  </line>\n"
						   "</draw>\n"
						   "<draw>\n"
						   "  <line fromX=\"2\" fromY=\"2\" toX=\"3\" toY=\"3\">\n"
						   "    <color r=\"1\" g=\"0\" b=\"1\" a=\"1\" />\n"
						   "  </line>\n"
						   "</draw>\n"
						   "<draw>\n"
						   "  <line fromX=\"3\" fromY=\"3\" toX=\"1\" toY=\"1\">\n"
						   "    <color r=\"1\" g=\"0\" b=\"1\" a=\"1\" />\n"
						   "  </line>\n"
						   "</draw>\n");
	}

	SECTION("Draw rectangle")
	{
		shape_drawing_lib::CRectangle rectangle({ 10, 10 }, 20, 30, 0xFFFF00);
		painter.Draw(rectangle);

		CHECK(oss.str() == "<draw>\n"
						   "  <line fromX=\"10\" fromY=\"10\" toX=\"30\" toY=\"10\">\n"
						   "    <color r=\"1\" g=\"1\" b=\"0\" a=\"1\" />\n"
						   "  </line>\n"
						   "</draw>\n"
						   "<draw>\n"
						   "  <line fromX=\"30\" fromY=\"10\" toX=\"30\" toY=\"40\">\n"
						   "    <color r=\"1\" g=\"1\" b=\"0\" a=\"1\" />\n"
						   "  </line>\n"
						   "</draw>\n"
						   "<draw>\n"
						   "  <line fromX=\"30\" fromY=\"40\" toX=\"10\" toY=\"40\">\n"
						   "    <color r=\"1\" g=\"1\" b=\"0\" a=\"1\" />\n"
						   "  </line>\n"
						   "</draw>\n"
						   "<draw>\n"
						   "  <line fromX=\"10\" fromY=\"40\" toX=\"10\" toY=\"10\">\n"
						   "    <color r=\"1\" g=\"1\" b=\"0\" a=\"1\" />\n"
						   "  </line>\n"
						   "</draw>\n");
	}
}

TEST_CASE("Draw single line from default start point with default color")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(oss);
	ModernGraphicsRendererAdapter adapter(renderer);

	adapter.LineTo(1, 2);

	CHECK(oss.str() == "<draw>\n"
					   "  <line fromX=\"0\" fromY=\"0\" toX=\"1\" toY=\"2\">\n"
					   "    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
					   "  </line>\n"
					   "</draw>\n");
}
