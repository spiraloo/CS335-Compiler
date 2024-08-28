#include<iostream>
#include<bits/stdc++.h>
#include"parse_tree.h"
using namespace std;
const int stack_offset = 8;
int func_count = 0;
map<string,string> func_name_map;
using namespace std;
int is_main_present =0;

struct instruction{
    string op="";
    string arg1="";
    string arg2="";
    string arg3="";
    string code="";
    string ins_type="";

    string comment="";
    instruction(){;};
    instruction(string , string a1="", string a2="", string a3="", string it="ins",string comment="");
};
struct subroutine_entry{
    string name = "";
    int offset = 0;         // offset from the base pointer in subroutine

    subroutine_entry();
    subroutine_entry(string, int);
    // other entries may be added later
};
struct subroutine_table{
    string subroutine_name;
    bool is_main_function = false;
    map<string, subroutine_entry> lookup_table;
    int total_space;
    int number_of_params = 0;

    subroutine_table();
    void construct_subroutine_table(vector<quad> subroutine_ins);
    bool isVariable(string s);
};
struct codegen {
    vector< vector<quad> > subroutines;
    vector<instruction> code;
    vector<subroutine_table* > sub_tables;
    // string code;
    
    codegen(){;};
    void append_ins(instruction ins);
    void print_code(string asm_file = "asm.s");

    void get_tac_subroutines();                             // generates all the subroutines from the tac
    void gen_tac_basic_block(vector<quad>, subroutine_table*);      // generates all the basic blocks from subroutines
    
    bool isVariable(string s);
    bool isMainFunction(string s);
    string get_func_name(string s);          

    void gen_global();                                      // generates code for the global region
    void gen_text();                                        // generates code for the text region
    void gen_fixed_subroutines();                           // generates some fixed subroutines
    void gen_subroutine(vector<quad> subroutine);           // generates code for individual subroutines
    void gen_basic_block(vector<quad> BB, subroutine_table*);       // generates code for basic blocks
    vector<instruction> make_x86_code(quad, int x = 0, int y = 0, int z = 0);     // generates x86 for a single tac instruction
};
instruction::instruction(string op, string a1, string a2, string a3, string it, string comment) : op(op), arg1(a1), arg2(a2), arg3(a3), ins_type(it), comment(comment){
    if(it == "ins") {           // default instructions
        if(arg3 == "") {
            code = "\t\t" + op;
            if(arg1 != ""){
                code += "\t" + arg1;
            } 
            if(arg2 != ""){
                code += ",\t" + arg2;
            }
        }
        else {

        }
    }
    else if(it == "segment") {  // text segment, global segment
        code = op;
        if(a1 != "") {
            code += "\t" + a1;
        }
    }
    else if(it == "label") {    // jump labels and subroutine labels
        code = arg1 + ":";
    }
    else if(it == "comment") {
        code = "\n\t\t# " + comment + "\n";
        return;
    }
    else {                      // other instruction types if used

    }
    if(comment != ""){
        code += "\t\t# " + comment;
    }
    code += "\n";
}

bool codegen::isVariable(string s) {   // if the first character is a digit/-/+, then it is a constant and not a variable
    if(s == "")
    {
        cout << "Error: Empty string is neither variable nor constant" << endl;
        exit(1);
    }
    return !(s[0] >= '0' && s[0] <= '9') && (s[0] != '-') && (s[0] != '+') && (s[0] != '\"');
}

bool codegen::isMainFunction(string s) {
    //to be checked
    if(s == "main") {
        return true;
    }
    return false;
}
string codegen::get_func_name(string s) {
    if(func_name_map.find(s) == func_name_map.end()) {
        func_count++;
        func_name_map[s] = "func" + to_string(func_count);
    }

    return func_name_map[s];
}

