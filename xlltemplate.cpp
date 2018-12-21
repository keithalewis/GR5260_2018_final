// xlltemplate.cpp
#include <random>
#include "xlltemplate.h"

using namespace xll;

AddIn xai_template(
	Documentation(LR"(
Jump diffusion binary put option.
)"));

// [f() + ... f()]/n
template<class X>
inline X mean(const std::function<X()>& f, size_t n)
{
	X m = 0;

	for (size_t i = 1; i <= n; ++i)
		m += (f() - m) / i;

	return m;
}


void test_jump_diffusion_cdf()
{
	//??? Question 6. Use std::normal_distribution and std::poisson_distribution to test jump_diffusion_cdf.
	std::default_random_engine dre;
	double a = 0.9;
	double lambda = 0.1;
	fms::jump_diffusion X(a, lambda);
	double mean = 0;
	double z = 0;
	size_t N = 1000;
	for (size_t n = 1; n <= N; ++n)
	{
		mean += (1 * (X.variate(dre) <= z) - mean) / n;
	}
	double cdf = X.cdf(z);
	ensure(fabs(mean - cdf) < 1 / sqrt(N));
}
test xai_test_jump_diffusion_cdf(test_jump_diffusion_cdf);

// SKIP
void test_jump_diffusion_implied()
{
	//??? Question 7. Test jump_diffusion::implied for the following implied volatilities
	double s[] = { 0.5, 0.1, 0.2, 0.5 };
}
//test xai_test_jump_diffusion_implied(test_jump_diffusion_implied);

//??? Questing 8. Write an add-in called FMS.JUMP_DIFFUSION that returns a handle to a fms::jump_diffusion object
static AddIn xai_jump_diffusion(
	Function(XLL_HANDLE, L"?xll_jump_diffusion", L"FMS.JUMP_DIFFUSION")
	.Arg(XLL_DOUBLE, L"a", L"is the dffusion parameter.")
	.Arg(XLL_DOUBLE, L"lambda", L"is the jump parameter.")
	.Uncalced()
	.FunctionHelp(L"Return a handle to a jump diffustion model.")
	.Category(L"XLL")
	.Documentation(L"Docs")
);
HANDLEX WINAPI xll_jump_diffusion(double a, double lambda)
{
#pragma XLLEXPORT
	handlex result;

	try {
		handle<fms::jump_diffusion> h(new fms::jump_diffusion(a, lambda));
		result = h.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}
//??? Questing 9. Write an add-in called FMS.JUMP_DIFFUSION.VALUE that uses the handle above to value a binary put option.
static AddIn xai_jump_diffusion_value(
	Function(XLL_HANDLE, L"?xll_jump_diffusion_value", L"FMS.JUMP_DIFFUSION.VALUE")
	.Arg(XLL_HANDLE, L"handle", L"is a handle returned by FMS.JUMP_DIFFUSION>")
	.Arg(XLL_DOUBLE, L"f", L"is the forward of the underlying.")
	.Arg(XLL_DOUBLE, L"s", L"is the volatility parameter.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike of the binary option.")
	.FunctionHelp(L"Returns the binary put forward value of a jump diffustion model.")
	.Category(L"XLL")
	.Documentation(L"Docs")
);
double WINAPI xll_jump_diffusion_value(HANDLEX h, double f, double s, double k)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		handle<fms::jump_diffusion> h_(h);
		ensure(h_);

		result = h_->value(f, s, k);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

std::default_random_engine dre;

static AddIn xai_jump_diffusion_variate(
	Function(XLL_HANDLE, L"?xll_jump_diffusion_variate", L"FMS.JUMP_DIFFUSION.VARIATE")
	.Arg(XLL_HANDLE, L"handle", L"is a handle returned by FMS.JUMP_DIFFUSION>")
	.Arg(XLL_DOUBLE, L"f", L"is the forward of the underlying.")
	.Arg(XLL_DOUBLE, L"s", L"is the volatility parameter.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike of the binary option.")
	.Volatile()
	.FunctionHelp(L"Returns a random value of the underlying.")
	.Category(L"XLL")
	.Documentation(L"Docs")
);
double WINAPI xll_jump_diffusion_variate(HANDLEX h, double f, double s, double k)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		handle<fms::jump_diffusion> h_(h);
		ensure(h_);

		double X = h_->variate(dre);

		result = f * exp(s*X - h_->kappa(s));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

//??? Questing 10. Create a spreadsheet that values a binary put option with parameters a = .9, lambda = .1, f = 100, s = 0.2, and k = 100.
// Use xllmonte to compare the closed form and Monte Carlo values.

