#include "record.h"

int hash(int key) {
  return (key%TSIZE);
}
