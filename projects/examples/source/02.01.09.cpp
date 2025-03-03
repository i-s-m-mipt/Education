int main()
{
    [[maybe_unused]] double x = 1.0;

//	[[maybe_unused]] int y1 = x; // bad

//	[[maybe_unused]] int y2 { x }; // error

//	[[maybe_unused]] int y3 { int(x) }; // bad

//	[[maybe_unused]] int y4 { (int)x }; // bad

	[[maybe_unused]] int y5 { static_cast < int > (x) };

//	[[maybe_unused]] int y6 { static_cast < int > ("aaaaa") }; // error
        
    [[maybe_unused]] int y7 = 'a';
}