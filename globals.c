
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
	{ 'l', L_FLAG },      // A_FLAG = (1 << 0),						We get more information / include in our expansion
	{ 'a', A_FLAG },      // L_FLAG = (1 << 1),						We get more information
	{ 'r', R_FLAG },      // R_FLAG = (1 << 2),						We change all our compare functions
	{ 't', T_FLAG },      // T_FLAG = (1 << 3),						Use the time_sort, or rev_time sort?
	{ 'R', F_FLAG },      // F_FLAG = ((1 << 4) | A_FLAG),			Use ZERO return cmpfunction
	{ 'f', RR_FLAG },     // RR_FLAG = (1 << 5)						Used in the reccursive call
	\
	{ '\0', 0 }
};
