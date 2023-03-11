#include <mutex>
#include "config.h"

using namespace std;

namespace global {
    int SHARED_DATA = 10;
    mutex MUTEX;
}