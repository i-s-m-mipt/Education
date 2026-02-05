//////////////////////////////////////////////////////////

// chapter : Number Processing

//////////////////////////////////////////////////////////

// section : Bitwise Operators

//////////////////////////////////////////////////////////

// content : Bit Fields
//
// content : Type Timestamp

//////////////////////////////////////////////////////////

struct Timestamp
{
    unsigned int hour   :  5 = 0;

    unsigned int minute :  6 = 0;

    unsigned int second :  6 = 0;

    unsigned int day    :  5 = 0;

    unsigned int month  :  4 = 0;

    unsigned int year   : 32 = 0;
};

//////////////////////////////////////////////////////////

int main()
{
    Timestamp timestamp(0, 0, 0, 1, 1, 1970);

//  ------------------------------------------------------

    static_assert(sizeof(Timestamp) == 8);

//  ------------------------------------------------------

//  [[maybe_unused]] auto year = &timestamp.year; // error
}

//////////////////////////////////////////////////////////