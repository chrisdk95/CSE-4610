#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include <string>

#include "Filesys.h"
#include "Sdisk.h"
#include "shell.h"
#include "block.h"
#include "table.h"
using namespace std;



//Sdisk one;
//Filesys two;
//Shell sh;

int main()
{
 Sdisk sdisk = Sdisk("diskdata.txt",256,128);
 Filesys fsys = Filesys("diskdata.txt",256,128);
 Shell shell = Shell("diskdata.txt",256,128);
 Table table = Table("diskdata.txt",256,128,"flatfile","indexfile");
 table.build_table("data.txt");

 string s;
 string command="go";
 string op1,op2;

 while (command != "quit")
     {
       command.clear();
       op1.clear();
       op2.clear();
       cout << "$";
       cout <<"Enter Data ....";
       getline(cin,s);
       int firstblank=s.find(' ');
       if (firstblank < s.length()) s[firstblank]='#';

       int secondblank=s.find(' ');
       command = s.substr(0,firstblank);

       if (firstblank < s.length())
         op1=s.substr(firstblank+1,secondblank-firstblank-1);
       if (secondblank < s.length())
         op2=s.substr(secondblank+1);
       if (command == "dir")
          {
            // use the ls function
            shell.dir();
          }
       if (command=="add")
          {
            shell.add(op1, op2);
            // The variable op1 is the new file and op2 is the file data
           }
       if (command=="del")
          {
            shell.del(op1);
            // The variable op1 is the file
           }
       if (command=="type")
          {
            shell.type(op1);
            // The variable op1 is the file
           }
       if (command=="copy")
          {
            shell.copy(op1, op2);
            // The variable op1 is the source file and the variable op2 is the destination file.
           }
       if (command == "search")
          {
            table.search(op1);
            // This is the command for Project 4
            // The variable op1 is the date
           }
       
      }

 return 0;
}