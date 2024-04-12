#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

#include <windows.h>

// =================================================================================================

class Chronometer
{
public:

	using clock_t = std::chrono::steady_clock;

	explicit Chronometer(std::string_view name) : m_name(name), m_begin(clock_t::now())
	{
		std::cout << "Chronometer " << m_name << " launched ... " << std::endl;
	}

	~Chronometer() noexcept 
	{
		try { elapsed(); } catch (...) { std::abort(); }
	}

	void elapsed() const
	{
		std::cout << "Chronometer " << m_name << " elapsed " << std::setprecision(6) <<
			std::fixed << std::chrono::duration_cast < std::chrono::microseconds > (
				clock_t::now() - m_begin).count() / 1'000'000.0 << " (seconds)" << std::endl;
	}

private:

	const std::string_view m_name;

	const clock_t::time_point m_begin;

}; // class Chronometer

// =================================================================================================

void test_cpp_v1()
{
	printf("Hello, world!\n\n");

	MessageBoxA(GetForegroundWindow(), "Hello, world!\n\n", "window", MB_OK);
}

void test_asm_v1()
{
	const char * string = "Hello, world!\n\n";

	__asm
	{
		push [string]

		call printf // note: cdecl calling convention

		pop eax
	}

	const char * window = "window";

	__asm
	{
		push MB_OK

		push [window]
		push [string]
		
		call GetForegroundWindow

		push eax
		
		call MessageBoxA // note: stdcall calling convention
	}
}

// =================================================================================================

[[nodiscard]] int test_cpp_v2()
{
	auto z = 0;

	{
		Chronometer chronometer("C++");

		auto x = 1, y = 1;

		for (auto i = 0; i < 10'000'000; ++i)
		{
			for (auto j = 0; j < 25; ++j)
			{
				z = x + y; x = y; y = z;
			}

			x = y = 1;
		}
	}

	return z;
}

[[nodiscard]] int test_asm_v2()
{
	auto z = 0;
	
	{
		Chronometer chronometer("ASM");

		__asm
		{
			mov eax, 1
			mov ebx, 1

			mov esi, 10000000

		loop_1:

			mov edi, 25

		loop_2:

			mov ecx, eax
			add ecx, ebx
			mov eax, ebx
			mov ebx, ecx

			dec edi
			jnz loop_2

			mov eax, 1
			mov ebx, 1

			dec esi
			jnz loop_1

			mov [z], ecx
		}
	}

	return z;
}

// =================================================================================================

[[nodiscard]] double test_cpp_v3(double * x, double * y, std::size_t size)
{
	auto z = 0.0;

	{
		Chronometer chronometer("C++");

		for (std::size_t i = 0; i < size; ++i)
		{
			z += std::pow(x[i] * y[i], 8.0);
		}
	}

	return z;
}

[[nodiscard]] double test_asm_v3(double * x, double * y, std::size_t size)
{
	auto z = 0.0;

	{
		const auto s = size;

		Chronometer chronometer("ASM");

		__asm
		{
			mov eax, [x]
			mov ebx, [y]
			mov ecx, [s]

			mov edx, 0

			fldz

		loop_1:
			
			fld qword ptr [eax + 8 * edx]
			fld qword ptr [ebx + 8 * edx]

			fmul

			mov esi, 3

		loop_pow_1:

			fld st(0)
			fmul

			dec esi
			jnz loop_pow_1

			fadd

			inc edx
			cmp edx, ecx
			jl loop_1;

			fstp [z]
		}
	}

	return z;
}

// =================================================================================================

[[nodiscard]] double test_cpp_v4(double * x, std::size_t size)
{
	auto z = 0.0;

	{
		Chronometer chronometer("C++");

		/*
		for (std::size_t i = 2; i < size; ++i)
		{
			z += x[i] * x[i - 1] * x[i - 2];
		}
		*/

		for (std::size_t i = 3; i < size; i += 2)
		{
			z += x[i - 1] * x[i - 2] * (x[i - 3] + x[i]);
		}
	}

	return z;
}

[[nodiscard]] double test_asm_v4(double * x, std::size_t size)
{
	auto z = 0.0;

	{
		const auto s = size;

		Chronometer chronometer("ASM");

		__asm
		{
			mov eax, [x]
			mov esi, [s]

			mov ebx, 0
			mov ecx, 1
			mov edx, 2

			fldz

		loop_1:

			fld qword ptr [eax + 8 * ecx]
			fld qword ptr [eax + 8 * edx]

			fmul

			inc edx
			fld qword ptr [eax + 8 * edx]
			fld qword ptr [eax + 8 * ebx]

			fadd
			fmul
			fadd

			add ebx, 2
			add ecx, 2

			inc edx
			cmp edx, esi
			jl loop_1

			fstp [z]
		}
	}

	return z;
}

// =================================================================================================

void test_1()
{
	std::cout << "Test 1 launched ... " << std::endl << std::endl;

	test_cpp_v1();
	test_asm_v1();
}

void test_2()
{
	std::cout << "Test 2 launched ... " << std::endl << std::endl;

	const auto result_cpp = test_cpp_v2();
	const auto result_asm = test_asm_v2();

	std::cout << "Result C++: " << result_cpp << std::endl;
	std::cout << "Result ASM: " << result_asm << std::endl << std::endl;
}

void test_3()
{
	std::cout << "Test 3 launched ... " << std::endl << std::endl;

	const std::size_t size = 10'000'000;

	const auto x = new double[size];
	const auto y = new double[size];

	for (std::size_t i = 0; i < size; ++i) x[i] = y[i] = 0.5;

	const auto result_cpp = test_cpp_v3(x, y, size);
	const auto result_asm = test_asm_v3(x, y, size);

	std::cout << "Result C++: " << std::setprecision(6) << std::fixed << result_cpp << std::endl;
	std::cout << "Result ASM: " << std::setprecision(6) << std::fixed << result_asm << std::endl << std::endl;

	delete[] x;
	delete[] y;
}

void test_4()
{
	std::cout << "Test 4 launched ... " << std::endl << std::endl;

	const std::size_t size = 10'000'000; // note: assume size > 3 and even

	const auto x = new double[size];

	for (std::size_t i = 0; i < size; ++i) x[i] = 0.25;

	const auto result_cpp = test_cpp_v4(x, size);
	const auto result_asm = test_asm_v4(x, size);

	std::cout << "Result C++: " << std::setprecision(6) << std::fixed << result_cpp << std::endl;
	std::cout << "Result ASM: " << std::setprecision(6) << std::fixed << result_asm << std::endl << std::endl;

	delete[] x;
}

// =================================================================================================

int main()
{
	test_1();
	test_2();
	test_3();
	test_4();

	return 0;
}