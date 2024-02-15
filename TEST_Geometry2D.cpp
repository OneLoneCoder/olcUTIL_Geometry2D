#define OLC_PGE_APPLICATION
#define OLC_IGNORE_VEC2D

#include "olcUTIL_Geometry2D.h"
#include "third_party/olcPixelGameEngine.h"

#define OLC_PGEX_QUICKGUI
#include "third_party/olcPGEX_QuickGUI.h"

#include <variant>
#include <optional>


using namespace olc::utils::geom2d;

// INSTRUCTIONS
// ~~~~~~~~~~~~
//
// A convoluted test file to make sure all the tests do what we think they do.
// Drag shapes with left mouse button
// Active Shape = GREEN
// Overlapped Shapes = YELLOW
// Contained Shapes = MAGENTA
// Intersection Points = RED
//
// Cast Rays with right mouse button (like lasers pew pew)
// Ray - DASHED CYAN

// Still not sure why the STL doesn't have this...
template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; };

template<class... Ts>
overloads(Ts...) -> overloads<Ts...>;

class Test_Geometry2D : public olc::PixelGameEngine
{
public:
	Test_Geometry2D()
	{
		// Name your application
		sAppName = "Testing Geometry2D Utilities";
	}

	// So what's going on here? Why are we redefining these base types? Are they not included in the header?
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//
	// Yes they are, and they can be used as expected. The challenge starts if you want to have a container filled
	// with different shapes. The shapes do not share a common base class. The utility library is not really intended
	// to be used this way - instead it's expected the user keep track of which shapes are interacting with which and
	// call the appropriate function. This "kinda" happens automatically at compile time as all the functions have 
	// exhaustive overrides to allow all the permutations of test.
	//
	// However for this test application I wanted a whole bunch of shapes the user can interact with. 'starfreakclone'
	// reworked my explicit (and lengthy) functions of comparisons and tests into some clever template-fu as seen here.
	//
	// "NOTE!! NEED A TEMPLATE GURU - IM SURE THIS MESS CAN BE TIDIED UP" - javidx9
	// "Never fear! We are here!" - starfreakclone, fux & eight&&

	struct Point
	{
		olc::vf2d points[1]; // the point
	};

	struct Line
	{
		olc::vf2d points[2]; // start, end
	};

	struct Rect
	{
		olc::vf2d points[2]; // pos top left, pos bottom right
	};

	struct Circle
	{
		olc::vf2d points[2]; // center pos, pos on circumference
	};

	struct Triangle
	{
		olc::vf2d points[3]; // the three points
	};

	struct Ray
	{
		olc::vf2d points[2]; // origin, direction
	};

	// Create desired shapes using a sequence of points
	static auto make_internal(const Point& p)    { return p.points[0]; }
	static auto make_internal(const Line& p)     { return line<float>{ p.points[0], p.points[1] }; }
	static auto make_internal(const Rect& p)     { return rect<float>{ p.points[0], (p.points[1] - p.points[0]) }; }
	static auto make_internal(const Circle& p)   { return circle<float>{ p.points[0], (p.points[1]-p.points[0]).mag() }; }
	static auto make_internal(const Triangle& p) { return triangle<float>{ p.points[0], p.points[1], p.points[2] }; }
	static auto make_internal(const Ray& p)      { return ray<float>{ p.points[0], (p.points[1]-p.points[0]).norm() }; }

	// The clever bit (and a bit new to me - jx9)
	using ShapeWrap = std::variant<Point, Line, Rect, Circle, Triangle, Ray>;

	enum Mode
	{
		CircleProject, LineProject, TriangleProject, NoProject
	};

	bool CheckOverlaps(const ShapeWrap& s1, const ShapeWrap& s2)
	{
		const auto dispatch = overloads{
			[](const auto& lhs, const auto& rhs)
			{
				return overlaps(make_internal(lhs), make_internal(rhs));
			},

			// Any combination of 'Ray' does not work because 'overlaps' is not implemented for it.
			[](const Ray&, const auto&) { return false; },
			[](const auto&, const Ray&) { return false; },
			[](const Ray&, const Ray&)  { return false; }
		};

		return std::visit(dispatch, s1, s2);
	}

	bool CheckContains(const ShapeWrap& s1, const ShapeWrap& s2)
	{
		const auto dispatch = overloads{
			[](const auto& lhs, const auto& rhs)
			{
				return contains(make_internal(lhs), make_internal(rhs));
			},
			// Any combination of 'Ray' does not work because 'contains' is not implemented for it.
			[](const Ray&, const auto&) { return false; },
			[](const auto&, const Ray&) { return false; },
			[](const Ray&, const Ray&)  { return false; }
		};

		return std::visit(dispatch, s1, s2);
	}

