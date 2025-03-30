#pragma once
#include <string>
#include <cpptrace/cpptrace.hpp>

#define CHECK_ERROR(a) if(a != NULL) { a.print(); }

typedef enum ErrorLevel {
    warning,
    error,
    exit_error
};

class Throw
{
private:
    std::string v_error;
    ErrorLevel v_level;
    int v_exitcode = 1;
    cpptrace::stacktrace v_trace;
    Throw(std::string error, ErrorLevel level, int exit, cpptrace::stacktrace trace);
    bool isError();
public:
    static Throw* Warning(std::string error);
    static Throw* Error(std::string error);
    static Throw* ExitError(std::string error);
    static Throw* ExitError(std::string error, int exit);

    static Throw* DynamicThrow(std::string error, ErrorLevel level);

    static bool Check(Throw* error);

    void Print();
};
