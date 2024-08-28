#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <fstream>
#include "symtable.h"
// #include "3ac.h"
#include <vector>
using namespace std;
extern SymbolTable* currentTable;
extern SymbolTable* globalTable;
vector<int> prev_label_if_else;
vector<vector<int>> end_labels_if_else;
static int stack_size = 0;
vector<int> prev_label_while;

vector<int> prev_label_for;

vector<vector<string>> ds_vector;
string ctor_obj = "";
STentry_Type TypeName(string value_name){
    if(value_name[0]=='I'){
        return STentry_Type::ste_integer;
    }
    else if(value_name[0] == 'S'){
        return STentry_Type::ste_str;
    }
    else if(value_name[0] == 'K' && value_name.size() == 14 && value_name == "KEYWORD (True)"){
        return STentry_Type::ste_bool;
    }
    else if(value_name[0] == 'K' && value_name.size() == 15 && value_name == "KEYWORD (False)"){
        return STentry_Type::ste_bool;
    }
    else if(value_name[0] == 'F'){
        return STentry_Type::ste_float;
    }
    else{
        return STentry_Type::ste_none;
    }
}

typedef struct quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
    string made_from = "";
    string code;
    int ins_line = 0,abs_jump = 0;
    bool is_target = false;

} quad;
string clean_string(string value)
{
    if(value == "")
        return value;
    int i = 0;
    while (value[i] != '(' && i < value.size()){
        i++;
    }
    i++;
    string original_value = "";
    while(i < value.size() -1 ){
        original_value += value[i];
        i++;
    }

    if(original_value == "")
    {
        original_value = value;
    }
    return original_value;
}
vector<quad> global_quads;
class TreeNode {
public:
    string value;
    string original_value;
    STentry* result;
    string type;
    SymbolTable* symbolTable;
    vector<quad> quads;
    TreeNode* parent = nullptr;
    vector<TreeNode*> children;
    int lineno;
    // for if else 
    
    TreeNode() {
        value = "";
        this->type = "";
        this->symbolTable = currentTable;
    }
    TreeNode(string value) {
        this->value = value;
        this->type = "";
        this->symbolTable = currentTable;
        int i = 0;
        while (value[i] != '(' && i < value.size()){
            i++;
        }
        i++;
        this->original_value = "";
        while(i < value.size() -1 ){
            this->original_value += value[i];
            i++;
        }

        if(this->original_value == "")
        {
            this->original_value = this->value;
        }
    }
    TreeNode (char* value) {
        // value = string(value);
        this->value = string(value);
        this->type = "";
        this->symbolTable = currentTable;
        int i = 0;
        string temp = string(value);
        while (temp[i] != '(' && i < temp.size()){
            i++;
        }
        i++;
        this->original_value = "";
        while(i < temp.size() -1 ){
            this->original_value += temp[i];
            i++;
        }
        if(this->original_value == "")
        {
            this->original_value = this->value;
        }
    }
    void addChild(TreeNode* child) {
        children.push_back(child);
    }
    void addChildFront(TreeNode* child){
        children.insert(children.begin(), child);
    }
    void setType(string type) {
        this->type = type;
    }
    void setlineno(int lineno) {
        this->lineno = lineno;
    }
    int getlineno() {
        return this->lineno;
    }
    //define a method to update value
    void updateValue(string value) {
        this->value = value;
    }
    void printTree(TreeNode* node) {
        if (node == nullptr) {
            cout << "epsilon" << "  ";
            return;
        }
        if(node->children.size() ==0)
            cout << node->value << "    " << "parent: " << node->parent->value << endl;

        for (TreeNode* child : node->children) {
            printTree(child);
        }
        cout << endl;
    }
    virtual ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }
    }
};
void generate_3ac(TreeNode *root, SymbolTable *table);
int cleanParseTree(TreeNode* node) {
    if (node->children.size() == 0) {
        return 0;
    }
    int non_null_children = 0;
    TreeNode* tmp = nullptr;
    for (int i=0; i<(node->children.size()); i++) {
        TreeNode* child = node->children[i];
        if(child != nullptr)
        {
            if(cleanParseTree(child) == 1)
            {
                delete child;
                child = nullptr;
                node->children[i] = nullptr;
            }
        }
        if (child != nullptr) {
            if (child->value == "INDENT" || child->value == "DEDENT" || child->value == "ENDMARKER" || child->value == "NEWLINE")
            {
                delete child;
                child = nullptr;
                node->children[i] = nullptr;
            }
            else
            {
                tmp = child;
                non_null_children++;
            }
        }
    }
    if (non_null_children == 0)
    {
        node->children.clear();
        node = nullptr;
        return 1;
    }
    if (non_null_children == 1) {
        node->value = tmp->value;
        node->original_value = tmp->original_value;
        node->type = tmp->type;
        node->result = tmp->result;
        node->symbolTable = tmp->symbolTable;
        node->lineno = tmp->lineno;
        node->children.clear();
        for(int i=0; i<(tmp->children.size()); i++)
        {
            node->children.push_back(tmp->children[i]);
        }
        tmp->children.clear();
        delete tmp;
        tmp = nullptr;
    }

    node->children.erase(remove_if(node->children.begin(), node->children.end(), [](TreeNode* child) {return child == nullptr;}),
        node->children.end());

    return 0;
}

void createParseTreeDot(TreeNode* node, ofstream& dotFile) {
        if (node == nullptr)
            return;

        string tmp = node->value;
            dotFile << "\"" << node << "\"[label=\"";
            for (char ch: tmp){
                if (ch == '\"'){
                    dotFile << "\\\"";
                }
                else {
                    dotFile << ch;
                }
            }
        if (node->children.size()==0){
            dotFile << "\" shape=box style=filled color=\"red\" fillcolor=\"grey\"];\n" <<endl;
        }
        else {
            dotFile << "\" shape=ellipse style=filled color=\"dodgerblue\" fillcolor=\"grey\"];\n"<< endl;
        }


        for (TreeNode* child : node->children) {
            if(child != nullptr)
            {
                dotFile << "\"" << node << "\" -> \"" << child << "\";" << endl;
                createParseTreeDot(child, dotFile);
            }
        }
    }

void createParentAST(TreeNode* node){
    if(node == nullptr)
        return;
    for(TreeNode* child : node->children)
    {
        if(child != nullptr)
        {
            child->parent = node;
            createParentAST(child);
        }
    }
}
void getAllTerminalValue(TreeNode* node,vector<TreeNode*> &values) {
    if (node->children.size()==0 && node != nullptr) {
        values.push_back(node);
    }

    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i] == nullptr) {
            continue;
        }
        // string value = getFirstTerminalValue(node->children[i]);
        getAllTerminalValue(node->children[i], values);
    }
    return ; // Return an empty string if no terminal value is found
    }
void getFuncParams(TreeNode* root, vector<STentry*> &params, SymbolTable* currentTable){
    if(root == nullptr)
    {
        cerr << "Error: getFuncParams called with null root" << endl;
        return;
    }
    if(root->original_value == "(" || root->original_value == ")" || root->original_value == "," || root->original_value == "[" || root->original_value == "]")
    {

        return;
    }
    if(root->children.size() == 0)
    {
        // cout << "---legit terminal" << endl;
        generate_3ac(root, currentTable);
        params.push_back(root->result);
        return;
    }
    if(root->original_value == "atom_expr" || root->type == "binary_op" || root->type == "unary_op" || root->type == "relop")
    {
        generate_3ac(root, currentTable);
        params.push_back(root->result);
        return;
    }
    if(root->original_value == "factor" && root->children[0]->type == "unary_op" )
    {
        generate_3ac(root, currentTable);
        params.push_back(root->result);
        return;
    }
    else
    {
        for(TreeNode* child : root->children)
        {
            getFuncParams(child, params, currentTable);
        }
    }
    return;
}

    /* AST structures ahead*/

