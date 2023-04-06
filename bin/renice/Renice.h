/*
 * Copyright (C) 2015 Niek Linnenbank
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

#ifndef __BIN_PS_PROCESSLIST_H
#define __BIN_PS_PROCESSLIST_H

#include <POSIXApplication.h>

/**
 * @addtogroup bin
 * @{
 */

/**
 * Output the system process list.
 */
class Renice : public POSIXApplication
{
  public:

    /**
     * Constructor
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    Renice (int argc, char **argv);

    /**
     * Execute the application.
     *
     * @return Result code
     */
    virtual Result exec();

    /**
     * Changes priority level of a process
     * 
     * @param pid     represents process
     * @param prioLvl represents priority level that a process will become
    */
    int changeLvl(int pid, int prioLvl);

    /**
     * Finds priority level of a process
     * 
     * @param pid     represents process
     * @param prioLvl represents priority level of process
    */
    int getPrio(int pid, int *prioLvl);
};

/**
 * @}
 */

#endif /* __BIN_PS_PROCESSLIST_H */
