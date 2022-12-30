#include "SDCard.hpp"
#include "error.h"

// macro to handle errors, prints the error message and returns the error code
#define ERROR_HANDLER(message, error) { \
        Serial.print(message); Serial.print(" "); Serial.print(error); \
        return error; \
    }

bool SDCard::init() {
    if(!Serial) Serial.begin(9600);
    return SD.begin() ? true : false;
}

/*
    Essentially all the files are stored in the SD card as a binary file.
    So the file is opened, the message is written and the file is closed, at the end its all just some kinda of text file.
*/

// creates a file in the SD card, given th path and the message to write
int SDCard::writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE); // open file for writing
    if(!file) ERROR_HANDLER(ERROR_FILE_OPEN_MSG, ERROR_FILE_OPEN); // if file is not opened, print error message

    file.print(message) ?  Serial.println("File written") : Serial.println("Write failed"); // if file is written, print success message, else print error message
    file.close();

    return __null;
}

// appends a message to a file, given the path and the message to append
int SDCard::appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file) ERROR_HANDLER(ERROR_FILE_APPEND_MSG, ERROR_FILE_APPEND);

    file.print(message) ?  Serial.println("Message appended") : Serial.println("Append failed");
    file.close();

    return __null;
}

// reads a file, given the path and returns the data as a string
String SDCard::readFile(fs::FS &fs, const char * path) {
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path, FILE_READ);
    if(!file) ERROR_HANDLER(ERROR_FILE_READ_MSG, String(ERROR_FILE_READ));

    String data = file.readString();
    file.close();
    return data;
}