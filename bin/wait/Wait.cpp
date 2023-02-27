#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"
#include "sys/wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for specific process to change state");
    parser().registerPositional("PID", "Wait for process with ID to change stage");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid = 0, status;

    if ((pid = atoi(arguments().get("PID"))) <= 16)
    {
        ERROR("Invalid Argument: Attempted to wait on non-child process");
        return InvalidArgument;
    }

    if (waitpid(pid, &status, 0) == -1)
    {
        ERROR("Invalid Argument: No process of ID " << arguments().get("PID") << " found");
        return InvalidArgument;
    }

    return Success;
}
