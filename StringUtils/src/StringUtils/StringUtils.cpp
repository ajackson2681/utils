#include "StringUtils/StringUtils.hpp"
#include <cstdarg>
#include <stdexcept>
#include <sstream>

namespace StringUtils
{
    std::string Format(const char* format_, ...) __attribute__ ((format(printf, 1, 2)))
    {
        va_list args;
        va_start(args, format_);

        // Get the size of the formatted string
        int size = std::vsnprintf(nullptr, 0, format_, args);
        va_end(args);

        if (size < 0) {
            throw std::runtime_error("Error formatting string");
        }

        // Create a string with the required size
        std::string result(size, '\0');

        // Format the string into the result
        va_start(args, format_);
        std::vsnprintf(&result[0], size + 1, format_, args);
        va_end(args);

        return result;
    }

    std::string ToLower(const std::string& str)
    {
        std::string result = str;
        for (char& c : result) {
            result += ((c >= 'A') && (c <= 'Z')) ? (c - 'A' + 'a') : c;
        }
        return result;
    }

    std::string ToUpper(const std::string& str)
    {
        std::string result = str;
        for (char& c : result) {
            result += ((c >= 'a') && (c <= 'z')) ? (c - 'a' + 'A') : c;
        }
        return result;
    }

    std::string Spaces(size_t numSpaces)
    {
        return std::string(numSpaces, ' ');
    }

    std::string FormatTime(const std::string& format, time_t time)
    {
        char buffer[256];
        struct tm* timeinfo = localtime(&time);
        strftime(buffer, sizeof(buffer), format.c_str(), timeinfo);
        return std::string(buffer);
    }

    void StringReplace(std::string& str, const std::string& from, const std::string& to)
    {
        if (from.empty()) {
            return;
        }

        size_t startPos = 0;
        while ((startPos = str.find(from, startPos)) != std::string::npos) {
            str.replace(startPos, from.length(), to);
            startPos += to.length();
        }
    }
    
    std::vector<std::string> Tokenize(const std::string& s, const char delimiter)
    {
        std::string token;
        std::vector<std::string> tokens;

        if (delimiter == '\0')  {
            std::istringstream iss(s);
            while (iss >> token) {
                tokens.push_back(token);
            }
        }
        else {
            std::stringstream ss(s);
            // Tokenize using the specified delimiter
            while (std::getline(ss, token, delimiter)) {
                tokens.push_back(token);
            }
        }
        
        return tokens;
    }
};