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

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    //return m_queue.count();
	Size size;
	size = m_queue_min.count() + m_queue_default.count() + m_queue_max.count();
	return size;
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    //m_queue.push(proc);
    //return Success;
	
	int priority = proc->getPriorityLevel();
	Scheduler::Result result;
	switch(priority)
	{
		case 1: 
			m_queue_min.push(proc);
			return Success;
		case 2: 
                        m_queue_lower.push(proc);
                        return Success;
		case 3: 
                        m_queue_default.push(proc);
                        return Success;
		case 4: 
                        m_queue_higher.push(proc);
                        return Success;
		case 5: 
                        m_queue_max.push(proc);
                        return Success;
	}
	return Success;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    //Size count = m_queue.count();
	Size min_count = m_queue_min.count();
	Size lower_count = m_queue_lower.count();
	Size default_count = m_queue_default.count();
	Size higher_count = m_queue_higher.count();
	Size max_count = m_queue_max.count();

    // Traverse the min Queue to remove the Process
    for (Size i = 0; i < min_count; i++)
    {
        Process *p = m_queue_min.pop();

        if (p == proc)
            return Success;
        else
            m_queue_min.push(p);
    }
    // Traverse the lower Queue to remove the Process
    for (Size i = 0; i < lower_count; i++)
    {
        Process *p = m_queue_lower.pop();

        if (p == proc)
            return Success;
        else
            m_queue_lower.push(p);
    }
    // Traverse the default Queue to remove the Process
    for (Size i = 0; i < default_count; i++)
    {
        Process *p = m_queue_default.pop();

        if (p == proc)
            return Success;
        else
            m_queue_default.push(p);
    }
    // Traverse the higher Queue to remove the Process
    for (Size i = 0; i < higher_count; i++)
    {
        Process *p = m_queue_higher.pop();

        if (p == proc)
            return Success;
        else
            m_queue_higher.push(p);
    }
    // Traverse the max Queue to remove the Process
    for (Size i = 0; i < max_count; i++)
    {
        Process *p = m_queue_max.pop();

        if (p == proc)
            return Success;
        else
            m_queue_max.push(p);
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process * Scheduler::select()
{
    if (m_queue_max.count() > 0)
    {
        Process *p = m_queue_max.pop();
        m_queue_max.push(p);

        return p;
    }
    if (m_queue_higher.count() > 0)
    {
        Process *p = m_queue_higher.pop();
        m_queue_higher.push(p);

        return p;
    }
    if (m_queue_default.count() > 0)
    {
        Process *p = m_queue_default.pop();
        m_queue_default.push(p);

        return p;
    }
    if (m_queue_lower.count() > 0)
    {
        Process *p = m_queue_lower.pop();
        m_queue_lower.push(p);

        return p;
    }
    if (m_queue_min.count() > 0)
    {
        Process *p = m_queue_min.pop();
        m_queue_min.push(p);

        return p;
    }

    return (Process *) NULL;
}