	std::vector<olc::vf2d> CheckIntersects(const ShapeWrap& s1, const ShapeWrap& s2)
	{
		const auto dispatch = overloads{
			[](const auto& lhs, const auto& rhs)
			{
				return intersects(make_internal(lhs), make_internal(rhs));
			},

			// Any combination of 'Ray' does not work because 'intersects' is not implemented for it.
			//[](const Ray&, const auto&) { return std::vector<olc::vf2d>{}; }, - Ray Intersections are implemented - tut tut :P

			// Ray vs Ray - needed explicitly because...
			[](const Ray& lhs, const Ray& rhs)  
			{ 
				return intersects(make_internal(lhs), make_internal(rhs)); 
			},

			// ...Shape vs Ray - Dont exist but this treats all f(x,ray) as invalid
			[](const auto&, const Ray&) { return std::vector<olc::vf2d>{}; },
		};

		return std::visit(dispatch, s1, s2);
	}

	std::optional<olc::v_2d<float>> CheckProject(const ShapeWrap& s1, const ShapeWrap& s2, const ShapeWrap& s3, 
												 const double& end_length = 0.5)
	{
		const auto dispatch = overloads{
			
			[](const auto& s1, const auto& s2, const auto& s3)
			{
				return std::optional<olc::v_2d<float>>{};
			},

			[](const Circle& s1, const Rect& s2, const Ray& s3)
			{
				return project(make_internal(s1), make_internal(s2), make_internal(s3));
			},

			[](const Circle& s1, const Triangle& s2, const Ray& s3)
			{
				return project(make_internal(s1), make_internal(s2), make_internal(s3));
			},

			[&](const Line& s1, const Circle& s2, const Ray& s3)
			{
				return project(make_internal(s1), make_internal(s2), make_internal(s3), end_length);
			}, 

		};

		return std::visit(dispatch, s1, s2, s3);
	}

	std::optional<triangle<float>> CheckProjectTriangle(const ShapeWrap& s1, const ShapeWrap& s2, const ShapeWrap& s3)
	{
		const auto dispatch = overloads{
			
			[](const auto& s1, const auto& s2, const auto& s3)
			{
				return std::optional<triangle<float>>{};
			},

			[](const Triangle& s1, const Circle& s2, const Ray& s3)
			{
				return project(make_internal(s1), make_internal(s2), make_internal(s3));
			}
		};
		
		return std::visit(dispatch, s1, s2, s3);
	}


	std::optional<ray<float>> CheckReflect(const olc::utils::geom2d::ray<float>& s1, const ShapeWrap& s2)
	{
		const auto dispatch = overloads{
			[&](const auto& a) -> std::optional<olc::utils::geom2d::ray<float>>
			{
				return reflect(s1, make_internal(a));
			}
		};

		return std::visit(dispatch, s2);
	}

	olc::v_2d<double> GetClosest(const olc::v_2d<double> p, const ShapeWrap& s)
	{
		const auto dispatch = overloads{
			[&](const auto& a) -> olc::v_2d<double>
			{
				return closest(make_internal(a), p);
			}
		};

		return std::visit(dispatch, s);
	}

	void draw_internal(const Point& x, const olc::Pixel col)
	{
		const auto p = make_internal(x);
		Draw(p, col);
	}

	void draw_internal(const Line& x, const olc::Pixel col)
	{
		const auto l = make_internal(x);
		DrawLine(l.start, l.end, col);
	}

	void draw_internal(const Rect& x, const olc::Pixel col)
	{
		const auto r = make_internal(x);
		DrawRect(r.pos, r.size, col);
	}

	void draw_internal(const Circle& x, const olc::Pixel col)
	{
		const auto c = make_internal(x);
		DrawCircle(c.pos, int32_t(c.radius), col);
	}

	void draw_internal(const Triangle& x, const olc::Pixel col)
	{
		const auto t = make_internal(x);
		DrawTriangle(t.pos[0], t.pos[1], t.pos[2], col);
	}

	void draw_internal(const Ray& x, const olc::Pixel col)
	{
		const auto t = make_internal(x);
		DrawLine(t.origin, t.origin+t.direction * 1000.0f, col, 0xF0F0F0F0);
	}

	void DrawShape(const ShapeWrap& shape, const olc::Pixel col = olc::WHITE)
	{
		std::visit([&](const auto& x)
		{
			draw_internal(x, col);
		}, shape);
	}

	std::vector<ShapeWrap> vecShapes;

