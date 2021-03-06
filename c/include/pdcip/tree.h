/**
 * @file tree.h
 * @author Derek Huang
 * @brief C header for general tree implementations
 * @copyright MIT License
 */

#ifndef PDCIP_TREE_H_
#define PDCIP_TREE_H_

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * A general multi-child tree for numeric data.
 */
typedef struct gen_tree_ {
  double value;
  size_t n_children;
  struct gen_tree_ **children;
} gen_tree;

gen_tree *
gen_tree_malloc(double, size_t, gen_tree **);

/**
 * Allocate a `gen_tree` instance on the heap with zero children.
 *
 * @param v `double` value to set the `gen_tree` node with
 * @returns `gen_tree *`
 */
#define gen_tree_malloc_default(v) gen_tree_malloc(v, 0, NULL)

/**
 * Allocate a `gen_tree` instance on the heap with no children and `NAN` value.
 *
 * @returns `gen_tree *`
 */
#define gen_tree_malloc_empty() gen_tree_malloc(NAN, 0, NULL);

/**
 * Free a `gen_tree` instance on the heap, but not its children.
 *
 * @param t `gen_tree *` pointer to `gen_tree` to free
 * @returns `void`
 */
#define gen_tree_free(t) free(t)

void
gen_tree_set_children(gen_tree *, size_t, gen_tree **);

/**
 * Reset the children of a `gen_tree *` without freeing the existing children.
 *
 * `n_children` is set to zero and the children are set to `NULL`.
 *
 * @param t `gen_tree *` pointer to `gen_tree` whose children we reset
 */
#define get_tree_reset_children(t) gen_tree_set_children(t, 0, NULL)

void
gen_tree_free_children_(gen_tree *, bool);

/**
 * Free the direct children of a `gen_tree *`.
 *
 * @param t `gen_tree *` whose direct children we wish to free
 * @returns `void`
 */
#define gen_tree_free_children(t) gen_tree_free_children_(t, false)

/**
 * Free all the child subtrees of a `gen_tree *`.
 *
 * @param t `gen_tree *` whose child subtrees we wish to free
 * @returns `void`
 */
#define gen_tree_free_children_deep(t) gen_tree_free_children_(t, true)

void
gen_tree_free_deep(gen_tree *);

gen_tree **
gen_tree_make_children(size_t, const double *);

void
gen_tree_free_children_array_(gen_tree **, size_t, bool);

/**
 * Frees `gen_tree *` array returned by `gen_tree_make_children`.
 *
 * This macro does not free any children of the `gen_tree *` specified; use
 * `gen_tree_free_children_array_deep` for that purpose.
 *
 * @param ar `gen_tree *` to contiguous `gen_tree *` to free
 * @param n `size_t` giving number of `gen_tree *` to free in `ar`
 * @returns `void`
 */
#define gen_tree_free_children_array(ar, n) \
  gen_tree_free_children_array_(ar, n, false)

/**
 * Deep frees `gen_tree *` array returned by `gen_tree_make_children`.
 *
 * Frees the children of the `gen_tree *` specified by `ar`.
 *
 * @param ar `gen_tree *` to contiguous `gen_tree *` to free
 * @param n `size_t` giving number of `gen_tree *` to free in `ar`
 * @returns `void`
 */
#define gen_tree_free_children_array_deep(ar, n) \
  gen_tree_free_children_array_(ar, n, true)

gen_tree **
gen_tree_dfs(const gen_tree *, size_t *);

/*
gen_tree **
gen_tree_bfs(const gen_tree *, size_t *);
*/

/**
 * A binary tree for numeric data.
 */
typedef struct binary_tree_ {
  double value;
  struct binary_tree_ *left;
  struct binary_tree_ *right;
} binary_tree;

binary_tree *
binary_tree_malloc(double, binary_tree *, binary_tree *);

/**
 * Allocate a `binary_tree` instance on the heap with zero children.
 *
 * @returns `binary_tree *`
 */
#define binary_tree_malloc_default(v) binary_tree_malloc(v, NULL, NULL)

/**
 * Allocate a `binary_tree` instance on heap with no children and `NAN` value.
 *
 * @returns `binary_tree *`
 */
#define binary_tree_malloc_empty() binary_tree_malloc(NAN, NULL, NULL)

/**
 * Free a `binary_tree` instance on the heap, but not its children.
 *
 * @param t `binary_tree *` pointer to `binary_tree` to free
 * @returns `void`
 */
#define binary_tree_free(t) free(t)

void
binary_tree_free_children_(binary_tree *, bool);

/**
 * Free the direct children of a `binary_tree *`.
 *
 * @param t `binary_tree *` whose direct children we wish to free
 * @returns `void`
 */
#define binary_tree_free_children(t) binary_tree_free_children_(t, false)

/**
 * Free all the child subtrees of a `binary_tree *`.
 *
 * @param t `gen_tree *` whose child subtrees we wish to free
 * @returns `void`
 */
#define binary_tree_free_children_deep(t) binary_tree_free_children_(t, true)

void
binary_tree_free_deep(binary_tree *);

binary_tree *
binary_tree_insert(binary_tree *, double);

double *
binary_tree_sorted_values(const binary_tree *, size_t *);

/*
binary_tree **
binary_tree_bfs(const binary_tree *, size_t *);

binary_tree **
binary_tree_dfs(const binary_tree *, size_t *);
*/

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* PDCIP_TREE_H_ */
