#include "heap1.h"
#include <iostream>
#include <string>

const unsigned MAX_ASCII_SYMBOLS = 1<<7;       // marks the total number of ASCII keys + 1 i.e, 127 + 1
int count[MAX_ASCII_SYMBOLS] = {0};            // hash storing frequency count of each symbol
int included[MAX_ASCII_SYMBOLS] = {0};         // auxilliary 0/1 hash to mark symbols that are present
int visited[MAX_ASCII_SYMBOLS] = {0};          // auxilliary 0/1 hash to mark symbols already visited
std::string keys = "abbbcdeef";                // store symbols (file) to be encoded
int max_file_symbols = 0;                      // tracks number of the unique symbols for a given file (text)
Heap C;                                        // the merger min heap of the frequencies (strengths) of the symbols

/* returns corresponding ASCII-bases address of a symbol to be decoded */
int hash(char symbol) 
{
    return (symbol % MAX_ASCII_SYMBOLS);
}

/* track frequency of each symbol in a given text (file) */
void frequency_count()
{
    for (int i = 0; i < keys.length(); i++)
        count[hash(keys[i])]++;
}

/* make the huffman minimum weight code tree based on weights(frequencies) of the codes */
Node_T huffman()
{
    frequency_count(); 
    for (int i = 0; i < keys.length(); i++) {
        if (!included[hash(keys[i])]) {
            max_file_symbols++;
        }
        included[hash(keys[i])] = 1;
    } 

    C.set_capacity(max_file_symbols + 1);
    for (int i = 0; i < MAX_ASCII_SYMBOLS; i++) {
        if (included[hash(keys[i])]) {
            Node_T new_node = new Node;
            new_node->depth = 0;
            new_node->strength = count[hash(keys[i])];
            new_node->symbol = keys[i];
            new_node->rchild = new_node->lchild = nullptr;
            C.insert_min_heap(new_node);
        } 
        included[hash(keys[i])] = 0;
    }

    for (int i = 1; i < max_file_symbols; i++) {
        Node_T new_node = new Node;
        Node_T x = C.delete_min_heap();
        Node_T y = C.delete_min_heap();
        new_node->depth = std::max(x->depth, y->depth) + 1;
        new_node->strength = x->strength + y->strength;
        new_node->symbol = 0;
        new_node->lchild = x;
        new_node->rchild = y;
        C.insert_min_heap(new_node);
    }
    return C.delete_min_heap();
}

/* transform given text to huffman prefix code */
void encode(const Node_T& root, std::string code, std::string * codes)
{
    if (root->lchild == nullptr && root->rchild == nullptr)  {
	codes[hash(root->symbol)] = code;
    }
    else {
	encode(root->lchild, code + '0', codes);
	encode(root->rchild, code + '1', codes);
    }
}

/* decode huffman codeword to the original text */
void decompress(const Node_T& root, std::string& codeword)
{
    Node_T current = root;
    for (int i = 0; i < codeword.length(); i++) {
        if (codeword[i] == '0')
            current = current->lchild;
        else 
            current = current->rchild;
        if (current->lchild == nullptr && current->rchild == nullptr) {
            std::cout.put(current->symbol);
            current = root;
        }
    }
    std::cout << std::endl;
}
    
int main() 
{
    Node_T root = huffman();
    std::string codes[MAX_ASCII_SYMBOLS];
    encode(root, "", codes);
    // print codes 
    std::string codeword = "";
    for (int i = 0; i < keys.length(); i++) {
        //jjjif (visited[hash(keys[i])] == 0) {
        //    std::cout << (char)keys[i] << ": " << codes[hash(keys[i])] << std::endl;
            codeword.append(codes[hash(keys[i])]);
       // }
        visited[hash(keys[i])] = 1;
    }
    std::cout << keys << std::endl;
    std::cout << codeword << std::endl;
    decompress(root, codeword);
    return 0;
}
