#include "logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <boost/format.hpp>

using namespace kalsengi;
using namespace std;

const int Logger::a = 2;
const char Logger::ERROR_FILE_NOT_FOUND_STR_FORMAT[] = "ERROR: %s couldn't be opened.";

Logger::Logger (string filePath) : _filePath(filePath)
{
    ofstream file (filePath);

    if (file.is_open()) {
        time_t date = chrono::system_clock::to_time_t( chrono::system_clock::now() );

        file << ctime(&date);

        file.close();
    } else {
        cerr << boost::format(ERROR_FILE_NOT_FOUND_STR_FORMAT) % filePath << endl;
    }
}

void Logger::log (string msg)
{
    ofstream file (_filePath, ios::app);

    if (file.is_open()) {

        file << msg << endl;

        file.close();
    } else {
        cerr << boost::format(ERROR_FILE_NOT_FOUND_STR_FORMAT) % _filePath << endl;
    }
}
