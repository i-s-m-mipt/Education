int main()
{
	[[maybe_unused]] bool x = false, y = true;

//  ------------------------------------------

	static_assert(sizeof(bool) == 1);
}