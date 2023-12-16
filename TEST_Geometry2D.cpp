#define OLC_PGE_APPLICATION
#define OLC_IGNORE_VEC2D

#include "olcUTIL_Geometry2D.h"
#include "third_party/olcPixelGameEngine.h"

#define OLC_PGEX_QUICKGUI
#include "third_party/olcPGEX_QuickGUI.h"


using namespace olc::utils::geom2d;


class Test_Geometry2D : public olc::PixelGameEngine
{
public:
	Test_Geometry2D()
	{
		// Name your application
		sAppName = "Testing Geometry2D Utilities";
	}

	enum class Shapes
	{
		Point,
		Line,
		Rect,
		Circle,
		Triangle,
	};

	Shapes nShape1 = Shapes::Point;
	Shapes nShape2 = Shapes::Point;
	
	olc::vf2d   shapePoint1, shapePoint2;
	rect<float> shapeRect1, shapeRect2;
	line<float> shapeLine1, shapeLine2;
	circle<float> shapeCircle1, shapeCircle2;
	triangle<float> shapeTriangle1, shapeTriangle2;

	olc::QuickGUI::Manager guiManager;
	olc::QuickGUI::CheckBox* guiShape1[5];
	olc::QuickGUI::CheckBox* guiShape2[5];
	olc::QuickGUI::CheckBox* guiEnvelopeShape[2];


public: 
	bool OnUserCreate() override
	{
		// Create GUI
		guiShape1[0] = new olc::QuickGUI::CheckBox(guiManager, "Point", true, { 10, 2 }, { 80, 16 });
		guiShape1[1] = new olc::QuickGUI::CheckBox(guiManager, "Line", false, { 100, 2 }, { 80, 16 });
		guiShape1[2] = new olc::QuickGUI::CheckBox(guiManager, "Rectangle", false, { 190, 2 }, { 80, 16 });
		guiShape1[3] = new olc::QuickGUI::CheckBox(guiManager, "Circle", false, { 280, 2 }, { 80, 16 });
		guiShape1[4] = new olc::QuickGUI::CheckBox(guiManager, "Triangle", false, { 370, 2 }, { 80, 16 });

		guiShape2[0] = new olc::QuickGUI::CheckBox(guiManager, "Point", true, { 10, 20 }, { 80, 16 });
		guiShape2[1] = new olc::QuickGUI::CheckBox(guiManager, "Line", false, { 100, 20 }, { 80, 16 });
		guiShape2[2] = new olc::QuickGUI::CheckBox(guiManager, "Rectangle", false, { 190, 20 }, { 80, 16 });
		guiShape2[3] = new olc::QuickGUI::CheckBox(guiManager, "Circle", false, { 280, 20 }, { 80, 16 });
		guiShape2[4] = new olc::QuickGUI::CheckBox(guiManager, "Triangle", false, { 370, 20 }, { 80, 16 });

		guiEnvelopeShape[0] = new olc::QuickGUI::CheckBox(guiManager, "Env Circle", false, { 10, 38 }, { 80, 16 });
		guiEnvelopeShape[1] = new olc::QuickGUI::CheckBox(guiManager, "Env Rect", false, { 100, 38 }, { 80, 16 });


		shapePoint1 = shapePoint2 = { 270.0f, 240.0f };
		shapeLine1 = line<float>({ 200.0f, 150.0f }, { 250.0f, 200.0f });
		shapeLine2 = line<float>({ 200.0f, 150.0f }, { 500.0f, 400.0f });
		shapeRect1 = rect<float>({ 100.0f, 100.0f }, { 50.0f, 75.0f });
		shapeRect2 = rect<float>({ 100.0f, 100.0f }, { 100.0f, 200.0f });
		shapeCircle1 = circle<float>({ 270.0f, 240.0f }, 60.0f);
		shapeCircle2 = circle<float>({ 270.0f, 240.0f }, 100.0f);
		shapeTriangle1 = shapeTriangle2 = triangle<float>({ 150.0f, 100.0f }, { 350.0f, 200.0f }, { 75.0f, 300.0f });
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		guiManager.Update(this);

		if (guiShape1[0]->bPressed || GetKey(olc::Key::K1).bPressed)
		{
			nShape1 = Shapes::Point;
			guiShape1[0]->bChecked = true;
			guiShape1[1]->bChecked = false;
			guiShape1[2]->bChecked = false;
			guiShape1[3]->bChecked = false;
			guiShape1[4]->bChecked = false;
		}

		if (guiShape1[1]->bPressed || GetKey(olc::Key::K2).bPressed)
		{
			nShape1 = Shapes::Line;
			guiShape1[0]->bChecked = false;
			guiShape1[1]->bChecked = true;
			guiShape1[2]->bChecked = false;
			guiShape1[3]->bChecked = false;
			guiShape1[4]->bChecked = false;
		}

		if (guiShape1[2]->bPressed || GetKey(olc::Key::K3).bPressed)
		{
			nShape1 = Shapes::Rect;
			guiShape1[0]->bChecked = false;
			guiShape1[1]->bChecked = false;
			guiShape1[2]->bChecked = true;
			guiShape1[3]->bChecked = false;
			guiShape1[4]->bChecked = false;
		}

		if (guiShape1[3]->bPressed || GetKey(olc::Key::K4).bPressed)
		{
			nShape1 = Shapes::Circle;
			guiShape1[0]->bChecked = false;
			guiShape1[1]->bChecked = false;
			guiShape1[2]->bChecked = false;
			guiShape1[3]->bChecked = true;
			guiShape1[4]->bChecked = false;
		}

		if (guiShape1[4]->bPressed || GetKey(olc::Key::K5).bPressed)
		{
			nShape1 = Shapes::Triangle;
			guiShape1[0]->bChecked = false;
			guiShape1[1]->bChecked = false;
			guiShape1[2]->bChecked = false;
			guiShape1[3]->bChecked = false;
			guiShape1[4]->bChecked = true;
		}



		if (guiShape2[0]->bPressed || GetKey(olc::Key::K6).bPressed)
		{
			nShape2 = Shapes::Point;
			guiShape2[0]->bChecked = true;
			guiShape2[1]->bChecked = false;
			guiShape2[2]->bChecked = false;
			guiShape2[3]->bChecked = false;
			guiShape2[4]->bChecked = false;
		}

		if (guiShape2[1]->bPressed || GetKey(olc::Key::K7).bPressed)
		{
			nShape2 = Shapes::Line;
			guiShape2[0]->bChecked = false;
			guiShape2[1]->bChecked = true;
			guiShape2[2]->bChecked = false;
			guiShape2[3]->bChecked = false;
			guiShape2[4]->bChecked = false;
		}

		if (guiShape2[2]->bPressed || GetKey(olc::Key::K8).bPressed)
		{
			nShape2 = Shapes::Rect;
			guiShape2[0]->bChecked = false;
			guiShape2[1]->bChecked = false;
			guiShape2[2]->bChecked = true;
			guiShape2[3]->bChecked = false;
			guiShape2[4]->bChecked = false;
		}

		if (guiShape2[3]->bPressed || GetKey(olc::Key::K9).bPressed)
		{
			nShape2 = Shapes::Circle;
			guiShape2[0]->bChecked = false;
			guiShape2[1]->bChecked = false;
			guiShape2[2]->bChecked = false;
			guiShape2[3]->bChecked = true;
			guiShape2[4]->bChecked = false;
		}

		if (guiShape2[4]->bPressed || GetKey(olc::Key::K0).bPressed)
		{
			nShape2 = Shapes::Triangle;
			guiShape2[0]->bChecked = false;
			guiShape2[1]->bChecked = false;
			guiShape2[2]->bChecked = false;
			guiShape2[3]->bChecked = false;
			guiShape2[4]->bChecked = true;
		}



		// Move Shape 1 according to mouse position
		switch (nShape1)
		{
		case Shapes::Point:
		{
			shapePoint1 = GetMousePos();
			break;
		}

		case Shapes::Line:
		{
			olc::vf2d v = shapeLine1.vector();
			shapeLine1.start = GetMousePos();
			shapeLine1.end = shapeLine1.start + v;
			break;
		}

		case Shapes::Rect:
		{
			shapeRect1.pos = GetMousePos();
			break;
		}

		case Shapes::Circle:
		{
			shapeCircle1.pos = GetMousePos();
			break;
		}

		case Shapes::Triangle:
		{
			olc::vf2d v = GetMousePos() - shapeTriangle1.pos[0];
			shapeTriangle1.pos[0] += v;
			shapeTriangle1.pos[1] += v;
			shapeTriangle1.pos[2] += v;
			break;
		}

		}


		bool bOverlaps = false;
		bool bContains = false;
		std::vector<olc::vf2d> vIntersections;
		olc::vf2d vClosest;

		// Tests
		if (nShape1 == Shapes::Point)
		{
			if (nShape2 == Shapes::Point)
			{
				bOverlaps = overlaps(shapePoint2, shapePoint1);
				bContains = contains(shapePoint2, shapePoint1);
				vIntersections = intersects(shapePoint2, shapePoint1);
				vClosest = closest(shapePoint2, shapePoint1);
			}

			if (nShape2 == Shapes::Line)
			{
				bOverlaps = overlaps(shapeLine2, shapePoint1);
				bContains = contains(shapeLine2, shapePoint1);
				vIntersections = intersects(shapeLine2, shapePoint1);
				vClosest = closest(shapeLine2, shapePoint1);
			}

			if (nShape2 == Shapes::Rect)
			{
				bOverlaps = overlaps(shapeRect2, shapePoint1);
				bContains = contains(shapeRect2, shapePoint1);
				vIntersections = intersects(shapeRect2, shapePoint1);
				vClosest = closest(shapeRect2, shapePoint1);
			}

			if (nShape2 == Shapes::Circle)
			{
				bOverlaps = overlaps(shapeCircle2, shapePoint1);
				bContains = contains(shapeCircle2, shapePoint1);
				vIntersections = intersects(shapeCircle2, shapePoint1);
				vClosest = closest(shapeCircle2, shapePoint1);
			}

			if (nShape2 == Shapes::Triangle)
			{
				bOverlaps = overlaps(shapeTriangle2, shapePoint1);
				bContains = contains(shapeTriangle2, shapePoint1);
				vIntersections = intersects(shapeTriangle2, shapePoint1);
				vClosest = closest(shapeTriangle2, shapePoint1);
			}
		}

		if (nShape1 == Shapes::Line)
		{
			if (nShape2 == Shapes::Point)
			{
				bOverlaps = overlaps(shapePoint2, shapeLine1);
				bContains = contains(shapePoint2, shapeLine1);
				vIntersections = intersects(shapePoint2, shapeLine1);
				vClosest = closest(shapeLine1, shapePoint2);
			}

			if (nShape2 == Shapes::Line)
			{
				bOverlaps = overlaps(shapeLine2, shapeLine1);
				bContains = contains(shapeLine2, shapeLine1);
				vIntersections = intersects(shapeLine2, shapeLine1);

			}

			if (nShape2 == Shapes::Rect)
			{
				bOverlaps = overlaps(shapeRect2, shapeLine1);
				bContains = contains(shapeRect2, shapeLine1);
				vIntersections = intersects(shapeRect2, shapeLine1);
			}

			if (nShape2 == Shapes::Circle)
			{
				bOverlaps = overlaps(shapeCircle2, shapeLine1);
				bContains = contains(shapeCircle2, shapeLine1);
				vIntersections = intersects(shapeCircle2, shapeLine1);
				vClosest = closest(shapeCircle2, shapeLine1);
			}

			if (nShape2 == Shapes::Triangle)
			{
				bOverlaps = overlaps(shapeTriangle2, shapeLine1);
				bContains = contains(shapeTriangle2, shapeLine1);
				vIntersections = intersects(shapeTriangle2, shapeLine1);
			}

			
		}

		if (nShape1 == Shapes::Rect)
		{
			if (nShape2 == Shapes::Point)
			{
				bOverlaps = overlaps(shapePoint2, shapeRect1);
				bContains = contains(shapePoint2, shapeRect1);
				vIntersections = intersects(shapePoint2, shapeRect1);
				vClosest = closest(shapeRect1, shapePoint2);
			}

			if (nShape2 == Shapes::Line)
			{
				bOverlaps = overlaps(shapeLine2, shapeRect1);
				bContains = contains(shapeLine2, shapeRect1);
				vIntersections = intersects(shapeLine2, shapeRect1);
			}

			if (nShape2 == Shapes::Rect)
			{
				bOverlaps = overlaps(shapeRect2, shapeRect1);
				bContains = contains(shapeRect2, shapeRect1);
				vIntersections = intersects(shapeRect2, shapeRect1);
			}

			if (nShape2 == Shapes::Circle)
			{
				bOverlaps = overlaps(shapeCircle2, shapeRect1);
				bContains = contains(shapeCircle2, shapeRect1);
				vIntersections = intersects(shapeCircle2, shapeRect1);
			}

			if (nShape2 == Shapes::Triangle)
			{
				bOverlaps = overlaps(shapeTriangle2, shapeRect1);
				bContains = contains(shapeTriangle2, shapeRect1);
				vIntersections = intersects(shapeTriangle2, shapeRect1);
			}
		}





		if (nShape1 == Shapes::Circle)
		{
			if (nShape2 == Shapes::Point)
			{
				bOverlaps = overlaps(shapePoint2, shapeCircle1);
				bContains = contains(shapePoint2, shapeCircle1);
				vIntersections = intersects(shapePoint2, shapeCircle1);
				vClosest = closest(shapeCircle1, shapePoint2);
			}

			if (nShape2 == Shapes::Line)
			{
				bOverlaps = overlaps(shapeLine2, shapeCircle1);
				bContains = contains(shapeLine2, shapeCircle1);
				vIntersections = intersects(shapeLine2, shapeCircle1);
				vClosest = closest(shapeCircle1, shapeLine2);
			}

			if (nShape2 == Shapes::Rect)
			{
				bOverlaps = overlaps(shapeRect2, shapeCircle1);
				bContains = contains(shapeRect2, shapeCircle1);
				vIntersections = intersects(shapeRect2, shapeCircle1);
			}

			if (nShape2 == Shapes::Circle)
			{
				bOverlaps = overlaps(shapeCircle2, shapeCircle1);
				bContains = contains(shapeCircle2, shapeCircle1);
				vIntersections = intersects(shapeCircle2, shapeCircle1);
			}

			if (nShape2 == Shapes::Triangle)
			{
				bOverlaps = overlaps(shapeTriangle2, shapeCircle1);
				bContains = contains(shapeTriangle2, shapeCircle1);
				vIntersections = intersects(shapeTriangle2, shapeCircle1);
			}
		}




		if (nShape1 == Shapes::Triangle)
		{
			if (nShape2 == Shapes::Point)
			{
				bOverlaps = overlaps(shapePoint2, shapeTriangle1);
				bContains = contains(shapePoint2, shapeTriangle1);
				vIntersections = intersects(shapePoint2, shapeTriangle1);
				vClosest = closest(shapeTriangle1, shapePoint2);
			}

			if (nShape2 == Shapes::Line)
			{
				bOverlaps = overlaps(shapeLine2, shapeTriangle1);
				bContains = contains(shapeLine2, shapeTriangle1);
				vIntersections = intersects(shapeLine2, shapeTriangle1);
			}

			if (nShape2 == Shapes::Rect)
			{
				bOverlaps = overlaps(shapeRect2, shapeTriangle1);
				bContains = contains(shapeRect2, shapeTriangle1);
				vIntersections = intersects(shapeRect2, shapeTriangle1);
			}

			if (nShape2 == Shapes::Circle)
			{
				bOverlaps = overlaps(shapeCircle2, shapeTriangle1);
				bContains = contains(shapeCircle2, shapeTriangle1);
				vIntersections = intersects(shapeCircle2, shapeTriangle1);
			}

			if (nShape2 == Shapes::Triangle)
			{
				bOverlaps = overlaps(shapeTriangle2, shapeTriangle1);
				bContains = contains(shapeTriangle2, shapeTriangle1);
				vIntersections = intersects(shapeTriangle2, shapeTriangle1);
			}
		}







		Clear(olc::VERY_DARK_BLUE);

		if (bOverlaps)
			DrawString({ 2, 450 }, "OVERLAP = TRUE");
		if (bContains)
			DrawString({ 2, 460 }, "CONTAINS = TRUE");
		
		DrawString({ 2, 470 }, "INTERSECTIONS = " + std::to_string(vIntersections.size()));

		// Draw Shape 1 - Under User Control
		switch (nShape1)
		{
		case Shapes::Point:
		{
			Draw(shapePoint1, olc::YELLOW);
			break;
		}

		case Shapes::Line:
		{
			DrawLine(shapeLine1.start, shapeLine1.end, olc::YELLOW);
			break;
		}

		case Shapes::Rect:
		{
			DrawRect(shapeRect1.pos, shapeRect1.size, olc::YELLOW);
			break;
		}

		case Shapes::Circle:
		{
			DrawCircle(shapeCircle1.pos, int32_t(shapeCircle1.radius), olc::YELLOW);
			break;
		}

		case Shapes::Triangle:
		{
			DrawTriangle(shapeTriangle1.pos[0], shapeTriangle1.pos[1], shapeTriangle1.pos[2], olc::YELLOW);
			break;
		}
		}

		// Draw Shape 2 - Fixed
		switch (nShape2)
		{
		case Shapes::Point:
		{
			Draw(shapePoint2, olc::WHITE);
			break;
		}

		case Shapes::Line:
		{
			DrawLine(shapeLine2.start, shapeLine2.end, olc::WHITE);
			break;
		}

		case Shapes::Rect:
		{
			DrawRect(shapeRect2.pos, shapeRect2.size, olc::WHITE);
			break;
		}

		case Shapes::Circle:
		{
			DrawCircle(shapeCircle2.pos, int32_t(shapeCircle2.radius), olc::WHITE);
			break;
		}

		case Shapes::Triangle:
		{
			DrawTriangle(shapeTriangle2.pos[0], shapeTriangle2.pos[1], shapeTriangle2.pos[2], olc::WHITE);
			break;
		}
		}

		// Draw Intersections
		for (const auto& i : vIntersections)
			FillCircle(i, 3, olc::RED);


		DrawCircle(vClosest, 5, olc::GREEN);

		if (guiEnvelopeShape[0]->bChecked)
		{
			circle<float> envelopingCircle;
			switch (nShape2)
			{
			case Shapes::Point:
				envelopingCircle = envelope_c(shapePoint2);
				break;
			case Shapes::Line:
				envelopingCircle = envelope_c(shapeLine2);
				break;
			case Shapes::Rect:
				envelopingCircle = envelope_c(shapeRect2);
				break;
			case Shapes::Circle:
				envelopingCircle = envelope_c(shapeCircle2);
				break;
			case Shapes::Triangle:
				envelopingCircle = bounding_circle(shapeTriangle2);
				break;
			}
			// using ceil to make sure it looks right
			DrawCircle(envelopingCircle.pos, int(std::ceil(envelopingCircle.radius)), olc::VERY_DARK_YELLOW);
		}
		if (guiEnvelopeShape[1]->bChecked)
		{
			rect<float> envelopingRect;
			switch (nShape2)
			{
			case Shapes::Point:
				envelopingRect = envelope_r(shapePoint2);
				break;
			case Shapes::Line:
				envelopingRect = envelope_r(shapeLine2);
				break;
			case Shapes::Rect:
				envelopingRect = envelope_r(shapeRect2);
				break;
			case Shapes::Circle:
				envelopingRect = envelope_r(shapeCircle2);
				break;
			case Shapes::Triangle:
				envelopingRect = bounding_box(shapeTriangle2);
				break;
			}
			DrawRect(envelopingRect.pos, envelopingRect.size, olc::MAGENTA);
		}

		guiManager.Draw(this);

		return true;
	}
};

int main()
{
	Test_Geometry2D demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	return 0;
}
