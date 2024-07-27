#ifndef _ABANDON_DEBUG_H_
#define _ABANDON_DEBUG_H_

#ifdef DEBUG // use -DDEBUG

#define ASSERT(info) std::cout << "\e[0;31m[" << __FILE__ << \
    "," << __LINE__ << "]" << info << "\e[0m" << std::endl; // red

#define INFO(info) std::cout << "\e[0;32m" << info << "\e[0m" << std::endl; // green

#else
#define ASSERT(info)
#define INFO(info)
#endif

#endif