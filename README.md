# CSE-4610
School Project instructions

The FIRST part of this project requires that you implement a class that will be used to simulate a disk drive. The disk drive will have numberofblocks many blocks where each block has blocksize many bytes

An explanation of the member functions follows :

Sdisk(diskname, numberofblocks, blocksize)
This constructor incorporates the creation of the disk with the "formatting" of the device. It accepts the integer values numberofblocks, blocksize, a string diskname and creates a Sdisk (software-disk). The Sdisk is a file of characters which we will manipulate as a raw hard disk drive. The function will check if the file diskname exists. If the file exists, it is opened and treated as a Sdisk with numberofblocks many blocks of size blocksize. If the file does not exist, the function will create a file called diskname which contains numberofblocks*blocksize many characters. This file is logically divided up into numberofblocks many blocks where each block has blocksize many characters.

getblock(blocknumber,buffer)
retrieves block blocknumber from the disk and stores the data in the string buffer. It returns an error code of 1 if successful and 0 otherwise.

putblock(blocknumber,buffer)
writes the string buffer to block blocknumber. It returns an error code of 1 if successful and 0 otherwise.

The SECOND part of this project requires that you implement a simple file system. In particular, you are going to write the software which which will handle dynamic file management. This part of the project will require you to implement the class Filesys along with member functions. In the description below, FAT refers to the File Allocation Table and ROOT refers to the Root Directory

An explanation of the member functions follows :

Filesys()
This constructor reads from the sdisk and either opens the existing file system on the disk or creates one for an empty disk. Recall the sdisk is a file of characters which we will manipulate as a raw hard disk drive. This file is logically divided up into number_of_blocks many blocks where each block has block_size many characters. Information is first read from block 1 to determine if an existing file system is on the disk. If a filesystem exists, it is opened and made available. Otherwise, the file system is created.
The module creates a file system on the sdisk by creating an intial FAT and ROOT. 

The file system consists of two primary data objects. The directory is a file that consists of information about files and sub-directories. The root directory contains a list of file (and directory) names along with a block number of the first block in the file (or directory). (Of course, other information about the file such as creation date, ownership, permissions, etc. may also be maintained.) 

The FAT is an array of block numbers indexed one entry for every block. Every file in the file system is made up of blocks, and the component blocks are maintained as linked lists within the FAT. FAT[0], the entry for the first block of the FAT, is used as a pointer to the first free (unused) block in the file system

fssynch
This module writes FAT and ROOT to the sdisk. It should be used every time FAT and ROOT are modified.

fsclose
This module writes FAT and ROOT to the sdisk (closing the sdisk).

buildfs
This module builds the initial FAT and ROOT. It then uses fssynch to write the FAT and ROOT to the sdisk.

fssynch
This module reads the FAT and ROOT from the sdisk.

newfile(file)
This function adds an entry for the string file in ROOT with an initial first block of 0 (empty). It returns error codes of 1 if successful and 0 otherwise (no room or file already exists).

rmfile(file)
This function removes the entry file from ROOT if the file is empty (first block is 0). It returns error codes of 1 if successful and 0 otherwise (not empty or file does not exist).

getfirstblock(file)
This function returns the block number of the first block in file. It returns the error code of 0 if the file does not exist.

addblock(file,buffer)
This function adds a block of data stored in the string buffer to the end of file F and returns the block number. It returns error code 0 if the file does not exist, and returns -1 if there are no available blocks (file system is full!).

delblock(file,blocknumber)
The function removes block numbered blocknumber from file and returns an error code of 1 if successful and 0 otherwise.

readblock(file,blocknumber,buffer)
gets block numbered blocknumber from file and stores the data in the string buffer. It returns an error code of 1 if successful and 0 otherwise.

writeblock(file,blocknumber,buffer)
writes the buffer to the block numbered blocknumber in file. It returns an appropriate error code.

nextblock(file,blocknumber)
returns the number of the block that follows blocknumber in file. It will return 0 if blocknumber is the last block and -1 if some other error has occurred (such as file is not in the root directory, or blocknumber is not a block in file.)

The THIRD part of this project requires that you implement a simple shell that uses your file system. This part of the project will require you to implement the class Shell along with member functions

An explanation of the member functions follows :

Shell(string filename, int blocksize, int numberofblocks): This will create a shell object using the Filesys on the file filename.
int dir(): This will list all the files in the root directory.
int add(string file, string buffer): add a new file using buffer as data
int del(string file): deletes the file
int type(string file): lists the contents of file
int copy(string file1, string file2): copies file1 to file2

In this (FOURTH) part of the project, you are going to create a database system with a single table which uses the file system from Project II. The input file will consist of records associated with Art History. The data file you will use as input consists of records with the following format: The data (180 records) is here
Date : 5 bytes
End : 5 bytes
Type : 8 bytes
Place : 15 bytes
Reference : 7 bytes
Description : variable
In the data file, an asterisk is also used to delimit each field and the last character of each record is an asterisk. The width of any record is never greater than 120 bytes. Therefore you can block the data accordingly.

The member functions are specified as follows :
Table(diskname,blocksize,numberofblocks,flatfile,indexfile)
This constructor creates the table object. It creates the new (empty) files flatfile and indexfile in the file system on the Sdisk using diskname.

Build_Table(input_file)
This module will read records from the input file (the raw data file described above), add the records to the flatfile and create index records consisting of the date and block number, and then add the index records to the index file. (Note that index records will have 10 bytes .. 5 bytes for the date and 5 bytes for the block number.)

Search(value)
This module accepts a key value, and searches the index file with a call to IndexSearch for the record where the date matches the specified value. IndexSearch returns the blocknumber of the block in the flat file where the target record is located. This block should then be read and the record displayed.

IndexSearch(value)
This module accepts a key value, and searches the index file indexfile for the record where the date matches the specified value. IndexSearch then returns the block number key of the index record where the match occurs.
