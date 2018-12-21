// xlltemplate.h
#include <math.h>
#include "xll12/xll/xll.h"
#include "xll12/xll/ensure.h"

#pragma warning(disable: 4100)

namespace fms {

	inline double normal_cdf(double z)
	{
		//return 0; //???Question 2. Return the standard normal cumulative distribution.
		static double sqrt2 = sqrt(2);

		return 0.5 + erf(z / sqrt2) / 2;
	}

	class jump_diffusion {
		double a, b, lambda;
	public:
		jump_diffusion(double a, double lambda)
			: a(a), lambda(lambda)
		{
			// ensure a and lambda are valid

			//b = 0; //??? put Question 1 formula here*/)
			ensure(0 < a && a <= 1);
			ensure(lambda > 0);

			b = (1 - a * a) / lambda; // or -(1 - a*a)/lambda
		}

		double cdf(double z)
		{
			//return 0; //??? Question 3. Return P(X <= z) where X = a X + b (N - lambda)

			// P(X <= z) = P(aZ + b(N - lambda) <= z)
			//           = P(Z <= (z - b(N - lambda))/a)
			//           = sum_{n>=0} P(Z <= (z - b(n - lambda))/a) lambda^n/n! exp(-lambda)
			double lambda_n = exp(-lambda); // lambda^n/n! exp(-lambda)
			double sum = normal_cdf((z - b * (-lambda)) / a)*lambda_n; // first term
			for (size_t n = 1; n < 100/* safeguard */; ++n) {
				lambda_n *= lambda / n;
				double term = normal_cdf((z - b * (n - lambda)) / a)*lambda_n;
				if (term + 1 == 1)
					break;
				sum += term;
			}

			return sum;
		}
		// kappa^Z(s) = s^2/2
		// kappa^N(s) = lambda(exp(s) - 1)
		// kappa^{a Z + b (N - lambda)}(s) = a*a*s*s/2 + lambda(exp(bs) - 1) = lambda*b*s
		double kappa(double s)
		{
			return a * a*s*s / 2 + lambda * (exp(b*s) - 1) - lambda*b*s;
		}
		// Binary put forward value
		double value(double f, double s, double k)
		{
			//return 0; //???Question 4. Return E 1(F <= k)
			// z = (kappa(s) + log k/f)/s
			double z = (kappa(s) + log(k/f)) / s;

			return cdf(z);
		}
		// SKIP
		// Binary put implied volatility using
		// https://github.com/keithalewis/MATHGR5260_001_2018/blob/master/GR5260/fms_root1d_newton.h
		double implied(double f, double v, double k)
		{
			return 0; //??Question 5. Return s such that v = value(s, k)
		}
		template<class R>
		double variate(R& rng)
		{
			std::normal_distribution<> Z;
			std::poisson_distribution<> N{ lambda };

			return a * Z(rng) + b * (N(rng) - lambda);
		}
	};

}