#include <fountain.h>

//#define RECEIVER
#define SENDER

#ifdef RECEIVER
#include <receiver.h>
#else
#include <sender.h>
#endif
