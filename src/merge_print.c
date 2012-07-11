#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "gl_list.h"

#include "merge_delta.h"
#include "doc_stream.h"
#include "doc_elt.h"
#include "doc_elt_ops.h"
#include "merge_print_ctxt.h"
#include "merge_print.h"

#include "merge_tree.h"
#include "merge_delta.h"
#include "doc_elt.h"
    
#define FUNC_NAME merge_print
#define CONTEXT_DOWN merge_print_ctxt
#define CONTEXT_GLOBAL doc_stream
//#define CONTEXT_LOCAL

#define START_FUNC							\
  merge_delta *delta = merge_node_get_delta (tree);			\
  doc_elt *elt = merge_delta_get_elt(delta);				\
  if (elt != NULL)							\
    {									\
     doc_elt_merge_print (elt, delta, &new_ct_down, ct_glob);		\
    }

//#define END_FUNC

#include "ltree_apply.h"

#undef FUNC_NAME
#undef CONTEXT_DONWARD
#undef CONTEXT_GLOBAL
#undef START_FUNC
#undef END_FUNC
