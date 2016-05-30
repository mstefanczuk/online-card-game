/**
 * Autor: Michał Stefańczuk
 */
#ifndef LOG_H
#define LOG_H

void printAndWriteLog(const char* tag, const char* text);
const std::string currentDateTime();
void printAndWriteLogString(const std::string tag, const std::string text);

#endif