vector<instruction> codegen :: make_x86_code(quad q,int x, int y , int z){
    vector<instruction> insts;
    instruction ins;
    if (q.code == ""){
        return insts;
    }
    else {
        if (q.made_from != "stack_increment" || q.made_from != "pop_param"){
            ins = instruction("", "", "", "", "comment", q.code);
            insts.push_back(ins);
        }
    }
    if (q.is_target){
        // cout << "label" << q.ins_line << ":\n";
        ins = instruction("","L"+to_string(q.ins_line),"","","label");
        insts.push_back(ins);
    }
    if (q.made_from  == "binary_op"){ // c(z) = a(x) op b(y)
            //load x into eax
        // cout << q.code << "is in binary op" << q.arg1 << q.arg2 << q.result << q.op <<endl;
        if(q.op == "+" || q.op == "+="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if (q.arg1[0] == '*'){
                    //argument is of type *t1
                    //x would have offset of q.arg1's temp variable we have to load the value of that temp variable
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                    //after this rd will have the value of *t1 which is desired.
                }
                else {
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("add", "$" + q.arg2, "%rdx");
            }
            else{
                if (q.arg2[0] == '*'){
                    //argument is of type *t1
                    //x would have offset of q.arg1's temp variable we have to load the value of that temp variable
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("add", "(%rcx)", "%rdx");
                    //after this rd will have the value of *t1 which is desired.
                }
                else {
                ins = instruction("add", to_string(y) + "(%rbp)", "%rdx");
                }
            }
            // insts.push_back(ins);

        }   
        else if (q.op == "-" || q.op == "-="){
             if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if (q.arg1[0] == '*'){
                    //argument is of type *t1
                    //x would have offset of q.arg1's temp variable we have to load the value of that temp variable
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                    //after this rd will have the value of *t1 which is desired.
                }
                else {
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("sub", "$" + q.arg2, "%rdx");
            }
            else{
                if (q.arg2[0] == '*'){
                    //argument is of type *t1
                    //x would have offset of q.arg1's temp variable we have to load the value of that temp variable
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("add", "(%rcx)", "%rdx");
                    //after this rd will have the value of *t1 which is desired.
                }
                else {
                ins = instruction("sub", to_string(y) + "(%rbp)", "%rdx");
                }
            }
            // insts.push_back(ins);
        }
        else if (q.op == "/" || q.op == "/=" || q.op == "//" ){ 
            if(!isVariable(q.arg1)){   // arg1 is a literal
                ins = instruction("movq", "$" + q.arg1, "%rax");
                insts.push_back(ins);
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rax");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rax)", "%rax");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rax");
                }
                insts.push_back(ins);                
            }
            ins = instruction("cqto");
            insts.push_back(ins);

            if(!isVariable(q.arg2)){  // arg2 is a literal
                ins = instruction("movq", "$" + q.arg2, "%rbx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rbx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rbx)", "%rbx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rbx");
                }
            }
            insts.push_back(ins);
            ins = instruction("idiv", "%rbx", "");
            insts.push_back(ins);
            ins = instruction("movq", "%rax", "%rdx");
        }
        else if (q.op == "*" ||  q.op == "*="){ 
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else {
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("imul", "$" + q.arg2, "%rdx");
            }
            else{
                if (q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("imul", "(%rcx)", "%rdx");
                }
                else {
                    ins = instruction("imul", to_string(y) + "(%rbp)", "%rdx");
                }
            }
        }
        else if (q.op == "%" || q.op == "%="){
            if(!isVariable(q.arg1)){   // arg1 is a literal
                ins = instruction("movq", "$" + q.arg1, "%rax");
                insts.push_back(ins);
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rax");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rax)", "%rax");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rax");
                }
                insts.push_back(ins);                
            }
            ins = instruction("cqto");
            insts.push_back(ins);

            if(!isVariable(q.arg2)){  // arg2 is a literal
                ins = instruction("movq", "$" + q.arg2, "%rbx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rbx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rbx)", "%rbx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rbx");
                }
            }
            insts.push_back(ins);
            ins = instruction("idiv", "%rbx", "");
        }
        //or xor and operators
        else if (q.op == "|" || q.op== "|="){  
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else {
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("or", "$" + q.arg2, "%rdx");
            }
            else{
                if (q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("or", "(%rcx)", "%rdx");
                }
                else {
                    ins = instruction("or", to_string(y) + "(%rbp)", "%rdx");
                }
            }    
        }
        else if (q.op == "&" || q.op == "&="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else {
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("and", "$" + q.arg2, "%rdx");
            }
            else{
                if (q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("and", "(%rcx)", "%rdx");
                }
                else {
                    ins = instruction("and", to_string(y) + "(%rbp)", "%rdx");
                }
            }     
        }
        else if (q.op == "^" || q.op == "^="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("xor", "$" + q.arg2, "%rdx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("xor", "(%rcx)", "%rdx");
                }
                else{
                    ins = instruction("xor", to_string(y) + "(%rbp)", "%rdx");
                }
            }
        }
        //relops
        else if (q.op == "<"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jg", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if (q.op == ">"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jl", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if (q.op == "=="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("je", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");

        }
        else if (q.op == ">=" ){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jle", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        else if (q.op == "<="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jge", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");

        }
        else if (q.op == "!="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if(q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("cmp", "%rdx", "%rcx");
            insts.push_back(ins);
            ins = instruction("jne", "1f");  // true
            insts.push_back(ins);
            ins = instruction("movq", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f"); // false
            insts.push_back(ins);
            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", "%rdx");
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");
        }
        //shift operators
        else if (q.op == "<<" | q.op == "<<="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else {
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if (q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("sal", "%cl", "%rdx");
        }
        else if (q.op == ">>" || q.op == ">>="){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else {
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg2, "%rcx");
            }
            else{
                if (q.arg2[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rcx)", "%rcx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
                }
            }
            insts.push_back(ins);
            ins = instruction("sar", "%cl", "%rdx");
        }
        //logical operators
        else if(q.op == "and"){
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("je", "1f");
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("je", "1f");
            insts.push_back(ins);
            ins = instruction("movq", "$1", to_string(z) + "(%rbp)" );
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);

            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$0", to_string(z) + "(%rbp)");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");            
        }

        else if(q.op == "or")
        {
            if(!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jne", "1f");
            insts.push_back(ins);

            if(!isVariable(q.arg2)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else{
                if(q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else{
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);

            ins = instruction("cmp", "$0", "%rdx");
            insts.push_back(ins);
            ins = instruction("jne", "1f");
            insts.push_back(ins);
            ins = instruction("movq", "$0", to_string(z) + "(%rbp)" );
            insts.push_back(ins);
            ins = instruction("jmp", "2f");
            insts.push_back(ins);

            ins = instruction("", "1", "", "", "label");
            insts.push_back(ins);
            ins = instruction("movq", "$1", to_string(z) + "(%rbp)");
            insts.push_back(ins);
            ins = instruction("", "2", "", "", "label");    
        }
        
        else if (q.op == "**="){

        }
        
        insts.push_back(ins);
        //store the result currently in rdx to offset z of q.result
        if (q.result[0] == '*'){
            ins = instruction("movq", to_string(z) + "(%rbp)", "%rcx");
            insts.push_back(ins);
            ins = instruction("movq", "%rdx", "(%rcx)");
        }
        else {
            ins = instruction("movq", "%rdx", to_string(z) + "(%rbp)");
        }
        insts.push_back(ins);
    }
    else if (q.made_from == "unary_op"){ //b(y) = op a(x)
        if (q.op == "u~"){
            if (!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rdx");
            }
            else {
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rdx)", "%rdx");
                }
                else {
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                }
            }
            insts.push_back(ins);
            ins = instruction("not", "%rdx");
        }
        else if (q.op == "u-"){
            ins = instruction("movq","$0","%rdx");
            insts.push_back(ins);
            if (!isVariable(q.arg1)){
                ins = instruction("sub", "$" + q.arg1, "%rdx");
            }
            else {
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("sub", "(%rcx)", "%rdx");
                }
                else {
                    ins = instruction("sub", to_string(x) + "(%rbp)", "%rdx");
                }
            }
        }
        else if (q.op == "u+"){
            ins = instruction("movq","$0","%rdx");
            insts.push_back(ins);
            if (!isVariable(q.arg1)){
                ins = instruction("add", "$" + q.arg1, "%rdx");
            }
            else {
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(x) + "(%rbp)", "%rcx");
                    insts.push_back(ins);
                    ins = instruction("add", "(%rcx)", "%rdx");
                }
                else {
                    ins = instruction("add", to_string(x) + "(%rbp)", "%rdx");
                }
            }
        }
        insts.push_back(ins);

        if (q.result[0] == '*'){
            ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            insts.push_back(ins);
            ins = instruction("movq", "%rdx", "(%rcx)");
        }
        else {
            ins = instruction("movq", "%rdx", to_string(y) + "(%rbp)");
        }
        insts.push_back(ins);
    }
    else if (q.made_from == "assign"){ // b(y) = a(x)
        if (!isVariable(q.arg1)){
            ins = instruction("movq", "$" + q.arg1, "%rdx");
        }
        else {
            if (q.arg1[0] == '*'){
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                insts.push_back(ins);
                ins = instruction("movq", "(%rdx)", "%rdx");
            }
            else {
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
        }
        insts.push_back(ins);
        if (q.result[0] == '*'){
            ins = instruction("movq", to_string(y) + "(%rbp)", "%rcx");
            insts.push_back(ins);
            ins = instruction("movq", "%rdx", "(%rcx)");
        }
        else {
            ins = instruction("movq", "%rdx", to_string(y) + "(%rbp)");
        }
        insts.push_back(ins);
    }
    else if (q.made_from == "assign_str"){
        // ins = instruction("lea", q.result + "_string(%rip)", to_string(x) + "(%rbp)");
        ins = instruction("lea", q.result + "_string(%rip)", "%rdx");
        insts.push_back(ins);
        ins = instruction("movq", "%rdx", to_string(x) + "(%rbp)");
        insts.push_back(ins);
    }
    else if (q.made_from == "conditional_jump"){ //if a(x) goto y
        if (!isVariable(q.arg1)){
            ins = instruction("movq", "$" + q.arg1, "%rdx");
        }
        else {
            if (q.arg1[0] == '*'){
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
                insts.push_back(ins);
                ins = instruction("movq", "(%rdx)", "%rdx");
            }
            else {
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rdx");
            }
        }
        insts.push_back(ins);
        ins = instruction("cmp", "$0", "%rdx");
        insts.push_back(ins);
        ins = instruction("jne", "L" + to_string(y));
        insts.push_back(ins);
    }
    else if (q.made_from == "goto"){ //goto x
        ins = instruction("jmp", "L" + to_string(x));
        insts.push_back(ins);
    }
    else if (q.made_from == "begin_func"){ //perform callee duties
        // y contains whether it is main function or not
        if (y == 1){
            // if (verbose){
            // cout << "this is the main function \n";
            // }
            ins = instruction("","main","","","label");
            insts.push_back(ins);
        }
        ins = instruction("",get_func_name(q.arg1),"","","label");
        insts.push_back(ins);


        ins = instruction("pushq", "%rbp");      // old base pointer
        insts.push_back(ins);
        ins = instruction("movq", "%rsp", "%rbp");    // shift base pointer to the base of the new activation frame
        insts.push_back(ins);
        ins = instruction("pushq", "%rbx");
        insts.push_back(ins);
        ins = instruction("pushq", "%rdi");
        insts.push_back(ins);
        ins = instruction("pushq", "%rsi");
        insts.push_back(ins);
        ins = instruction("pushq", "%r12");
        insts.push_back(ins);
        ins = instruction("pushq", "%r13");
        insts.push_back(ins);
        ins = instruction("pushq", "%r14");
        insts.push_back(ins);
        ins = instruction("pushq", "%r15");
        insts.push_back(ins);
        //shift stack ptr to make space for locals and temporaries.
        if (x > 0){
            ins = instruction("subq", "$" + to_string(x), "%rsp");
            insts.push_back(ins);
        }
    }
    else if (q.made_from == "return"){ // return a(y)
        if (q.arg1 != ""){
            //return with any non void value
            if (!isVariable(q.arg1)){
                ins = instruction("movq", "$" + q.arg1, "%rax");
            }
            else {
                if (q.arg1[0] == '*'){
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rax");
                    insts.push_back(ins);
                    ins = instruction("movq", "(%rax)", "%rax");
                }
                else {
                    ins = instruction("movq", to_string(y) + "(%rbp)", "%rax");
                }
            }
            insts.push_back(ins);
        }
            ins = instruction("add", "$" + to_string(x), "%rsp"); // deletes all local and temp variables.
            insts.push_back(ins);
            ins = instruction("popq", "%r15");                      // restore old register values
            insts.push_back(ins);
            ins = instruction("popq", "%r14");
            insts.push_back(ins);
            ins = instruction("popq", "%r13");
            insts.push_back(ins);
            ins = instruction("popq", "%r12");
            insts.push_back(ins);
            ins = instruction("popq", "%rsi");
            insts.push_back(ins);
            ins = instruction("popq", "%rdi");
            insts.push_back(ins);
            ins = instruction("popq", "%rbx");
            insts.push_back(ins);
            ins = instruction("popq", "%rbp");
            insts.push_back(ins);

            ins = instruction("ret");
            insts.push_back(ins);
        
    }
    else if (q.made_from == "end_func"){
        if (x == 1){
            ins = instruction("movq", "$60", "%rax");
            insts.push_back(ins);
            ins = instruction("xor", "%rdi", "%rdi");
            insts.push_back(ins);
            ins = instruction("syscall");
            insts.push_back(ins);
        }
        else {
             // end func cannot return any values    
            ins = instruction("add", "$" + to_string(y), "%rsp");   // delete all local and temporary variables
            insts.push_back(ins);
            ins = instruction("popq", "%r15");                      // restore old register values
            insts.push_back(ins);
            ins = instruction("popq", "%r14");
            insts.push_back(ins);
            ins = instruction("popq", "%r13");
            insts.push_back(ins);
            ins = instruction("popq", "%r12");
            insts.push_back(ins);
            ins = instruction("popq", "%rsi");
            insts.push_back(ins);
            ins = instruction("popq", "%rdi");
            insts.push_back(ins);
            ins = instruction("popq", "%rbx");
            insts.push_back(ins);
            ins = instruction("popq", "%rbp");
            insts.push_back(ins);
            ins = instruction("ret");
            insts.push_back(ins);
        }
    }
    else if (q.made_from == "stack_increment"){
        //leave it as it is 
    }
    else if (q.made_from == "function_call"){ //x has no of params
        if (x == 0){
            ins = instruction("pushq", "%rax");
            insts.push_back(ins);
            ins = instruction("pushq", "%rcx");
            insts.push_back(ins);
            ins = instruction("pushq", "%rdx");
            insts.push_back(ins);
            ins = instruction("pushq", "%r8");
            insts.push_back(ins);
            ins = instruction("pushq", "%r9");
            insts.push_back(ins);
            ins = instruction("pushq", "%r10");
            insts.push_back(ins);
            ins = instruction("pushq", "%r11");
            insts.push_back(ins);
        }
        ins = instruction("call", this -> get_func_name(q.arg1));      // call the function
        insts.push_back(ins);
        if (this->get_func_name(q.arg1) == "print"){
            ins = instruction("add", "$8", "%rsp");
            insts.push_back(ins);
        }
        else if (this->get_func_name(q.arg1) == "memalloc"){
            ins = instruction("add", "$8", "%rsp");
            insts.push_back(ins);
        }
        else if (x > 0){ //pop the parameters
            ins = instruction("add", "$" + to_string(x*stack_offset), "%rsp");
            insts.push_back(ins);
        }
    }
    else if (q.made_from == "return_val"){
        if (q.result != ""){
            ins = instruction("movq","%rax", to_string(x) + "(%rbp)");
            insts.push_back(ins);
        }
        ins = instruction("popq", "%r11");
        insts.push_back(ins);
        ins = instruction("popq", "%r10");
        insts.push_back(ins);
        ins = instruction("popq", "%r9");
        insts.push_back(ins);
        ins = instruction("popq", "%r8");
        insts.push_back(ins);
        ins = instruction("popq", "%rdx");
        insts.push_back(ins);
        ins = instruction("popq", "%rcx");
        insts.push_back(ins);
        ins = instruction("popq", "%rax");
        insts.push_back(ins);
    }
    else if (q.made_from == "push_param"){
        if (y == 1){
        ins = instruction("pushq", "%rax");
        insts.push_back(ins);
        ins = instruction("pushq", "%rcx");
        insts.push_back(ins);
        ins = instruction("pushq", "%rdx");
        insts.push_back(ins);
        ins = instruction("pushq", "%r8");
        insts.push_back(ins);
        ins = instruction("pushq", "%r9");
        insts.push_back(ins);
        ins = instruction("pushq", "%r10");
        insts.push_back(ins);
        ins = instruction("pushq", "%r11");
        insts.push_back(ins);
        }
        if (!isVariable(q.arg1)){
            ins = instruction("pushq", "$" + q.arg1, "");
            insts.push_back(ins);

        }
        else {
            if (q.arg1[0] == '*'){
                ins = instruction("movq", to_string(x) + "(%rbp)", "%rcx");
                insts.push_back(ins);
                ins = instruction("pushq", "(%rcx)", "");
            }
            else {
                ins = instruction("pushq", to_string(x) + "(%rbp)", "");
                // insts.push_back(ins);
            }
            // ins = instruction("pushq", to_string(x) + "(%rbp)");
            insts.push_back(ins);
        }
    }
    return insts;
}
void codegen::get_tac_subroutines() {
    vector<quad> subroutine;
    bool func_started = false;
    for(quad q : global_quads) {
        if(q.made_from == "function_call") {
            if(q.arg1 == "main"){
                is_main_present =1;
            }
        }
    }
    for(quad q : global_quads) {
        if(is_main_present==1){
            if(q.made_from == "begin_func") {
                func_started = true;
            }

            if(func_started) {
                subroutine.push_back(q);
            }

            if(q.made_from == "end_func") {
                func_started = false;
                if(subroutine.size()){
                    this -> subroutines.push_back(subroutine);
                    subroutine.clear();
                }
            }
        }
        else {
            cout << "Fatal Error: No call to main function found" << endl;
            cout << "Assembly not generated!" << endl;
            exit(1);
        } 
    }
}
void codegen::gen_global() {
    // @TODO
    instruction ins;
    ins = instruction(".data", "", "", "", "segment");
    this -> code.push_back(ins);

    ins = instruction("integer_format:", ".asciz", "\"%ld\\n\"", "", "ins");
    this -> code.push_back(ins);
    ins = instruction("string_format:", ".asciz", "\"%s\\n\"", "", "ins");
    this -> code.push_back(ins);

    for(auto it: ds_vector){
        ins = instruction(it[0], it[1], it[2], it[3], it[4]);
        this -> code.push_back(ins);
    }
    ins = instruction(".global", "main", "", "", "segment");      // define entry point
    this -> code.push_back(ins);
}
void codegen::gen_fixed_subroutines() {
    func_name_map["print"] = "print";
    func_name_map["memalloc"] = "memalloc";
    func_name_map["printstr"] = "printstr";
    func_name_map["mystrcmp"] = "mystrcmp";
    func_name_map["mystrcmpN"] = "mystrcmpN";
}
void codegen::gen_basic_block(vector<quad> BB, subroutine_table* sub_table) {
    for(quad q : BB) {
        vector<instruction> insts;
        if(q.made_from == "conditional_jump"){
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = q.abs_jump;
            insts = this -> make_x86_code(q, x, y);
        }
        else if(q.made_from == "goto"){
            insts = this -> make_x86_code(q, q.abs_jump);
        }
        else if(q.made_from == "binary_op"){
            int z = sub_table -> lookup_table[q.result].offset;
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = sub_table -> lookup_table[q.arg2].offset;
            insts = this -> make_x86_code(q, x, y, z);            
        }
            else if(q.made_from == "unary_op"){    // b(y) = op a(x)
            int y = sub_table -> lookup_table[q.result].offset;
            int x = sub_table -> lookup_table[q.arg1].offset;
            insts = this -> make_x86_code(q, x, y);           
        }
        else if(q.made_from == "assign"){   // b(y) = a(x)
            int y = sub_table -> lookup_table[q.result].offset;
            int x = sub_table -> lookup_table[q.arg1].offset;
            insts = this -> make_x86_code(q, x, y);                
        }
        else if(q.made_from == "assign_str"){
            int x = sub_table -> lookup_table[q.result].offset;
            insts = this -> make_x86_code(q, x);
        }
        else if(q.made_from == "store"){        // *(r(z) + a2) = a1(x)
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = sub_table -> lookup_table[q.arg2].offset;   // always 0 since q.arg2 contains a constant always
            int z = sub_table -> lookup_table[q.result].offset;

            insts = this -> make_x86_code(q, x, y, z);
        }
        else if(q.made_from == "load"){         // r(z) = *(a1(x) + a2)
            int x = sub_table -> lookup_table[q.arg1].offset;
            int y = sub_table -> lookup_table[q.arg2].offset; // always 0 since q.arg2 contains a constant always
            int z = sub_table -> lookup_table[q.result].offset;

            insts = this -> make_x86_code(q, x, y, z);
        }
        else if(q.made_from == "push_param"){   // push_param a1(x)
            int x = sub_table -> lookup_table[q.arg1].offset;
            sub_table -> number_of_params++;
            insts = this -> make_x86_code(q, x, sub_table -> number_of_params);
        }
        else if(q.made_from == "pop_param"){   // r(x) = pop_param
            // no need to do anything really

            insts = this -> make_x86_code(q);
        }
        else if(q.made_from == "function_call") {
            insts = this -> make_x86_code(q, sub_table -> number_of_params);
            sub_table -> number_of_params = 0;          // reset variable
        }
        else if(q.made_from == "return") { //this is for return
            insts = this -> make_x86_code(q, sub_table -> total_space - 8 * stack_offset, sub_table -> lookup_table[q.arg1].offset);
        }
        else if (q.made_from == "return_val"){
            insts = this->make_x86_code(q, sub_table->lookup_table[q.result].offset);
        }
        else if(q.made_from == "begin_func") {  // manage callee saved registers
            if(isMainFunction(q.arg1)) {
                sub_table -> is_main_function = true;
            }
            insts = this -> make_x86_code(q, sub_table -> total_space - 8 * stack_offset, sub_table -> is_main_function);        // space of 8 registers is not considered
        }
        else if(q.made_from == "end_func") {    // clean up activation record
            // ideally only reaches this place in a void function
            insts = this -> make_x86_code(q, sub_table -> is_main_function, sub_table -> total_space - 8 * stack_offset);
        }
        else if(q.made_from == "stack_increment") {       // no need to do anything really
            insts = this -> make_x86_code(q);
        }
        else{
            insts = this -> make_x86_code(q);
        }

        // append all the instructions finally
        for(instruction ins : insts) {
            this -> code.push_back(ins);
        }
    }
}
void codegen::gen_tac_basic_block(vector<quad> subroutine, subroutine_table* sub_table) {    // generates basic blocks from subroutines
    set<int> leaders;
    vector<quad > BB;

    int base_offset = subroutine[0].ins_line;
    leaders.insert(base_offset);

    for(quad q : subroutine) {
        if(q.made_from == "conditional_jump" || q.made_from == "goto") {
            leaders.insert(q.abs_jump);
            leaders.insert(q.ins_line + 1);
        }
        else if(q.made_from == "function_call") {
            leaders.insert(q.ins_line);
            leaders.insert(q.ins_line + 1); // call func is made of a singular basic block
        }
    }

    vector<int> ascending_leaders;
    for(int leader : leaders) { 
        ascending_leaders.push_back(leader); 
    }
    
    int prev_leader = ascending_leaders[0];
    for(int i = 1; i < ascending_leaders.size(); i++) {
        BB.clear();
        
        for(int j = prev_leader; j < ascending_leaders[i]; j++) {
            BB.push_back(subroutine[j - base_offset]);
        }
        prev_leader = ascending_leaders[i];

        this -> gen_basic_block(BB, sub_table);
    }

    BB.clear();
    int final_leader = ascending_leaders[ascending_leaders.size() - 1];
    for(int i = final_leader; i - base_offset < subroutine.size(); i++) {
        BB.push_back(subroutine[i - base_offset]);
    }

    this -> gen_basic_block(BB, sub_table);
}

void codegen::gen_text() {
    instruction ins(".text", "", "", "", "segment");
    this -> code.push_back(ins);

    this -> gen_fixed_subroutines();

    this -> get_tac_subroutines();      // get the subroutines from entire TAC

    for(auto subroutine : this -> subroutines) {
        subroutine_table* sub_table = new subroutine_table();
        sub_table -> construct_subroutine_table(subroutine);

        this -> sub_tables.push_back(sub_table);
        this -> gen_tac_basic_block(subroutine, sub_table);
    }
}

void codegen::print_code(string asm_file) {
    ofstream out(asm_file);
    
    if(asm_file == "") {
        for(auto ins : this -> code) {
            cout << ins.code;
        }
    }
    else {
        for(auto ins : this -> code) {
            out << ins.code;
        }
    }

    ifstream print_func("print_func.s");
    string line;

    while(getline(print_func, line)){
        out << line << '\n';
    }

    ifstream print_func_str("print_func_str.s");
    while(getline(print_func_str, line)){
        out << line << '\n';
    }

    ifstream mystrcmp("strcmp.s");
    while(getline(mystrcmp, line)){
        out << line << '\n';
    }
    

    ifstream alloc_mem("memalloc.s");
    while(getline(alloc_mem, line)) {
        out << line << '\n';
    }
}

subroutine_entry::subroutine_entry(){;}

subroutine_entry::subroutine_entry(string name, int offset) {
    this -> name = name;
    this -> offset = offset;
}

subroutine_table::subroutine_table(){;}

bool subroutine_table::isVariable(string s) {   // if the first character is a digit/-/+, then it is a constant and not a variable
    if(s == "")
    {
        cout << "Error: Empty string is neither variable nor constant" << endl;
        exit(1);
    }
    return !(s[0] >= '0' && s[0] <= '9') && (s[0] != '-') && (s[0] != '+') && (s[0] != '\"');
}
void subroutine_table::construct_subroutine_table(vector<quad> subroutine_ins){
     int pop_cnt = 2;         // 1 8 byte space for the return address + old base pointer
    int local_offset = 8;    // 8 callee saved registers hence, 8 spaces kept free, rsp shall automatically be restored, rbp too
    for (quad q : subroutine_ins ){
        if (q.made_from == "begin_func" || q.made_from == "function_call" || q.made_from == "stack_increment" ){
            continue;
        }
        if(q.made_from == "pop_param") {
            this -> lookup_table[q.arg1] = subroutine_entry(q.arg1, stack_offset*pop_cnt);
            this -> lookup_table["*"+q.arg1] = subroutine_entry("*"+q.arg1, stack_offset*pop_cnt);
            pop_cnt++;
        }
        else {
            if (q.made_from == "conditional_jump"){
                if (this->lookup_table.find(q.arg1) == this->lookup_table.end() && isVariable(q.arg1)){
                    this->lookup_table[q.arg1] = subroutine_entry(q.arg1, -stack_offset*local_offset);
                    this->lookup_table["*"+q.arg1] = subroutine_entry("*"+q.arg1, -stack_offset*local_offset);
                    local_offset++;
                }
            }
            else if (q.made_from == "goto"){
                continue;
            }
            else {
                if (q.arg1 != "" && this->lookup_table.find(q.arg1) == this->lookup_table.end() && isVariable(q.arg1)){
                    this->lookup_table[q.arg1] = subroutine_entry(q.arg1, -stack_offset*local_offset);
                    this->lookup_table["*"+q.arg1] = subroutine_entry("*"+q.arg1, -stack_offset*local_offset);
                    local_offset++;
                }
                else if (q.arg2 != "" && this->lookup_table.find(q.arg2) == this->lookup_table.end() && isVariable(q.arg2)){
                    this->lookup_table[q.arg2] = subroutine_entry(q.arg2, -stack_offset*local_offset);
                    this->lookup_table["*"+q.arg2] = subroutine_entry("*"+q.arg2, -stack_offset*local_offset);
                    local_offset++;
                }
                else if(q.result != "" && this -> lookup_table.find(q.result) == this -> lookup_table.end() && isVariable(q.result)) {
                    // cout << "result: " << q.result << "created" <<  endl ;
                    this -> lookup_table[q.result] = subroutine_entry(q.result, -stack_offset*local_offset);
                    this->lookup_table["*"+q.result] = subroutine_entry("*"+q.result, -stack_offset*local_offset);
                    local_offset++;
                }
                if(q.result == "s" && isVariable(q.result) == 0)
                    cout << "Error: varible not detected for " << q.result << endl;
            }
        }
    }
    this -> total_space = stack_offset*local_offset; // total space occupied by callee saved registers + locals + temporaries
}
