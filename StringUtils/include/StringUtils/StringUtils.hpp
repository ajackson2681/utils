#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
    /**
     * @brief Use printf semantics to format a string
     * 
     */
    std::string Format(const char* format_, ...) __attribute__ ((format(printf, 1, 2)));

    /**
     * @brief Converts a string to all lowercase
     * 
     * @param str 
     * @return std::string 
     */
    std::string ToLower(const std::string& str);

    /**
     * @brief Converts a string to all uppercase
     * 
     * @param str 
     * @return std::string 
     */
    std::string ToUpper(const std::string& str);

    /**
     * @brief Returns a string containing the specified number of spaces
     * 
     * @param numSpaces 
     * @return std::string 
     */
    std::string Spaces(size_t numSpaces);

    /**
     * @brief Formats a time value according to the specified format. See 
     * strftime for format specifiers.
     * 
     * @param format 
     * @param time 
     * @return std::string 
     */
    std::string FormatTime(const std::string& format, time_t time);

    /**
     * @brief Replaces all occurrences of a substring with another string
     * 
     * @param str 
     * @param from 
     * @param to 
     */
    void StringReplace(std::string& str, const std::string& from, const std::string& to);

    /**
     * @brief Splits a string into tokens based on whitespace or a specified delmiter
     * if no delimiter is specified, whitespace will be used as the default delimiter
     * 
     * @param s 
     * @param delimiter
     * @return std::vector<std::string> 
     */
    std::vector<std::string> Tokenize(const std::string& s, const char delimiter = '\0');

};