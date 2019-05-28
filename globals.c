
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
	{ 'R', RR_FLAG, NULL, NULL },
	{ 'l', L_FLAG, NULL, NULL },
	{ 'a', A_FLAG, NULL, NULL },
	{ 'r', R_FLAG, NULL, NULL },
	{ 't', T_FLAG, &sort_by_time, &sort_by_rev_time },
	{ 'f', F_FLAG, &sort_by_nosort, &sort_by_nosort },
	\
	{ '\0', 0, NULL, NULL}
};
