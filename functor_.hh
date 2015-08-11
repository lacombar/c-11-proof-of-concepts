#include <functional>

typedef void (*cb_t)(void *);

void test(cb_t fn, void *arg);
void test(std::function<void(void)> f);
