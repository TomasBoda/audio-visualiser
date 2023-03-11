#include <mutex>

namespace global {
    extern int SHARED_DATA;
    extern std::mutex MUTEX;
}