	size_t nSelectedShapeIndex = -1;
	olc::vi2d vOldMousePos;
	Mode mode = Mode::NoProject;

public: 
	bool OnUserCreate() override
	{
		vecShapes.push_back({ Point{ { { 250.0f, 10.0f } } } });

		vecShapes.push_back({ Line{ { { 20.0f, 10.0f }, {50.0f, 70.0f} } } });
		vecShapes.push_back({ Line{ { { 80.0f, 10.0f }, {10.0f, 20.0f} } } });

		vecShapes.push_back({ Rect{ { { 80.0f, 10.0f }, {110.0f, 60.0f} } } });

		vecShapes.push_back({ Circle{ { { 130.0f, 20.0f }, {170.0f, 20.0f} } } });
		vecShapes.push_back({ Circle{ { { 330.0f, 300.0f }, {420.0f, 300.0f} } } });
		vecShapes.push_back({ Circle{ { { 330.0f, 300.0f }, {400.0f, 300.0f} } } });

		vecShapes.push_back({ Triangle{{ {50.0f, 100.0f}, {10.0f, 150.0f}, {90.0f, 150.0f}} }});
		vecShapes.push_back({ Triangle{{ {350.0f, 200.0f}, {500.0f, 150.0f}, {450.0f, 400.0f}} }});

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_BLUE);

		olc::vf2d vMouseDelta = GetMousePos() - vOldMousePos;
		vOldMousePos = GetMousePos();

		if (GetMouse(0).bReleased)
			nSelectedShapeIndex = -1;

		if (GetKey(olc::Key::C).bPressed) mode = Mode::CircleProject;
		if (GetKey(olc::Key::L).bPressed) mode = Mode::LineProject;
		if (GetKey(olc::Key::T).bPressed) mode = Mode::TriangleProject;
		if (GetKey(olc::Key::N).bPressed) mode = Mode::NoProject;

		// Check for mouse hovered shapes
		ShapeWrap mouse{ Point{olc::vf2d(GetMousePos())} };


		if (nSelectedShapeIndex < vecShapes.size() && GetMouse(0).bHeld)
		{
			// Visit the selected shape and offset.
			std::visit([&](auto& shape)
			{
				for (auto& p : shape.points)
				{
					p += vMouseDelta;
				}
			}, vecShapes[nSelectedShapeIndex]);
		}

