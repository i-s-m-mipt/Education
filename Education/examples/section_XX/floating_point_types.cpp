import std;

int main()
{
	float f = 0.0; // note: single precision floating point type, used in compatibility cases

	std::cout << sizeof(f) << std::endl; // note: usually 32 bits

	double d = 0.0; // note: double precision floating point type, used in most common cases

	std::cout << sizeof(d) << std::endl; // note: usually 64 bits

	long ld = 0.0; // note: extended precision floating point type, used in scientific computing

	std::cout << sizeof(ld) << std::endl; // note: usually 80 or 128 bits

	auto x = 0.0; // note: auto -> double

	auto y = 1.0f; // note: auto -> float, looks like Hungarian notation

	std::cout << 3.14    << std::endl;
	std::cout << 4e2     << std::endl;
	std::cout << 1.67e-5 << std::endl;

	auto f = 3.14f;

	std::cout << std::fixed << 12.34 << std::endl;
	std::cout << std::scientific << 12.34 << std::endl;
	std::cout << std::defaultfloat << 12.34 << std::endl;

	const auto pi = std::numbers::pi_v < long double >;

	const auto default_precision = std::cout.precision();

	const auto max_precision = std::numeric_limits < long double > ::digits10 + 1;

	std::cout << default_precision << ' ' << max_precision << std::endl;

	for (auto p = 0; p <= max_precision; ++p)
	{
		std::cout << std::setw(2) << p << " - " << std::setprecision(p) << std::fixed << pi << std::endl;
	}

	std::cout << std::setprecision(default_precision);

	std::cout << std::numeric_limits < int > ::min() << std::endl;
	std::cout << std::numeric_limits < int > ::max() << std::endl;

	std::cout << std::boolalpha << std::numeric_limits < double > ::has_infinity << std::endl;

	auto max = std::numeric_limits < double > ::max();
	auto inf = std::numeric_limits < double > ::infinity();

	if (inf > max)
	{
		std::cout << std::defaultfloat << inf << ' ' << max << std::endl;
	}

	std::cout << std::log(-1) << std::endl;

	auto x = 0.0;
	auto y = 1.0;

	std::cout << -x / y << std::endl;

	std::cout << std::boolalpha << are_equal(1.0, 0.1 * 10) << std::endl;

	return 0;
}