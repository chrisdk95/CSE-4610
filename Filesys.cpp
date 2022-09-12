#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include <vector>
#include<fstream>
#include<iomanip>
#include <cstdlib>
#include<iterator>
#include<algorithm>

#include "Filesys.h"
#include "Sdisk.h"
#include "block.h"


using namespace std;

Filesys::Filesys(string filename, int numberofblocks, int blocksize) : Sdisk(filename, numberofblocks, blocksize)
{
  string buffer;
  int code = getblock(1, buffer);
  if(code == 0)
  {
    cout << "Error occurs " << endl;
    return;
  }

  rootsize = getblocksize()/12;
  fatsize = ((getnumberofblocks()*6)/getblocksize())+1;

  code = getblock(1, buffer);
  if(buffer[0] == '#')      // No File System exists
  {
    buildfs();
  }
  else
  {
    readfs();              // File System exists

  }
  fssynch();
}

int Filesys::buildfs()
{
  // Write ROOT to Sdisk in block 1
  ostringstream ostream;
  for(int i = 0; i < rootsize; i++)
  {
      filename.push_back("XXXXX");
      firstblock.push_back(0);
      ostream << "XXXXX" << " " << 0 << " ";
  }

  string buffer = ostream.str();
  vector<string>blocks = block(buffer, getblocksize());
  putblock(1, blocks[0]);

  // Write FAT to Sdisk in block 2
  ostringstream ostream2;
  fat.push_back(fatsize + 2);
  fat.push_back(1);
  for(int i = 0; i < fatsize; i++){
    fat.push_back(-1);
  }

  for(int i = fatsize + 2; i < getnumberofblocks(); i++)
  {
      fat.push_back(i + 1);
  }

  fat[fat.size() - 1] = 0;
  for(int i = 0; i < fat.size(); i++)
  {
      ostream2 << fat[i] << " ";
  }

  string buffer2 = ostream2.str();
  vector<string>blocks2 = block(buffer2, getblocksize());
  for(int i = 0; i < blocks2.size(); i++)
  {
      putblock(2 + i, blocks2[i]);
  }
  return 0;
}

int Filesys::newfile(string file)
{
  for(int i = 0; i < filename.size(); i++)
  {
    if(filename[i] == file)
    {
      cout << "File exists" << endl;
      cout<<" "<<endl;
      return 0;
    }
  }

  for(int i = 0; i < filename.size(); i++)
  {
    if(filename[i] == "XXXXX")
    {
      //cout << "Creating file: " << file << endl;
      filename[i] = file;
      firstblock[i] = 0;
      fssynch();
      return 1;
    }
  }
  //cout << "No space root in ROOT" << endl;
  return 0;
}

int Filesys::addblock(string file, string block)
{
  // return allocated block number
  int blockid = getfirstblock(file);
  if(blockid == -1)
  {
    //cout << "No such file." << endl;     //addblock file doesnt exist
    return 0;
  }

  int allocate = fat[0];
  if (allocate == 0)
  {
    cout << "no space in disk......addblock" << endl;
    cout<< " "<<endl;
    return 0;
  }



  fat[0] = fat[fat[0]];
  fat[allocate] = 0;

  if(blockid == 0)
  {
    for(int i = 0; i < rootsize; i++)
    {
      if(filename[i] == file)
      {
        firstblock[i] = allocate;
      }
    }
  }
  else
  {
    int b = blockid;
    while(fat[b] != 0)
    {
      b = fat[b];
    }
    //fat[b] = allocate;
  }
  putblock(allocate, block);
  fssynch();
  return allocate;
}

int Filesys::delblock(string file, int blocknumber)
{ 
  if(! checkblock(file, blocknumber))
  {
    cout << "No can do....delblock"<<endl;
    cout<<"  "<<endl;
    return 0;
  }
  int block = getfirstblock(file);
  if(block == blocknumber)
  {
    for(int i = 0; i < filename.size(); i++)
    {
      if(filename[i] == file)
      {
        firstblock[i] = fat[blocknumber];
        //break;
      }
    }
  }
  else
  {
    int b = block;
    while(fat[b] != blocknumber)
    {
      b = fat[b];
    }
    fat[b] = fat[blocknumber];
  }
  // Update free list
  fat[blocknumber] = fat[0];
  fat[0] = blocknumber;
  fssynch();
  return 1;
}

