/////////////////////////////////////////////////////////////////////////////////

// chapter : Algorithms and Ranges

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

//  -----------------------------------------

	virtual int test(int x, int y) const = 0;
};

/////////////////////////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

	__attribute__((noinline)) int test(int x, int y) const override;
};

/////////////////////////////////////////////////////////////////////////////////

class Server : public Entity
{
public :

	__attribute__((noinline)) int test(int x, int y) const override;
};

/////////////////////////////////////////////////////////////////////////////////

int Client::test(int x, int y) const { return x + y; }

int Server::test(int x, int y) const { return x + y; }

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

	std::bernoulli_distribution distribution(0.5);

	std::random_device device;

	std::default_random_engine engine(device());

	std::shared_ptr < Entity > entity = std::make_shared < Client > ();

	if (distribution(engine))
	{
		entity = std::make_shared < Server > ();
	}

	Functor functor;

	auto lambda = [](auto x, auto y) __attribute__((noinline)) { return x + y; };

	std::function < int(int, int) > function = lambda;

    for (auto element : state)
    {
		auto z = 0;

		switch (argument)
		{
			case 1 : { z = test        (x, y); break; }

			case 2 : { z = entity->test(x, y); break; }

			case 3 : { z = functor     (x, y); break; }

			case 4 : { z = lambda      (x, y); break; }

			case 5 : { z = function    (x, y); break; }
		}

		benchmark::DoNotOptimize(z);
    }
}

/////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4)->Arg(5);

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

/////////////////////////////////////////////////////////////////////////////////