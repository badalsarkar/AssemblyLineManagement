// Name:Badal Sarkar
// Seneca Student ID:137226189
// Seneca email:bsarkar2@myseneca.ca
// Date of completion:November 24, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>

    class Utilities
    {
        size_t m_widthField{0};
        static char m_delimiter;
        public:
        void setFieldWidth(size_t); //sets the field width
        size_t getFieldWidth()const;    //returns the field width
        const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);   //extracts token from first parameter
        static void setDelimiter(const char);   //sets the delimiter for this class to the character received
        const char getDelimiter()const;     //returns the delimiter character of the current object
    };


    //free helper
    void trim(std::string&);
#endif