int Filesys::fssynch()
{
  // Writing the ROOT and FAT into the disk
  ostringstream ostream;
  for(int i = 0; i < rootsize; i++)
  {
    ostream << filename[i] << " " << firstblock[i] << " ";
  }
  
  string buffer1 = ostream.str();
  vector<string> block1 = block(buffer1, getblocksize());
  putblock(1, block1[0]);

  ostringstream ostream2;
  for(int i = 0; i < fat.size(); i++)
  {
    ostream2 << fat[i] << " ";
  }
  
  string buffer2 = ostream2.str();
  vector<string> blocks2 = block(buffer2, getblocksize());
  for(int i = 0; i < blocks2.size(); i++)
  {
    putblock(2 + i, blocks2[i]);
  }
  return 1;
}

int Filesys::readfs()
{
  // Reading into the ROOT
  istringstream istream;
  string buffer,buffer2;
  getblock(1, buffer);
  string tempbuffer;
  istream.str(buffer);
  for(int i = 0; i < rootsize; i++)
  {
      // string s;
      // int t;
      // istream >> s;
      // istream >> t;
      // filename.push_back(s);
      // firstblock.push_back(t);
      getblock(2+i, tempbuffer);   
      buffer2 +=tempbuffer;// my FAT is in buffer 2
      tempbuffer.clear();
  }

  // Reading into the FAT
  istringstream istream1, istream2;
  istream.str(buffer);
  istream.str(buffer2);
  for(int i = 0; i < rootsize; i++)
  {
      string f;
      int n;
      istream1>>f>>n;
      filename.push_back(f);
      firstblock.push_back(n);
      //getblock(i + 2, b);
      //buffer2 += b;
  }

  int k;
  //istream2.str(buffer2);
  for(int i = 0; i < getnumberofblocks(); i++)
  {
      //int t;
      istream2 >> k;
      fat.push_back(k);
  }
  return 1;
}

int Filesys::getfirstblock(string file)
{
  // returns firstblock of file or
  // returns 0 if file is empty or doesnt exist
  for(int i = 0; i < filename.size(); i++)
  {
    if(filename[i] == file)
    {
      //cout << "returning first block." << endl;
      return firstblock[i];
    }
  }
  //cout << "No such file." << endl;  //getfirstblock file doesnt exist
  return -1;
}

bool Filesys::checkblock(string file, int block)
{
  // return false if block doesnt exist
  int blockid = getfirstblock(file);
  if (blockid == -1)
  {
    return false;
  }

  // return true if block exists
  while(blockid != 0)
  {
    if(blockid == block)
    {
      return true;
    }
    blockid = fat[blockid];
  }
  return true;
}

int Filesys::readblock(string file, int blocknumber, string& buffer)
{
  if(checkblock(file, blocknumber) )
  {
    getblock(blocknumber, buffer);
    return 1;
  }
  else
  {
    return 0;
  }
}

int Filesys::writeblock(string file, int blocknumber, string buffer)
{
  if(checkblock(file, blocknumber))
  {
    putblock(blocknumber, buffer);
    return 1;
  }
  else
  {
    return 0;
  }
}

int Filesys::nextblock(string file, int blocknumber)
{
  if(checkblock(file, blocknumber))
  {
    return fat[blocknumber];
  }
  else
  {
    return -1;
  }
}

// int Filesys::fsclose()
// {
//   fssynch();
//   return 0;
// }



int Filesys::rmfile(string file)
{
  for(int i = 0; i < filename.size(); i++)
  {
    if(filename[i] == file) //&& firstblock[i] == 0)
    {
      if(firstblock[i]==0)
      {
        filename[i] = "XXXXX";
        //firstblock[i] = 0;
        fssynch();
        return 1;
      }
    }
  }
  return 0;
}







// Added ls() from shell lab
vector<string> Filesys::ls()
{
  vector<string> flist;
  for(int i=0; i<filename.size(); i++)
  {
    if(filename[i] != "XXXXX")
    {
      flist.push_back(filename[i]);
    }
  }
  return flist;
}