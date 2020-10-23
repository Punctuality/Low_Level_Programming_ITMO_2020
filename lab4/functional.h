//
//  functional.h
//  TestC
//
//  Created by Sergey Fedorov on 10/23/20.
//

#ifndef functional_h
#define functional_h

#include "linked_list.h"

// For anonymous functions
#define lambda(l_ret_type, l_arguments, l_body)        \
  ({                                                   \
   l_ret_type l_anonymous_functions_name l_arguments   \
   l_body                                              \
   &l_anonymous_functions_name;                        \
   })

void foreach(const linked_list list, void(*func)(value));

linked_list map(const linked_list list, value(*op)(value));

void map_mut(const linked_list list, value(*op)(value));

value fold_l(const linked_list list, value acc, value(*op)(value, value));

linked_list unfold_l(value init, size_t length, value(*op)(value)); // Basically same as iterate, but more canonical;

#endif /* functional_h */
