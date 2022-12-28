#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#include <FS.h>
#include <SD.h>
#include <SPI.h>

class SDCard {
public:
  bool init();
  int writeFile(fs::FS &fs, const char *path, const char *message);
  int appendFile(fs::FS &fs, const char *path, const char *message);
  String readFile(fs::FS &fs, const char *path);
};

#endif