#ifndef TABLE_H
#define TABLE_H
#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include "Filesys.h"
#include "Sdisk.h"
using namespace std;

class Table : public Filesys
{
    public:
        Table(string diskname,int numberofblocks, int blocksize, string flatfile, string indexfile);
        int build_table(string input_file);
        int search(string values);

    private:
        string flatfile;
        string indexfile;
        int indexsearch(string value);
};

#endif