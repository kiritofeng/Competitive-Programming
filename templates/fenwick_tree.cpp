#include <assert.h>

/**
 * A fenwick tree is a data structure
 * It supports Range Sum and Point Updates
 * It is possible to extend these
 * to range updates and point queries
 * The two basic operations are:
 * Query: Find the sum of all elements up
 * to a given index in O(log N)
 * Update: Adds a certain value to a single
 * element in O(log N)
 */
 
const int MAXN = 100004;
long long bit[MAXN];

void update(int ind, int val) {
  for(;ind < MAXN;ind += ind & -ind)
    bit[ind] += val;
}

long long query(int ind) {
  long long ret = 0;
  for(;ind;ind -= ind & -ind)
    ret += bit[ind];
  return ret;
}

int main() {
  update(1, 5);
  update(5, 5);
  assert(query(5) == 10);
  assert(query(2) == 5);
  update(5, -5);
  assert(query(10) == 5);
}
