Partners: Eli Poppele and Jon Takagi

# README
##Contents
1. Declarations
2. Implementations
3. Files
4. Testing
5. Results

## Declarations
### hforest.hh  
This file was provided by the instructor. No changes were made, despite their descriptions as "My solutions to HW6.", which had us build a maxheap. This file describes a minheap instead.
### htree.hh
This file defines a node for a tree. It was provided by the instructor and no changes were made. Also, the functions are implemented in the header file, which I'm pretty sure is a crime.
### bitio.hh
Header file for the bitio Class. Includes declarations; all functions should be commented
and explained in the actual file itself, since I comment my code, unlike some certain people.
### huffman.hh
This file defines the huffman class. A `huffman` object has two member functions as specified by the assignment: `encode` a character and get back a vector of booleans, and `decode`, which takes a single bit and returns the integer representation of the character it encodes.
It has one private method, which builds a huffman tree, and two private data members: the frequency table, stored as a vector of ints, and a pointer to the huffman tree it stores.
We chose to store the frequency table as a vector of integers because we use raw frequency rather than normalized frequency - every time we use a character, it goes up by one. Therefore, integers are sufficient, and simpler. We store a pointer to the huffman tree to use in the decode method.
##Implementations
###hforest.cc
Nothing to see here, folks.
###huffman.cc
#### Constructor
The constructor uses the `assign` function to set the initial frequency of every character to 0. It also begins by building a tree. This isn't strictly necessary, as encoding begins by rebuilding the tree, and if `root` is nullptr when decode is called (as it would be when the first call is to decode) then decode rebuilds the tree. However, this helped us avoid errors during debugging.
#### encode
This method relies on the `path_to` method of the HTree class, which was written by the instructor. I then convert the vector of `Direction` to a vector of `bool` using a very clever one line method. This was a mistake - I was using left = 1 in my encode when I wanted to use left = 0, and I didn't notice because I left myself a comment indicating otherwise. However, now it works, and it's still only 1 line :) Using `push_back` isn't the most efficient, but it saves me type problems and ensures that the vector stays in the right order.
#### decode
This method takes a bit, and traverses the tree to locate the symbol that it represents. If the single bit doesn't unambigously identify a symbol, it returns a negative value. If it returned a negative value, the next time it is called, then it attempts to parse the new bit as an addition to the previous sequence. If you pass a sequence that isn't there, it just loops and returns nonsense data, but won't crash. It WILL screw up your results, so don't screw up your results.
#### build_tree
This method is the meat of the class - while this method didn't work, it was impossible to debug errors in the other two. It follows the algorithm described in the assignment. We gave the dummy nodes negative keys starting at -257 and counting up to aid in debugging. They could also all have a key of -1, and the method would work the same way. Also, we chose to ensure that if l is a long tree rather than a node containing a symbol, it is on the left. This gives the tree a less efficient shape that was easier for us to visualize and debug. Allowing it to match left and right by the smallest value will give a smaller tree, giving smaller codes.
###bitio.cc
Includes the implementation of the bitio class. All functions should be
explained and commented in the code itself. For the design of this, I chose
to have bitio have a pending_ character which holds the current bit in progress.
This is where the bits are stored for output until we reach one byte, so we can
outstream the character (as we can't outsteam a single bit) and serves a similar
function in reverse for the input, pulling the input byte into the pending_ character
and then processing and outputting it one bit at a time.
###encoder.cc
This program inclues all of our previos classes. It is called with a number of files
as arguments and produces .comp compressed versions of those files using our huffman
compression. The file should contain comments explaining the code.
##decoder.cc
This program is similar to encoder, but takes .comp files (actually any files, but
it will turn anything that isn't .comp into a pile of spaghetti) and produces decoded
versions of them with a .plaintext extension. There are a few known errors in this,
that may be due to huffman or due to issues in it's own file, but the final character
in a file is sometimes no decoded properly. In some cases, a y at the end of the .txt
becomes a u at the end of the .plaintext.

##Files
---------------------------------------------------------------
A quick overview of all files included in this mess.
README.md : This file. .md because it's markdown i think? Jon did that part.
bitio .hh .cc .o : Header and implementation files for the bitio class, as well as the object file.
catch.hpp : This is just the catch header for its implementation in test_tree (or something); it really shouldn't be here but our make file compiles test for htree so I guess we need it for that.
decoder .cc .o & no extension : The implementation, object, and binary files for the decoder program.
encoder .cc .o & no extension : The implementation, object, and binary files for the encoder program.
hforest .cc .hh .o : Files for Hforest. I think these were copied from Eitan's, but in any case they're
    just here since they're implemented in huffman; they also should have the change in pop_tree to 
    return the min tree instead of the max.
htree-2.hh : I honestly don't know what this is.
htree .cc .hh .o : Same as for Hforest, only these declare and implement the HTree Class. I hope.
huffman .cc .hh .o : Implementation and declaration of the Huffman Class code, as well as the leftover
    object file. These should be described above.
makefile : The makefile used to compile the project. Use this and the make command.
Makefile.dm : I think Jon tried to make a markdown of makefile. I don't know how that went. This file
    shouldn't be necessary; default to using the other one.
test_bitio .cc .o & no extn. : The implementation of the testing of the bitio class, plus the object
    and binary files. These files should include an additional edge case assert, and the program
    should run with all asserts met.
test_hforest .cc .o & no extn. : The testing files for hforest. These are added with the makefile into
    the final complete test, but should be taken from last project and/or Eitan; they ought to function
    fine and should not need to be opened.
test_htree .cc .o & no extn. : See above; only for htree class.
test_huffman .cc .p & no extn. : The testing files (implementation, object, and binary) for the testing
    of huffman. These were based off Eitan's tests. They don't appear to test any other edge cases.
test_huffman-jon.cc : This is Jon's test file for huffman; he should be writing this. If I recall, this
    includes extended testing for huffman that was used for troubleshooting, including functions to test
    properties of the huffman tree and forest and perhaps print as well.
test_tree : The testing program file for htree testing, with a funny name because we didn't change the
    makefile much. It ought to run fine, but also is not exactly part of the huffman project.
verify.sh : Program file used to verify testing, described below.
    
txt-files/ : Folder containing test files used for testing.

---------------------------------------------------------------

## Testing
`verify.sh` looks in the `txt-files` directory. It expects every file `blah.txt` to have a matching `blah.txt.comp.plaintext`. I also included several types of file, including one without any extension, to ensure that the script correctly matches the decomp and the original. The script was also tested against a file with spaces in the name to ensure correct behavior. 
The results from our testing appear in the table below:
-----------------------------------------------------------------------------
file name:                      |size(bytes)|.comp size(bytes)  |files match?
-----------------------------------------------------------------------------
bee-movie-script.txt            |  52,755   |      31,409       |    Yes.
constitution.txt                |  45,119   |      25,690       |    missing new line at end
never-gonna-give-you-up.txt     |   1,758   |       1,110       |    missing new line at end
ohmanireallyneedonemoretest.txt |      42   |         108*      |    missing period at end
test.txt                        |   3,438   |       2,022       |    Yes.
-----------------------------------------------------------------------------
*not expected to compress efficiently.


OTHER NOTES:
Compile using the makefile. There are two, I don't know the difference (Jon does),
but just using the command make should be fine.
Known errors include the decoding error described in the decoder.cc section, as well
as a core dump error when trying to encode certain files, including 'If.txt' and 
'torch-of-life'; the source of this error appears to be in the huffman code.
The apparent source of this error is the m-dash character, "—", which is not "-", the
short dash that appears on a keyboard. It seems this character might not have an eight
bit representation? Or our program is bad. This character is quite prevalent in poetry
(good poetry at least) copy-pasted from the iternet, so it would explain why so many poems
failed to encode.

The error is: terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 18446744073709551586) >= this->size() (which is 257)
Aborted (core dumped)







