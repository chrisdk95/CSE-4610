
#include<fstream>
#include<iostream> 
#include<vector>
#include<string>
#include "Sdisk.h"
 
using namespace std;
 


Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{
    this->diskname=diskname;
    this->numberofblocks=numberofblocks;
    this->blocksize=blocksize;
    fstream input;

    input.open(diskname.c_str(), ios::in | ios::out);
    //bool diskstatus=file1.good();
    //  file1.close();
    if(input.good())
    {
        input.close();
        return;
    }
    else
    {
        input.close();
        ofstream outfile;
        outfile.open(diskname.c_str());

        for(int i = 0; i < numberofblocks*blocksize; i++)
        {
            outfile.put('#');
        }
        outfile.close();
        return;
    }
}

int Sdisk:: getblock(int blocknumber,string& buffer)//----------------------------------------------------
{
    if(blocknumber > (numberofblocks -1))
    {
        return 0;
    }
    ifstream input;
    char temp;
    input.open(diskname.c_str());

    if(! input.is_open())
    {
        return 0;
    }
   input.seekg(blocknumber * blocksize);
   for( int i =0; i < blocksize; i ++) 
   {
       input.get(temp);
       buffer.push_back(temp);
   }
   input.close();
   return 1;

}

int Sdisk::putblock(int blocknumber,string buffer)
{
    if(blocknumber > (numberofblocks -1))
    {
        return 0;
    }
    fstream output;
    output.open(diskname.c_str(), ios::in | ios::out);

    if(! output.is_open())
    {
        return 0;
    }
    output.seekg(blocknumber * blocksize);
    for(int i = 0; i < buffer.length(); ++i)
    {
        output.put(buffer[i]);
    }
    output.close();
    return 1;
}

int Sdisk::getnumberofblocks()
{
    return this->numberofblocks;
}
int Sdisk::getblocksize()
{
    return this->blocksize;
}