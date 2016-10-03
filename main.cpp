/*Brainf**k interpreter. 
 * List of symbols:
 * > : Increment data pointer
 * < : Decrement data pointer
 * + : Increase value held at current data pointer address by 1
 * - : Decrease value by 1
 * . : Output the byte at the data pointer
 * , : Accept a byte of input, and store where the data pointer points
 * [ : If the byte at the current data pointer is 0, jump to the symbol after the matching ]
 * ] : If the byte at the current data pointer is non-zero, just to the symbol after the matching [
 * 
 */
 
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void interpret(string prog, char* ptr){
    int bracket_count=0;

    for (int i=0; i<prog.length(); ++i){
        if (prog[i] == '>') ++ptr;
        else if (prog[i] == '<') --ptr; //This and the next few lines are straightforward. 
        else if (prog[i] == '+') ++*ptr;
        else if (prog[i] == '-') --*ptr;
        else if (prog[i] == '.') cout << *ptr; 
        else if (prog[i] == ',') cin >> *ptr;
        else if (prog[i] == ']' && *ptr != 0){ //Now for loops, which are more involved. This is end of loop, and if it should go back to start, tracks back.
            ++bracket_count;
            while (bracket_count > 0){
                --i;
                if (prog[i] == ']') ++bracket_count; //takes into account nested loops. Counts ['s and ]'s until they balance.
                else if (prog[i] == '[') --bracket_count;
            }
        }
        else if (prog[i] == '[' && *ptr == 0){ //At beginning of loop that needs to be skipped - needs to jump to symbol after matching ]
            --bracket_count;      //decided that ['s are negative, and ]'s are positive. Nice to have conventions.
            ++i;
            while (bracket_count < 0){
                if (prog[i] == ']') ++bracket_count; 
                else if (prog[i] == '[') --bracket_count;
                ++i; //arranged so we end on symbol after ].
            }
        }
    }
}

int main(int argc, char *argv[]){
    string prog = argv[1]; 
    char tape[10000]={0}; //Before this line, I had endless "Segmentation Fault (Core Dumped)" errors. I was being really dumb.
    interpret(prog, tape); //Called it tape since Brainf**k works quite Turing machine-like.
    return 0;
}
