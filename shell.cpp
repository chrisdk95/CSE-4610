#include "shell.h"
#include "block.h"
#include "Filesys.h"

using namespace std;


Shell::Shell(string diskname, int numberofblocks, int blocksize ) : Filesys( diskname, numberofblocks,blocksize )

{

}



int Shell::dir()
{ vector<string> flist=ls();
  for (int i=0; i<flist.size(); i++)
      {
        cout << flist[i] << endl;

      }
      return 0;
}


int Shell::add(string filename, string buffer)
{
    int code = getfirstblock(filename);
    if (code >=0)
    {
        cout << "File exists....................................." << endl;
        return 0;
    }


    code = newfile(filename);
    if(code ==0)
    {
        cout<<"Failed"<<endl;
        return 0;
    }

    vector<string>blocks=block(buffer,getblocksize());
    for(int i =0; i < blocks.size(); i ++)
    {
        code = addblock(filename,blocks[i]);
        if ( code ==0)
        {
            cout<<"Error occurred"<<endl;
        }
        return 0;
    }
    return 0;
}


int Shell::del(string file)
{

    int block=getfirstblock(file);
    while(block !=0)
    {
        int code = delblock(file,block);
        block = getfirstblock(file);
    }
    rmfile(file);
    return 0;
}



int Shell::copy(string file1,string file2)
{
    int block=getfirstblock(file1);

    int code = newfile(file2);

    while(block !=0)
    {
        string buffer;
        readblock (file1,block,buffer);
       code = addblock(file2,buffer);
        block = nextblock(file1,block);
   
    }
    return 1;
}

int Shell::type(string file)
{
    int block =getfirstblock(file);
    string buffer;
    while(block > 0)
    {
        string p;
        int error =readblock(file,block,p);
        buffer += p;
        block = nextblock(file,block);
    }
    cout<<buffer<<endl;
    cout<< buffer.length()<<endl;
    return 0;
}