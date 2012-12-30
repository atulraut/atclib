/***
* Aim : Implement Polymorphism using C.
* Date : Thursday, December 20 2012, 11:50 PM
* File : public_defs.h
*/
#ifndef PUBLIC_DEFS_H_
#define PUBLIC_DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include "plug-01.h"
#include "plug-02.h"

typedef struct {
  int (*init) ();
  int (*close) ();
} at_base_type;

typedef struct {
	at_base_type *handle;
} at_v_table_type;

enum at_type {
  PLUG_01=0,
  PLUG_02,
  LAST
}at_plugin_type_list;

at_base_type plug_1_handle;  // plug-in-01 Handle
at_base_type plug_2_handle;  // plug-in-02 Handle
#endif
