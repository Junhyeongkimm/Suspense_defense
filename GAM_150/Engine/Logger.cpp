/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    TODAY¡¯S DATE
*/

#include <iostream>
#include "Logger.h"
CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point start) : min_level(severity), out_stream("Trace.log") {
    if (use_console == true) {
        out_stream.set_rdbuf(std::cout.rdbuf());
    }
}

CS230::Logger::~Logger() {
    out_stream.flush();
    out_stream.close();
}

void CS230::Logger::log(CS230::Logger::Severity severity, std::string message) {
    if (min_level <= severity)
    {
        switch (severity)
        {
        case CS230::Logger::Severity::Verbose:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t" << "Verbose\t" << message << std::endl;
            break;
        case CS230::Logger::Severity::Debug:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t" << "Debug\t" << message << std::endl;
            break;
        case CS230::Logger::Severity::Event:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t" << "Event\t" << message << std::endl;
            break;
        case CS230::Logger::Severity::Error:
            out_stream.precision(4);
            out_stream << '[' << std::fixed << seconds_since_start() << "]\t" << "Error\t" << message << std::endl;
            break;
        default:
            break;
        }
    }
    return;
}

double CS230::Logger::seconds_since_start()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - start_time).count();
    return dt;

}