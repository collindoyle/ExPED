/* grouptext.h : The interface of a set of functions which determine whether two text elements can be grouped to higher one
 * written by CHU Yimin
 * University of Tokyo
 */

#include "common.h"
#include "pedchar.h"
#include "pedphrase.h"


PED_BOOL is_groupable_to_phrase (pedphrase * phrase, pedchar * achar);

PED_BOOL is_groupable_to_line (pedline * line, pedphrase * phrase);
