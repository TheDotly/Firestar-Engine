#include "DataTypes/Throw.h"
#include "Debug/Debug.h"

#define WARN_COLOUR fg(fmt::rgb(255,255,143))
#define ERROR_COLOUR fg(fmt::rgb(255,49,49))

void Throw::Print() {
    switch (v_level)
    {
        case warning:
        fmt::print(WARN_COLOUR | fmt::emphasis::bold, "⚠ WARN: ");
        fmt::print(WARN_COLOUR, "{}\n", v_error.c_str());
        v_trace.print();
        break; 
        case error:
        fmt::print(ERROR_COLOUR | fmt::emphasis::bold, "⚠ ERROR: ");
        fmt::print(ERROR_COLOUR, "{}\n", v_error.c_str());
        v_trace.print();
        break;
        case exit_error:
        fmt::print(ERROR_COLOUR | fmt::emphasis::bold, "⚠ ERROR: ");
        fmt::print(ERROR_COLOUR, "{}\n", v_error.c_str());
        v_trace.print();
        exit(v_exitcode);
        break;
    default:
        break;
    }
}

Throw::Throw(std::string error, ErrorLevel level, int exit, cpptrace::stacktrace trace){
    v_error = error;
    v_level = level;
    v_exitcode = exit;
    v_trace = trace;
}

Throw* Throw::Error(std::string error) {
    return new Throw(error, ErrorLevel::error,-1 , cpptrace::generate_trace());
}

Throw* Throw::ExitError(std::string error){
    return new Throw(error, exit_error,-1 , cpptrace::generate_trace());
}

Throw* Throw::ExitError(std::string error, int exit){
    return new Throw(error, exit_error,exit , cpptrace::generate_trace());
}

Throw* Throw::Warning(std::string error){
    return new Throw(error, ErrorLevel::warning,-1 , cpptrace::generate_trace());
}

Throw* Throw::DynamicThrow(std::string error, ErrorLevel level){
    switch (level)
    {
    case ErrorLevel::warning: return Throw::Warning(error);
    case ErrorLevel::error: return Throw::Error(error);
    case ErrorLevel::exit_error: return Throw::ExitError(error);
    default: return Throw::Warning(error);
    }
}

bool Throw::Check(Throw* error){
    if(error == nullptr){
        return true;
    }

    error->Print();
    
    return error->isError();
}

bool Throw::isError(){
    if(v_level == warning){
        return false;
    }
    return true;
}