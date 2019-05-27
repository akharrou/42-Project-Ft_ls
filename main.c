/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:52:48 by akharrou          #+#    #+#             */
/*   Updated: 2019/05/26 19:34:55 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
**
**    Handled Flags:
**
**       -a      Include directory entries whose names begin with a dot (.).
**
**       -l      (The lowercase letter ``ell''.) List in long format. (See
**               below.) If the output is to a terminal, a total sum for all
**               the file sizes is output on a line before the long listing.
**
**       -R      Recursively list subdirectories encountered.
**
**       -r      Reverse the order of the sort to get reverse lexicographical
**               order or the oldest entries first (or largest files last, if
**               combined with sort by size
**
**       -t      Sort by time modified (most recently modified first) before
**               sorting the operands by lexicographical order.
**
**
**    | -- file mode -- | -- number of links -- | -- owner name -- | -- group name -- | -- number of bytes in the file -- | -- abbreviated month -- | -- day-of-month file was last modified -- | -- hour file last modified -- | -- minute file last modified -- | -- and the pathname.
**          drwx------               16                akharrou          2018_october                12288                            May                              20                                     16                                   :22                         .
**
**
**             $> drwx------  16 akharrou  2018_october    12288 May 20 16:22 .
**
**
**    Allowed Functions:
**
**
**        ◦ stat
**        ◦ lstat
**
**        ◦ getpwuid
**        ◦ getgrgid
**
**        ◦ getxattr
**        ◦ tcgetattr
**        ◦ listxattr
**
**        ◦ readlink
**
**        ◦ time
**        ◦ ctime
**
**
**        ◦ opendir
**        ◦ readdir
**        ◦ closedir
**
**        ◦ write
**        ◦ malloc
**        ◦ free
**
**        ◦ strerror
**        ◦ perror
**        ◦ exit



** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**  opendir:
**
**       NAME
**            opendir - open a directory
**
**       PROTOTYPE
**            DIR
**                   *opendir(const char *);
**
**       DESCRIPTION
**            The opendir() function opens a directory stream corresponding
**            to the directory named by the dirname argument. The directory
**            stream is positioned at the first entry. If the type DIR, is
**            implemented using a file descriptor, applications will only
**            be able to open up to a total of {OPEN_MAX} files and
**            directories. A successful call to any of the exec functions
**            will close any directory streams that are open in the calling
**            process.
**
**        RETURN VALUE
**             Upon successful completion, opendir() returns a pointer to an
**             object of type 'DIR'. Otherwise, a null pointer is returned and
**             errno is set to indicate the error.
**
** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**  readdir:
**
**       NAME
**            readdir - read (the entry) a directory
**
**       PROTOTYPE
**            struct dirent
**                   *readdir(DIR *dirp);
**
**       DESCRIPTION
**            The readdir() function returns a pointer to a structure
**            representing the directory entry at the current position
**            in the directory stream specified by the argument dirp,
**            and positions the directory stream at the next entry.
**
**            It returns a null pointer upon reaching the end of the directory
**            stream. The structure dirent defined by the <dirent.h> header
**            describes a directory entry.
**
**            If entries for dot or dot-dot exist, one entry will be returned
**            for dot and one entry will be returned for dot-dot; otherwise
**            they will not be returned.
**
**        RETURN VALUE
**             Upon successful completion, readdir() returns a pointer to an
**             object of type struct 'dirent'.
**
**             When an error is encountered, a null pointer is returned and
**             errno is set to indicate the error.
**
**             When the end of the directory is encountered, a null pointer
**             is returned and errno is not changed.
**
** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**  closedir:
**
**       NAME
**            closedir - close a directory
**
**       PROTOTYPE
**            int
**                   closedir(DIR *dirp);
**
**       DESCRIPTION
**            The closedir() function closes the directory stream referred
**            to by the argument 'dirp'. Upon return, the value of 'dirp'
**            may no longer point to an accessible object of the type DIR.
**            If a file descriptor is used to implement type DIR, that file
**            descriptor will be closed.
**
**        RETURN VALUE
**             Upon successful completion, closedir() returns 0. Otherwise,
**             -1 is returned and errno is set to indicate the error.
**
**        ERRORS
**             The closedir() function may fail if:
**
**               [EBADF]
**                    The dirp argument does not refer to an open directory
**                    stream.
**
**               [EINTR]
**                    The closedir() function was interrupted by a signal.
**
** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**
**    The <sys/types.h> header includes definitions for at least the following types:
**
**          blkcnt_t
**               Used for file block counts
**
**          blksize_t
**               Used for block sizes
**
**          clock_t
**               Used for system times in clock ticks or CLOCKS_PER_SEC (see <time.h>).
**
**          clockid_t
**               Used for clock ID type in the clock and timer functions.
**
**          dev_t
**               Used for device IDs.
**
**          fsblkcnt_t
**               Used for file system block counts
**
**          fsfilcnt_t
**               Used for file system file counts
**
**          gid_t
**               Used for group IDs.
**
**          id_t
**               Used as a general identifier; can be used to contain at least a pid_t, uid_t or a gid_t.
**
**
**          ino_t
**               Used for file serial numbers.
**
**          key_t
**               Used for interprocess communication.
**
**          mode_t
**               Used for some file attributes.
**
**          nlink_t
**               Used for link counts.
**
**          off_t
**               Used for file sizes.
**
**          pid_t
**               Used for process IDs and process group IDs.
**
**          pthread_attr_t
**               Used to identify a thread attribute object.
**
**          pthread_cond_t
**               Used for condition variables.
**
**          pthread_condattr_t
**               Used to identify a condition attribute object.
**
**          pthread_key_t
**               Used for thread-specific data keys.
**
**          pthread_mutex_t
**               Used for mutexes.
**
**          pthread_mutexattr_t
**               Used to identify a mutex attribute object.
**
**          pthread_once_t
**               Used for dynamic package initialisation.
**
**          pthread_rwlock_t
**               Used for read-write locks.
**
**          pthread_rwlockattr_t
**               Used for read-write lock attributes.
**
**          pthread_t
**               Used to identify a thread.
**
**          size_t
**               Used for sizes of objects.
**
**          ssize_t
**               Used for a count of bytes or an error indication.
**
**          suseconds_t
**               Used for time in microseconds
**
**          time_t
**               Used for time in seconds.
**
**          timer_t
**               Used for timer ID returned by timer_create().
**
**          uid_t
**               Used for user IDs.
**
**          useconds_t
**               Used for time in microseconds.
**
** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**
**
**       NAME
**            readlink, readlinkat -- read value of a symbolic link
**
**       SYNOPSIS
**            #include <unistd.h>
**
**            ssize_t
**            readlink( const char *restrict path,
**                      char *restrict buf,
**                      size_t bufsize              );
**
**       DESCRIPTION
**            readlink() places the contents of the symbolic link path in the
**            buffer buf, which has size bufsize.  Readlink does not append a
**            NUL character to buf.
**
**            The readlinkat() system call is equivalent to readlink() except
**            in the case where path specifies a relative path. In this case
**            the symbolic link whose content is read relative to the directory
**            associated with the file descriptor fd instead of the current
**            working directory. If readlinkat() is passed the special value
**            AT_FDCWD in the fd parameter, the current working directory is
**            used and the behavior is identical to a call to readlink().
**
**       RETURN VALUES
**            The call returns the count of characters placed in the buffer
**            if it succeeds, or a -1 if an error occurs, placing the error
**            code in the global variable errno.
**
** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**
**       NAME
**            DIR -- directory descriptor
**
**       DECLARATION
**
**           ==>> structure describing an open directory. <<==
**
**           typedef struct
**           {
**                int                           __dd_fd;       // file descriptor associated with directory
**                long                          __dd_loc;      // offset in current buffer
**                long                          __dd_size;     // amount of data returned
**                char                          *__dd_buf;     // data buffer
**                int                           __dd_len;      // size of data buffer
**                long                          __dd_seek;     // magic cookie returned
**                __unused long                 __padding;     // (__dd_rewind space left for bincompat)
**                int                           __dd_flags;    // flags for readdir
**                __darwin_pthread_mutex_t      __dd_lock;     // for thread locking
**                struct _telldir               *__dd_td;      // telldir position recording
**           }
**           DIR;
**
**       DESCRIPTION
**            The type DIR, which is defined in the header <dirent.h>,
**            represents a directory stream, which is an ordered sequence
**            of all the directory entries in a particular directory.
**            Directory entries represent files; files may be removed
**            from a directory or added to a directory asynchronously
**            to the operation of readdir().
**
** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**
**             NAME
**                  struct dirent -- directory structure
**
**             DECLARATION
**
**                 ==>> structure describing a directory <<==
**
**                 #define __DARWIN_MAXNAMLEN   (255)
**                 #define __DARWIN_MAXPATHLEN  (1024)
**
**                 #define __DARWIN_STRUCT_DIRENTRY
**                 {
**                     __uint64_t    d_ino;           // file number of entry
**                     __uint64_t    d_seekoff;       // seek offset (optional, used by servers)
**                     __uint16_t    d_reclen;        // length of this record                      NOTE : MAYBE USEFUL
**                     __uint16_t    d_namlen;        // length of string in d_name                 NOTE : USEFUL
**                     __uint8_t     d_type;          // file type, see below                       NOTE : USEFUL
**                     char          d_name[1024];    // entry name (up to MAXPATHLEN bytes)        NOTE : USEFUL
**                 }
**
**                 struct dirent __DARWIN_STRUCT_DIRENTRY;
**
**             DESCRIPTION
**                  .
**
** — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #
**
**
**
**
**
**
**
**
**
**
**
**
**
**
*/

#include "ft_ls.h"

void    listdir(DIR *dirdes)
{
    struct dirent	*dir;

	if (!dirdes)
	{
        perror(NULL);
		return ;
	}
	errno = 0;
	while (errno == 0 && (dir = readdir(dirdes)) != NULL)
		ft_printf("%s\n", dir->d_name);
	if (errno != 0)
		perror(NULL);
	return ;
}

void	listdirname(const char *dirname)
{
    DIR             *dirdes;

    dirdes = opendir(dirname);
	if (dirdes)
	{
		listdir(dirdes);
		closedir(dirdes);
	}
	else
		perror(NULL);
	return ;
}

void    listcwd(void)
{
	listdirname(".");
}

void    listparentdir(void)
{
	listdirname("..");
}

int		main(int ac, const char *av[])
{

	// listcwd();
	// listparentdir();
	listdirname(av[1]);

	(void)ac;
	(void)av;

	return (0);
}
