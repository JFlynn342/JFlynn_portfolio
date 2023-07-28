#include "BezierCurve.h"
using namespace DirectX;
namespace Animation {
	BezierCurve::BezierCurve(const XMFLOAT2& p0, const XMFLOAT2& p1, const XMFLOAT2& p2):
		_p0{ p0 }, _p1{ p1 }, _p2{ p2 } {
		// make sure the length of the curve covers the entire blend
		assert(p0.x == 0.f);
		assert(p2.x == 1.f);
	}
	float BezierCurve::GetValueAtPosition(float pos) const {
		XMVECTOR result = (1 - pos) * ((1 - pos) * XMLoadFloat2(&_p0) + pos * XMLoadFloat2(&_p1)) + pos * ((1 - pos) * XMLoadFloat2(&_p1) + pos * XMLoadFloat2(&_p2));
		XMFLOAT2 temp;
		XMStoreFloat2(&temp, result);
		return temp.y;
	}
};

