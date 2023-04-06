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

#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ProcessClient.h>
#include "Renice.h"
#include <sys/renice.h>

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Alters priority of running processes");
    parser().registerFlag('n', "priority", "Changes priority to user input");
    parser().registerPositional("PROCPRIO", "The priority of the process");
    parser().registerPositional("PID", "The PID of the process we want to change");
}

int Renice::getPrio(int pid, int* prioLvl)
{
    const ProcessClient process;
    ProcessClient::Info info;
    process.processInfo(pid, info);

    errno = 0;

    *prioLvl = info.kernelState.priorityLevel;
    if (*prioLvl == -1 && errno)
    {
        WARNING("Failed to get priority");
        return -errno;
    }
    return 0;
}

int Renice::changeLvl(int pid, int prioLvl)
{
    int prevLvl, newLvl;

    //If getPriority does not return an error then we set priority
    if (getPrio(pid, &prevLvl) != 0)
        return 1;

    //Sets priority and checks for error
    if (renicepid((ProcessID) pid, prioLvl) != 0)
        return 1;

    // Is set priority was successful, check again for error
    if (getPrio(pid, &newLvl) !=0)
        return 1;

    //Program was successful to change priority
    printf("Priority set. \n");
    return 0;
}

Renice::Result Renice::exec()
{
    int prioLvl = 0, pid = 0, errs = 0;

    prioLvl = atoi(arguments().get("PROCPRIO"));
    pid = atoi(arguments().get("PID"));

    if (!arguments().get("priority"))
    {
        ERROR("No valid flag found");
        return InvalidArgument;
    }

    if (prioLvl > 5 || prioLvl < 1)
    {
        ERROR("Invalid priority level")
        return InvalidArgument;
    }

    errs |= changeLvl(pid, prioLvl);
    return errs != 0 ? IOError : Success;
}
