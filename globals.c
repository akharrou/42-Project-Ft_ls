
/*
**  Ft_ls -- Global Variable Definition(s).
*/

#include "ft_ls.h"

/*
**    DESCRIPTION
**         Dispatch table associating every flag with the
**         unique bit it is represented by.
*/

t_flag g_flags[] =
{
	{ 'R', RR_FLAG, NULL, NULL },     // RR_FLAG = (1 << 5)						Used in the reccursive call
	{ 'l', L_FLAG, NULL, NULL },      // A_FLAG = (1 << 0),						We get more information / include in our expansion
	{ 'a', A_FLAG, NULL, NULL },      // L_FLAG = (1 << 1),						We get more information
	{ 'r', R_FLAG, NULL, NULL },      // R_FLAG = (1 << 2),						We change all our compare functions
	{ 't', T_FLAG, &sort_by_time, &sort_by_rev_time },      // T_FLAG = (1 << 3),						Use the time_sort, or rev_time sort?
	{ 'f', F_FLAG, &sort_by_nosort, &sort_by_nosort },      // F_FLAG = ((1 << 4) | A_FLAG),			Use ZERO return cmpfunction
	\
	{ '\0', 0 }
};
