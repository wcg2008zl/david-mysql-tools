/* Copyright (C) 2000-2001 MySQL AB, 2008-2009 Sun Microsystems, Inc

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/*
  Static variables for heap library. All definied here for easy making of
  a shared library
*/

#ifndef _global_h
#include "heapdef.h"
#endif

LIST *heap_open_list=0,*heap_share_list=0;

#ifdef HAVE_PSI_INTERFACE
#ifdef THREAD
PSI_mutex_key hp_key_mutex_HP_SHARE_intern_lock;

static PSI_mutex_info all_heap_mutexes[]=
{
  { & hp_key_mutex_HP_SHARE_intern_lock, "HP_SHARE::intern_lock", 0}
  /*
    Note:
    THR_LOCK_heap is part of mysys, not storage/heap.
  */
};
#endif /* THREAD */

void init_heap_psi_keys()
{
#ifdef THREAD
  const char* category= "memory";
  int count;

  if (PSI_server == NULL)
    return;

  count= array_elements(all_heap_mutexes);
  PSI_server->register_mutex(category, all_heap_mutexes, count);
#endif /* THREAD */
}
#endif /* HAVE_PSI_INTERFACE */


