#ifndef SHELL_H
#define SHELL_H

#include "Sdisk.h"
#include "Filesys.h"

class Shell: public Filesys
    {
        public :
            Shell(string diskname, int numberofblocks, int blocksize);
            int dir();// lists all files

            int add(string filename,string buffer);// add a new file using buffer as data
            
            int del(string file);// deletes the file
            int type(string file);//lists the contents of file
            int copy(string file1, string file2);//copies file1 to file2
    };

#endif