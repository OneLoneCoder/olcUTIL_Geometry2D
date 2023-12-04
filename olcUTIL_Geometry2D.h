/*
	OneLoneCoder - Geometry 2D v1.01
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	A collection of 2D Geometric primitives and functions to work with
	and between them.


	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2023 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com

	Authors
	~~~~~~~
	David Barr, aka javidx9, (c) OneLoneCoder 2019, 2020, 2021, 2022, 2023
	Gusgo99
	Gorbit99
	MagetzUb
	Dandistine
	cstdint
	piratux
	sigonasr
	bixxy

	Changes:
	v1.01:		+Made constants inline
				+Header guards (lol... sigh...)

*/

#pragma once
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>

#ifndef OLC_V2D_TYPE
#define OLC_V2D_TYPE
namespace olc
{
	/*
		A complete 2D geometric vector structure, with a variety
		of useful utility functions and operator overloads
	*/
	template<class T>
	struct v_2d
	{
		static_assert(std::is_arithmetic<T>::value, "olc::v_2d<type> must be numeric");

		// x-axis component
		T x = 0;
		// y-axis component
		T y = 0;

		// Default constructor
		inline constexpr v_2d() = default;

		// Specific constructor
		inline constexpr v_2d(T _x, T _y) : x(_x), y(_y)
		{}

		// Copy constructor
		inline constexpr v_2d(const v_2d& v) = default;

		// Assignment operator
		inline constexpr v_2d& operator=(const v_2d& v) = default;


		// Returns rectangular area of vector
		inline constexpr auto area() const
		{
			return x * y;
		}

		// Returns magnitude of vector
		inline auto mag() const
		{
			return std::sqrt(x * x + y * y);
		}

		// Returns magnitude squared of vector (useful for fast comparisons)
		inline constexpr T mag2() const
		{
			return x * x + y * y;
		}

		// Returns normalised version of vector
		inline v_2d norm() const
		{
			auto r = 1 / mag();
			return v_2d(x * r, y * r);
		}

		// Returns vector at 90 degrees to this one
		inline constexpr v_2d perp() const
		{
			return v_2d(-y, x);
		}

		// Rounds both components down
		inline constexpr v_2d floor() const
		{
			return v_2d(std::floor(x), std::floor(y));
		}

		// Rounds both components up
		inline constexpr v_2d ceil() const
		{
			return v_2d(std::ceil(x), std::ceil(y));
		}

		// Returns 'element-wise' max of this and another vector
		inline constexpr v_2d max(const v_2d& v) const
		{
			return v_2d(std::max(x, v.x), std::max(y, v.y));
		}

		// Returns 'element-wise' min of this and another vector
		inline constexpr v_2d min(const v_2d& v) const
		{
			return v_2d(std::min(x, v.x), std::min(y, v.y));
		}

		// Calculates scalar dot product between this and another vector
		inline constexpr auto dot(const v_2d& rhs) const
		{
			return this->x * rhs.x + this->y * rhs.y;
		}

		// Calculates 'scalar' cross product between this and another vector (useful for winding orders)
		inline constexpr auto cross(const v_2d& rhs) const
		{
			return this->x * rhs.y - this->y * rhs.x;
		}

		// Treat this as polar coordinate (R, Theta), return cartesian equivalent (X, Y)
		inline constexpr v_2d cart() const
		{
			return v_2d(std::cos(y) * x, std::sin(y) * x);
		}

		// Treat this as cartesian coordinate (X, Y), return polar equivalent (R, Theta)
		inline constexpr v_2d polar() const
		{
			return v_2d(mag(), std::atan2(y, x));
		}

		// Clamp the components of this vector in between the 'element-wise' minimum and maximum of 2 other vectors
		inline constexpr v_2d clamp(const v_2d& v1, const v_2d& v2) const
		{
			return this->max(v1).min(v2);
		}

		// Linearly interpolate between this vector, and another vector, given normalised parameter 't'
		inline constexpr v_2d lerp(const v_2d& v1, const double t) const
		{
			return (T(1.0 - t)) + (v1 * T(t));
		}

		// Compare if this vector is numerically equal to another
		inline constexpr bool operator == (const v_2d& rhs) const
		{
			return (this->x == rhs.x && this->y == rhs.y);
		}

		// Compare if this vector is not numerically equal to another
		inline constexpr bool operator != (const v_2d& rhs) const
		{
			return (this->x != rhs.x || this->y != rhs.y);
		}

		// Return this vector as a std::string, of the form "(x,y)"
		inline constexpr std::string str() const
		{
			return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
		}

		// Allow 'casting' from other v_2d types
		template<class F>
		inline constexpr operator v_2d<F>() const
		{
			return { static_cast<F>(this->x), static_cast<F>(this->y) };
		}
	};

