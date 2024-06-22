#include <bits/stdc++.h>
using namespace std;

unordered_map<string, string> comp0 = {
    {"0",    "101010"},
    {"1",    "111111"},
    {"-1",   "111010"},
    {"D",    "001100"},
    {"A",    "110000"},
    {"!D",   "001101"},
    {"!A",   "110001"},
    {"-D",   "001111"},
    {"-A",   "110011"},
    {"D+1",  "011111"},
    {"A+1",  "110111"}, 
    {"D-1",  "001110"},
    {"A-1",  "110010"},
    {"D+A",  "000010"},
    {"D-A",  "010011"},
    {"A-D",  "000111"},
    {"D&A",  "000000"},
    {"D|A",  "010101"}
};
unordered_map<string, string> comp1 = {
    {"0",    "101010"},
    {"1",    "111111"},
    {"-1",   "111010"},
    {"D",    "001100"},
    {"M",    "110000"},
    {"!D",   "001101"},
    {"!M",   "110001"},
    {"-D",   "001111"},
    {"-M",   "110011"},
    {"D+1",  "011111"},
    {"M+1",  "110111"},
    {"D-1",  "001110"},
    {"M-1",  "110010"},
    {"D+M",  "000010"},
    {"D-M",  "010011"},
    {"M-D",  "000111"},
    {"D&M",  "000000"},
    {"D|M",  "010101"}
};
unordered_map<string, string> destination = {
    {"null", "000"},
    {"M",    "001"},
    {"D",    "010"},
    {"MD",   "011"},
    {"A",    "100"},
    {"AM",   "101"},
    {"AD",   "110"},
    {"AMD",  "111"}
};
unordered_map<string, string> jumptobin = {
    {"null", "000"},
    {"JGT",  "001"},
    {"JEQ",  "010"},
    {"JGE",  "011"},
    {"JLT",  "100"},
    {"JNE",  "101"},
    {"JLE",  "110"},
    {"JMP",  "111"}
};
unordered_map<string, int> table = {
    {"R0", 0},
    {"R1", 1},
    {"R2", 2},
    {"R3", 3},
    {"R4", 4},
    {"R5", 5},
    {"R6", 6},
    {"R7", 7},
    {"R8", 8},
    {"R9", 9},
    {"R10", 10},
    {"R11", 11},
    {"R12", 12},
    {"R13", 13},
    {"R14", 14},
    {"R15", 15},
    {"SCREEN", 16384},
    {"KBD", 24576},
    {"SP", 0},
    {"LCL", 1},
    {"ARG", 2},
    {"THIS", 3},
    {"THAT", 4}
};

int found(string s, char find) //returns 1 if char c is in string s and 0 otherwise
{
    int ans=0;
    for (char c : s)
    {
        if(c == find)
        {
            ans=1;
            break;
        }
    }
    return ans;
}

int existvalue(unordered_map<string, int>& table, int value) //returns 1 if value exists in map and 0 otherwise
{
    for (auto& it : table)
    {
        if (value == it.second) return 1;
    }
    return 0;
}

int isint(string s) //returns 1 if s is an integer and 0 otherwise
{
    for(char c : s)
    {
        if(!isdigit(c)) return 0;
    }
    return 1;
}

int isa(string s) //returns 1 if A instruction, and 0 if C instruction
{
    if(s[0] == '@') return 1;
    return 0;
}

