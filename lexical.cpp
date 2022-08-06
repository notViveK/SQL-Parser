#include<iostream>
#include<cstring>
#include<string>
using namespace std;

//...................SYMBOL TABLE......................//
namespace SymTab{
    
    const int MAX = 100;
    
    class Node
{

    string identifier, type;
    
    Node *next;

public:
    Node()
    {
        next = NULL;
    }

    Node(string key, string type)
    {
        this->identifier = key;
        this->type = type;
        
        next = NULL;
    }

    void print()
    {
        cout << "Identifier's Name:" << identifier<< "\nType:" << type << endl;
    }
    friend class SymbolTable;
};

class SymbolTable
{
    Node *head[MAX];

public:
    SymbolTable()
    {
        for (int i = 0; i < MAX; i++)
            head[i] = NULL;
    }

    int hashf(string id); // hash function
    bool insert(string id, string Type);
    string find(string id);
    
};
// Function to find an identifier
string SymbolTable::find(string id)
{
    int index = hashf(id);
    Node* start = head[index];
  
    if (start == NULL)//empty symbol table
        return "-1";
  
    while (start != NULL) {
  
        if (start->identifier == id) {
            start->print();
            return " ";
        }
  
        start = start->next;
    }
  
    return "-1"; // not found
}

// Function to insert an identifier
bool SymbolTable::insert(string id, string type)
{
    int index = hashf(id);
    Node *p = new Node(id, type);

    if (head[index] == NULL)
    {
        head[index] = p;
        cout << "\n" << id << "\t"<< type;

        return true;
    }

    else
    {
        Node *start = head[index];
        while (start->next != NULL)
            start = start->next;

        start->next = p;
        cout << "\n" << id << "\t"<< type;

        return true;
    }

    return false;
}
// hash function for sym table
int SymbolTable::hashf(string id)
{
    int asciiSum = 0;

    for (int i = 0; i < id.length(); i++)
    {
        asciiSum = asciiSum + id[i];
    }

    return (asciiSum % 100);
}
}

//.....................................................//

//...................DECLARATIONS.......................//
int dfa=0;
string key[]={"select","delete","insert","value","into","from","where","order","group","by"};
string tokens[1000];
int total=0;
SymTab::SymbolTable st;
//.....................................................//
//.....START STATE.....//
void start(char c){
    int check=((int)c);
    if((check>=65&&check<=90)||(check>=97&&check<=122)){
        dfa=1;
    }
    else{
        dfa=-1;
    }
}
//.....STATE 1.....//
void state1(char c){
    int check=((int)c);
    if((check>=65&&check<=90)||(check>=97&&check<=122)){
        dfa=1;
    }
    else if(check>=48&&check<=57){
        dfa=1;
    }
    else if(c==','){
        dfa=1;
    }
    else if(c=='*'){
        dfa=2;
    }
    else if(isspace(c)){
        dfa=3;
    }
    else if(c=='>'||c=='<'||c=='='){
        dfa=5;
    }
    else if(c==';'){
        dfa=6;
    }
    else{
        dfa=-1;
    }
}
//.....STATE 2.....//
void state2(char c){
    if(isspace(c)){
        dfa=3;
    }
    else{
        dfa=-1;
    }
}
//.....STATE 3.....//
void state3(char c){
    int check=((int)c);
    if((check>=65&&check<=90)||(check>=97&&check<=122)){
        dfa=1;
    }
    else if(check>=48&&check<=57){
        dfa=4;
    }
    else{
        dfa=-1;
    }
}
//.....STATE 4.....//
void state4(char c){
    int check=((int)c);
    if(check>=48&&check<=57){
        dfa=4;
    }
    else if(isspace(c)){
        dfa=3;
    }
    else if(c=';'){
        dfa=6;
    }
    else{
        dfa=-1;
    }
}
//.....STATE 5.....//
void state5(char c){
    int check=((int)c);
    if(c=='='){
        dfa=5;
    }
    else if((check>=65&&check<=90)||(check>=97&&check<=122)){
        dfa=1;
    }
    else if(check>=48&&check<=57){
        dfa=4;
    }
    else{
        dfa=-1;
    }

}
//..........LEXICAL CHECKING...........//
int check_lex(string input){
    int len=input.length();
    for(int i=0;i<len;i++){
        if (dfa == 0)
            start(input[i]);
        else if (dfa == 1)
            state1(input[i]);
        else if (dfa == 2)
            state2(input[i]);
        else if (dfa == 3)
            state3(input[i]);
        else if (dfa == 4)
            state4(input[i]);
        else if (dfa == 5)
            state5(input[i]);
        else
            break;
    }
    if(dfa==6){
        return 1;
    }
    else{
        return 0;
    }
}

