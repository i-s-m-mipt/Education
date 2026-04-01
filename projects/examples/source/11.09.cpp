/////////////////////////////////////////////////////////////////////////////////

// chapter : Algorithms

/////////////////////////////////////////////////////////////////////////////////

// section : Lambda Expressions

/////////////////////////////////////////////////////////////////////////////////

// content : Microbenchmarking

/////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <memory>
#include <random>

/////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

/////////////////////////////////////////////////////////////////////////////////

__attribute__((noinline)) auto test(int x, int y)
{
	return x + y;
}

/////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

	virtual ~Entity() = default;

//  ------------------------------------------------------------------

	__attribute__((noinline))         int test_v1(int x, int y) const;

	__attribute__((noinline)) virtual int test_v2(int x, int y) const;
};

/////////////////////////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

	__attribute__((noinline)) int test_v2(int x, int y) const override;
};

/////////////////////////////////////////////////////////////////////////////////

class Server : public Entity
{
public :

	__attribute__((noinline)) int test_v2(int x, int y) const override;
};

/////////////////////////////////////////////////////////////////////////////////

int Entity::test_v1(int x, int y) const { return x + y; }

int Entity::test_v2(int x, int y) const { return x + y; }

int Client::test_v2(int x, int y) const { return x + y; }

int Server::test_v2(int x, int y) const { return x + y; }

/////////////////////////////////////////////////////////////////////////////////

class Functor
{
public :

	__attribute__((noinline)) auto operator()(int x, int y) const;
};

/////////////////////////////////////////////////////////////////////////////////

auto Functor::operator()(int x, int y) const
{
	return x + y;
}

/////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
	auto argument = state.range(0);

	auto volatile x = 1, y = 2;

	std::shared_ptr < Entity > entity_1 = std::make_shared < Entity > ();

	std::shared_ptr < Entity > entity_2 = std::make_shared < Client > ();

	std::bernoulli_distribution distribution(0.5);

	std::random_device device;

	std::default_random_engine engine(device());

	if (distribution(engine))
	{
		entity_2 = std::make_shared < Server > ();
	}

	Functor functor;

	auto lambda = [](auto x, auto y) __attribute__((noinline)) { return x + y; };

	std::function < int(int, int) > function = lambda;

    for (auto element : state)
    {
		auto z = 0;

		switch (argument)
		{
			case 1 : { z = test             (x, y); break; }

			case 2 : { z = entity_1->test_v1(x, y); break; }

			case 3 : { z = entity_2->test_v2(x, y); break; }

			case 4 : { z = functor          (x, y); break; }

			case 5 : { z = lambda           (x, y); break; }

			case 6 : { z = function         (x, y); break; }
		}

		benchmark::DoNotOptimize(z);
    }
}

/////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5)->Arg(6);

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

/////////////////////////////////////////////////////////////////////////////////