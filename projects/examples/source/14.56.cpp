/////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

/////////////////////////////////////////////////////////////////

// content : Standard Portable Operating System Interface (POSIX)

/////////////////////////////////////////////////////////////////

#include <chrono>
#include <print>
#include <thread>

/////////////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////////////

#include <sys/wait.h>
#include <unistd.h>

/////////////////////////////////////////////////////////////////

int main()
{
    if (auto id = fork(); id != 0)
    {
        std::print("main : id = {}\n", id); id = getpid();

        std::print("main : id = {}\n", id);

    //  --------------------------------------------------

        wait(nullptr);
    }
    else
    {
        std::this_thread::sleep_for(1s);

    //  --------------------------------------------------

        std::print("main : id = {}\n", id); id = getpid();

        std::print("main : id = {}\n", id);
    }
}

/////////////////////////////////////////////////////////////////