string upperstr(string str){
    int len=str.length();
    string result;
    for(int i=0;i<len;i++){
        result+=(char)(str[i]-32);
    }
    return result;
}

int is_num(string str){
    int len=str.length();
    int flag=0;
    for(int i=0;i<len;i++){
        if(isdigit(str[i])){
            flag=0;
        }
        else{
            flag=1;
            break;
        }
    }
    if(flag==0) return 1;
    else return 0;
}

string generate_lex(string input){
    int len=input.length(), start, end;
    string result="", sub;
    char c;
    start=0;
    for(int i=0;i<len;i++){
        c=input[i];
        if(isspace(c)||c==','||c=='>'||c=='<'||c==';'){
            end=i-start;
            sub=input.substr(start,end);
            start=i+1;
            int flag=0;
            for(int j=0;j<10;j++){
                string keyu=upperstr(key[j]);
                if(key[j].compare(sub)==0||keyu.compare(sub)==0){
                    flag=1;
                    break;
                }
            }
            if(flag==1){
                result+=sub;
                result+=c;
                if(isspace(c)){
                    tokens[total]=sub;
                    total+=1;
                }
                else{
                    string te="";
                    te+=c;
                    tokens[total]=sub;
                    total+=1;
                    tokens[total]=te;
                    total+=1;
                }
            }
            else{
                if(is_num(sub)){
                        result+="num";
                        result+=c;
                        if(isspace(c)){
                    tokens[total]="num";
                    total+=1;
                    st.insert(sub,"num");
                }
                else{
                    string te="";
                    te+=c;
                    tokens[total]="num";
                    total+=1;
                    tokens[total]=te;
                    total+=1;
                    st.insert(sub,"num");
                }
                    }
                    else{
                        result+="id";
                        result+=c;
                        if(isspace(c)){
                    tokens[total]="id";
                    total+=1;
                    st.insert(sub,"id");
                }
                else{
                    string te="";
                    te+=c;
                    tokens[total]="id";
                    total+=1;
                    tokens[total]=te;
                    total+=1;
                    st.insert(sub,"id");
                }
                    }
            }
        }
        else if(c=='='){
            if(input[i-1]=='>'||input[i-1]=='<'){
                result+=c;
                start=i+1;
                string te="";
                te+=c;
                tokens[total-1]=input[i-1]+te;
                total+=1;
            }
            else{
                end=i-start;
                sub=input.substr(start,end);
                int flag=0;
                for(int j=0;j<10;j++){
                    string keyu=upperstr(key[j]);
                    if(key[j].compare(sub)==0||keyu.compare(sub)==0){
                        flag=1;
                        break;
                    }
                }
                if(flag==1){
                    result+=sub;
                    result+=c;
                    string te="";
                    te+=c;
                    tokens[total]=sub;
                    total+=1;
                    tokens[total]=te;
                    total+=1;
                }
                else{
                    if(is_num(sub)){
                        result+="num";
                        result+=c;
                        string te="";
                        te+=c;
                        tokens[total]="num";
                    total+=1;
                        tokens[total]=te;
                    total+=1;
                    st.insert(sub,"num");
                    }
                    else{
                        result+="id";
                        result+=c;
                        string te="";
                        te+=c;
                        tokens[total]="id";
                    total+=1;
                        tokens[total]=te;
                    total+=1;
                    st.insert(sub,"id");
                    }
                }
                start=i+1;
            }
        }
    }
    return result;
}

int main()
{
    string input, result;
    
    cout<<">>";
    getline(cin, input);
    cout<<"\nGiven Input Query : "<<input;
    if(check_lex(input)){
        result=generate_lex(input);
        cout<<"\nLexical Output : "<<result;
    }
    else{
        cout<<"\nNot Accepted";
    }
    cout<<"\n"<<total;
    for(int i=0;i<total;i++){
        cout<<"\n";
        cout<<">>"<<tokens[i];
        
    }

    cout<<st.find("age");

    return 0;
}