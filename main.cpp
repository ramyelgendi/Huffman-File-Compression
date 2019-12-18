//
//  main.cpp
//  TEXT Compression Utility
//
//  Created by Ramy ElGendi on 11/26/19.
//  Copyright © 2019 Ramy ElGendi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <iterator>
#include <map>
using namespace std;

struct TREE_NODE
{
    char ch;
    int COUNT;
    TREE_NODE *left, *right;
};

TREE_NODE *getNode(char ch, int COUNT, TREE_NODE *left, TREE_NODE *right)
{
    TREE_NODE *node = new TREE_NODE();

    node->ch = ch;
    node->COUNT = COUNT;
    node->left = left;
    node->right = right;
    
    return node;
}

struct comp
{
    bool operator()(TREE_NODE *l, TREE_NODE *r)
    {
        // highest priority item has lowest COUNTuency
        return l->COUNT > r->COUNT;
    }
};


// GLOBAL STUFF
//================
unordered_map<char, int> COUNT;
unordered_map<char, string> H_CODE;
priority_queue<TREE_NODE *, vector<TREE_NODE *>, comp> pq;
double MAX_LENGTH=0;
TREE_NODE* root;
string  ADDRESS_TEXT =  "/Users/ramyelgendi/Desktop/321 Bonus/321 Bonus/Testbench/Text.txt";
string  ADDRESS_CODE = "/Users/ramyelgendi/Desktop/321 Bonus/321 Bonus/Testbench/Code.huf";
string  ADDRESS_OUTPUT = "/Users/ramyelgendi/Desktop/321 Bonus/321 Bonus/Testbench/Output.txt";
string str = "";
string result;
bool first_run = true;

//================
// FUNCTIONS
//================

void writefile(string,string);
long double frequency(string);
//================

// traverse the Huffman Tree and store Huffman Codes in a map.
void encode(TREE_NODE *root, string str, unordered_map<char, string> &H_CODE)
{
    if(root == nullptr)
        return;
    
//    if(!first_run)
//        for(auto loop : H_CODE)
//            if(loop.first==root->ch)
//                return;
//    
    // found a leaf node
    if(!root->left && !root->right) {
        H_CODE[root->ch] = str;
//        st[H_CODE[root->ch]]++;
    }

    encode(root->left, str + "0", H_CODE);
    encode(root->right, str + "1", H_CODE);
} // encode()

// traverse the Huffman Tree and decode the encoded string
void decode(TREE_NODE *root, int &index, string str,string& result)
{
    if(root == nullptr)
        return;
    
    // found a leaf node
    if(!root->left && !root->right)
    {
        result+= root->ch;
        return;
    }
    index++;
    
    
    if(str[index] == '0')
        decode(root->left, index, str,result);
    else
        decode(root->right, index, str,result);
} // decode()

// Builds Huffman Tree and H_CODE and decode given input TEXT
void buildHuffmanTree(bool flag,string TEXT)
{
    if(flag) {
        if(1) {
            for(char ch : TEXT)
                COUNT[ch]++;

            for(auto loop : COUNT)
                pq.push(getNode(loop.first, loop.second, nullptr, nullptr));

            while(pq.size() != 1)
            {
                TREE_NODE *left = pq.top(); pq.pop();
                TREE_NODE *right = pq.top(); pq.pop();
                
                int sum = left->COUNT + right->COUNT;
                pq.push(getNode('\0', sum, left, right));
            }
            
            root = pq.top();
        }
        
    encode(root, "", H_CODE);
    str = "";
        for(char ch : TEXT) {
        str += H_CODE[ch];
            if(H_CODE[ch].length()>MAX_LENGTH) // GETTING THE <L>
                MAX_LENGTH=H_CODE[ch].length();
        }
    
        

    writefile(ADDRESS_CODE,str);
    cout<<"Successfuly encoded!"<<endl;

    } else {
    int index = -1;
        result = "";
    while(index < (int)TEXT.size() - 2)
        decode(root, index, TEXT,result);
    writefile(ADDRESS_OUTPUT,result);
        cout<<"Successfuly decoded!"<<endl;
    }
}
void list(){
        cout << "Huffman Codes are:\n" << endl;
        for(auto loop : H_CODE)
            cout << loop.first << " " << loop.second << endl;
}

