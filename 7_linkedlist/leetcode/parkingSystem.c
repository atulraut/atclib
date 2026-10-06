/***
    https://leetcode.com/problems/design-parking-system/
    Design Parking System

    Design a parking system for a parking lot. The parking
    lot has three kinds of parking spaces: big, medium,
    and small, with a fixed number of slots for each size.

    Implement the ParkingSystem class:

    ParkingSystem(int big, int medium, int small) Initializes
    object of the ParkingSystem class. The number of slots for
    each parking space are given as part of the constructor.
    bool addCar(int carType) Checks whether there is a parking
    space of carType for the car that wants to get into the parking
    lot. carType can be of three kinds: big, medium, or small,
    which are represented by 1, 2, and 3 respectively. A car can
    only park in a parking space of its carType. If there is no
    space available, return false, else park the car in that size
    space and return true.

    Input
    ["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
    [[1, 1, 0], [1], [2], [3], [1]]
    Output
    [null, true, true, false, false]

    Explanation
    ParkingSystem parkingSystem = new ParkingSystem(1, 1, 0);
    parkingSystem.addCar(1); // return true because there is 1 available slot for a big car
    parkingSystem.addCar(2); // return true because there is 1 available slot for a medium car
    parkingSystem.addCar(3); // return false because there is no available slot for a small car
    parkingSystem.addCar(1); // return false because there is no available slot for a big car. It is already occupied.

    Constraints:
    0 <= big, medium, small <= 1000
    carType is 1, 2, or 3
    At most 1000 calls will be made to addCar

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings *.c -lm

    Date: 18 Oct 2021
    Fair Oaks, CA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

typedef struct {
  int bigSlot;
  int medSlot;
  int smlSlot;
} ParkingSystem;

ParkingSystem* parkingSystemCreate(int big, int medium, int small) {
  ParkingSystem *parkSys = (ParkingSystem *)malloc(sizeof(ParkingSystem));
  parkSys->bigSlot = big;
  parkSys->medSlot = medium;
  parkSys->smlSlot = small;
  return parkSys;
}

bool parkingSystemAddCar(ParkingSystem* obj, int carType) {
  switch (carType) {
  case 1:
    if (obj->bigSlot > 0) {
      obj->bigSlot--;
      return true;
    } else {
      return false;
    }
  case 2:
    if (obj->medSlot > 0) {
      obj->medSlot--;
      return true;
    } else {
      return false;
    }
  case 3:
    if (obj->smlSlot > 0) {
      obj->smlSlot--;
      return true;
    } else {
      return false;
    }
  };
  return false;
}

void parkingSystemFree(ParkingSystem* obj) {
  free(obj);
}

int main (int argc, char **argv) {
  int ret = 0;

  ParkingSystem* parkingSystem =  parkingSystemCreate(1, 1, 0);
  ret = parkingSystemAddCar(parkingSystem, 1); // return true because there is 1 available slot for a big car
  debug("Output = %d", ret);
  ret = parkingSystemAddCar(parkingSystem, 2); // return true because there is 1 available slot for a medium car
  debug("Output = %d", ret);
  ret = parkingSystemAddCar(parkingSystem, 3); // return false because there is no available slot for a small car
  debug("Output = %d", ret);
  ret = parkingSystemAddCar(parkingSystem, 1); // return false because there is no available slot for a big car. It is
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=109 :Output = 1
   [main] L=111 :Output = 1
   [main] L=113 :Output = 0
   [main] L=115 :Output = 0
**/
