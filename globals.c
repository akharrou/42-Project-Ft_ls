
/*
**  Ft_ls -- Global Variable Definition(s).
*/

/*
**    DESCRIPTION
**         Dispatch table associating every single flag specifier to
**         its function (handler).
*/

// t_handler g_table[] =
// {
// 	{ '%', &mod_handler },
// 	{ 'c', &c_handler },
// 	{ 'i', &i_handler },
// 	{ 'u', &u_handler },
// 	{ 'f', &f_handler },
// 	{ 'b', &b_handler },
// 	{ 'o', &o_handler },
// 	{ 'd', &d_handler },
// 	{ 'x', &x_handler },
// 	{ 'X', &xx_handler },
// 	{ 's', &s_handler },
// 	{ 'r', &r_handler },
// 	{ 'p', &p_handler },
// 	{ '\0', NULL }
// };


#include "ft_ls.h"

t_flag g_flags[] =
{
	{ 'l', L_FLAG },
	{ 'a', A_FLAG },
	{ 'r', R_FLAG },
	{ 't', T_FLAG },
	{ 'R', F_FLAG },
	{ 'f', RR_FLAG },
	\
	{ '\0', 0 }
};