// Function to generate a new temporary variable
string newTemp() {
    static int count = 0;
    return "t" + to_string(count++);
}

// Function to generate a new label
string newLabel() {
    static int count = 0;
    return "L" + to_string(count++);
}

// Function to generate a 3AC assignment statement
quad assignment( string result,string arg1) {
    quad q;
    q.op = "=";
    q.arg1 = clean_string(arg1);
    q.result = clean_string(result);
    q.code = clean_string(result) + " = " + clean_string(arg1);
    q.made_from = "assign";
    return q;
}
quad assignment_str(string target, string source){
    quad q;
    q.op = "=s";
    q.arg1 = clean_string(source);
    q.result = clean_string(target);
    q.code = clean_string(target) + " =s " + clean_string(source);
    q.made_from = "assign_str";
    return q;
}
// Function to generate a 3AC binary operation statement
quad binaryOperation(string op, string arg1, string arg2, string result) {
    quad q;
    q.op = clean_string(op);
    q.arg1 = clean_string(arg1);
    q.arg2 = clean_string(arg2);
    q.result = clean_string(result);
    q.code = clean_string(result) + " = " + clean_string(arg1) + " " + clean_string(op) + " " + clean_string(arg2);
    q.made_from = "binary_op";
    return q;
}
quad returnVal(string result){
    quad q;
    q.op = "return_value";
    q.result = clean_string(result);
    if(result == ""){
        q.code = "return_value";
    }
    else{
        q.code = "return " + clean_string(result);
    }
    q.code = clean_string(result)+ " "+ "return_value";
    q.made_from = "return_val";
    return q;
}
// Function to generate a 3AC unary operation statement
quad unaryOperation(string op, string arg1, string result) {
    quad q;
    q.op = clean_string(op);
    q.arg1 = clean_string(arg1);
    q.result = clean_string(result);
    q.code = clean_string(result) + " = " + clean_string(op) + " " + clean_string(arg1);
    q.made_from = "unary_op";
    return q;
}

// Function to generate a 3AC conditional jump statement
quad conditionalJump(string op, string arg1, string arg2, string label) {
    quad q;
    q.op = clean_string(op);
    q.arg1 = clean_string(arg1);
    q.arg2 = clean_string(arg2);
    q.result = clean_string(label);
    q.code = clean_string(op) + " " + clean_string(arg1) + " " + clean_string(arg2) + " " + clean_string(label);
    q.made_from = "conditional_jump";
    return q;
}

// Function to generate a 3AC unconditional jump statement
quad unconditionalJump(string label) {
    quad q;
    q.op = "goto";
    q.result = label;
    q.code = "goto " + clean_string(label);
    q.made_from = "goto";
    return q;
}

// Function to generate a 3AC label statement
quad labelStatement(string label) {
    quad q;
    q.op = "label";
    q.result = label;
    return q;
}


// Function to generate a 3AC function call statement
quad functionCall(string functionName,int no_of_params) {
    quad q;
    q.op = "call";
    q.arg1 = functionName;
    q.arg2 = to_string(no_of_params);
    q.code = "call " + clean_string(functionName) + " " + clean_string(to_string(no_of_params));
    q.made_from = "function_call";
    // q.arg2.pop_back(); // Remove the trailing comma
    return q;
}

// Function to generate a 3AC return statement
quad returnStatement(string arg) {
    quad q;
    q.op = "return";
    q.arg1 = clean_string(arg);
    q.result = "";
    q.code = "return " + clean_string(arg);
    q.made_from = "return";
    return q;
}

quad BeginFunc(string arg1){
    quad q;
    q.op = "beginfunc";
    q.arg1 = arg1;
    q.code = "beginfunc " + clean_string(arg1);
    q.made_from = "begin_func";
    return q;
}
quad EndFunc(string arg1){
    quad q;
    q.op = "endfunc";
    q.arg1 = clean_string(arg1);
    q.code = "endfunc " + clean_string(arg1);
    q.made_from = "end_func";
    return q;
}
quad array_access(string result,string arg1){
    quad q;
    q.op = "*";
    q.arg1 = clean_string(arg1);
    q.result = clean_string(result);
    q.code = clean_string(result) + " = " + q.op + clean_string(arg1);
    q.made_from = "array_access";
    return q;

}
// Function to generate a 3AC param statement
quad pushparam(string value){
    quad q;
    q.op = "param";
    q.arg1 = clean_string(value);
    q.result = "";
    q.code = "param " + clean_string(value);
    q.made_from = "push_param";
    return q;
}
quad popparam(string value){
    quad q;
    q.op = "popparam";
    q.arg1 = clean_string(value);
    q.result = "";
    q.code = "popparam " + clean_string(value);
    q.made_from = "pop_param";
    return q;
}
quad stackincrement(int value){
    quad q;
    q.op = "stackptr";
    if (value > 0){
        q.arg1 = "+" + to_string(value);
    }
    else {
        q.arg1 = to_string(value);
    }
    q.result = "";
    q.code = "stackptr " + clean_string(q.arg1);
    q.made_from = "stack_increment";
    return q;
}
void traverse_AST(TreeNode* root)
{
    if(root == nullptr)
    {
        return;
    }
    cout << root->value << " " << root->original_value << " " << " #children = " << root->children.size() <<endl;
    cout << "childs: " ;
    for(auto child : root->children)
    {
        if(child != nullptr )
            cout << child->value << " " << child->original_value << " " << endl;
        // traverse_AST(child);
    }
    cout << endl;
    for(auto child : root->children)
    {
        traverse_AST(child);
    }

}
void print_quads_global(){
    if(global_quads.size() == 0){
        cout << "No quads to print" << endl;
        return;
    }
    for(int i=0;i<global_quads.size();i++){
        cout << i << ":\t\t" << global_quads[i].op << "\t\t" << global_quads[i].arg1 << "\t\t" << global_quads[i].arg2 << "\t\t" << global_quads[i].result << endl;
    }

}


void print_quads_to_file(const std::string& filename) {
    std::ofstream outputFile(filename); // Open the file for writing
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    if (global_quads.empty()) {
        outputFile << "No quads to print" << std::endl;
        outputFile.close(); // Close the file
        return;
    }

    for (size_t i = 0; i < global_quads.size(); ++i){
        outputFile << i << ":\t\t" <<  global_quads[i].code << std::endl;
    }


    outputFile.close(); // Close the file
}
//to be called after the quads are generated
void updatelineofquads(){
    for (int i=0;i<global_quads.size();i++){
        global_quads[i].ins_line = i;
        if (global_quads[i].made_from == "conditional_jump" || global_quads[i].made_from == "goto"){
            global_quads[i].abs_jump = stoi(global_quads[i].result);
        }
    }
    int ins_count = 1;
    set<int> targets;
    for (auto (&q) : global_quads ){
        if (q.abs_jump){
            targets.insert(q.abs_jump);
        }
        ins_count++;
    }
    for (auto (&q) : global_quads ){
        if (targets.find(q.ins_line)!=targets.end()){
            q.is_target = true;
        }
    }
}

