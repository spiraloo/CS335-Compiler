#include<iostream>
#include<unordered_map>
#include<string>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

vector<string> class_names;
string clean_string_ST(string value)
{
    if(value == "")
        return value;
    int i = 0;
    while (value[i] != '(' && i < value.size()){
        i++;
    }
    i++;

    string original_value = "";
    
    while(i < ((value.size()) -1)){
        original_value += value[i];
        i++;
    }

    if(original_value == "")
    {
        original_value = value;
    }


    return original_value;
}
class Value {
    public:
        int intValue;
        bool boolValue;
        float floatValue;
        string strValue;
};
enum class ST_Type {
    st_top,
    st_function,
    st_class,
    st_block
};

enum class STentry_Type {
    ste_integer,
    ste_float,
    ste_str,
    ste_bool,
    ste_func_def,
    ste_class_def,
    ste_class_obj,
    ste_any,
    ste_none,
};
int sizeofdatatype(STentry_Type type){
    switch(type){
        case STentry_Type::ste_integer:
            return 8;
        case STentry_Type::ste_float:
            return 4;
        case STentry_Type::ste_str:
            return 8;
        case STentry_Type::ste_bool:
            return 8;
        case STentry_Type::ste_class_obj:
            return 8;
    }
}
string type_to_string(STentry_Type type){
    switch(type){
        case STentry_Type::ste_integer:
            return "int";
        case STentry_Type::ste_float:
            return "float";
        case STentry_Type::ste_str:
            return "str";
        case STentry_Type::ste_bool:
            return "bool";
        case STentry_Type::ste_func_def:
            return "func_def";
        case STentry_Type::ste_class_def:
            return "class_def";
        case STentry_Type::ste_class_obj:
            return "class_obj";
        case STentry_Type::ste_none:
            return "none";
        case STentry_Type::ste_any:
            return "any";
    }
}
// class SymbolTable;
class STentry{
private:
    string name;
    bool init;
    STentry_Type type;
    bool is_list;
    // STentry_Type list_type;
    string class_obj_name; //which class does this object belong to
    int lineno;
    Value value;
    void* nested_table;
    int offset;
    int width;
    int to_print =1;

public:
    STentry(string name, STentry_Type type, int lineno, void* nested_table) {
        this->name = name;
        this->type = type;
        this->lineno = lineno;
        this->nested_table = nested_table;
        this->init = false;
        this->offset = 0;
    }
    STentry(string name){
        this->name = name;
    }
    void set_to_print(int value){
        this->to_print = value;
    }
    void set_init() {
        this->init = true;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    void set_offset(int offset) {
        this->offset = offset;
    }
    void set_width(int width) {
        this->width = width;
    }
    void set_type(STentry_Type type) {
        this->type = type;
    }
    void set_class_obj_name(string name) {
        this->class_obj_name = name;
    }
    void set_is_list(bool value) {
        this->is_list = value;
    }
    void set_nested_table(void* nested_table) {
        this->nested_table = nested_table;
    }
    void set_value(string value) {
        switch(type){
            case STentry_Type::ste_integer:
                this->value.intValue = stoi(value);
                break;
            case STentry_Type::ste_float:
                this->value.floatValue = (double)(stof(value));
                break;
            case STentry_Type::ste_str:
                this->value.strValue = value;
                break;
            case STentry_Type::ste_bool:
                this->value.boolValue = value == "True" ? true : false;
                break;
        
        }
    }
    int get_lineno() {
        return this->lineno;
    }
    int get_to_print(){
        return this->to_print;
    }
    string get_name() {
        return this->name;
    }
    int get_offset() {
        return this->offset;
    }
    int get_width() {
        return this->width;
    }
    void* get_nested_table() {
        return this->nested_table;
    }
    STentry_Type get_type() {
        return this->type;
    }
    bool get_is_list() {
        return this->is_list;
    }
    string get_class_obj_name() {
        return this->class_obj_name;
    }
    // STentry_Type
    void print_entry() {
        cout << "Name: " << name << " Type: " << (int)type << " Line: " << lineno << endl;
    }

    void print_entry_csv(ofstream& outfile) {
        outfile << name << "," << (int)(type) << "," << lineno << endl;
    }
    

};
extern int size_of_type(STentry* entry);
class SymbolTable {
private:
    unordered_map<string, STentry*> table_entries;
    int offset; //offset of the next entry for the current table .
    string name;
    ST_Type type;
    int start_lineno;
    bool is_param = false;
    int size; //if type == class then size is the size of the class
    STentry_Type return_type; // if type == function
    string class_obj_name; // if type == function
    bool is_list; // if type == function
    vector<STentry*> params; // if type == function
    string function_name; // if type == function
    SymbolTable* parent;
    vector<SymbolTable*> nested_tables;
public:
    SymbolTable(ST_Type type, int start_lineno, SymbolTable* parent, STentry_Type return_type,string name) {
        this->type = type;
        this->start_lineno = start_lineno;
        this->parent = parent;
        this->return_type = return_type;
        this->name = name;
        this->offset = 0;
        this->size = 0;
    }
    void set_return_type(STentry_Type return_type) {
        this->return_type = return_type;
    }
    void set_offset(int offset) {
        this->offset = offset;
    }
    void insert(string name, STentry* entry) {
        this->table_entries[name] = entry;
    }
    void set_param(bool value){
        this->is_param = value;
    }
    void set_parent(SymbolTable* parent) {
        this->parent = parent;
    }
    void set_size(int size) {
        this->size = size;
    }
    void set_function_name(string name) {
        this->function_name = name;
    }
    void push_param(STentry* param) {
        this->params.push_back(param);
    }
    void set_class_obj_name(string name) {
        this->class_obj_name = name;
    }
    void set_is_list(bool value) {
        this->is_list = value;
    }
    void print_table() {
        cout << "Symbol Table " <<  " : " << this->name << " offset " << this->offset  << " size " << this->size << endl;
        for(auto it = table_entries.begin(); it != table_entries.end(); it++) {
            cout << it->first << " " << "offset" << " " << it->second->get_offset() << endl;
            it->second->print_entry();
            if (it->second->get_nested_table() != nullptr) {
                SymbolTable* nested_table = (SymbolTable*)(it->second->get_nested_table());
                // nested_table->print_params();
                nested_table->print_table();
            }
            
        }
    }
    void add_nested_table(SymbolTable* nested_table) {
        nested_tables.push_back(nested_table);
    }

