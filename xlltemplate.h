// xlltemplate.h
#include "xll12/xll/xll.h"
#include "xll12/xll/ensure.h"

#pragma warning(disable: 4100)

namespace fms {

	inline double normal_cdf(double z)
	{
		return 0; //???Question 2. Return the standard normal cumulative distribution.
	}

	class jump_diffusion {
		double a, b, lambda;
	public:
		jump_diffusion(double a, double lambda)
			: a(a), lambda(lambda)
		{
			// ensure a and lambda are valid

			b = 0; //??? put Question 1 formula here*/)
		}
		double cdf(double z)
		{
			return 0; //??? Question 3. Return P(X <= z) where X = a X + b (N - lambda)
		}
		// Binary put forward value
		double value(double f, double s, double k)
		{
			return 0; //???Question 4. Return E 1(F <= k)
		}
		// Binary put implied volatility using
		// https://github.com/keithalewis/MATHGR5260_001_2018/blob/master/GR5260/fms_root1d_newton.h
		double implied(double f, double v, double k)
		{
			return 0; //??Question 5. Return s such that v = value(s, k)
		}
	};

}