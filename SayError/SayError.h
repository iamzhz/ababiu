#ifndef _ABANDON_SAYERROR_H_
#define _ABANDON_SAYERROR_H_

#include "../include.h"

void sayError(int line, int column, std::string info);
void sayError(std::string info);
#endif