	// Multiplication operator overloads between vectors and scalars, and vectors and vectors
	template<class TL, class TR>
	inline constexpr auto operator * (const TL& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs * rhs.x, lhs * rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator * (const v_2d<TL>& lhs, const TR& rhs)
	{
		return v_2d(lhs.x * rhs, lhs.y * rhs);
	}

	template<class TL, class TR>
	inline constexpr auto operator * (const v_2d<TL>& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator *= (v_2d<TL>& lhs, const TR& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	// Division operator overloads between vectors and scalars, and vectors and vectors
	template<class TL, class TR>
	inline constexpr auto operator / (const TL& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs / rhs.x, lhs / rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator / (const v_2d<TL>& lhs, const TR& rhs)
	{
		return v_2d(lhs.x / rhs, lhs.y / rhs);
	}

	template<class TL, class TR>
	inline constexpr auto operator / (const v_2d<TL>& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator /= (v_2d<TL>& lhs, const TR& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	// Unary Addition operator (pointless but i like the platinum trophies)
	template<class T>
	inline constexpr auto operator + (const v_2d<T>& lhs)
	{
		return v_2d(+lhs.x, +lhs.y);
	}

	// Addition operator overloads between vectors and scalars, and vectors and vectors
	template<class TL, class TR>
	inline constexpr auto operator + (const TL& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs + rhs.x, lhs + rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator + (const v_2d<TL>& lhs, const TR& rhs)
	{
		return v_2d(lhs.x + rhs, lhs.y + rhs);
	}

	template<class TL, class TR>
	inline constexpr auto operator + (const v_2d<TL>& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator += (v_2d<TL>& lhs, const TR& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	template<class TL, class TR>
	inline constexpr auto operator += (v_2d<TL>& lhs, const v_2d<TR>& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	// Unary negation operator overoad for inverting a vector
	template<class T>
	inline constexpr auto operator - (const v_2d<T>& lhs)
	{
		return v_2d(-lhs.x, -lhs.y);
	}

	// Subtraction operator overloads between vectors and scalars, and vectors and vectors
	template<class TL, class TR>
	inline constexpr auto operator - (const TL& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs - rhs.x, lhs - rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator - (const v_2d<TL>& lhs, const TR& rhs)
	{
		return v_2d(lhs.x - rhs, lhs.y - rhs);
	}

	template<class TL, class TR>
	inline constexpr auto operator - (const v_2d<TL>& lhs, const v_2d<TR>& rhs)
	{
		return v_2d(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	template<class TL, class TR>
	inline constexpr auto operator -= (v_2d<TL>& lhs, const TR& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	// Greater/Less-Than Operator overloads - mathematically useless, but handy for "sorted" container storage
	template<class TL, class TR>
	inline constexpr bool operator < (const v_2d<TL>& lhs, const v_2d<TR>& rhs)
	{
		return (lhs.y < rhs.y) || (lhs.y == rhs.y && lhs.x < rhs.x);
	}

	template<class TL, class TR>
	inline constexpr bool operator > (const v_2d<TL>& lhs, const v_2d<TR>& rhs)
	{
		return (lhs.y > rhs.y) || (lhs.y == rhs.y && lhs.x > rhs.x);
	}

	// Allow olc::v_2d to play nicely with std::cout
	template<class T>
	inline constexpr std::ostream& operator << (std::ostream& os, const v_2d<T>& rhs)
	{
		os << rhs.str();
		return os;
	} 

	// Convenient types ready-to-go
	typedef v_2d<int32_t> vi2d;
	typedef v_2d<uint32_t> vu2d;
	typedef v_2d<float> vf2d;
	typedef v_2d<double> vd2d;
}
#else
	#include "olcPixelGameEngine.h"
#endif



namespace olc::utils::geom2d
{
	// Lemon Meringue
	inline const double pi = 3.141592653589793238462643383279502884;

	// Floating point error margin
	inline const double epsilon = 0.001;

	//https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
	template <typename T>
	constexpr int sgn(T val) { return (T(0) < val) - (val < T(0)); }

	// Defines a line segment
	template<typename T>
	struct line
	{
		olc::v_2d<T> start;
		olc::v_2d<T> end;

		inline line(const olc::v_2d<T>& s = { T(0), T(0) },
			const olc::v_2d<T>& e = { T(0), T(0) })
			: start(s), end(e)
		{ }

		// Get vector pointing from start to end
		inline constexpr olc::v_2d<T> vector() const
		{
			return (end - start);
		}

		// Get length of line
		inline constexpr T length()
		{
			return vector().mag();
		}

		// Get length of line^2
		inline constexpr T length2()
		{
			return vector().mag2();
		}

		

		// Given a real distance, get point along line
		inline constexpr olc::v_2d<T> rpoint(const T& distance) const
		{
			return start + vector().norm() * distance;
		}

		// Given a unit distance, get point along line
		inline constexpr olc::v_2d<T> upoint(const T& distance) const
		{
			return start + vector() * distance;
		}

		// Return which side of the line does a point lie
		inline constexpr int32_t side(const olc::v_2d<T>& point) const
		{
			double d = vector().cross(point - start);
			if (d < 0)
				return -1;
			else
				if (d > 0)
					return 1;
				else
					return 0;
		}
	};

	template<typename T>
	struct ray
	{
		olc::v_2d<T> origin;
		olc::v_2d<T> direction;
	};

	template<typename T>
	struct rect
	{
		olc::v_2d<T> pos;
		olc::v_2d<T> size;

		inline rect(const olc::v_2d<T>& p = { T(0), T(0) },
			const olc::v_2d<T>& s = { T(1), T(1) })
			: pos(p), size(s)
		{ }

		inline olc::v_2d<T> middle() const
		{
			return pos + (size * double(0.5));
		}

		// Get line segment from top side of rectangle
		inline line<T> top() const
		{
			return { pos, {pos.x + size.x, pos.y } };
		}

		// Get line segment from bottom side of rectangle
		inline line<T> bottom() const
		{
			return { {pos.x, pos.y + size.y}, pos + size };
		}

		// Get line segment from left side of rectangle
		inline line<T> left() const
		{
			return { pos, {pos.x, pos.y + size.y} };
		}

		// Get line segment from right side of rectangle
		inline line<T> right() const
		{
			return { {pos.x + size.x, pos.y }, pos + size };
		}

		// Get a line from an indexed side, starting top, going clockwise
		inline line<T> side(const size_t i) const
		{
			if ((i & 0b11) == 0) return top();
			if ((i & 0b11) == 1) return right();
			if ((i & 0b11) == 2) return bottom();
			if ((i & 0b11) == 3) return left();
		}

		// Get area of rectangle
		inline constexpr T area() const
		{
			return size.x * size.y;
		}

		// Get perimeter of rectangle
		inline constexpr T perimeter() const
		{
			return T(2) * (size.x + size.y);
		}
	};


	template<typename T>
	struct circle
	{
		olc::v_2d<T> pos;
		T radius = T(0);

		inline circle(const olc::v_2d<T>& p = { T(0), T(0) }, const T r = T(0))
			: pos(p), radius(r)
		{ }

		// Get area of circle
		inline constexpr T area() const
		{
			return T(pi) * radius * radius;
		}

		// Get circumference of circle
		inline constexpr T perimeter() const
		{
			return T(2.0 * pi) * radius;
		}

		// Get circumference of circle
		inline constexpr T circumference() const
		{
			return perimeter();
		}
	};


	template<typename T>
	struct triangle
	{
		std::array<olc::v_2d<T>, 3> pos;

		inline triangle(
			const olc::v_2d<T>& p0 = { T(0), T(0) },
			const olc::v_2d<T>& p1 = { T(0), T(0) },
			const olc::v_2d<T>& p2 = { T(0), T(0) })
			: pos{ p0,p1,p2 }
		{ }

		// Get a line from an indexed side, starting top, going clockwise
		inline line<T> side(const size_t i) const
		{
			return line(pos[i % 3], pos[(i + 1) % 3]);
		}

		// Get area of triangle
		inline constexpr T area() const
		{
			return double(0.5) * std::abs(
				(pos[0].x * (pos[1].y - pos[2].y)) +
				(pos[1].x * (pos[2].y - pos[0].y)) +
				(pos[2].x * (pos[0].y - pos[1].y)));
		}

		// Get perimeter of triangle
		inline constexpr T perimeter() const
		{
			return line(pos[0], pos[1]).length()
				+ line(pos[1], pos[2]).length()
				+ line(pos[2], pos[0]).length();
		}
	};


	template<typename T>
	struct polygon
	{
		std::vector<olc::v_2d<T>> pos;
	};


	// =========================================================================================================================
	// Closest(shape, point) ===================================================================================================

	// Returns closest point to point
	template<typename T1, typename T2>
	inline olc::v_2d<T1> closest(const olc::v_2d<T1>& p1, [[maybe_unused]] const olc::v_2d<T2>& p2)
	{
		return p1;
	}

	// Returns closest point on line to point
	template<typename T1, typename T2>
	inline olc::v_2d<T1> closest(const line<T1>& l, const olc::v_2d<T2>& p)
	{		
		auto d = l.vector();
		double u = std::clamp(double(d.dot(p - l.start)) / d.mag2(), 0.0, 1.0);
		return l.start + u * d;
	}

	// Returns closest point on circle to point
	template<typename T1, typename T2>
	inline olc::v_2d<T1> closest(const circle<T1>& c, const olc::v_2d<T2>& p)
	{		
		return c.pos + olc::vd2d(p - c.pos).norm() * c.radius;
	}

	// Returns closest point on rectangle to point
	template<typename T1, typename T2>
	inline olc::v_2d<T1> closest(const rect<T1>& r, const olc::v_2d<T2>& p)
	{
		// Note: this algorithm can be reused for polygon
		auto c1 = closest(r.top(), p);
		auto c2 = closest(r.bottom(), p);
		auto c3 = closest(r.left(), p);
		auto c4 = closest(r.right(), p);

		auto d1 = (c1 - p).mag2();
		auto d2 = (c2 - p).mag2();
		auto d3 = (c3 - p).mag2();
		auto d4 = (c4 - p).mag2();

		auto dmin = d1;
		auto cmin = c1;

		if (d2 < dmin) {
			dmin = d2;
			cmin = c2;
		}
		if (d3 < dmin) {
			dmin = d3;
			cmin = c3;
		}
		if (d4 < dmin) {
			dmin = d4;
			cmin = c4;
		}

		return cmin;
	}

	// Returns closest point on triangle to point
	template<typename T1, typename T2>
	inline olc::v_2d<T1> closest(const triangle<T1>& t, const olc::v_2d<T2>& p)
	{
		olc::utils::geom2d::line<T1> l{t.pos[0], t.pos[1]};
		auto p0 = closest(l, p);
		auto d0 = (p0 - p).mag2();

		l.end = t.pos[2];
		auto p1 = closest(l, p);
		auto d1 = (p1 - p).mag2();

		l.start = t.pos[1];
		auto p2 = closest(l, p);
		auto d2 = (p2 - p).mag2();

		if((d0 <= d1) && (d0 <= d2)) {
			return p0;
		} else if((d1 <= d0) && (d1 <= d2)) {
			return p1;
		} else {
			return p2;
		}
	}











	// ================================================================================================================
	// POINT ==========================================================================================================

	// Checks if point contains point
	template<typename T1, typename T2>
	inline constexpr bool contains(const olc::v_2d<T1>& p1, const olc::v_2d<T2>& p2)
	{
		return (p1 - p2).mag2() < epsilon;
	}

	// Checks if line contains point
	template<typename T1, typename T2>
	inline constexpr bool contains(const line<T1>& l, const olc::v_2d<T2>& p)
	{
		double d = ((p.x - l.start.x) * (l.end.y - l.start.y) - (p.y - l.start.y) * (l.end.x - l.start.x));
		if (std::abs(d) < epsilon)
		{
			// point is on line
			double u = l.vector().dot(p - l.start) / l.vector().mag2();
			return (u >= double(0.0) && u <= double(1.0));
		}

		return false;
	}

	// Checks if rectangle contains point
	template<typename T1, typename T2>
	inline constexpr bool contains(const rect<T1>& r, const olc::v_2d<T2>& p)
	{
		return !(p.x < r.pos.x || p.y < r.pos.y ||
			p.x > (r.pos.x + r.size.x) || p.y > (r.pos.y + r.size.y));
	}

	// Checks if circle contains a point
	template<typename T1, typename T2>
	inline constexpr bool contains(const circle<T1>& c, const olc::v_2d<T2>& p)
	{
		return (c.pos - p).mag2() < (c.radius * c.radius);
	}

	// Checks if triangle contains a point
	template<typename T1, typename T2>
	inline constexpr bool contains(const triangle<T1>& t, const olc::v_2d<T2>& p)
	{
		// http://jsfiddle.net/PerroAZUL/zdaY8/1/
		T2 A = T2(0.5) * (-t.pos[1].y * t.pos[2].x + t.pos[0].y * (-t.pos[1].x + t.pos[2].x) + t.pos[0].x * (t.pos[1].y - t.pos[2].y) + t.pos[1].x * t.pos[2].y);
		T2 sign = A < T2(0) ? T2(-1) : T2(1);
		T2 s = (t.pos[0].y * t.pos[2].x - t.pos[0].x * t.pos[2].y + (t.pos[2].y - t.pos[0].y) * p.x + (t.pos[0].x - t.pos[2].x) * p.y) * sign;
		T2 v = (t.pos[0].x * t.pos[1].y - t.pos[0].y * t.pos[1].x + (t.pos[0].y - t.pos[1].y) * p.x + (t.pos[1].x - t.pos[0].x) * p.y) * sign;
		return s > T2(0) && v > T2(0) && (s + v) < T2(2) * A * sign;
	}




	// Check if point overlaps with point (analagous to contains())
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const olc::v_2d<T1>& p1, const olc::v_2d<T2>& p2)
	{
		return contains(p1, p2);
	}

	// Checks if line segment overlaps with point
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const line<T1>& l, const olc::v_2d<T2>& p)
	{
		return contains(l, p);
	}

	// Checks if rectangle overlaps with point
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const rect<T1>& r, const olc::v_2d<T2>& p)
	{
		return contains(r, p);
	}

	// Checks if circle overlaps with point
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const circle<T1>& c, const olc::v_2d<T2>& p)
	{
		return contains(c, p);
	}

	// Checks if triangle overlaps with point
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const triangle<T1>& t, const olc::v_2d<T2>& p)
	{
		return contains(t, p);
	}




	// Get intersection points where point intersects with point
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const olc::v_2d<T1>& p1, const olc::v_2d<T2>& p2)
	{
		if (contains(p1, p2))
			return { p1 };
		
		return {};
	}

	// Get intersection points where line segment intersects with point
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const line<T1>& l, const olc::v_2d<T2>& p)
	{
		if (contains(l, p))
			return { p };
		
		return {};
	}

	// Get intersection points where rectangle intersects with point
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const rect<T1>& r, const olc::v_2d<T2>& p)
	{
		if (contains(r.top(), p)) return { p };
		if (contains(r.bottom(), p)) return { p };
		if (contains(r.left(), p)) return { p };
		if (contains(r.right(), p)) return { p };
		return {};
	}

	// Get intersection points where circle intersects with point
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const circle<T1>& c, const olc::v_2d<T2>& p)
	{
		if (std::abs((p - c.pos).mag2() - (c.radius * c.radius)) <= epsilon)
			return { p };

		return {};
	}

	// Get intersection points where triangle intersects with point
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const triangle<T1>& t, const olc::v_2d<T2>& p)
	{
		if (contains(t.side(0), p)) return { p };
		if (contains(t.side(1), p)) return { p };
		if (contains(t.side(2), p)) return { p };
		return {};
	}












	// ================================================================================================================
	// LINE ===========================================================================================================

	// Check if point contains line segment
	template<typename T1, typename T2>
	inline constexpr bool contains([[maybe_unused]] const olc::v_2d<T1>& p, [[maybe_unused]] const line<T2>& l)
	{
		return false; // It can't!
	}

	// Check if line segment contains line segment
	template<typename T1, typename T2>
	inline constexpr bool contains(const line<T1>& l1, const line<T2>& l2)
	{
		return overlaps(l1, l2.start) && overlaps(l1, l2.end);
	}

	// Check if rectangle contains line segment
	template<typename T1, typename T2>
	inline constexpr bool contains(const rect<T1>& r, const line<T2>& l)
	{
		return contains(r, l.start) && contains(r, l.end);
	}

	// Check if circle contains line segment
	template<typename T1, typename T2>
	inline constexpr bool contains(const circle<T1>& c1, const line<T2>& l)
	{
		return contains(c1, l.start) && contains(c1, l.end);
	}

	// Check if triangle contains line segment
	template<typename T1, typename T2>
	inline constexpr bool contains(const triangle<T1>& t, const line<T2>& l)
	{
		return contains(t, l.start) && contains(t, l.end);
	}




	// Check if point overlaps line segment
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const olc::v_2d<T1>& p, const line<T2>& l)
	{
		return contains(l, p);
	}

	// Check if line segment overlaps line segment
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const line<T1>& l1, const line<T2>& l2)
	{
		double D = ((l2.end.y - l2.start.y) * (l1.end.x - l1.start.x) - (l2.end.x - l2.start.x) * (l1.end.y - l1.start.y));
		double uA = ((l2.end.x-l2.start.x)*(l1.start.y-l2.start.y) - (l2.end.y-l2.start.y)*(l1.start.x-l2.start.x)) / D;
		double uB = ((l1.end.x-l1.start.x)*(l1.start.y-l2.start.y) - (l1.end.y-l1.start.y)*(l1.start.x-l2.start.x)) / D;
		return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
	}

	// Check if rectangle overlaps line segment
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const rect<T1>& r, const line<T2>& l)
	{

		return overlaps(r.left(),l)||
			overlaps(r.top(),l)||
			overlaps(r.bottom(),l)||
			overlaps(r.right(),l);
	}

	// Check if circle overlaps line segment
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const circle<T1>& c, const line<T2>& l)
	{
		auto vClosest = closest(l, c.pos);
		return ((c.pos - vClosest).mag2() < (c.radius * c.radius));
	}