vector<string> tokenizec (string& s)
{
    vector<string> ans;
    size_t indexequal = s.find('=');
    size_t indexsemi = s.find(';');
    if (indexequal == string::npos)
    {   
        string comp = s.substr(0,indexsemi); 
        string jump = s.substr(indexsemi+1, s.length() - indexsemi-1);
        auto jump_it = jumptobin.find(jump);
        string jump_binary = jump_it->second;

        ans.push_back("null");
        ans.push_back(comp);
        ans.push_back(jump);
        return ans;
    }
    else if(indexsemi == string::npos)
    {
        string dest = s.substr(0, indexequal);
        auto dest_it = destination.find(dest);
        string dest_binary = dest_it->second;
        string comp = s.substr(indexequal+1, s.length() - indexequal-1);
        ans.push_back(dest);
        ans.push_back(comp);
        ans.push_back("null");
        return ans;
    }
    else
    {
        string dest = s.substr(0, indexequal);
        auto dest_it = destination.find(dest);
        string dest_binary = dest_it->second;
        string comp = s.substr(indexequal+1, indexsemi-indexequal-1);
        string jump = s.substr(indexsemi+1, s.length()-indexsemi-1);
        auto jump_it = jumptobin.find(jump);
        string jump_binary = jump_it->second;

        ans.push_back(dest);
        ans.push_back(comp);
        ans.push_back(jump);
        return ans;
    }
}

string cinst(string& s)
{   
    vector<string> tokens = tokenizec(s);
    string dest_binary = destination.find(tokens[0])->second;
    string comp = tokens[1];
    string comp_binary;
    string a="";
    string def = "111";
    if(found(comp, 'A'))
    {
        auto comp_it = comp0.find(comp);
        comp_binary = comp_it->second;
        a="0";
    }
    else if (found(comp, 'M'))
    {
        auto comp_it = comp1.find(comp);
        comp_binary = comp_it->second;
        a="1";
    }
    else
    {
        auto comp_it = comp0.find(comp);
        comp_binary = comp_it->second;
        a="0";
    }
    string jump = tokens[2];
    auto jump_it = jumptobin.find(jump);
    string jump_binary = jump_it->second;

    return def + a + comp_binary + dest_binary + jump_binary;

}

string nospace(string input)
{
    string ans="";
    for (char c : input)
    {
        if(c!=' ') ans+=c;
    }
    return ans;
}

string dectobin(string dec)
{
    int number = stoi(dec);
    string binary = "";
    if(number==0) return "0000000000000000";
    while(number > 0)
    {
        if(number%2==0) binary ='0' + binary;
        else binary = '1' + binary;
        number=number/2;
    }
    int length = binary.length();
    for (int i=length+1; i<17; i++) binary = '0' + binary;
    return binary;
}

string ainst(string s)
{
    if(isint(s)) return dectobin(s);//if s is an integer
    else
    {
        auto it = table.find(s);
        int key = it->second;
        return dectobin(to_string(key));
    }
}


void insert(ifstream& file) //handling symbols
{
    int lineno=0;
    string templine;
    while(getline(file, templine))
    {
        string line = nospace(templine);
        if(line[0] == '(') 
        {   
            table[line.substr(1, line.length() - 2)] = lineno;
            continue;
        }
        else if (line[0] == '/' || line.empty()) continue;
        lineno++;
    }
    file.clear();
    file.seekg(0, ios::beg); 
}

void variables(ifstream& file) //handling variables. call this after calling insert
{
    int start=16;   
    string temp;
    while(getline(file, temp))
    {
        string line = nospace(temp);
        if(line[0]!='@') continue;
        string substring = line.substr(1);
        auto it = table.find(substring);
        if(it!=table.end()) continue;//substring already exists in table(i.e it is a symbol)
        else if(!isint(substring))
        {
            while(true) //while start is not a value in the table insert key substring with value start
            {
                table[substring] = start++;
                break;
            }
        }
    }
    file.clear();
    file.seekg(0, ios::beg); 
}

int main(int argc, char* argv[])
{
    ifstream inputfile(argv[1]);
    if(!inputfile.is_open())return 1;
    ofstream outputfile(argv[2]); 
    if(!outputfile.is_open()) return 1;
    insert(inputfile);
    variables(inputfile);
    string templine; 
    while(getline(inputfile, templine))
    {
        string line = nospace(templine);
        if(line[0]=='/' || line.empty() || line[0]=='(') continue;
        string statement = line.substr(1);
        if(isa(line)) outputfile << ainst(statement) << endl;
        else outputfile << cinst(line) << endl;
    }
}