bool checkTypeequivalence(STentry* a, STentry* b) {
    if(a==nullptr || b== nullptr)
        return false; 
    if (a->get_is_list() && b->get_is_list()) {
        if (a->get_type()== STentry_Type :: ste_any || b->get_type()== STentry_Type :: ste_any){
            return true;
         }
         if (a->get_type() == STentry_Type::ste_class_obj && b->get_type() == STentry_Type::ste_class_obj) {
        return a->get_class_obj_name() == b->get_class_obj_name();
        }
        if (a->get_type() == b->get_type()) {
            return true;
        }
        return false;
    }
    if (a->get_type() == STentry_Type :: ste_any || b->get_type() == STentry_Type :: ste_any){
        return true;
    }
    if (a->get_type() == STentry_Type::ste_class_obj && b->get_type() == STentry_Type::ste_class_obj) {
        return a->get_class_obj_name() == b->get_class_obj_name();
        
    }
    if (a->get_type() == b->get_type()) {
        return true;
    }
    else if((a->get_type() == STentry_Type::ste_bool && b->get_type() == STentry_Type::ste_integer) || (a->get_type() == STentry_Type::ste_integer && b->get_type() == STentry_Type::ste_bool))
    {
        return true;
    }

    return false;
}

bool checkarrayTypeequivalence(STentry* a,STentry*b){
    if (b->get_is_list() == true){
        return false;
    }
    if (a->get_type() == STentry_Type::ste_class_obj && b->get_type() == STentry_Type::ste_class_obj) {
        return a->get_class_obj_name() == b->get_class_obj_name();
        
    }
    if (a->get_type() == b->get_type()) {
        return true;
    }
    else if((a->get_type() == STentry_Type::ste_bool && b->get_type() == STentry_Type::ste_integer) || (a->get_type() == STentry_Type::ste_integer && b->get_type() == STentry_Type::ste_bool))
    {
        return true;
    }
    if (a->get_type() == STentry_Type::ste_any || b->get_type() == STentry_Type::ste_any){
        return true;
    }
    return false;
}

void backpatch(int source, int target){

    global_quads[source].result = to_string(target);
    if (global_quads[source].made_from == "goto" ){
        global_quads[source].code = "goto " + to_string(target);
    }
    else if (global_quads[source].made_from == "conditional_jump"){
        global_quads[source].code = global_quads[source].op + " " + global_quads[source].arg1 + " " + global_quads[source].arg2 + " " + to_string(target);
    }
}

void initializeGlobalSymbolTable(){
    //pushing all keywords
    vector<string> keywords = {"False","None","True","and","assert","break","class","continue","def","elif","else","for","from","global","if","in","nonlocal","not","or","raise","return","while"};
    for(int i=0;i<keywords.size();i++){
        STentry* entry = new STentry("KEYWORD ("+keywords[i]+")");
        entry->set_to_print(0);
        if (keywords[i]=="False" || keywords[i]=="True"){
            entry->set_type(STentry_Type::ste_bool);
        }
        else if (keywords[i]=="None"){
            entry->set_type(STentry_Type::ste_none);
        }
        if(entry->get_offset()!=0)
            globalTable->insert(entry->get_name(),entry);
    }
    //pushing all built in functions
    vector<string> built_in_functions = {"print","range","len"};
    STentry* entry = new STentry("NAME (print)");
    entry->set_type(STentry_Type::ste_func_def);
    SymbolTable* table = new SymbolTable(ST_Type::st_function, 0, globalTable, STentry_Type::ste_none,"NAME (print)");
    table->set_function_name("print");
    entry->set_nested_table((void*)table);
    globalTable->insert(entry->get_name(),entry);
    STentry* param = new STentry("print_param");
    param->set_type(STentry_Type::ste_any);
    table->insert(param->get_name(),param);
    table->push_param(param);
    
    entry = new STentry("NAME (range)");
    entry->set_type(STentry_Type::ste_func_def);
    table = new SymbolTable(ST_Type::st_function, 0, globalTable, STentry_Type::ste_none,"NAME (range)");
    table->set_function_name("range@any");
    entry->set_nested_table((void*)table);
    globalTable->insert(entry->get_name(),entry);


    entry = new STentry("NAME (len)");
    entry->set_type(STentry_Type::ste_func_def);
    table = new SymbolTable(ST_Type::st_function, 0, globalTable, STentry_Type::ste_integer,"NAME (len)");
    table->set_function_name("len@any");
    entry->set_nested_table((void*)table);
    globalTable->insert(entry->get_name(),entry);
    param = new STentry("len_param");
    param->set_type(STentry_Type::ste_any);
    param->set_is_list(true);
    table->insert(param->get_name(),param);
    table->push_param(param);

    //special case for __name__
    entry = new STentry("NAME (__name__)",STentry_Type::ste_str,0,NULL);
    globalTable->insert(entry->get_name(),entry);
}

