/*
typedef enum io_status_ {
    SUCCESS,
    ERROR_OPEN,
    ERROR_READ,
    ERROR_MEM,
    } io_status;
*/
#ifndef IO_STATUS_H
#define IO_STATUS_H

enum class io_status{
    success,
    eof,
    no_open,
    format, // бывший error_read
    memory,
};
#endif