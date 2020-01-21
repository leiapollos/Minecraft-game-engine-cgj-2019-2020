#ifndef SINGLETON_H
#define SINGLETON_H

#include "NonCopyable.h"
#include "NonMovable.h"

class Singleton : public NonMovable, public NonCopyable {
};

#endif // SINGLETON_H