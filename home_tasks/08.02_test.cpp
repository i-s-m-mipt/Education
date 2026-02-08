//////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Number Processing

////////////////////////////////////////////////////////////////////////////////////////////

// section : Long Arithmetic

////////////////////////////////////////////////////////////////////////////////////////////

// content : Function main

////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <sstream>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////////////

#include "08.02.hpp"

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "Testing original functionality..." << std::endl;
	
	Integer x = std::string(32, '1');
	
	Integer y = std::string(32, '2');

//  ----------------------------------------------------------------------------------------

	assert((x += y) == "+33333333333333333333333333333333"s);

	assert((x -= y) == "+11111111111111111111111111111111"s);

	assert((x *= y) == "+246913580246913580246913580246908641975308641975308641975308642"s);

	assert((x /= y) == "+11111111111111111111111111111111"s);

//  ----------------------------------------------------------------------------------------

	std::cout << "Testing remainder operator with assignment..." << std::endl;
	
	Integer a = 17;
	Integer b = 5;
	a %= b;
	std::cout << "17 % 5 = " << a << std::endl;
	assert(a == 2);

	Integer c = -17;
	c %= b;
	std::cout << "-17 % 5 = " << c << std::endl;
	assert(c == -2);

	Integer d = 17;
	Integer e = -5;
	d %= e;
	std::cout << "17 % -5 = " << d << std::endl;
	assert(d == 2);

//  ----------------------------------------------------------------------------------------

	std::cout << "Testing friend remainder operator..." << std::endl;
	
	Integer f = 23;
	Integer g = 7;
	Integer h = f % g;
	std::cout << "23 % 7 = " << h << std::endl;
	assert(h == 2);

	Integer i = -23;
	Integer j = i % g;
	std::cout << "-23 % 7 = " << j << std::endl;
	assert(j == -2);

//  ----------------------------------------------------------------------------------------

	std::cout << "Testing pow function..." << std::endl;
	
	Integer k = 3;
	Integer l = k.pow(4);
	std::cout << "3^4 = " << l << std::endl;
	assert(l == 81);

	Integer m = 2;
	Integer n = m.pow(10);
	std::cout << "2^10 = " << n << std::endl;
	assert(n == 1024);

	Integer o = 12345;
	Integer p = o.pow(0);
	std::cout << "12345^0 = " << p << std::endl;
	assert(p == 1);

	Integer q = -3;
	Integer r = q.pow(3);
	std::cout << "(-3)^3 = " << r << std::endl;
	assert(r == -27);

	Integer s = -2;
	Integer t = s.pow(4);
	std::cout << "(-2)^4 = " << t << std::endl;
	assert(t == 16);

//  ----------------------------------------------------------------------------------------

	std::cout << "Testing sign function..." << std::endl;
	
	Integer u = 123;
	std::cout << "sign(123) = " << u.sign() << std::endl;
	assert(u.sign() == 1);

	Integer v = -456;
	std::cout << "sign(-456) = " << v.sign() << std::endl;
	assert(v.sign() == -1);

	Integer w = 0;
	std::cout << "sign(0) = " << w.sign() << std::endl;
	assert(w.sign() == 0);

//  ----------------------------------------------------------------------------------------

	std::cout << "Testing abs function..." << std::endl;
	
	Integer x1 = 789;
	Integer x2 = x1.abs();
	std::cout << "abs(789) = " << x2 << std::endl;
	assert(x2 == 789 && x2.sign() == 1);

	Integer y1 = -789;
	Integer y2 = y1.abs();
	std::cout << "abs(-789) = " << y2 << std::endl;
	assert(y2 == 789 && y2.sign() == 1);

	Integer z1 = 0;
	Integer z2 = z1.abs();
	std::cout << "abs(0) = " << z2 << std::endl;
	assert(z2 == 0 && z2.sign() == 0);

//  ----------------------------------------------------------------------------------------

	std::cout << "Testing other operators..." << std::endl;
	
	assert((x ++  ) == "+11111111111111111111111111111111"s);

	assert((x --  ) == "+11111111111111111111111111111112"s);

	assert((  ++ y) == "+22222222222222222222222222222223"s);

	assert((  -- y) == "+22222222222222222222222222222222"s);

//  ----------------------------------------------------------------------------------------

	assert((x +  y) == "+33333333333333333333333333333333"s);

	assert((x -  y) == "-11111111111111111111111111111111"s);

	assert((x *  y) == "+246913580246913580246913580246908641975308641975308641975308642"s);

	assert((x /  y) == "+0"s);

	assert((x %  y) == "+11111111111111111111111111111111"s);

//  ----------------------------------------------------------------------------------------

	assert((x <  y) == 1);

	assert((x >  y) == 0);

	assert((x <= y) == 1);

	assert((x >= y) == 0);

	assert((x == y) == 0);

	assert((x != y) == 1);

//  ----------------------------------------------------------------------------------------
	
	std::stringstream stream_1(std::string(32, '1'));

	std::stringstream stream_2;

//  ----------------------------------------------------------------------------------------
	
	stream_1 >> x;

	stream_2 << x;
	
//  ----------------------------------------------------------------------------------------
	
	assert(stream_2.str() == stream_1.str());

//  ----------------------------------------------------------------------------------------

	assert(sqrt(multiply(x, x)) == x);

	std::cout << "\nAll tests passed successfully!" << std::endl;
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////