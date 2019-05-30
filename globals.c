
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
	{  '1',  ONE_FLAG, compare_by_ascii,  reverse_compare_by_ascii  },
	{  'R',  RR_FLAG,  compare_by_ascii,  reverse_compare_by_ascii  },
	{  'l',  L_FLAG,   compare_by_ascii,  reverse_compare_by_ascii  },
	{  'a',  A_FLAG,   compare_by_ascii,  reverse_compare_by_ascii  },
	{  'r',  R_FLAG,   compare_by_ascii,  reverse_compare_by_ascii  },
	{  't',  T_FLAG,   &compare_by_time,  &reverse_compare_by_time  },
	{  's',  S_FLAG,   &compare_by_size,  &reverse_compare_by_size  },
	{  'f',  F_FLAG,   &compare_by_none,  &compare_by_none          },
	\
	{ '\0', 0, NULL, NULL}
};
