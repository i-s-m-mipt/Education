////////////////////////////////////////////////////////////////////////////////////////////

// chapter : String Processing

////////////////////////////////////////////////////////////////////////////////////////////

// section : Character Encodings

////////////////////////////////////////////////////////////////////////////////////////////

// content : Text Data Localization
//
// content : Locales and Facets
//
// content : Container std::locale
//
// content : Classic C Locale
//
// content : Function std::use_facet
//
// content : Facet std::numpunct
//
// content : Facet std::moneypunct
//
// content : C-Style Locales
//
// content : Function std::setlocale
//
// content : Macro LC_ALL

////////////////////////////////////////////////////////////////////////////////////////////

// support : sudo locale-gen ru_RU.utf8
//
// support : locale -a

////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <locale>

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::locale locale_1("en_US.utf8"); 

    std::locale locale_2("ru_RU.utf8");

//  ----------------------------------------------------------------------------------------

	assert((std::use_facet < std::  numpunct < char > > (locale_1).thousands_sep()) == ',');

    assert((std::use_facet < std::  numpunct < char > > (locale_2).thousands_sep()) == ' ');

//  ----------------------------------------------------------------------------------------

	assert((std::use_facet < std::moneypunct < char > > (locale_1).curr_symbol  ()) == "$");

    assert((std::use_facet < std::moneypunct < char > > (locale_2).curr_symbol  ()) == "₽");

//  ----------------------------------------------------------------------------------------

//	std::setlocale(LC_ALL, "en_US.utf8"); // bad
}

////////////////////////////////////////////////////////////////////////////////////////////