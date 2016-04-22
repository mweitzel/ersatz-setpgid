/*
 * Modified 2016 - Matthew Weitzel
*/
/*
 * Copyright (c) 2012 Jerry Kuch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 *  An ersatz setpgid command for those Unixes (e.g. Mac OS X) that
 *  don't have one.  Intended to work like (or enough like) the one
 *  from the util-linux-ng package that I can run the RabbitMQ test
 *  suite post summer 2011 on a Mac OS X dev machine.
 *
 *  Synopsis:
 *      setpgid program [arg...]
 *
 *  Description:
 *      setpgid runs a program in a new group.
 *
 *  See Also:
 *      setpgid(2)
 *
 */
int
main(int argc, char *argv[])
{
    if( argc < 2 )
    {
        fprintf(stderr,
                "usage: %s program [arg ...]\n",
                (char *)argv[0]);
    }

    // Create a new group and make this setpgid process the group
    // leader for the new group; This setpgid process also becomes
    // the process group leader of a new process group and has no
    // controlling terminal...
    if (setpgid(0,0) < 0)
    {
        perror("setpgid");
        exit(1);
    }

    // Execute the requested command with the given arguments,
    // replacing our current process image (which now has its own
    // happy group) with a new process image...
    execvp(argv[1], argv + 1);

    // If we got to here, squawk and exit with an error code...
    perror("execvp");
    exit(1);
}

