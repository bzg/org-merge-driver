/**
 * @file org_document.c
 */

#include "debug.h"
#include "config.h"
#include "gl_array_list.h"
#include "gl_list.h"

#include "doc_elt.h"
#include "org_heading.h"
#include "org_text.h"

#include "org_document.h"

struct org_document
{
  doc_elt elt;
  gl_list_t subheadings;
  gl_list_t subtext;
};

typedef struct org_document org_document;

/* Forward Declarations */
static doc_elt_ops_print     org_print_op;
static doc_elt_ops_isrelated org_isrelated_op;
static doc_elt_ops_compare   org_compare_op;
static doc_elt_ops_merge     org_merge_op;
static doc_elt_ops_isupdated org_isupdated_op;

/* Declaration of org_element operations table */
doc_elt_ops org_document_ops = {
  /* printing */
  .print         = &org_print_op,
  /* comparing */
  .isrelated     = &org_isrelated_op,
  .compare       = &org_compare_op,
  /* merging */
  .merge         = &org_merge_op,
  .isupdated     = &org_isupdated_op
};

/* Constructor, Destructor */
org_document *
org_document_create_empty (doc_elt_ops *ops)
{
  org_document *d = malloc (sizeof (org_document));
  doc_elt_set_ops (&(d->elt), ops);
  doc_elt_set_type (&(d->elt), ORG_DOCUMENT);
  d->subheadings = gl_list_nx_create_empty (GL_ARRAY_LIST, NULL,
					    NULL, NULL, true);
  d->subtext = gl_list_nx_create_empty (GL_ARRAY_LIST, NULL,
					NULL, NULL, true);
  return d;
}

void
org_document_free (org_document *self)
{
  free (self);
}

/* Adding sub elements */
void
org_document_add_text_last (org_document *document, doc_src src, org_text *text)
{
  /* wrap the element in a doc_ref, and add it to the list */
  doc_ref *ref = doc_ref_create_empty ();
  doc_ref_set_src (ref, src);
  doc_ref_set_elt (ref, (doc_elt *) text);
  gl_list_nx_add_last (document->subtext, ref);
  return;
}

void
org_document_add_heading_last (org_document *document, doc_src src, org_heading *heading)
{
  /* wrap the element in a doc_ref, and add it to the list */
  doc_ref *ref = doc_ref_create_empty ();
  doc_ref_set_src (ref, src);
  doc_ref_set_elt (ref, (doc_elt *) heading);
  gl_list_nx_add_last (document->subheadings, ref);
  return;
}

void
org_document_print (org_document *doc, print_ctxt *ctxt, doc_stream *out)
{
  debug_msg (DOC_ELT, 3, "Print merging org_document\n");
  debug_msg (DOC_ELT, 5, "Printing text\n");
  doc_reflist_print (doc->subtext, ctxt, out);
  debug_msg (DOC_ELT, 3, "Printing headings\n");
  doc_reflist_print (doc->subheadings, ctxt, out);
  return;
}

void
org_document_merge (org_document *anc, org_document *desc, merge_ctxt *ctxt)
{
  debug_msg (DOC_ELT, 3, "Merging org_document\n");
  debug_msg (DOC_ELT, 5, "Merging text\n");
  doc_reflist_merge (anc->subtext, desc->subtext, ctxt);
  debug_msg (DOC_ELT, 3, "Merging headings\n");
  doc_reflist_merge (anc->subheadings, desc->subheadings, ctxt);
  return;
}

/* doc_elt interface */
static void
org_print_op (doc_ref *ref, print_ctxt *ctxt, doc_stream *out)
{
  /**
   * @todo make sure the doc merge print
   */
  org_document *doc = (org_document *) doc_ref_get_elt (ref);
  org_document_print (doc, ctxt, out);
  return;
}

static bool
org_isrelated_op (doc_ref *local, doc_ref *remote, void *context)
{
  /* all org_documents are relatable */
  return true;
}

static int
org_compare_op (doc_elt *a, doc_src a_src, doc_elt *b, doc_src b_src)
{
  /* all org_documents are identical */
  return true;
}

static void
org_merge_op (doc_ref *a, doc_ref *b, merge_ctxt *ctxt)
{
  /**
   * @todo actually merge things
   */
  return;
}

static bool
org_isupdated_op (doc_ref *a)
{
  /**
   * @todo implement an actual function
   */
  /* check if the children are updated */
  /* check if this element is updated */
  return true;
}
