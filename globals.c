
/*
**  Ft_ls -- Global Variable Definition(s).
*/

#include "ft_ls.h"

t_flag g_flags[] =
{
	{ 'a',
	 &ls_a_handler },

	{ 'l',
	 &ls_l_handler },

	{ 'r',
	 &ls_r_handler },

	{ 't',
	 &ls_t_handler },

	{ 'R',
	 &ls_rr_handler },

	{ 'f',
	 &ls_f_handler }
};
