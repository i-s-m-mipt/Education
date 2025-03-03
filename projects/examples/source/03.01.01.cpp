struct Entity 
{ 
	int data_1 = 0, data_2 = 0;
};

///////////////////////////////////////////////////////////////////////////

int main()
{
    [[maybe_unused]] Entity entity_1, entity_2(2), entity_3(3, 3);
		
	[[maybe_unused]] Entity entity_4 { .data_1 = 4 };

	[[maybe_unused]] Entity entity_5 { .data_1 = 5, .data_2 = 5 };

	[[maybe_unused]] Entity entity_6 { .data_2 = 6 };

//	[[maybe_unused]] Entity entity_7 { .data_2 = 7, .data_1 = 7 }; // error
}