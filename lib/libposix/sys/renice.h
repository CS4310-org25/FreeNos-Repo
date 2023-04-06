/*
 * Copyright (C) 2009 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBPOSIX_RENICE_H
#define __LIBPOSIX_RENICE_H

#include <Macros.h>
#include <ProcessClient.h>
#include "types.h"

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libposix
 * @{
 */

/**
 * Returns the exit status of the child process
 *
 * @param st Contains the stat_loc value from renicepid()
 *
 * @return Exit status of the child process
 */
#define WEXITSTATUS(st) (st)

/**
 * @brief Renice for a child process to stop or terminate
 *
 * The renice() and renicepid() functions shall obtain status information
 * pertaining to one of the caller's child processes. Various options
 * permit status information to be obtained for child processes that
 * have terminated or stopped. If status information is available for
 * two or more child processes, the order in which their status is
 * reported is unspecified.
 *
 * @param pid Process ID of child to renice for.
 * @param stat_loc Points to an integer for storing the exit status.
 * @param newPriority newPriority to be assigned to currently ready/running process
 * @param options Optional flags.
 *
 * @return Process ID of the child on success or -1 on error
 */
extern C int renicepid(ProcessID pid, int newPriority);

/**
 * @}
 * @}
 */

#endif /* __LIBPOSIX_RENICE_H */