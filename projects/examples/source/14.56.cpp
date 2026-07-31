/////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

/////////////////////////////////////////////////////////////////

// content : System Interfaces
//
// content : Standard Portable Operating System Interface (POSIX)
//
// content : System Calls fork, getpid and wait
//
// content : Process ID (PID)
//
// content : Parent Process ID (PPID)
//
// content : Process Priority from +39 (low) to  0 (high)
//
// content : Process Niceness from -20 (low) to 19 (high)
//
// content : Tools ps and htop
//
// content : Task Scheduling Algorithms
//
// content : Preemptive and Cooperative Multitasking
//
// content : Time-Sharing Algorithm
//
// content : Tool nice

/////////////////////////////////////////////////////////////////

// support : ps -eo uid,pid,ppid,comm
//
// support : htop
//
// support : sudo nice -n -20 ./14.56

/////////////////////////////////////////////////////////////////

#include <chrono>
#include <iostream>
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

//  ------------------------------------------------------

    std::print("main : enter char : "); std::cin.get();
}

/////////////////////////////////////////////////////////////////