#ifndef LOGGER_H
#define LOGGER_H 

#include <string>

namespace kalsengi
{
    class Logger
    {
        private:
            std::string _filePath;

            static const int a;
            static const char ERROR_FILE_NOT_FOUND_STR_FORMAT[];

        public:
            Logger (std::string filePath);

            void    log (std::string msg);

    };
}

#endif /* LOGGER_H */
