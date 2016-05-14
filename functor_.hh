#include <functional>

typedef void (*cb_t)(void *);

using cb_pair_t = std::pair<cb_t, void *>;
void test(cb_pair_t);
void test(cb_t fn, void *arg);
void test(std::function<void(void)> f);
