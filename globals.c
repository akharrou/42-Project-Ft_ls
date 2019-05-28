
/*
**  Ft_ls -- Global Variable Definition(s).
*/

#include "ft_ls.h"

/*
**    DESCRIPTION
**         Dispatch table associating every flag with the
**         unique bit it is represented by & its comparsion.
**         function if it has one.
*/

t_flag g_flags[] =
{
	{ '1', ONE_FLAG, NULL, NULL },
	{ 'R', RR_FLAG, NULL, NULL },
	{ 'l', L_FLAG, NULL, NULL },
	{ 'a', A_FLAG, NULL, NULL },
	{ 'r', R_FLAG, NULL, NULL },
	{ 't', T_FLAG, &compare_by_time, &reverse_compare_by_time },
	{ 'f', F_FLAG, &compare_by_none, &compare_by_none },
	\
	{ '\0', 0, NULL, NULL}
};
