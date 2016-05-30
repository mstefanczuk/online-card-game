/**
 * Autor: Michał Stefańczuk
 */
#ifndef LOG_H
#define LOG_H

const std::string currentDateTime();
void printAndWriteLog(const char* tag, const char* text);
void printAndWriteLogString(const std::string tag, const std::string text);
void initFileName(std::string name);

#endif
