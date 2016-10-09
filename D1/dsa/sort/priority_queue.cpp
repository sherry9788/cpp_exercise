#include "priority_queue.h"

int power2(int n) {
	if (n == 0)
		return 1;
	else
		return 2 * power2(n - 1);
}