	// Check if triangle overlaps line segment
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const triangle<T1>& t, const line<T2>& l)
	{
		return overlaps(t, l.start) || overlaps(t.side(0), l) || overlaps(t.side(1), l) || overlaps(t.side(2), l);
	}




	// Get intersection points where point intersects with line segment
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const olc::v_2d<T1>& p, const line<T2>& l)
	{
		return intersects(l, p);
	}

	// Get intersection points where line segment intersects with line segment
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const line<T1>& l1, const line<T2>& l2)
	{
		float rd = l1.vector().cross(l2.vector());
		if (rd == 0) return {}; // Parallel or Colinear TODO: Return two points

		//Inverse rd product
		rd = 1.f / rd;

		//Cross products: 
		//rn = (b1b2 x b1a1)
		float rn = ((l2.end.x - l2.start.x) * (l1.start.y - l2.start.y) - (l2.end.y - l2.start.y) * (l1.start.x - l2.start.x)) * rd;
		//sn = (a1a2 x b1a1)
		float sn = ((l1.end.x - l1.start.x) * (l1.start.y - l2.start.y) - (l1.end.y - l1.start.y) * (l1.start.x - l2.start.x)) * rd;

		//Return the intersection depth
		//if (d) *d = rn;

		if (rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)
			return {}; // Intersection not within line segment

		return { l1.start + rn * l1.vector()};
	}

	// Get intersection points where rectangle intersects with line segment
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const rect<T1>& r, const line<T2>& l)
	{
		std::vector<olc::v_2d<T2>>intersections;
		std::vector<olc::v_2d<T2>>result=intersects(r.left(),l);
		if(result.size()>0)intersections.push_back(result[0]);
		result=intersects(r.right(),l);
		if(result.size()>0)intersections.push_back(result[0]);
		result=intersects(r.top(),l);
		if(result.size()>0)intersections.push_back(result[0]);
		result=intersects(r.bottom(),l);
		if(result.size()>0)intersections.push_back(result[0]);
		return intersections;
	}

	// Get intersection points where circle intersects with line segment
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const circle<T1>& c, const line<T2>& l)
	{
		// Compute point closest to the circle on the line
		const auto d = l.vector();
		const auto u = d.dot(c.pos - l.start) / d.mag2();
		const auto closestPoint = l.start + u * d;

		const auto dist = (c.pos - closestPoint).mag2();
		const auto rr = c.radius * c.radius;

		if (std::abs(dist - rr) < epsilon)
		{
			// Circle "kisses" the line
			return {closestPoint};
		}
		else if (dist > rr)
		{
			// Circle is too far away
			return {};
		}
		
		// Circle intersects the line
		const auto length = std::sqrt(c.radius * c.radius - dist);
		const auto p1 = closestPoint + l.vector().norm() * length;
		const auto p2 = closestPoint - l.vector().norm() * length;

		std::vector<olc::v_2d<T2>> intersections;
		intersections.reserve(2);

		if ((p1 - closest(l, p1)).mag2() < epsilon * epsilon)
			intersections.push_back(p1);
		if ((p2 - closest(l, p2)).mag2() < epsilon * epsilon)
			intersections.push_back(p2);

		return intersections;
	}

	// Get intersection points where triangle intersects with line segment
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const triangle<T1>& t, const line<T2>& l)
	{
		std::vector<olc::v_2d<T2>> intersections;
		intersections.reserve(2);

		auto lineVsLine = [&intersections](const auto& l1, const auto& l2) {
			auto ints = intersects(l1, l2);

			for (auto&& i : ints)
				intersections.push_back(std::move(i));
		};

		lineVsLine(line(t.pos[0], t.pos[1]), l);
		lineVsLine(line(t.pos[1], t.pos[2]), l);
		lineVsLine(line(t.pos[0], t.pos[2]), l);

		// remove potential duplicate intersection.
		if (intersections.size() == 2 && intersections[0] == intersections[1])
			intersections.pop_back();

		return intersections;
	}












	// ================================================================================================================
	// RECTANGLE ======================================================================================================

	// Check if point contains rectangle
	template<typename T1, typename T2>
	inline constexpr bool contains([[maybe_unused]] const olc::v_2d<T1>& p, [[maybe_unused]] const rect<T2>& r)
	{
		return false; // It can't!
	}

	// Check if line segment contains rectangle
	template<typename T1, typename T2>
	inline constexpr bool contains([[maybe_unused]] const line<T1>& l, [[maybe_unused]] const rect<T2>& r)
	{
		return false; // It can't
	}

	// Check if rectangle contains rectangle
	template<typename T1, typename T2>
	inline constexpr bool contains(const rect<T1>& r1, const rect<T2>& r2)
	{
		return (r2.pos.x >= r1.pos.x) && (r2.pos.x + r2.size.x < r1.pos.x + r1.size.x) &&
			(r2.pos.y >= r1.pos.y) && (r2.pos.y + r2.size.y < r1.pos.y + r1.size.y);
	}

	// Check if circle contains rectangle
	template<typename T1, typename T2>
	inline constexpr bool contains(const circle<T1>& c, const rect<T2>& r)
	{
		return contains(c, r.pos) 
			&& contains(c, olc::v_2d<T2>{ r.pos.x + r.size.x, r.pos.y })
			&& contains(c, olc::v_2d<T2>{ r.pos.x, r.pos.y + r.size.y })
			&& contains(c, r.pos + r.size);
	}

	// Check if triangle contains rectangle
	template<typename T1, typename T2>
	inline constexpr bool contains(const triangle<T1>& t, const rect<T2>& r)
	{
		return contains(t, r.pos) 
			&& contains(t, r.pos + r.size)
			&& contains(t, olc::v_2d<T2>{ r.pos.x + r.size.x,r.pos.y })
			&& contains(t, olc::v_2d<T2>{ r.pos.x, r.pos.y + r.size.y });
	}




	// Check if point overlaps rectangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const olc::v_2d<T1>& p, const rect<T2>& r)
	{
		return overlaps(r, p);
	}

	// Check if line segment overlaps rectangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const line<T1>& l, const rect<T2>& r)
	{
		return overlaps(r, l);
	}

	// Check if rectangle overlaps rectangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const rect<T1>& r1, const rect<T2>& r2)
	{
		return (r1.pos.x < r2.pos.x + r2.size.x && r1.pos.x + r1.size.x >= r2.pos.x &&
			r1.pos.y < r2.pos.y + r2.size.y && r1.pos.y + r1.size.y >= r2.pos.y);
	}

	// Check if circle overlaps rectangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const circle<T1>& c, const rect<T2>& r)
	{
		// Inspired by this (very clever btw) 
		// https://stackoverflow.com/questions/45370692/circle-rectangle-collision-response
		// But modified to work :P
		double overlap = (olc::v_2d<T2>{ std::clamp(c.pos.x, r.pos.x, r.pos.x + r.size.x), std::clamp(c.pos.y, r.pos.y, r.pos.y + r.size.y) } - c.pos).mag2();
		if (std::isnan(overlap)) overlap = 0;
		return (overlap - (c.radius * c.radius)) < 0;
	}

	// Check if triangle overlaps rectangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const triangle<T1>& t, const rect<T2>& r)
	{
		return overlaps(t, r.top())
			|| overlaps(t, r.bottom())
			|| overlaps(t, r.left())
			|| overlaps(t, r.right())
			|| contains(r, t.pos[0]);
	}




	// Get intersection points where point intersects with rectangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const olc::v_2d<T1>& p, const rect<T2>& r)
	{
		return intersects(r, p);
	}

	// Get intersection points where line segment intersects with rectangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const line<T1>& l, const rect<T2>& r)
	{
		return intersects(r,l);
	}

	// Get intersection points where rectangle intersects with rectangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const rect<T1>& r1, const rect<T2>& r2)
	{
		// TODO:
		return {};
	}

	// Get intersection points where circle intersects with rectangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const circle<T1>& c, const rect<T2>& r)
	{
		// TODO:
		return {};
	}

	// Get intersection points where triangle intersects with rectangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const triangle<T1>& t, const rect<T2>& r)
	{
		// TODO:
		return {};
	}













	// ================================================================================================================
	// CIRCLE =========================================================================================================

	// Check if point contains circle
	template<typename T1, typename T2>
	inline constexpr bool contains([[maybe_unused]] const olc::v_2d<T1>& p, [[maybe_unused]] const circle<T2>& c)
	{
		return false; // It can't!
	}

	// Check if line segment contains circle
	template<typename T1, typename T2>
	inline constexpr bool contains([[maybe_unused]] const line<T1>& l, [[maybe_unused]] const circle<T2>& c)
	{
		return false; // It can't!
	}

	// Check if rectangle contains circle
	template<typename T1, typename T2>
	inline constexpr bool contains(const rect<T1>& r, const circle<T2>& c)
	{
		return r.pos.x + c.radius <= c.pos.x
			&& c.pos.x <= r.pos.x + r.size.x - c.radius
			&& r.pos.y + c.radius <= c.pos.y
			&& c.pos.y <= r.pos.y + r.size.y - c.radius;
	}

	// Check if circle contains circle
	template<typename T1, typename T2>
	inline constexpr bool contains(const circle<T1>& c1, const circle<T2>& c2)
	{
		return (c1.pos - c2.pos).mag2() <= (c1.radius - c2.radius) * (c1.radius - c2.radius);
	}

	// Check if triangle contains circle
	template<typename T1, typename T2>
	inline constexpr bool contains(const triangle<T1>& t, const circle<T2>& c)
	{
		return contains(t, c.pos) && (c.pos - closest(t, c.pos)).mag2() >= c.radius * c.radius;
	}




	// Check if point overlaps circle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const olc::v_2d<T1>& p, const circle<T2>& c)
	{
		return overlaps(c, p);
	}

	// Check if line segment overlaps circle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const line<T1>& l, const circle<T2>& c)
	{
		return overlaps(c, l);
	}

	// Check if rectangle overlaps circle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const rect<T1>& r, const circle<T2>& c)
	{
		return overlaps(c, r);
	}

	// Check if circle overlaps circle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const circle<T1>& c1, const circle<T2>& c2)
	{
		return (c1.pos - c2.pos).mag2() <= (c1.radius + c2.radius) * (c1.radius + c2.radius);
	}

	// Check if triangle overlaps circle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const triangle<T1>& t, const circle<T2>& c)
	{
		return contains(t, c.pos) || (c.pos - closest(t, c.pos)).mag2() <= c.radius * c.radius;
	}




	// Get intersection points where point intersects with circle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const olc::v_2d<T1>& p, const circle<T2>& c)
	{
		return intersects(c, p);
	}

	// Get intersection points where line segment intersects with circle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const line<T1>& l, const circle<T2>& c)
	{
		return intersects(c, l);
	}

	// Get intersection points where rectangle intersects with circle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const rect<T1>& r, const circle<T2>& c)
	{
		return intersects(c, r);
	}

	// Get intersection points where circle intersects with circle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const circle<T1>& c1, const circle<T2>& c2)
	{
		// TODO:
		return {};
	}

	// Get intersection points where triangle intersects with circle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const triangle<T1>& t, const circle<T2>& c)
	{
		// TODO:
		return {};
	}













	// ================================================================================================================
	// TRIANGLE =======================================================================================================

	// Check if point contains triangle
	template<typename T1, typename T2>
	inline constexpr bool contains([[maybe_unused]] const olc::v_2d<T1>& p, [[maybe_unused]] const triangle<T2>& t)
	{
		return false; // It can't!
	}

	// Check if line segment contains triangle
	template<typename T1, typename T2>
	inline constexpr bool contains([[maybe_unused]] const line<T1>& l, [[maybe_unused]] const triangle<T2>& t)
	{
		return false; // It can't
	}

	// Check if rectangle contains triangle
	template<typename T1, typename T2>
	inline constexpr bool contains(const rect<T1>& r, const triangle<T2>& t)
	{
		return contains(r, t.side(0))
			&& contains(r, t.side(1))
			&& contains(r, t.side(2));
	}

	// Check if circle contains triangle
	template<typename T1, typename T2>
	inline constexpr bool contains(const circle<T1>& c, const triangle<T2>& t)
	{
		// TODO:
		return false;
	}

	// Check if triangle contains triangle
	template<typename T1, typename T2>
	inline constexpr bool contains(const triangle<T1>& t1, const triangle<T2>& t2)
	{
		// TODO:
		return false;
	}




	// Check if point overlaps triangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const olc::v_2d<T1>& p, const triangle<T2>& t)
	{
		return overlaps(t, p);
	}

	// Check if line segment overlaps triangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const line<T1>& l, const triangle<T2>& t)
	{
		return overlaps(t, l);
	}

	// Check if rectangle overlaps triangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const rect<T1>& r, const triangle<T2>& t)
	{
		return overlaps(t, r);
	}

	// Check if circle overlaps triangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const circle<T1>& c, const triangle<T2>& t)
	{
		return overlaps(t, c);
	}

	// Check if triangle overlaps triangle
	template<typename T1, typename T2>
	inline constexpr bool overlaps(const triangle<T1>& t1, const triangle<T2>& t2)
	{
		// TODO:
		return false;
	}




	// Get intersection points where point intersects with triangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const olc::v_2d<T1>& p, const triangle<T2>& t)
	{
		return intersects(t, p);
	}

	// Get intersection points where line segment intersects with triangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const line<T1>& l, const triangle<T2>& t)
	{
		return intersects(t, l);
	}

	// Get intersection points where rectangle intersects with triangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const rect<T1>& r, const triangle<T2>& t)
	{
		return intersects(t, r);
	}

	// Get intersection points where circle intersects with triangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const circle<T1>& c, const triangle<T2>& t)
	{
		return intersects(t, c);
	}

	// Get intersection points where triangle intersects with triangle
	template<typename T1, typename T2>
	inline std::vector<olc::v_2d<T2>> intersects(const triangle<T1>& t1, const triangle<T2>& t2)
	{
		// TODO:
		return {};
	}



	// Return circle that fully encapsulates a point
	template<typename T1>
	inline constexpr circle<T1> envelope_c(const olc::v_2d<T1>& p)
	{
		return circle<T1>(p, 0);
	}

	// Return circle that fully encapsulates a line
	template<typename T1>
	inline constexpr circle<T1> envelope_c(const line<T1>& l)
	{
		return {l.upoint(0.5),l.vector().mag()/2};
	}

	// Return circle that fully encapsulates a rectangle
	template<typename T1>
	inline constexpr circle<T1> envelope_c(const rect<T1>& r)
	{
		// Construct the circle from the rectangle's diagonal
		return envelope_c(line<T1>(r.pos, r.pos + r.size));
	}

	// Return circle that fully encapsulates a circle
	template<typename T1>
	inline constexpr circle<T1> envelope_c(const circle<T1>& c)
	{
		return c;
	}

	// Return circle that fully encapsulates a triangle
	template<typename T1>
	inline constexpr circle<T1> envelope_c(const triangle<T1>& t)
	{
		olc::v_2d<T1> circumcenter;

		double D = 2 * (t.pos[0].x * (t.pos[1].y - t.pos[2].y) + t.pos[1].x * (t.pos[2].y - t.pos[0].y) + t.pos[2].x * (t.pos[0].y - t.pos[1].y));
		circumcenter.x = T1(double(
			(t.pos[0].x * t.pos[0].x + t.pos[0].y * t.pos[0].y) * (t.pos[1].y - t.pos[2].y) + 
			(t.pos[1].x * t.pos[1].x + t.pos[1].y * t.pos[1].y) * (t.pos[2].y - t.pos[0].y) + 
			(t.pos[2].x * t.pos[2].x + t.pos[2].y * t.pos[2].y) * (t.pos[0].y - t.pos[1].y)
		) / D);
		circumcenter.y = T1(double(
			(t.pos[0].x * t.pos[0].x + t.pos[0].y * t.pos[0].y) * (t.pos[2].x - t.pos[1].x) + 
			(t.pos[1].x * t.pos[1].x + t.pos[1].y * t.pos[1].y) * (t.pos[0].x - t.pos[2].x) +
			(t.pos[2].x * t.pos[2].x + t.pos[2].y * t.pos[2].y) * (t.pos[1].x - t.pos[0].x)
		) / D);

		double r = 0;
		for (auto& point : t.pos) {
			r = std::max(r, double(std::hypot(circumcenter.x - point.x, circumcenter.y - point.y)));
		}

		return {circumcenter, T1(r)};
	}









	// Return rectangle that fully encapsulates a point
	template<typename T1>
	inline constexpr rect<T1> envelope_r(const olc::v_2d<T1>& p)
	{
		return rect<T1>(p, { 0,0 });
	}

	// Return rectangle that fully encapsulates a line
	template<typename T1>
	inline constexpr rect<T1> envelope_r(const line<T1>& l)
	{
		T1 min_x=std::min(l.start.x,l.end.x);
		T1 min_y=std::min(l.start.y,l.end.y);
		T1 size_x=std::abs(l.start.x-l.end.x);
		T1 size_y=std::abs(l.start.y-l.end.y);
		return {{min_x,min_y},{size_x,size_y}};
	}

	// Return rectangle that fully encapsulates a rectangle
	template<typename T1>
	inline constexpr rect<T1> envelope_r(const rect<T1>& r)
	{
		return r;
	}

	// Return rectangle that fully encapsulates a circle
	template<typename T1>
	inline constexpr rect<T1> envelope_r(const circle<T1>& c)
	{		
		return rect<T1>(c.pos - v_2d<T1>{c.radius, c.radius}, { c.radius * 2, c.radius * 2 });
	}

	// Return rectangle that fully encapsulates a triangle
	template<typename T1>
	inline constexpr rect<T1> envelope_r(const triangle<T1>& t)
	{
		auto vMin = t.pos[0].min(t.pos[1].min(t.pos[2]));
		auto vMax = t.pos[0].max(t.pos[1].max(t.pos[2]));
		return rect<T1>(vMin, vMax - vMin);
	}

}