    void print_table_csv(ofstream& outfile) {

        // outfile << "Symbol Table," << name << ",offset," << offset << ",size," << size << endl;
        for (auto it = table_entries.begin(); it != table_entries.end(); it++) 
        {   

            
            if(it->second->get_to_print() == 1){    
                SymbolTable* nested_table = (SymbolTable*)(it->second->get_nested_table());
                // if(nested_table != nullptr) {
                //     cout<<clean_string_ST(nested_table->get_name())<<endl;
                // }
                outfile << clean_string_ST(it->first) << "," << it->second->get_lineno() << "," 
                << type_to_string(it->second->get_type()) << "," << it->second->get_is_list() << "," 
                << clean_string_ST(it->second->get_class_obj_name()) << "," ;
                if (nested_table != nullptr) {
                    outfile << clean_string_ST(nested_table->get_name());
            
                }
                else {
                    outfile << "NULL";
                }
                outfile << ",";
                outfile << it->second->get_offset() << "," << it->second->get_width() << endl;

                // it->second->print_entry_csv(outfile);
                if (it->second->get_nested_table() != NULL)
                {
                    add_nested_table((SymbolTable*)(it->second->get_nested_table()));
                    
                }
            }
        }

        for (auto nested_table : nested_tables) 
        {
            outfile<< clean_string_ST(nested_table->get_name()) << ":" <<  endl;
            nested_table->print_table_csv(outfile);
        }
    }
    void print_table_txt(ofstream& outfile) {
    // Print column headings with lines below
    outfile << "Symbol Table\n";
    outfile << "Name           LineNo  Type       IsList  ClassObjName       NestedTableName       Offset  Width\n";
    outfile << "------------------------------------------------------------------------------------------------\n";

    // Print table entries
    for (auto it = table_entries.begin(); it != table_entries.end(); it++) {
        if (it->second->get_to_print() == 1) {
            SymbolTable* nested_table = (SymbolTable*)(it->second->get_nested_table());
            outfile << std::left << std::setw(15) << clean_string_ST(it->first) << " ";
            outfile << std::left << std::setw(7) << it->second->get_lineno() << " ";
            outfile << std::left << std::setw(10) << type_to_string(it->second->get_type()) << " ";
            outfile << std::left << std::setw(7) << it->second->get_is_list() << " ";
            outfile << std::left << std::setw(18) << clean_string_ST(it->second->get_class_obj_name()) << " ";

            if (nested_table != nullptr) {
                outfile << std::left << std::setw(20) << clean_string_ST(nested_table->get_name());
            } else {
                outfile << std::left << std::setw(20) << "NULL";
            }
            outfile << std::left << std::setw(7) << it->second->get_offset() << " ";
            outfile << std::left << std::setw(5) << it->second->get_width() << "\n";

            // Recursively print nested tables
            // if (it->second->get_nested_table() != NULL) {
            //     add_nested_table((SymbolTable*)(it->second->get_nested_table()));
            // }
        }
    }

    // Print tables recursively with proper separators
    for (auto nested_table : nested_tables) {
        outfile << "\n\n" << "Table: " << clean_string_ST(nested_table->get_name()) << "\n";
        outfile << "---------------------------------------\n";
        nested_table->print_table_txt(outfile);
    }
}


    ST_Type get_type() {
        return this->type;
    }
    STentry_Type get_return_type() {
        return this->return_type;
    }
    void print_params() {
        cout << "Params: " << endl;
        for(auto it = params.begin(); it != params.end(); it++) {
            cout << (*it)->get_name() << " ";
            (*it)->print_entry();
        }
    }
    string get_name() {
        return this->name;
    }   
    int get_offset() {
        return this->offset;
    }
    int get_size() {
        return this->size;
    }
    string get_function_name() {
        return this->function_name;
    }
    vector<STentry*> get_params() {
        return this->params;
    }
    STentry* lookup(string name) {
        if(table_entries.find((name)) != table_entries.end()) {
            return table_entries[(name)];
        }
        return NULL;
    }
    STentry* recurr_lookup (string name) {
        if(table_entries.find((name)) != table_entries.end()) {
            return table_entries[(name)];
        }
        if(parent != NULL)
            return parent->recurr_lookup(name);
        
        return nullptr;
    }
    STentry* recurr_lookup_in_class(string name) {
        if (this->type != ST_Type::st_class) {
            return nullptr;
        }
        if(table_entries.find((name)) != table_entries.end()) {
            return table_entries[(name)];
        }
        if(parent != nullptr)
            return parent->recurr_lookup_in_class(name);
        
        return nullptr;
    }
    SymbolTable* get_parent() {
        return this->parent;
    }
    void copySymbolTable(SymbolTable* table) {
        // we wll make the parent of this table to be the provided table and while searching we will be looking up the parent table as well :)
        // cout << "Copying table " << table->get_name() << " to " << this->name << endl;
        this->parent = table;
        this->offset = table->get_offset();
        this->size = table->get_size();
    }
};