#include "interrupt.h"


int upgrade (int *m_isUpgraded) {
      printf ("\n[upgrade] interrupt.c ");
      *m_isUpgraded = 1;
      printf ("\n[upgrade] isUpgraded = %d ", *m_isUpgraded);
      *m_isUpgraded = 3;
      printf ("\n[upgrade] isUpgraded = %d \n", *m_isUpgraded);
      return 0;
}

