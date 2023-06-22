#pragma once
#include <DirectXMath.h>
namespace Animation {
	class BezierCurve final{
	public:
		BezierCurve(const DirectX::XMFLOAT2& p0, const DirectX::XMFLOAT2& p1, const DirectX::XMFLOAT2& p2);
		BezierCurve(const BezierCurve&) = default;
		BezierCurve(BezierCurve&&) = default;
		BezierCurve& operator=(const BezierCurve&) = default;
		BezierCurve& operator=(BezierCurve&&) = default;
		~BezierCurve() = default;
		/// <summary>
		/// gets the value of the curve at the spacified position
		/// </summary>
		/// <param name="pos">the position to evaluate</param>
		/// <returns>the value at the specified position</returns>
		float GetValueAtPosition(float pos) const;
	private:
		DirectX::XMFLOAT2 _p0;
		DirectX::XMFLOAT2 _p1;
		DirectX::XMFLOAT2 _p2;
	};

}