		size_t nMouseIndex = 0;
		for (const auto& shape : vecShapes)
		{
			const int shapeMargin = 5;
			if (CheckContains(shape, mouse) || (GetClosest(vOldMousePos, shape) - vOldMousePos).mag() < shapeMargin)
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
		std::vector<std::optional<olc::v_2d<float>>> projected_circle_left_ray;
		std::vector<std::optional<olc::v_2d<float>>> projected_circle_right_ray;
		std::vector<std::optional<olc::v_2d<float>>> projected_line_left_ray;
		const double left_line_end_length = 0.1;
		std::vector<std::optional<olc::v_2d<float>>> projected_line_right_ray;
		std::vector<std::optional<triangle<float>>> projected_triangle_left_ray;
		std::vector<std::optional<triangle<float>>> projected_triangle_right_ray;
		const Line line_to_project{ { { 100.0f, 100.0f }, {130.0f, 100.0f} } };
		const Triangle triangle_to_project{ { {50.0f, 100.0f}, {10.0f, 150.0f}, {90.0f, 150.0f}} };


		if (GetMouse(1).bHeld)
		{
			// Enable Ray Mode
			bRayMode = true;

			ray1 = { Ray{{ { 10.0f, 10.0f }, olc::vf2d(GetMousePos())} }}; 
			ray2 = { Ray{{ { float(ScreenWidth() - 10), 10.0f }, olc::vf2d(GetMousePos())} }};

			
			for (size_t i = 0; i < vecShapes.size(); i++)
			{
				const auto& vTargetShape = vecShapes[i];

				const auto vPoints1 = CheckIntersects(ray1, vTargetShape);
				vIntersections.insert(vIntersections.end(), vPoints1.begin(), vPoints1.end());

				const auto vPoints2 = CheckIntersects(ray2, vTargetShape);
				vIntersections.insert(vIntersections.end(), vPoints2.begin(), vPoints2.end());

			}

			const auto vPoints3 = CheckIntersects(ray2, ray1);
			vIntersections.insert(vIntersections.end(), vPoints3.begin(), vPoints3.end());
			

			for (const auto& shape : vecShapes)
			{
				if(mode == Mode::CircleProject && (std::holds_alternative<Rect>(shape) || std::holds_alternative<Triangle>(shape)))
				{
					projected_circle_left_ray.push_back(CheckProject(Circle{ { { 130.0f, 20.0f }, {150.0f, 20.0f} } }, shape, ray1));
					projected_circle_right_ray.push_back(CheckProject(Circle{ { { 130.0f, 20.0f }, {150.0f, 20.0f} } }, shape, ray2));
				}

				else if (mode == Mode::LineProject && (std::holds_alternative<Circle>(shape)))
				{
					projected_line_left_ray.push_back(CheckProject(line_to_project, shape, ray1, left_line_end_length));
					projected_line_right_ray.push_back(CheckProject(line_to_project, shape, ray2));
				}

				else if (mode == Mode::TriangleProject && (std::holds_alternative<Circle>(shape)))
				{
					projected_triangle_left_ray.push_back(CheckProjectTriangle(triangle_to_project, shape, ray1));
					projected_triangle_right_ray.push_back(CheckProjectTriangle(triangle_to_project, shape, ray2));
				}
			}
			
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
		if (nSelectedShapeIndex < vecShapes.size())
			DrawShape(vecShapes[nSelectedShapeIndex], olc::GREEN);
		else if (nMouseIndex < vecShapes.size())
			DrawShape(vecShapes[nMouseIndex], olc::DARK_GREEN);

		// Draw Intersections
		for (const auto& intersection : vIntersections)
			FillCircle(intersection, 3, olc::RED);

		if (bRayMode)
		{
			DrawShape(ray1, olc::CYAN); 
			DrawShape(ray2, olc::CYAN);

			for(const auto& projection : projected_circle_left_ray)
			{
				if (mode == Mode::CircleProject && projection.has_value())
				{
					DrawCircle(projection.value(), 20.0f, olc::CYAN);
				}
			}
			
			for (const auto& projection : projected_circle_right_ray)
			{
				if (mode == Mode::CircleProject && projection.has_value())
				{
					DrawCircle(projection.value(), 20.0f, olc::RED);
				}
			}

			for (const auto& projection : projected_line_left_ray)
			{
				if (mode == Mode::LineProject && projection.has_value())
				{
					const auto& vec = make_internal(line_to_project).vector().norm();
					const auto& end_length = left_line_end_length * make_internal(line_to_project).vector().mag();
					const auto& start_length = (left_line_end_length - 1) * make_internal(line_to_project).vector().mag();
					const olc::vf2d start = projection.value() + vec * end_length;
					const olc::vf2d end = projection.value() + vec * start_length;
					Line line_to_draw{ {{start}, {end}} };
					DrawShape(line_to_draw, olc::CYAN);
				}
			}

			for (const auto& projection : projected_line_right_ray)
			{
				if (mode == Mode::LineProject && projection.has_value())
				{
					const auto& vec = make_internal(line_to_project).vector().norm();
					const auto& half_length = 0.5 * make_internal(line_to_project).vector().mag();
					const olc::vf2d start = projection.value() - vec * half_length;
					const olc::vf2d end = projection.value() + vec * half_length;
					Line line_to_draw{ {{start}, {end}} };
					DrawShape(line_to_draw, olc::RED);
				}
			}

			for (const auto& projection : projected_triangle_left_ray)
			{
				if (mode == Mode::TriangleProject && projection.has_value())
				{
					const auto p0 = projection.value().pos[0],
							   p1 = projection.value().pos[1],
						       p2 = projection.value().pos[2];

					DrawTriangle(p0, p1, p2, olc::CYAN);
				}
			}

			for (const auto& projection : projected_triangle_right_ray)
			{
				if (mode == Mode::TriangleProject && projection.has_value())
				{
					const auto p0 = projection.value().pos[0],
							   p1 = projection.value().pos[1],
							   p2 = projection.value().pos[2];

					DrawTriangle(p0, p1, p2, olc::RED);
				}
			}

		}

		// Laser beam		
		ray<float> ray_laser{ {10.0f, 300.0f}, {1.0f, 0.0f} };
		bool ray_stop = false;
		int nBounces = 100;
		size_t last_hit_index = -1;
		
		
		ray<float> ray_reflected;

		while (!ray_stop && nBounces > 0)
		{
			// Find closest
			ray_stop = true;
			size_t closest_hit_index = -1;
			float fClosestDistance = 10000000.0f;

			for (size_t i = 0; i < vecShapes.size(); i++)
			{
				// Dont check against origin shape
				if (i == last_hit_index) continue;

				const auto& vTargetShape = vecShapes[i];
				auto hit = CheckReflect(ray_laser, vTargetShape);
				if (hit.has_value())
				{
					float d = (ray_laser.origin - hit.value().origin).mag();
					if (d < fClosestDistance)
					{
						fClosestDistance = d;
						closest_hit_index = i;
						ray_reflected = hit.value();
					}					
				}
			}

			if (closest_hit_index != -1)
			{				
				DrawLine(ray_laser.origin, ray_reflected.origin, olc::Pixel(rand() % 155 + 100, 0, 0));
				ray_laser = ray_reflected;
				ray_stop = false;
				last_hit_index = closest_hit_index;
				nBounces--;
			}

			if (ray_stop)
			{
				// Ray didnt hit anything
				nBounces = 0;
				DrawLine(ray_laser.origin, ray_laser.origin + ray_laser.direction * 1000.0f, olc::Pixel(rand() % 155 + 100, 0, 0));
			}
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
