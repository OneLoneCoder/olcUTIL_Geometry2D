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
		Ray,
	};

	struct ShapeWrap
	{
		Shapes type = Shapes::Point;
		std::vector<olc::vf2d> points;
	};

	auto MakePoint(const std::vector<olc::vf2d>& p) { return p[0]; }
	auto MakeLine(const std::vector<olc::vf2d>& p)  { return line<float>{ p[0], p[1] }; }
	auto MakeRect(const std::vector<olc::vf2d>& p) { return rect<float>{ p[0], (p[1] - p[0]) }; }
	auto MakeCircle(const std::vector<olc::vf2d>& p) { return circle<float>{ p[0], (p[1]-p[0]).mag() }; }
	auto MakeTriangle(const std::vector<olc::vf2d>& p) { return triangle<float>{ p[0], p[1], p[2] }; }
	auto MakeRay(const std::vector<olc::vf2d>& p) { return ray<float>{ p[0], (p[1]-p[0]).norm() }; }

	// NOTE!! NEED A TEMPLATE GURU - IM SURE THIS MESS CAN BE TIDIED UP

	bool CheckOverlaps(const ShapeWrap& s1, const ShapeWrap& s2)
	{
		if (s1.type == Shapes::Point)
		{
			switch (s2.type)
			{
			case Shapes::Point: 
				return overlaps(MakePoint(s1.points), MakePoint(s2.points));
			case Shapes::Line: 
				return overlaps(MakePoint(s1.points), MakeLine(s2.points));
			case Shapes::Rect: 
				return overlaps(MakePoint(s1.points), MakeRect(s2.points));
			case Shapes::Circle: 
				return overlaps(MakePoint(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle: 
				return overlaps(MakePoint(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Line)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return overlaps(MakeLine(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return overlaps(MakeLine(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return overlaps(MakeLine(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return overlaps(MakeLine(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return overlaps(MakeLine(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Rect)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return overlaps(MakeRect(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return overlaps(MakeRect(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return overlaps(MakeRect(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return overlaps(MakeRect(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return overlaps(MakeRect(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Circle)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return overlaps(MakeCircle(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return overlaps(MakeCircle(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return overlaps(MakeCircle(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return overlaps(MakeCircle(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return overlaps(MakeCircle(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Triangle)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return overlaps(MakeTriangle(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return overlaps(MakeTriangle(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return overlaps(MakeTriangle(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return overlaps(MakeTriangle(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return overlaps(MakeTriangle(s1.points), MakeTriangle(s2.points));
			}
		}

		return false;
	}

	bool CheckContains(const ShapeWrap& s1, const ShapeWrap& s2)
	{
		if (s1.type == Shapes::Point)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return contains(MakePoint(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return contains(MakePoint(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return contains(MakePoint(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return contains(MakePoint(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return contains(MakePoint(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Line)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return contains(MakeLine(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return contains(MakeLine(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return contains(MakeLine(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return contains(MakeLine(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return contains(MakeLine(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Rect)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return contains(MakeRect(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return contains(MakeRect(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return contains(MakeRect(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return contains(MakeRect(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return contains(MakeRect(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Circle)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return contains(MakeCircle(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return contains(MakeCircle(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return contains(MakeCircle(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return contains(MakeCircle(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return contains(MakeCircle(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Triangle)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return contains(MakeTriangle(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return contains(MakeTriangle(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return contains(MakeTriangle(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return contains(MakeTriangle(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return contains(MakeTriangle(s1.points), MakeTriangle(s2.points));
			}
		}

		return false;
	}

	std::vector<olc::vf2d> CheckIntersects(const ShapeWrap& s1, const ShapeWrap& s2)
	{
		if (s1.type == Shapes::Point)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return intersects(MakePoint(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return intersects(MakePoint(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return intersects(MakePoint(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return intersects(MakePoint(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return intersects(MakePoint(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Line)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return intersects(MakeLine(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return intersects(MakeLine(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return intersects(MakeLine(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return intersects(MakeLine(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return intersects(MakeLine(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Rect)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return intersects(MakeRect(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return intersects(MakeRect(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return intersects(MakeRect(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return intersects(MakeRect(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return intersects(MakeRect(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Circle)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return intersects(MakeCircle(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return intersects(MakeCircle(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return intersects(MakeCircle(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return intersects(MakeCircle(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return intersects(MakeCircle(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Triangle)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return intersects(MakeTriangle(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return intersects(MakeTriangle(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return intersects(MakeTriangle(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return intersects(MakeTriangle(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return intersects(MakeTriangle(s1.points), MakeTriangle(s2.points));
			}
		}

		if (s1.type == Shapes::Ray)
		{
			switch (s2.type)
			{
			case Shapes::Point:
				return intersects(MakeRay(s1.points), MakePoint(s2.points));
			case Shapes::Line:
				return intersects(MakeRay(s1.points), MakeLine(s2.points));
			case Shapes::Rect:
				return intersects(MakeRay(s1.points), MakeRect(s2.points));
			case Shapes::Circle:
				return intersects(MakeRay(s1.points), MakeCircle(s2.points));
			case Shapes::Triangle:
				return intersects(MakeRay(s1.points), MakeTriangle(s2.points));
			}
		}

	
		return {};
	}

	void DrawShape(const ShapeWrap& shape, const olc::Pixel col = olc::WHITE)
	{
		switch (shape.type)
		{
		case Shapes::Point: {
			const auto p = MakePoint(shape.points);
			Draw(p, col);
			break; }
		case Shapes::Line: {
			const auto l = MakeLine(shape.points);
			DrawLine(l.start, l.end, col);
			break; }
		case Shapes::Rect: {
			const auto r = MakeRect(shape.points);
			DrawRect(r.pos, r.size, col);
			break; }
		case Shapes::Circle: {
			const auto c = MakeCircle(shape.points);
			DrawCircle(c.pos, int32_t(c.radius), col);
			break; }
		case Shapes::Triangle: {
			const auto t = MakeTriangle(shape.points);
			DrawTriangle(t.pos[0], t.pos[1], t.pos[2], col);
			break; }
		case Shapes::Ray: {
			const auto t = MakeRay(shape.points);
			DrawLine(t.origin, t.origin+t.direction * 1000.0f, col, 0xF0F0F0F0);
			break; }
		}
	}

	std::vector<ShapeWrap> vecShapes;

	size_t nSelectedShapeIndex = -1;
	olc::vi2d vOldMousePos;

public: 
	bool OnUserCreate() override
	{
		vecShapes.push_back({ Shapes::Point, { { 250.0f, 10.0f } } });
		vecShapes.push_back({ Shapes::Line, { { 20.0f, 10.0f }, {50.0f, 70.0f} } });
		vecShapes.push_back({ Shapes::Rect, { { 80.0f, 10.0f }, {110.0f, 60.0f} } });
		vecShapes.push_back({ Shapes::Circle, { { 130.0f, 20.0f }, {170.0f, 20.0f} } });

		vecShapes.push_back({ Shapes::Circle, { { 330.0f, 300.0f }, {420.0f, 300.0f} } });
		vecShapes.push_back({ Shapes::Circle, { { 330.0f, 300.0f }, {400.0f, 300.0f} } });

		vecShapes.push_back({ Shapes::Triangle, {{50.0f, 100.0f}, {10.0f, 150.0f}, {90.0f, 150.0f}} });
		vecShapes.push_back({ Shapes::Triangle, {{350.0f, 200.0f}, {500.0f, 150.0f}, {450.0f, 400.0f}} });

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_BLUE);

		olc::vf2d vMouseDelta = GetMousePos() - vOldMousePos;
		vOldMousePos = GetMousePos();

		if (GetMouse(0).bReleased)
			nSelectedShapeIndex = -1;

		// Check for mouse hovered shapes
		ShapeWrap mouse{ Shapes::Point, {olc::vf2d(GetMousePos())} };


		if (nSelectedShapeIndex < vecShapes.size() && GetMouse(0).bHeld)
		{
			for (auto& p : vecShapes[nSelectedShapeIndex].points)
			{
				p += vMouseDelta;
			}
		}

		size_t nMouseIndex = 0;
		for (const auto& shape : vecShapes)
		{
			if (CheckContains(shape, mouse))
			{
				break;
			}

			nMouseIndex++;
		}

		if (nMouseIndex < vecShapes.size() && GetMouse(0).bPressed)
			nSelectedShapeIndex = nMouseIndex;

		// Check Contains
		std::vector<size_t> vContains;
		std::vector<size_t> vOverlaps;
		std::vector<olc::vf2d> vIntersections;
		if (nSelectedShapeIndex < vecShapes.size())
		{
			for (size_t i = 0; i < vecShapes.size(); i++)
			{
				if (i == nSelectedShapeIndex) continue; // No self check

				const auto& vTargetShape = vecShapes[i];

				const auto vPoints = CheckIntersects(vecShapes[nSelectedShapeIndex], vTargetShape);
				vIntersections.insert(vIntersections.end(), vPoints.begin(), vPoints.end());

				if(CheckContains(vecShapes[nSelectedShapeIndex], vTargetShape))
					vContains.push_back(i);

				if (CheckOverlaps(vecShapes[nSelectedShapeIndex], vTargetShape))
					vOverlaps.push_back(i);
			}
		}


		ShapeWrap  ray1, ray2;



		bool bRayMode = false;
		if (GetMouse(1).bHeld)
		{
			// Enable Ray Mode
			bRayMode = true;

			ray1 = { Shapes::Ray, {{ 10.0f, 10.0f }, olc::vf2d(GetMousePos())} }; 
			ray2 = { Shapes::Ray, {{ float(ScreenWidth() - 10), 10.0f }, olc::vf2d(GetMousePos())} };

			
			for (size_t i = 0; i < vecShapes.size(); i++)
			{
				const auto& vTargetShape = vecShapes[i];

				const auto vPoints1 = CheckIntersects(ray1, vTargetShape);
				vIntersections.insert(vIntersections.end(), vPoints1.begin(), vPoints1.end());

				const auto vPoints2 = CheckIntersects(ray2, vTargetShape);
				vIntersections.insert(vIntersections.end(), vPoints2.begin(), vPoints2.end());
			}

			const auto vPoints3 = intersects(MakeRay(ray2.points), MakeRay(ray1.points));
			vIntersections.insert(vIntersections.end(), vPoints3.begin(), vPoints3.end());
			

		}

		// Draw All Shapes
		for (const auto& shape : vecShapes)
			DrawShape(shape);


		// Draw Overlaps
		for (const auto& shape_idx : vOverlaps)
			DrawShape(vecShapes[shape_idx], olc::YELLOW);

		// Draw Contains
		for (const auto& shape_idx : vContains)
			DrawShape(vecShapes[shape_idx], olc::MAGENTA);

		// Draw Manipulated Shape
		if(nSelectedShapeIndex < vecShapes.size())
			DrawShape(vecShapes[nSelectedShapeIndex], olc::GREEN);

		// Draw Intersections
		for (const auto& intersection : vIntersections)
			FillCircle(intersection, 3, olc::RED);

		if (bRayMode)
		{
			DrawShape(ray1, olc::CYAN); 
			DrawShape(ray2, olc::CYAN);
		}

		return true;
	}
};

int main()
{
	Test_Geometry2D demo;
	if (demo.Construct(512, 480, 2, 2, false, true))
		demo.Start();
	return 0;
}
