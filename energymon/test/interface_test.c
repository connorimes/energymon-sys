#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include "energymon-default.h"

int main() {
  energymon impl;
  energymon_get_default(&impl);

  char source[100];
  impl.fsource(source, sizeof(source));
  printf("Initializing reading from %s\n", source);
  assert(impl.finit(&impl) == 0);
  uint64_t result = impl.fread(&impl);
  assert(result >= 0);
  printf("Got reading: %"PRIu64"\n", result);
  assert(impl.ffinish(&impl) == 0);
  printf("Finished reading from %s\n", source);

  return 0;
}
