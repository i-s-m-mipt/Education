struct Entity 
{ 
	int x = 0, y = 0;
};

//////////////////////////////////////////////////////////////////

int main()
{
    [[maybe_unused]] Entity entity_1, entity_2(2), entity_3(3, 3);
		
	[[maybe_unused]] Entity entity_4 { .x = 4 };

	[[maybe_unused]] Entity entity_5 { .x = 5, .y = 5 };

	[[maybe_unused]] Entity entity_6 { .y = 6 };

//	[[maybe_unused]] Entity entity_7 { .y = 7, .x = 7 }; // error
}