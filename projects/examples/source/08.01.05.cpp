struct Timestamp
{
    unsigned int second :  6 = 0;

    unsigned int minute :  6 = 0;

    unsigned int hour   :  5 = 0;

    unsigned int day    :  5 = 0;

    unsigned int month  :  4 = 0;

    unsigned int year   : 32 = 0;
};

/////////////////////////////////////////////

int main()
{
    Timestamp timestamp(0, 0, 0, 1, 1, 1970);

//  -----------------------------------------

//  auto year = &timestamp.year; // error

//  -----------------------------------------

    static_assert(sizeof(Timestamp) == 8);
}