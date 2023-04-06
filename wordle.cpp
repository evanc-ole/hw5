#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
//bool hasFloats(const string& word, const string& floating);
void alpha(char c, const string& in, size_t pos, int hyphens, const string& floating, 
const set<string>& dict, set<string>& ret);
int countHyphens( const string& word);
//bool ValidWord(const string& word, const set<string>& dict);
void genWords(const string& in, const string& floating, size_t pos, int hyphens,
							const set<string>& dict, set<string>& ret);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	set<string> ret;
	int hyphens = countHyphens(in);
	genWords(in, floating, 0, hyphens, dict, ret);
	return ret;
}

//return how many unknown characters are in the word
int countHyphens(const string& word){
	int count = 0;
	for(char c : word){
		if(c == '-') count++;
	}
	return count;
}

//recurse for each possible letter
void genWords(const string& in, const string& floating, size_t pos, int hyphens,
const set<string>& dict, set<string>& ret){
	if(!hyphens and pos == in.length() and dict.find(in) != dict.end() and !floating.length()){
		ret.insert(in);
		return;
	}
	else if(pos == in.length()) return;
	if(in[pos] == '-'){
		alpha('a', in, pos, hyphens, floating, dict, ret);
	}
	else{
		genWords(in, floating, pos+1, hyphens, dict, ret);
	}
}


void alpha(char c, const string& in, size_t pos, int hyphens, const string& floating, 
const set<string>& dict, set<string>& ret){
	if(!hyphens and pos == in.length() and dict.find(in) != dict.end() and !floating.length()){
		ret.insert(in);
		return;
	}
	else if(pos == in.length()) return;
	string temp = in; temp[pos] = c;
	string new_float = floating;
	
	size_t n = new_float.find_first_of(c, 0);
	if(n != string::npos){
		new_float.erase(n, 1);
	}

	if(hyphens < new_float.length()) return;
	genWords(temp, new_float, pos+1, hyphens-1, dict, ret);
	
	//if gone through the entire alphabet
	if(c == 'z') return;
	else alpha(c+1, in, pos, hyphens, floating, dict, ret);

}


