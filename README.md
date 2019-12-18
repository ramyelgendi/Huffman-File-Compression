# Huffman File Compression
 File compression using huffman coding

The code is designed to encode a given text file and decode it by default during the first run, then it asks the user to pick the next step (whether he wants to decode or encode).
The path of the input and output files are global variables defined inside the program (I tried making them inputs but the program kept giving me errors and skipping them so I just predefined them as global variables). Also, I commented the part where it gives the user a choice to input but its already there incase someone wants to test them, all what you have to do is uncomment them.
The <L> is defined as MAX_LENGTH and it is defined as a global variable. It is calculated at the final encoding step (before adding it to the file), each character's created bit code is checked for its length, and the maximum length is the <L>.
The efficiency is calculated after encoding and decoding the default run and it is displayed on the console.
There is an option to list all of the codes for each character, and this option is given to the users on the console.
There is a function called checkfiles() that makes sure that the text file exists, and the output file is empty because my writefile function does not overwrite the file, it adds to it so it must be empty before the first run.

I used https://www.geeksforgeeks.org/unordered_map to understand how is this template used.
