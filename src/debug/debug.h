#ifndef _ABANDON_DEBUG_H_
#define _ABANDON_DEBUG_H_

#ifdef DEBUG // use -DDEBUG

#define ASSERT(info) std::cout << "[" << __FILE__ << \
    "," << __LINE__ << "]" << info << std::endl;

#else

#define ASSERT(info)

#endif

#endif