#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>

#include "table.h"
#include "block.h"
#include "Filesys.h"
using namespace std;

Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile) : Filesys(diskname, numberofblocks, blocksize)
{
    this->flatfile = flatfile;
    this->indexfile = indexfile;
}

int Table::build_table(string input_file)
{
    int code = newfile(indexfile);
    code = newfile(flatfile);
    ostringstream ostream;//create indexfile
    ifstream infile;
    infile.open(input_file.c_str());
    string inputline;
    getline(infile, inputline);

    while (infile.good())
    {
        string key = inputline.substr(0, 5);
        string rest = inputline.substr(5);
        vector<string>blocks = block(inputline, getblocksize());
        int blockid = addblock(flatfile, blocks[0]);
        ostream << key << " " << blockid << " ";
        getline(infile, inputline);
    }
    ostream << "XXXXX" << " " << 0 << " ";
    //get the index file done!
    string buffer = ostream.str();
    vector<string>iblock = block(buffer, getblocksize());
    //create indexfile
    for (int i = 0; i<iblock.size(); i++)
        {
            addblock(indexfile, iblock[i]);
        }
    //done
    return 1;
}

int Table::indexsearch(string value)
    {
        //istringstream instream;
        string buffer;
        int blockid = getfirstblock(indexfile);
        while(blockid != 0)
            {
                string b;
                readblock(indexfile, blockid, b);
                buffer += b;
                blockid = nextblock(indexfile, blockid);
            }

        istringstream istream;
        istream.str(buffer);
        string k;
        int b;
        istream >> k >> b;
        while(k != "XXXXX")
            {
                if(k == value)
                    {
                        return b;
                    }
                istream >> k >> b;
            }
        return 0;
    }

int Table::search(string value)
{
    int ecode = indexsearch(value);
    if(ecode == 0)//record not found
        {
            cout << "Record not found";
            return 0;
        }
    else //record found
        {
            string buffer;
            ecode = readblock(flatfile, ecode, buffer);
            cout << buffer;
            return 1;
        }
}