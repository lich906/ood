#include "catch.hpp"
#include "fakeit.hpp"

#include "Presenter/ShapesPresenter.h"

using namespace fakeit;

TEST_CASE("Shapes presenter")
{
	ShapeStore store;

	ShapesPresenter presenter(store);
}
