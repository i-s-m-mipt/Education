///////////////////////////////////////////////////////////////////////////////

// chapter : Streams and Serialization

///////////////////////////////////////////////////////////////////////////////

// section : File Management

///////////////////////////////////////////////////////////////////////////////

// content : Directories
//
// content : Function std::filesystem::create_directory
//
// content : Directory Attributes
//
// content : Function std::filesystem::create_directories
//
// content : Function std::filesystem::copy
//
// content : Enumeration std::filesystem::copy_options
//
// content : Function std::filesystem::remove_all

///////////////////////////////////////////////////////////////////////////////

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <print>

///////////////////////////////////////////////////////////////////////////////

int main()
{
	auto path = std::filesystem::current_path();

//  ---------------------------------------------------------------------------

	std::filesystem::create_directory(path / "directory");

	std::filesystem::create_directory(path / "directory", path);

//  ---------------------------------------------------------------------------

	std::filesystem::create_directories("1/2/3");

//  ---------------------------------------------------------------------------

	std::fstream("1/2/3/output.data", std::ios::out);

//  ---------------------------------------------------------------------------

	std::filesystem::copy("1", "2");
		
	std::filesystem::copy("1", "2", std::filesystem::copy_options::recursive);

//  ---------------------------------------------------------------------------

	std::print("main : enter char : "); std::cin.get();

//  ---------------------------------------------------------------------------

	std::filesystem::remove_all("1");
	
	std::filesystem::remove_all("2");

//  ---------------------------------------------------------------------------

	std::filesystem::remove_all(std::filesystem::current_path() / "directory");

//  ---------------------------------------------------------------------------

//  std::filesystem::remove_all("/"); // bad
}

///////////////////////////////////////////////////////////////////////////////