void generate_3ac(TreeNode *root, SymbolTable *table) {
    if (root == nullptr) return;
    if(root->children.size() == 0)
    {
        if (root->value == "NAME (self)"){
            //it means we have called the constructor of an inherited class and we have to pass the object of the class which is self in the current class so nothing just return self
            root->result = new STentry(root->value);
            root->result->set_type(STentry_Type::ste_none);
            return;
        }
        if(root->original_value == "return")
        {
            global_quads.push_back(returnStatement(""));
            return;
        }
        STentry* result = new STentry(root->value);
        if (TypeName(root->value) == STentry_Type::ste_integer){
            result->set_type(STentry_Type::ste_integer);
            result->set_name(root->value);
        }
        else if (TypeName(root->value) == STentry_Type::ste_str){
            string source_str = clean_string(root->value);
            string target_str = newTemp();
            if(source_str[0] == '\"'){
                vector<string> vec = {target_str + "_string:", ".asciz", source_str, "", "ins" };
                ds_vector.push_back(vec);

                global_quads.push_back(assignment_str(target_str, source_str));
                result->set_name(target_str);
            }
            else
                result->set_name(root->value);
            result->set_type(STentry_Type::ste_str);
        }
        else if (TypeName(root->value) == STentry_Type::ste_bool){
            string source_str = clean_string(root->value);
            if(source_str == "True")
                result->set_name("1");
            else
                result->set_name("0");
            result->set_type(STentry_Type::ste_integer);
        }
        else if (TypeName(root->value) == STentry_Type::ste_float){
            result->set_type(STentry_Type::ste_float);
            result->set_name(root->value);
        }
        else {
            STentry* variable = table->recurr_lookup(root->value);
            if (variable == nullptr){
                cout << "error: variable not declared at line no." << root->getlineno() << endl;
                exit(1);
            }
            result->set_type(variable->get_type());
            result->set_name(variable->get_name());
            result->set_class_obj_name(variable->get_class_obj_name());
            result->set_is_list(variable->get_is_list());
            result->set_width(variable->get_width());
            result->set_offset(variable->get_offset());
        }
        root->result = result;
        return;
    }
    if (root->value == "atom"){
        generate_3ac(root->children[1], table);
        root->result = root->children[1]->result;
        return;
    }
    if (root->value == "atom_expr"){
        //get all terminals from here , if second child is '(' then it is a function call
        vector<TreeNode*> values;
        getAllTerminalValue(root, values);
        if (values[1]->original_value == "("){
            //function 
            STentry* function = table->recurr_lookup(values[0]->value);

            if (function->get_type() == STentry_Type::ste_class_def){
                //we have to call the constructor of the class
                
                SymbolTable* classTable = (SymbolTable*)globalTable->lookup(values[0]->value)->get_nested_table();
                
                SymbolTable* init_func_table = (SymbolTable*)(classTable->lookup("NAME (__init__)")->get_nested_table());
                if(init_func_table == nullptr){
                    cout << "Line no:" << root->getlineno() << " error: constructor not defined" << endl;
                    exit(1);
                }
                
                vector<STentry*> params = init_func_table->get_params();
                vector<STentry*> param_values_entries;
                getFuncParams(root->children[1], param_values_entries, table);
                for (int i = param_values_entries.size()-1;i>=0;i--){
                    if (param_values_entries[i] == nullptr){
                        cout << "Line no:" << root->getlineno() << " error: variable not declared" << endl;
                        exit(1);
                    }
                    if (checkTypeequivalence(params[i],param_values_entries[i]) == false){
                        cout << "Line no:" << root->getlineno() << " error: type mismatch6" << endl;
                        exit(1);
                    }
                    global_quads.push_back(pushparam(param_values_entries[i]->get_name()));
                global_quads.push_back(stackincrement(size_of_type(param_values_entries[i])));
                }
                
                global_quads.push_back(pushparam(ctor_obj));
                global_quads.push_back(stackincrement(classTable->get_size()));
                global_quads.push_back(functionCall(init_func_table->get_function_name(),params.size()));
                global_quads.push_back(returnVal(""));
                return;
            }

            if (function == nullptr){
                cout << "Line no:" << root->getlineno() << " error: function not declared" << endl;
                exit(1);
            }
            if (function->get_type() != STentry_Type::ste_func_def){
                cout << "Line no:" << root->getlineno()  << " error: not a function" << endl;
                exit(1);
            }
            
            vector<STentry*> parameters = ((SymbolTable*)(function->get_nested_table()))->get_params() ;
            vector<STentry*> param_values_entries;
            getFuncParams(root->children[1], param_values_entries, table);
            if (function->get_name() == "NAME (len)"){
                //its the len function we know it can have only one parameter.
                if (param_values_entries.size() != 1){
                    cout << "Line no:" << root->getlineno() << " error: len function can have only one parameter" << endl;
                    exit(1);
                }
                if (param_values_entries[0] == nullptr){
                    cout << "Line no:" << root->getlineno() << " error: variable not declared" << endl;
                    exit(1);
                }
                if (param_values_entries[0]->get_is_list() == false){
                    cout << "Line no:" << root->getlineno() << " error: len function can only be called on a list" << endl;
                    exit(1);
                }
                string temp = newTemp();
                int size = param_values_entries[0]->get_width()/(sizeofdatatype(param_values_entries[0]->get_type()));
                global_quads.push_back(assignment(temp,to_string(size)));
                root->result = new STentry(temp);
                root->result->set_type(STentry_Type::ste_integer);
                return;
            }

            for (int i=0;i<parameters.size();i++){
                if (param_values_entries[i] == nullptr){
                    cout << "Line no:" << root->getlineno() << " error: variable not declared" << endl;
                    exit(1);
                }
                if (checkTypeequivalence(parameters[i],param_values_entries[i]) == false){
                    cout << "Line no:" << root->getlineno() << " error: type mismatch7" << endl;
                    exit(1);
                }
            }

            for (int i = param_values_entries.size()-1; i >= 0; i--){
                global_quads.push_back(pushparam(param_values_entries[i]->get_name()));
                global_quads.push_back(stackincrement(size_of_type(param_values_entries[i])));
            }

            string arg1 = ((SymbolTable*)(function->get_nested_table()))->get_function_name();
            if(arg1 == "print" && param_values_entries[0]->get_type() == STentry_Type::ste_str && (!(param_values_entries[0]->get_is_list())))
            {
                arg1 = arg1 + "str";
            }
            global_quads.push_back(functionCall(arg1, param_values_entries.size()));
            STentry* result = new STentry(newTemp());
            result->set_type(((SymbolTable*)(function->get_nested_table()))->get_return_type());
            if (result->get_type() == STentry_Type::ste_none){
                result->set_name("");
            }
            global_quads.push_back(returnVal(result->get_name()));
            root->result = result;
        }
        
        // if second child is '.' then it is a class object
        else if (values[1]->original_value == "." && values.size() >3 && values[3]->original_value == "(" ){
            // this is a class object function call but this should be a class function call it should be a class name.function name
            //class object
            //I would have to check if the values[0] is a class object or a class name
            if (table->recurr_lookup(values[0]->value) == nullptr){
                cout << "Line no:" << root->getlineno() << " error: class not declared" << endl;
                exit(1);
            }
            if (find(class_names.begin(),class_names.end(),values[0]->value)!= class_names.end()){
                //means it is a class name
                //we can call any function of the class name
                SymbolTable* class_name = (SymbolTable*)(globalTable->lookup(values[0]->value)->get_nested_table());
                STentry* function = class_name->recurr_lookup(values[2]->value);
                if (function == nullptr){
                    cout << "Line no:" << root->getlineno() << " error: function not declared" << endl;
                    exit(1);
                }
                if (function->get_type() != STentry_Type::ste_func_def){
                    cout << "Line no:" << root->getlineno() << " error: not a function" << endl;
                    exit(1);
                }
                vector<STentry*> parameters = ((SymbolTable*)(function->get_nested_table()))->get_params() ;
                vector<STentry*> param_values_entries;
                getFuncParams(root->children[1]->children[1], param_values_entries, table);
                if ((values[4] != nullptr) && (param_values_entries[0]->get_name() == "NAME (self)")){
                    // this is the case when we have to call the constructor of the class
                    vector<STentry*> params = ((SymbolTable*)(function->get_nested_table()))->get_params();
                    for (int i = param_values_entries.size()-1;i>=1;i--){
                        if (param_values_entries[i] == nullptr){
                            cout << "Line no:" << root->getlineno() << " error: variable not declared" << endl;
                            exit(1);
                        }
                        if (checkTypeequivalence(params[i-1],param_values_entries[i]) == false){
                            cout << "Line no:" << root->getlineno() << " error: type mismatch8" << endl;
                            exit(1);
                        }
                        global_quads.push_back(pushparam(param_values_entries[i]->get_name()));
                        global_quads.push_back(stackincrement(size_of_type(param_values_entries[i])));
                    }

                    global_quads.push_back(pushparam(param_values_entries[0]->get_name()));
                    global_quads.push_back(stackincrement(class_name->get_size()));
                    global_quads.push_back(functionCall(((SymbolTable*)(function->get_nested_table()))->get_function_name(),params.size()));
                    global_quads.push_back(returnVal(""));
                    return;

                }
                //means it is a function of the class 

                for (int i =  parameters.size()-1;i>=0; i--){
                if (param_values_entries[i] == nullptr){
                    cout << "Line no:" << root->getlineno() << " error: variable not declared" << endl;
                    exit(1);
                }
                if (checkTypeequivalence(parameters[i],param_values_entries[i]) == false){
                    cout << "Line no:" << root->getlineno() << " error: type mismatch9" << endl;
                    exit(1);
                }
                global_quads.push_back(pushparam(param_values_entries[i]->get_name()));
                global_quads.push_back(stackincrement(size_of_type(param_values_entries[i])));
            }
             global_quads.push_back(functionCall(((SymbolTable*)(function->get_nested_table()))->get_function_name(), (param_values_entries.size())));   
            
             STentry* result = new STentry(newTemp());
            result->set_type(((SymbolTable*)(function->get_nested_table()))->get_return_type());
            if (result->get_type() == STentry_Type::ste_none){
                result->set_name("");
            }
            global_quads.push_back(returnVal(result->get_name())); 
            root->result = result;
            return;
            }
            //means it is a method of the class object
            STentry* class_obj = table->recurr_lookup(values[0]->value);
            SymbolTable* class_name = (SymbolTable*)(globalTable->lookup(class_obj->get_class_obj_name())->get_nested_table());
            if (class_obj == nullptr){
                cout << "Line no:" << root->getlineno() <<" " << "error: class not declared" << endl;
                exit(1);
            }
            if(class_obj->get_type() != STentry_Type::ste_class_obj){
                cout << "Line no:" << root->getlineno() <<" " << "error: not a class object" << endl;
                exit(1);
            }
            STentry* function =class_name->recurr_lookup(values[2]->value);
            if (function == nullptr){
                cout << "Line no:" << root->getlineno() <<" " << "error: function not declared" << endl;
                exit(1);
            }
            if (function->get_type() != STentry_Type::ste_func_def){
                cout << "Line no:" << root->getlineno() <<" " << "error: not a function" << endl;
                exit(1);
            }
            vector<STentry*> parameters = ((SymbolTable*)(function->get_nested_table()))->get_params() ;
            
            vector<STentry*> param_values_entries;
            getFuncParams(root->children[1]->children[1], param_values_entries, table);
            for (int i =  parameters.size()-1;i>=0; i--){
                if (param_values_entries[i] == nullptr){
                    cout << "Line no:" << root->getlineno() << " error: variable not declared" << endl;
                    exit(1);
                }
                if (checkTypeequivalence(parameters[i],param_values_entries[i]) == false){
                    cout << "Line no:" << root->getlineno() << " error: type mismatch10" << endl;
                    exit(1);
                }
                global_quads.push_back(pushparam(param_values_entries[i]->get_name()));
                global_quads.push_back(stackincrement(size_of_type(param_values_entries[i])));
            }
            global_quads.push_back(pushparam(values[0]->value));
            global_quads.push_back(functionCall(((SymbolTable*)(function->get_nested_table()))->get_function_name(), (param_values_entries.size())));   
            
             STentry* result = new STentry(newTemp());
            result->set_type(((SymbolTable*)(function->get_nested_table()))->get_return_type());
            if (result->get_type() == STentry_Type::ste_none){
                result->set_name("");
            }
            global_quads.push_back(returnVal(result->get_name())); 
            root->result = result;
            return;
        }

        //else if second child is '[' then it is an array access
        else if(values[1]->original_value == "." && values.size() > 3 && values[3]->original_value == "[")
        {
            // array access
            generate_3ac(root->children[1]->children[1]->children[1], table);
            STentry* child_result = root->children[1]->children[1]->children[1]->result;
            if(child_result == nullptr)
            {
                cout << "Line no:" << root->getlineno() <<" " << "error: index not declared" << endl;
                exit(1);
            }
            // if child_result is not of type integer, throw error
            else if(child_result->get_type() != STentry_Type::ste_integer)
            {
                cout << "Line no:" << root->getlineno() <<" " << "error: index is not of type integer" << endl;
                exit(1);
            }
            // lookup for the class object
            STentry* entry;
            if(values[0]->original_value == "self")
            {
                // find the current class object symbol table
                SymbolTable* class_table = table->get_parent();
                entry = class_table->recurr_lookup_in_class(values[2]->value);
                if(entry == nullptr)
                {
                    cout << "Line no:" << root->getlineno() <<" " << "error: class object not declared" << endl;
                    exit(1);
                }
            }
            else 
            {
                // find the symboltable corresponding to values[0]
                if(table->lookup(values[0]->value) == NULL){
                    cout << "Couldnt find " << values[0]->value << " in " << table->get_name() << endl;
                    exit(1);
                }
                string class_table_name = (table->lookup(values[0]->value))->get_class_obj_name();
                SymbolTable* class_table = (SymbolTable*)((globalTable->lookup(class_table_name))->get_nested_table());
                entry = class_table->recurr_lookup_in_class(values[2]->value);
                //cout << "--entry is " << entry->get_name() << endl;
                
                if(entry == nullptr)
                {
                    cout << "Line no:" << root->getlineno() <<" " << "error: class object not declared" << endl;
                    exit(1);
                }
            }
            // check type equivalence of child_result and entry
            if(entry->get_is_list() == false)
            {
                cout << "Line no:" << root->getlineno() <<" " << "error: not an array" << endl;
                exit(1);
            }
            
            
            // string offset = to_string(stoi(clean_string(child_result->get_name())) * size_of_type(entry));
            string newstr = newTemp();
            global_quads.push_back(binaryOperation("+", values[0]->original_value, to_string(entry->get_offset()), newstr));

            string str1 = newTemp();
            global_quads.push_back(binaryOperation("*", clean_string(child_result->get_name()), to_string(size_of_type(entry)) , str1));
            global_quads.push_back(binaryOperation("+", newstr, str1, str1));
            STentry* result = new STentry("*"+str1);
            result->set_type(entry->get_type());
            result->set_class_obj_name(entry->get_class_obj_name());
            root->result = result;
        }
        else if(values[1]->original_value == "." )
        {
            STentry* entry;
            if(values[0]->original_value == "self")
            {
                // find the current class object symbol table
                SymbolTable* class_table = table;
                if (table->get_type()== ST_Type::st_function)
                {
                     class_table = table->get_parent();
                }
                entry = class_table->recurr_lookup_in_class(values[2]->value);
                if(entry == nullptr)
                {
                    cout << "Line no:" << root->getlineno() <<" " << "error: class object attribute not declared" << endl;
                    exit(1);
                }
            }
            else 
            {
                // find the symboltable corresponding to values[0]
                STentry* class_obj = table->recurr_lookup(values[0]->value);
                SymbolTable* class_table = (SymbolTable*)(globalTable->lookup(class_obj->get_class_obj_name())->get_nested_table());
                entry = class_table->recurr_lookup_in_class(values[2]->value);
                if(entry == nullptr)
                {
                    cout << "Line no:" << root->getlineno() <<" " << "error: class object ATtribute not declared" << endl;
                    exit(1);
                }
            }
            string newstr = newTemp();
            global_quads.push_back(binaryOperation("+", values[0]->original_value, to_string(entry->get_offset()), newstr));
            newstr = "*" + newstr;
            STentry* result = new STentry(newstr);
            result->set_type(entry->get_type());
            result->set_is_list(entry->get_is_list());
            result->set_width(entry->get_width());
            result->set_offset(entry->get_offset());
            result->set_class_obj_name(entry->get_class_obj_name());
            root->result = result;

        }

        else if (values[1]->original_value == "["){
            STentry* variable = table->recurr_lookup(root->children[0]->value);
            if(variable == nullptr)
            {
                cout << "Line no:" << root->getlineno() <<" " << "error: variable not declared" << endl;
                exit(1);
            }
            else if(variable->get_is_list() == false)
            {
                cout << "Line no:" << root->getlineno() <<" " << "error: not an array" << endl;
                exit(1);
            }
            
            generate_3ac(root->children[1]->children[1], table);
            STentry* child_result = root->children[1]->children[1]->result;
            if(child_result == nullptr)
            {
                cout << "Line no:" << root->getlineno() <<" " << "error: index not declared" << endl;
                exit(1);
            }
            // if child_result is not of type integer, throw error
            else if(child_result->get_type() != STentry_Type::ste_integer)
            {
                cout << "Line no:" << root->getlineno() <<" " << "error: index is not of type integer" << endl;
                exit(1);
            }
            
            string str1 = newTemp();
            global_quads.push_back(binaryOperation("*", clean_string(child_result->get_name()), to_string(size_of_type(variable)) , str1));
            global_quads.push_back(binaryOperation("+", clean_string(variable->get_name()), str1, str1));
            STentry* result = new STentry("*"+str1);
            result->set_type(variable->get_type());
            result->set_class_obj_name(variable->get_class_obj_name());
            root->result = result;
        }
    }
    else if (root->type == "binary_op") 
    {   
        if (root->children.size() <= 1) 
        {
            cout << "Line no:" << root->getlineno() <<" " << "error: binary operator with less than two operands" << endl;
            exit(1);
        } 

        generate_3ac(root->children[0], table);
        generate_3ac(root->children[1], table);

        if(checkTypeequivalence(root->children[0]->result, root->children[1]->result) == false)
        {
            cout << "Line no:" << root->getlineno() <<" " << "error: type mismatch1" << endl;
            exit(1);
        }
        else 
        {   
            
            // concatenate quads of children
            // generate quad for the binary operation
            STentry* result = new STentry(newTemp());
            STentry* arg1 = root->children[0]->result;
            STentry* arg2 = root->children[1]->result;
            global_quads.push_back(binaryOperation(root->value, clean_string(arg1->get_name()), clean_string(arg2->get_name()), clean_string(result->get_name())));
            result->set_type(arg1->get_type());
            result->set_is_list(arg1->get_is_list());
            result->set_class_obj_name(arg1->get_class_obj_name());
            root->result = result;
        }
    }
    else if(root->original_value == "factor" && root->children[0]->type == "unary_op") // tbd
    {
        if(root->children.size() !=2){
            cout << "Line no:" << root->getlineno() <<" " << "error: unary operator with no operand" << endl;
            exit(1);
        }
        generate_3ac(root->children[1], table);
        STentry* result = new STentry(newTemp());
        STentry* arg1 = root->children[1]->result;
        string unary_oper = "u"+root->children[0]->original_value;
        global_quads.push_back(unaryOperation(unary_oper, clean_string(arg1->get_name()), clean_string(result->get_name())));
        result->set_type(arg1->get_type());
        result->set_is_list(arg1->get_is_list());
        result->set_class_obj_name(arg1->get_class_obj_name());
        root->result = result;

    
    }
    else if(root->original_value == "not_test")
    {
        if(root->children.size() != 2)
        {
            cout << "Line no:" << root->getlineno() <<" " << "error: not operator with no operand" << endl;
            exit(1);
        }
        generate_3ac(root->children[1], table);
        STentry* result = new STentry(newTemp());
        STentry* arg1 = root->children[1]->result;
        string unary_oper = "u"+root->children[0]->original_value;

        global_quads.push_back(unaryOperation(unary_oper, clean_string(arg1->get_name()), clean_string(result->get_name())));
        result->set_type(arg1->get_type());
        result->set_is_list(arg1->get_is_list());
        result->set_class_obj_name(arg1->get_class_obj_name());
        root->result = result;
    }

    else if (root->type == "augassign")
    {   
        generate_3ac(root->children[0], table);
        generate_3ac(root->children[1], table);
        if (checkTypeequivalence(root->children[0]->result, root->children[1]->result) == false)
        {
            cout << "Line no:" << root->getlineno() <<" " << "error: type mismatch2" << endl;
            exit(1);
        }
        if (root->children.size() <= 1) 
        {
            cout << "Line no:" << root->getlineno() <<" " << "error: binary operator with less than two operands" << endl;
            exit(1);
        } 
        else 
        {
            //augassign 
            string arg1 = clean_string(root->children[0]->result->get_name());
            string arg2 = clean_string(root->children[1]->result->get_name());

            global_quads.push_back(binaryOperation(root->value, arg1, arg2, arg1));
            root->result = root->children[0]->result;
        }
    }
    else if(root->type == "assign")
    {  
        if (root->children[0]->original_value == ":"){
            //it is a declaration if i
            // declaration has been handled in parser while making symbol table
            STentry* variable; 
            if(root->children[0]->children[0]->children.size() ==0)
            {
                variable = table->lookup(root->children[0]->children[0]->value);
            }
            else if(root->children[0]->children[0]->children[0]->original_value == "self") // current table would be the table of the method init so we switch to the parent table
            {
                variable = table->get_parent()->lookup(root->children[0]->children[0]->children[1]->children[1]->value);
            }
            if (variable->get_is_list() == true){
                // it is a list

                vector<STentry*> values; // to be replaced by values once older implementation is useless
                getFuncParams(root->children[1], values, table);
                int size = values.size();

                variable->set_width(size*sizeofdatatype(variable->get_type()));
                //assuming that the values are int, float ,string , bool
                string temp = newTemp();

                if (root->children[0]->children[0]->value != "atom_expr"){


                    global_quads.push_back(pushparam(to_string(variable->get_width())));
                    global_quads.push_back(functionCall("memalloc", 1));
                    global_quads.push_back(returnVal(temp));
                    
                    global_quads.push_back(assignment(root->children[0]->children[0]->original_value, temp));
                }
                else {
                    //it is a class object of type self.x
                    // we are currently in the symbol table of the function __init__.
                    
                    //if it is self.x then we need to get the class symbol table and then get the offset of x
                    //then we need to assign the value to the offset of the class object
                    SymbolTable* class_table = table->get_parent();
                    STentry* class_var = class_table->recurr_lookup_in_class(root->children[0]->children[0]->children[1]->children[1]->value);
                    if (class_var == nullptr){
                        cout << "Line no:" << root->getlineno() <<" " << "attribute not found" << endl;
                        exit(1);
                    }
                    global_quads.push_back(binaryOperation("+",clean_string(root->children[0]->children[0]->children[0]->value),to_string(class_var->get_offset()), temp));
                }
                //this gives the base address of the memory allocated for the array
                //now we need to assign the values to the array
                for (int i = 0; i < size; i++){

                    if(checkarrayTypeequivalence(variable, values[i]) == false)
                    {
                        cout << "Line no:" << root->getlineno() <<" " << "error: type mismatch11" << endl;
                        exit(1);
                    }
                    global_quads.push_back(assignment("*"+temp, values[i]->get_name()));
                    global_quads.push_back(binaryOperation("+", temp, to_string(sizeofdatatype(variable->get_type())), temp));
                }
                values.clear();
                STentry* result = new STentry(variable->get_name());
                root->result = result;
            }
            else if (root->children[0]->children[0]->children[0]->original_value == "self")
            {
                // now in the variable I have the attribute to be assigned
                //basically self.x : int = 5
                generate_3ac(root->children[1], table);
                if (variable == nullptr){
                    cout << "Line: " << root->getlineno() << " error: class attribute " << variable->get_name() <<" not declared" << endl;
                    exit(1);
                }
                if (checkTypeequivalence(variable, root->children[1]->result) == false){
                    cout << "Line: " << root->getlineno() << " error: type mismatch4" << endl;
                    exit(1);
                }
                string temp = newTemp();
                global_quads.push_back(binaryOperation("+",clean_string(root->children[0]->children[0]->children[0]->value),to_string(variable->get_offset()), temp));
                global_quads.push_back(assignment("*"+temp, root->children[1]->result->get_name()));
                //after this we need not send the result to the parent
            }
            else if (variable->get_class_obj_name() != "")
            {
                // class object declaration
                SymbolTable* class_table = (SymbolTable*)(globalTable->lookup(variable->get_class_obj_name())->get_nested_table());
                //first i need to allocate memory for the class object
                // and then call the constructor which will initialize the values

                global_quads.push_back(pushparam(to_string(class_table->get_size())));
                global_quads.push_back(functionCall("memalloc", 1));

                ctor_obj = clean_string(variable->get_name());
                global_quads.push_back(returnVal(ctor_obj));
                generate_3ac(root->children[1], table);                
            }

            else {
                // basic data type hai ye toh
                generate_3ac(root->children[1], table);
                string source_str = clean_string(root->children[1]->result->get_name());
                string target_str = clean_string(variable->get_name());

                if(root->children[1]->result->get_type() == STentry_Type::ste_str)
                {
                    if(source_str[0] == '\"') // raw string
                    {
                        // push this string into the data segment
                        vector<string> vec = {target_str + "_string:", ".asciz", source_str, "", "ins" };
                        ds_vector.push_back(vec);

                        global_quads.push_back(assignment_str(target_str, source_str));
                    }
                    else
                    {
                        global_quads.push_back(assignment(target_str, source_str));
                    }
                }
                else
                    global_quads.push_back(assignment(target_str, source_str));
            }
        }
        else {
            generate_3ac(root->children[1], table);
            //it is a normal assignment without declaration
            //it can be a class object or a normal variable
            //if it is a class object then we need to get the class symbol table and then get the offset of x
            if (root->children[0]->value != "atom_expr"){
                //it is a normal variable
                STentry* variable = table->recurr_lookup(root->children[0]->value);
                if (variable == nullptr){
                    cout << "Line:" << root->getlineno()  << " the variable " << clean_string(root->children[0]->value) <<  " is not declared but is used" << endl;
                    exit(1);
                }
                if ( checkTypeequivalence(variable, root->children[1]->result) == false){
                    cout << "Line no:" << root->getlineno() <<" " << "error: type mismatch5" << endl;
                    exit(1);
                }
                global_quads.push_back(assignment(clean_string(variable->get_name()), root->children[1]->result->get_name()));
                STentry* result = new STentry(variable->get_name());
                root->result = result;

            }
            else {
                generate_3ac(root->children[0], table);

                STentry* result1 = root->children[0]->result;
                STentry* result2 = root->children[1]->result;
                global_quads.push_back(assignment(clean_string(result1->get_name()), clean_string(result2->get_name())));
                root->result = result1;
                root->result->set_type(result1->get_type());
                root->result->set_is_list(result1->get_is_list());
                root->result->set_class_obj_name(result1->get_class_obj_name());    
            }
        }
    }
    
    else if(root->type == "relop")
    {   
        if (root->children.size() <= 1) 
        {
            cout << "Line no:" << root->getlineno() <<" " << "error: assignment operator with less than two operands" << endl;
            exit(1);
        } 
        generate_3ac(root->children[0], table);
        generate_3ac(root->children[1], table);
        
        string result = newTemp();
        string arg1 = clean_string(root->children[0]->result->get_name());
        string arg2 = clean_string(root->children[1]->result->get_name());

        if(root->original_value == "==" && root->children[0]->result->get_type() == STentry_Type::ste_str && root->children[1]->result->get_type() == STentry_Type::ste_str)
        {
            global_quads.push_back(pushparam(arg1));
            global_quads.push_back(pushparam(arg2));
            global_quads.push_back(functionCall("mystrcmp", 2));
            global_quads.push_back(returnVal(result));
        }
        else if(root->original_value == "!=" && root->children[0]->result->get_type() == STentry_Type::ste_str && root->children[1]->result->get_type() == STentry_Type::ste_str)
        {
            global_quads.push_back(pushparam(arg1));
            global_quads.push_back(pushparam(arg2));
            global_quads.push_back(functionCall("mystrcmpN", 2));
            global_quads.push_back(returnVal(result));
        }
        else
        {
            global_quads.push_back(binaryOperation(root->value, arg1, arg2, result));
        }
        root->result = new STentry(result);
        root->result->set_type(root->children[0]->result->get_type());
    }
    else if(root->type == "logical_op")
    {
        if (root->children.size() <= 1) 
        {
            // throw error: binary operator with only one operand
            cout << "Line no:" << root->getlineno() <<" " << "error: assignment operator with less than two operands" << endl;
            exit(1);
        }

        generate_3ac(root->children[0], table);
        generate_3ac(root->children[1], table);

        string arg1 = clean_string(root->children[0]->result->get_name());
        string arg2 = clean_string(root->children[1]->result->get_name());

        string result = newTemp();

        global_quads.push_back(binaryOperation(root->value, arg1, arg2, result));
        root->result = new STentry(result);
        root->result->set_type(STentry_Type::ste_integer);

    }
    else if(root->value == "if_stmt")
    {
        generate_3ac(root->children[1], table);
        string fall = to_string(global_quads.size()+2);
        global_quads.push_back(conditionalJump("if", clean_string(root->children[1]->result->get_name()), "goto", fall));
        global_quads.push_back(unconditionalJump(""));
        prev_label_if_else.push_back(stoi(fall)-1);
        end_labels_if_else.push_back(vector<int>());
        if(root->children.size() == 4)
        {
            (end_labels_if_else[end_labels_if_else.size()-1]).push_back(global_quads.size()-1);
        }
        generate_3ac(root->children[3], table);

        if(root->children.size() > 4)
        {
            generate_3ac(root->children[4], table);
        }
        if(root->children.size() > 5)
        {
            generate_3ac(root->children[5], table);
        }
        string endLabel = to_string(global_quads.size());
        for(int i=0; i<end_labels_if_else[end_labels_if_else.size()-1].size(); i++)
        {
            backpatch(end_labels_if_else[end_labels_if_else.size()-1][i], stoi(endLabel));
        }
        end_labels_if_else.pop_back();
        prev_label_if_else.pop_back();
    }
    else if(root->value == "if_stmt1")
    {
        if(root->children[0]->value == "if_stmt1")
        {
            generate_3ac(root->children[0], table);
            global_quads.push_back(unconditionalJump(""));
            end_labels_if_else[end_labels_if_else.size()-1].push_back(global_quads.size()-1);

            backpatch(prev_label_if_else[prev_label_if_else.size()-1], global_quads.size());
            generate_3ac(root->children[2], table);
            string fall = to_string(global_quads.size()+2);
            global_quads.push_back(conditionalJump("if", clean_string(root->children[2]->result->get_name()), "goto", fall));
            global_quads.push_back(unconditionalJump(""));
            prev_label_if_else[prev_label_if_else.size()-1] = stoi(fall)-1;
            generate_3ac(root->children[4], table);
        }
        else
        {
            global_quads.push_back(unconditionalJump(""));
            end_labels_if_else[end_labels_if_else.size()-1].push_back(global_quads.size()-1);

            backpatch(prev_label_if_else[prev_label_if_else.size()-1], global_quads.size());
            generate_3ac(root->children[1], table);
            string fall = to_string(global_quads.size()+2);
            global_quads.push_back(conditionalJump("if", clean_string(root->children[1]->result->get_name()), "goto", fall));
            global_quads.push_back(unconditionalJump(""));
            prev_label_if_else[prev_label_if_else.size()-1] = stoi(fall)-1;
            generate_3ac(root->children[3], table);
        }
    }
    else if(root->value == "if_stmt2")
    {
        global_quads.push_back(unconditionalJump(""));
        end_labels_if_else[end_labels_if_else.size()-1].push_back(global_quads.size()-1);

        backpatch(prev_label_if_else[prev_label_if_else.size()-1], global_quads.size());
        generate_3ac(root->children[2], table);
    }
    else if(root->value == "while_stmt")
    {
        string begin = to_string(global_quads.size());
        generate_3ac(root->children[1], table);
        string fall = to_string(global_quads.size()+2);
        global_quads.push_back(conditionalJump("if", root->children[1]->result->get_name(), "goto", fall));
        global_quads.push_back(unconditionalJump(""));

        prev_label_while.push_back(stoi(fall)-1);

        generate_3ac(root->children[3], table);
        global_quads.push_back(unconditionalJump(begin));
        string prevLabel = to_string(global_quads.size());

        backpatch(prev_label_while[prev_label_while.size()-1], stoi(prevLabel));

        prev_label_while.pop_back();
    }
    else if(root->value == "for_stmt"){
        vector<STentry*> values;
        getFuncParams(root->children[3]->children[1], values, table);

        if(values.size() > 1){
            string end= values[1]->get_name(); 
            string start = root->children[1]->original_value;
            global_quads.push_back(assignment(start, values[0]->get_name()));
            string begin = to_string(global_quads.size());
            string temp1 = newTemp();
            global_quads.push_back(binaryOperation("<", start, end, temp1));
            string fall = to_string(global_quads.size()+2);
            global_quads.push_back(conditionalJump("if", temp1, "goto", fall));
            global_quads.push_back(unconditionalJump(""));

            prev_label_for.push_back(stoi(fall) -1);

            generate_3ac(root->children[5], table); 
            string temp2 = newTemp();
            global_quads.push_back(binaryOperation("+", start, "1", temp2));
            global_quads.push_back(assignment(start, temp2));
            global_quads.push_back(unconditionalJump(begin));

            string prevLabel = to_string(global_quads.size());
            backpatch(prev_label_for[prev_label_for.size()-1], stoi(prevLabel));

            prev_label_for.pop_back();

        }
        else {
            
            string start = root->children[1]->original_value;
            string end = newTemp();
            global_quads.push_back(assignment(start, to_string(0)));
            global_quads.push_back(assignment(end, values[0]->get_name()));
            string begin = to_string(global_quads.size());
            string temp1 = newTemp();
            global_quads.push_back(binaryOperation("<", start, end, temp1));
            string fall = to_string(global_quads.size()+2);
            global_quads.push_back(conditionalJump("if", temp1, "goto", to_string(global_quads.size()+2)));
            global_quads.push_back(unconditionalJump(""));

            prev_label_for.push_back(stoi(fall) -1);

            generate_3ac(root->children[5], table); 
            string temp2 = newTemp();
            global_quads.push_back(binaryOperation("+", start, "1", temp2));
            global_quads.push_back(assignment(start, temp2));
            global_quads.push_back(unconditionalJump(begin));

            string prevLabel = to_string(global_quads.size());
            backpatch(prev_label_for[prev_label_for.size()-1], stoi(prevLabel));

            prev_label_for.pop_back();
        }

    }
    
    else if(root->value == "funcdef"){
        
        STentry* function = table->lookup(root->children[1]->value);
        if(function == nullptr){
            cout << "Line no:" << root->getlineno() <<" " << "error: function not declared" << endl;
            exit(1);
        }
        global_quads.push_back(BeginFunc(((SymbolTable*)(function->get_nested_table()))->get_function_name()));
        vector<string> params;
        vector<TreeNode*> params1;
        vector<TreeNode*> values;
        getAllTerminalValue(root->children[2], values);
        if(values.size() > 2){
        if (values[1]->original_value == "self"){
            SymbolTable* classTable = ((SymbolTable*)(function->get_nested_table()))->get_parent();
            STentry* class_obj = globalTable->lookup(classTable->get_name());
            values[1]->result = class_obj;
            params.push_back(values[1]->value);
            params1.push_back(values[1]);
        }
        else {
            params.push_back(values[1]->value);
            params1.push_back(values[1]);
            generate_3ac(values[1], (SymbolTable*)(function->get_nested_table()));
        }
        }
        for(int i=2; i<values.size()-1; i++){
            if(values[i]->original_value == ","){
                params.push_back(values[i+1]->value);
                params1.push_back(values[i+1]);
                generate_3ac(values[i+1], (SymbolTable*)(function->get_nested_table()));
            }

        }
        for(int i=0;i<params.size();i++){
            global_quads.push_back(popparam(params[i]));
            global_quads.push_back(stackincrement(-1*size_of_type(params1[i]->result)));
        }

        if(root->children[3]->children[0]->original_value == "->") // if there are parameters
        {
            generate_3ac(root->children[3]->children[3], (SymbolTable*)(function->get_nested_table())); 
        }
        else  // function with no return type
        {
            generate_3ac(root->children[3]->children[1], (SymbolTable*)(function->get_nested_table()));

        }
        global_quads.push_back(EndFunc( ((SymbolTable*)(function->get_nested_table()))->get_function_name()));
        
    }
    else if(root->value == "return_stmt"){
        vector<TreeNode*> values;
        getAllTerminalValue(root, values);
        if(values.size() == 1){
            global_quads.push_back(returnStatement(""));
        }
        else {
            generate_3ac(root->children[1], table);
            global_quads.push_back(returnStatement(clean_string(root->children[1]->result->get_name())));

        }
    }
    else if(root->value == "classdef")
    {
        STentry* class_entry = table->lookup(root->children[1]->value);
        if(class_entry == nullptr){
            cout << "Line no:" << root->getlineno() <<" " << "error: class not declared" << endl;
            exit(1);
        }
        SymbolTable* class_table = (SymbolTable*)(class_entry->get_nested_table());
        if(root->children[2]->original_value == ":") // without inheretence
        {
            generate_3ac(root->children[3], class_table);
        }
        else    // with single inheretence (multiple inheretence is not supported!)
        {
            generate_3ac(root->children[4], class_table);
        }
    }
    else if(root->original_value == ":"){
        //do nothing. This is a declaration
    }
    else 
    {
        for (TreeNode* child : root->children) {
            generate_3ac(child, table);
        }
    
    }
    return ;
}
