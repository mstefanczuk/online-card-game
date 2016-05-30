/**
 * Autor: Michał Stefańczuk
 */
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>

std::string fileName;

// Get current date/time, format is YYYY-MM-DD_HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);

    return buf;
}

void printAndWriteLog(const char* tag, const char* text)
{
  printf("%s: %s\n", tag, text);

  std::string contentString = currentDateTime() + " " + std::string(tag) + ": " + std::string(text);

  const char* contentChar = contentString.c_str();

  FILE* pFile = fopen(fileName.c_str(), "a");
  fprintf(pFile, "%s\n", contentChar);
  fclose(pFile);
}

void printAndWriteLogString(const std::string tag, const std::string text)
{
  printf("%s: %s\n", tag.c_str(), text.c_str());

  std::string contentString = currentDateTime() + " " + tag + ": " + text;

  const char* contentChar = contentString.c_str();

  FILE* pFile = fopen(fileName.c_str(), "a");
  fprintf(pFile, "%s\n", contentChar);
  fclose(pFile);
}

void initFileName(std::string name) {
	fileName = name;
}

