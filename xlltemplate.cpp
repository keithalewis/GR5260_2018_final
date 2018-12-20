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
}
test xai_test_jump_diffusion_cdf(test_jump_diffusion_cdf);

void test_jump_diffusion_implied()
{
	//??? Question 7. Test jump_diffusion::implied for the following implied volatilities
	double s[] = { 0.5, 0.1, 0.2, 0.5 };
}
test xai_test_jump_diffusion_implied(test_jump_diffusion_implied);

//??? Questing 8. Write an add-in called FMS.JUMP_DIFFUSION that returns a handle to a fms::jump_diffusion object

//??? Questing 9. Write an add-in called FMS.JUMP_DIFFUSION.VALUE that uses the handle above to value a binary put option.

//??? Questing 10. Create a spreadsheet that values a binary put option with parameters a = .9, lambda = .1.
// Use xllmonte to compare the closed from and Monte Carlo value.