void readfile(string address,string& TEXT)
{
    ifstream FILE;
    FILE.open(address); //open the input file

    stringstream strStream;
    strStream << FILE.rdbuf(); //read the file
    TEXT = strStream.str(); //str holds the content of the file
    FILE.close();
}
void writefile(string address,string TEXT)
{
    ofstream FILE(address);
    FILE<<TEXT;
    FILE.close();
}
bool checkfiles()
{
    ifstream file;
    file.open(ADDRESS_TEXT);
    if(file.fail()) {cout<<"[ERROR] TEXT Address Does Not Exist!"<<endl;return false;}file.close();
    file.open( ADDRESS_CODE, ios::out | ios::trunc ); file.close();
    file.open( ADDRESS_OUTPUT, ios::out | ios::trunc ); file.close();

    cout<<"\n- All files exist!"<<endl;
    return true;
}
long double frequency(string s) {
          
    map<char , long double >m;
    map<char , long double >::iterator itr;
    
    long double length = s.length(),total = 0.0;
    
    for(long i=0;i<s.length();i++)
        m[s[i]]++;
    
    long double count = 1,temp=0;
    for(auto loop : H_CODE) {
    for(itr=m.begin();itr!=m.end();itr++)
        if(loop.first==itr->first) {
            temp = itr->second/length;
            total = temp*count + total;
            count++;
        }
    }
    total = total - (count*temp) + (count-1)*temp; // GETTING THE <L>
    return total;
}

int main() {
    bool choice;
    
    cout<<"\n- The TEXT File Address is: "<<ADDRESS_TEXT<<endl;
//    cout<<"Do you want to change the address? [Enter 1 or 0 only]: ";
//    cin>>choice1;
//    if(choice1) {
//        cout<<"Enter your new address"<<endl;
//        cin>>ADDRESS_TEXT;
//    }
    
    cout<<"\n- The Output File Address is: "<<ADDRESS_OUTPUT<<endl;
//    cout<<"Do you want to change the address? [Enter 1 or 0 only]: ";
//    cin>>choice2;
//    if(choice2) {
//        cout<<"Enter your new address"<<endl;
//        cin>>ADDRESS_OUTPUT;
//    }
    cout<<"\n- The Huffman Code File Address is: "<<ADDRESS_CODE<<endl;
//    cout<<"Do you want to change the address? [Enter 1 or 0 only]: ";
//    cin>>choice3;
//    if(choice3) {
//        cout<<"Enter your new address"<<endl;
//        cin>>ADDRESS_CODE;
//    }
    
    string temp;
    bool flag;
    if(!checkfiles())
        return 0;
    
    // Encode text file to huffman code file
    
    readfile(ADDRESS_TEXT,temp);
    buildHuffmanTree(1,temp);
    long double FREQ = frequency(temp);
    readfile(ADDRESS_CODE,temp);

    buildHuffmanTree(0,temp);
        
    
    cout<<"\n\n  Number of Character Bits  =  "<<MAX_LENGTH<<endl;
       cout<<"  <L>  =  "<<FREQ<<endl;
       cout<<"   η   =  "<<(MAX_LENGTH/FREQ)*100.0<<"%\n\n"<<endl;

    
    cout<<"Do you want to view the generated Huffman Code for each character? \n1: YES \n0: NO\n-> Choice: ";
        cin>>choice;
        if(choice)
            list();


        cout<<"Huffman codes have been created and stored at tree! \n";
        first_run= false;
        int s;
        while(s!=20) {
        cout<<"\nDo you want to \n0: Decode \n1: Encode\n-> Choice: "<<endl;
        cin>>flag;

            if(flag) {
            readfile(ADDRESS_TEXT,temp);
            buildHuffmanTree(flag,temp);
                
            cout<<"Do you want to view the generated Huffman Code for each character? \n1: YES \n0: NO\n-> Choice: ";
                 cin>>choice;
                 if(choice)
                     list();
            
            
        }else{
            readfile(ADDRESS_CODE,temp);
            buildHuffmanTree(flag,temp);
            
            
        }
            
            s++;
        }
    }
