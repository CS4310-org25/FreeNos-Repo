#include "sys/renice.h"
#include "sys/types.h"
#include <errno.h>

int renicepid(ProcessID pid, int newPriority)
{
    ProcessClient process;

    switch ((const API::Result) (process.setPriority(pid, newPriority) & 0xffff))
    {
        case API::NotFound:
            errno = ESRCH;
            return -1; 

        case API::Success:
            return 0;

        default:
            errno = EIO;
            return -1;
    }
}