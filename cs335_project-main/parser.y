%{
    #include <cstdio> 
    #include <cstring>
    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <stdio.h>
    #include "x86.hpp"
    using namespace std;
    extern vector<string> class_names;
    extern "C" int yylex();
    extern "C" int yylineno;
    void yyerror(const char* s);
    extern "C" FILE* yyin;
    TreeNode* root = nullptr;
    SymbolTable* globalTable = new SymbolTable(ST_Type::st_top , 1, nullptr, STentry_Type::ste_none,"globalTable");
    
    SymbolTable* currentTable = globalTable;
    bool verbose = false;
    bool type_expect = false;
    vector<string> type_expect_list;
    int size_of_type(STentry* entry){
    if (entry->get_type() == STentry_Type::ste_class_obj) {
        if (find(class_names.begin(), class_names.end(), entry->get_class_obj_name()) != class_names.end()) {
            SymbolTable* class_entry = (SymbolTable*)globalTable->lookup(entry->get_class_obj_name())->get_nested_table();
            return (class_entry->get_size());
        }
    }
    else if (entry->get_type() == STentry_Type::ste_class_def)
    {
        SymbolTable* class_entry = (SymbolTable*)globalTable->lookup(entry->get_name())->get_nested_table();
        return (class_entry->get_size());
    }
    else {
        return sizeofdatatype(entry->get_type());
    }
}
    void find_type(STentry* entry, bool is_return_type)
    {
        if(type_expect_list.size() == 0)
        {
            printf("Line %d:Type Error : No type for the parameter %s \n",entry->get_lineno(), entry->get_name());
            exit(1);
        }
        int i =0;
        if(type_expect_list[0] == "NAME (list)")
        {
            if(is_return_type)
                currentTable->set_is_list(true);
            else
                entry->set_is_list(true);
            i = 1;
        }
        if(type_expect_list[i] == "NAME (int)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_integer);
            else
                entry->set_type(STentry_Type::ste_integer);
        }
        else if(type_expect_list[i] == "NAME (float)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_float);
            else
                entry->set_type(STentry_Type::ste_float);
        }
        else if(type_expect_list[i] == "NAME (bool)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_bool);
            else
                entry->set_type(STentry_Type::ste_bool);
        }
        else if(type_expect_list[i] == "NAME (str)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_str);
            else
                entry->set_type(STentry_Type::ste_str);
        }
        else if (type_expect_list[i] == "KEYWORD (None)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_none);
            else
                entry->set_type(STentry_Type::ste_none);
        }
        else if(find(class_names.begin(), class_names.end(), type_expect_list[i]) != class_names.end())
        {
            if(is_return_type)
            {
                currentTable->set_return_type(STentry_Type::ste_class_obj);
                currentTable->set_class_obj_name(type_expect_list[i]);
            }
            else
            {
                entry->set_type(STentry_Type::ste_class_obj);
                entry->set_class_obj_name(type_expect_list[i]);
            }
        }
        else
        {
            cout << "Line " << entry->get_lineno() << ":Type Error : Invalid type for " << entry->get_name() << endl;
            exit(1);
        }
        return;
        
    }
%}
%union{
    char* str;
    class TreeNode* ptr;
    int num;    
}
%token<str> NEWLINE ENDMARKER
%token<str> NAME
%token<str> INDENT DEDENT
%token<str> NUMBER
%token<str> STRING
%token<str> KEYWORD_FALSE KEYWORD_NONE KEYWORD_TRUE KEYWORD_AND KEYWORD_ASSERT KEYWORD_BREAK KEYWORD_CLASS KEYWORD_CONTINUE KEYWORD_DEF KEYWORD_ELIF KEYWORD_ELSE KEYWORD_FOR KEYWORD_FROM KEYWORD_GLOBAL KEYWORD_IF KEYWORD_IN KEYWORD_NONLOCAL KEYWORD_NOT KEYWORD_OR  KEYWORD_RAISE KEYWORD_RETURN KEYWORD_WHILE
%token<str> OP_POWER OP_INT_DIVIDE_EQUALS OP_POWER_EQUALS OP_RIGHT_SHIFT_EQUALS
%token<str> OP_LEFT_SHIFT_EQUALS OP_XOR_EQUALS OP_OR_EQUALS OP_AND_EQUALS
%token<str> OP_MOD_EQUALS OP_DIVIDE_EQUALS OP_MULTIPLY_EQUALS OP_MINUS_EQUALS
%token<str> OP_PLUS_EQUALS OP_NOT_EQUALS OP_EQUALS OP_RIGHT_SHIFT OP_LEFT_SHIFT
%token<str> OP_INT_DIVIDE OP_GREATER_THAN_EQUALS OP_LESS_THAN_EQUALS OP_ARROW
%token<str> ':' ',' ';' '.' '(' ')' '[' ']' '+' '-' '*' '/' '%' '&' '|' '^' '~' '<' '>' '='

%type<ptr> file_input file_input1 file_input2
%type<ptr> funcdef funcdef1 parameters parameters1
%type<ptr> typedargslist tfpdef tfpdef1 typedargslist1 typedargslist2 
%type<ptr> stmt
%type<ptr> simple_stmt compound_stmt simple_stmt2 simple_stmt3
%type<ptr> small_stmt
%type<ptr> expr_stmt flow_stmt global_stmt nonlocal_stmt assert_stmt assert_stmt1
%type<ptr> expr_stmt3 expr_stmt2 expr_stmt1
%type<ptr> testlist_star_expr  augassign testlist_star_expr1 testlist_star_expr2
%type<ptr> test test1 testlist testlist1 testlist2 testlist3
%type<ptr> break_stmt continue_stmt return_stmt raise_stmt raise_stmt1 raise_stmt2
%type<ptr> global_stmt1 nonlocal_stmt1
%type<ptr>  if_stmt if_stmt1 if_stmt2 
%type<ptr> while_stmt while_stmt1
%type<ptr> for_stmt for_stmt1
%type<ptr> classdef classdef1 
%type<ptr> suite suite1
%type<ptr> or_test or_test1
%type<ptr> and_test and_test1
%type<ptr> not_test
%type<ptr> comparison comparison1
%type<ptr> comp_op
%type<ptr> expr expr1
%type<ptr> xor_expr xor_expr1
%type<ptr> and_expr and_expr1
%type<ptr> shift_expr shift_expr1 shift_expr2
%type<ptr> arith_expr arith_expr1 arith_expr2
%type<ptr> term term1 term2
%type<ptr> factor factor1
%type<ptr> power power1 
%type<ptr> atom_expr atom_expr1
%type<ptr> atom atom1 atom2
%type<ptr> trailer trailer1
%type<ptr> testlist_comp testlist_comp1 testlist_comp2 
%type<ptr> subscriptlist subscriptlist2 subscriptlist1
%type<ptr> subscript subscript1 subscript2
%type<ptr> exprlist exprlist1 exprlist2
%type<ptr> arglist arglist1 arglist2
%type<ptr> arglist_class arglist_class1 argument_class
%type<ptr> argument argument1
%right '='
%right KEYWORD_IF KEYWORD_ELSE KEYWORD_ELIF
%left KEYWORD_OR KEYWORD_AND 
%right KEYWORD_NOT
%left '<' '>' OP_EQUALS OP_GREATER_THAN_EQUALS OP_LESS_THAN_EQUALS OP_NOT_EQUALS
%left '|'
%left '^'
%left '&'
%left OP_LEFT_SHIFT OP_RIGHT_SHIFT
%left '+' '-'
%left '*' '/' OP_INT_DIVIDE '%'
%right OP_POWER
%left '(' ')' '[' ']'
%nonassoc OP_PLUS_EQUALS OP_MINUS_EQUALS OP_MULTIPLY_EQUALS OP_DIVIDE_EQUALS OP_MOD_EQUALS OP_AND_EQUALS OP_OR_EQUALS OP_XOR_EQUALS OP_LEFT_SHIFT_EQUALS OP_RIGHT_SHIFT_EQUALS OP_POWER_EQUALS OP_INT_DIVIDE_EQUALS
%%
file_input : file_input1 ENDMARKER {
                                    TreeNode* node2 = new TreeNode($2);
                                    $$ = new TreeNode("file_input");
                                    $$->addChild($1);
                                    $$->addChild(node2);
                                    if (verbose){
                                    printf("parsing done successfully\n");
                                    }
                                    root = $$;
                                    // globalTable->print_table();
                                    // cout << "--table printed--" << endl;
                                    return 0;
                                    }
file_input1 : {$$ = nullptr;}
            | file_input1 file_input2 {
                                        $$ = new TreeNode("file_input1");
                                        $$->addChild($1);
                                        $$->addChild($2);
                                    }
file_input2 : stmt {
                    $$ = $1;
                    }
             | NEWLINE{
                    $$ = new TreeNode($1);
             }
funcdef : KEYWORD_DEF NAME {
                /*we have to check if the name of the function already exists then error */
                 if (currentTable->lookup(string($2))!=NULL){
                   cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << string($2) << " is not allowed. Previous defined at line "<< currentTable->lookup(string($2))->get_lineno() << endl;
                   exit(1);
                 }
                 SymbolTable* newTable = new SymbolTable(ST_Type::st_function, yylineno, currentTable, STentry_Type::ste_none, string($2));            
                 STentry* entry = new STentry($2, STentry_Type::ste_func_def, yylineno, (void*)newTable);   
                 currentTable->insert(string($2), entry);
                 currentTable = newTable;
                 currentTable-> set_param(true);
}
parameters funcdef1 {
                        TreeNode* node1 = new TreeNode($1);
                        TreeNode* node2 = new TreeNode($2);
                        $$ = new TreeNode("funcdef");
                        $$->setlineno(yylineno);
                        $$->addChild(node1);
                        $$->addChild(node2);
                        $$->addChild($4);
                        $$->addChild($5);
                        /*we have to end the scope of the function here as the function has ended*/
                        string function_name = "";
                        //if it is a method of a class then we also have to add the class_name in the begiining of the function name
                        if (currentTable->get_parent()->get_type() == ST_Type :: st_class ){
                            function_name += clean_string(currentTable->get_parent()->get_name());
                            function_name += "_";
                        }
                         function_name = function_name + node2->original_value;
                        for(auto it : currentTable->get_params()){
                            //appending the function names.
                            function_name = function_name + "_" + type_to_string(it->get_type());
                        }
                        currentTable->set_function_name(function_name);
                        currentTable = currentTable->get_parent();
                    }
funcdef1 : ':' suite {
                        TreeNode* node1 = new TreeNode($1);
                        $$ = new TreeNode("funcdef1");
                        $$->addChild(node1);
                        $$->addChild($2);
                    }
        | OP_ARROW {
            type_expect = true;
        }
        test ':' {
            type_expect = false;
            find_type(NULL, true);
            type_expect_list.clear();
        } suite {
                            TreeNode* node1 = new TreeNode($1);
                            TreeNode* node4 = new TreeNode($4);
                            $$ = new TreeNode("funcdef1");
                            $$->addChild(node1);
                            $$->addChild($3);
                            $$->addChild(node4);
                            $$->addChild($6);
                        }


parameters : '(' parameters1 {
                                TreeNode* node1 = new TreeNode($1);
                                $$ = new TreeNode("parameters");
                                $$->addChild(node1);
                                $$->addChild($2);
                            
        }
parameters1 : ')' {
                    $$ =  new TreeNode($1);
                }
            | typedargslist ')' {
                                TreeNode* node1 = new TreeNode($2);
                                $$ = new TreeNode("parameters1");
                                $$->addChild($1);
                                 $$->addChild(node1);
                }
                                    
typedargslist : tfpdef  typedargslist1 typedargslist2  {
                                                                        $$ = new TreeNode("typedargslist");
                                                                        $$->addChild($1);
                                                                        $$->addChild($2);
                                                                        $$->addChild($3);
                                                                    }
            /* | '*' typedargslist6 {
                                    TreeNode* node1 = new TreeNode($1);
                                    $$ = new TreeNode("typedargslist");
                                    $$->addChild(node1);
                                    $$->addChild($2);
                                } */
            /* | OP_POWER tfpdef typedargslist7 {
                                        TreeNode* node1 = new TreeNode($1);
                                        $$ = new TreeNode("typedargslist");
                                        $$->addChild(node1);
                                        $$->addChild($2);
                                        $$->addChild($3);
                                    } */
typedargslist1 :                {   
                                    $$ =nullptr;
                                }   
                | '=' test     {
                                    TreeNode* node1 = new TreeNode($1);
                                    $$ = new TreeNode("typedargslist1");
                                    $$->addChild(node1);
                                }
typedargslist2 :                {    
                                    $$ = nullptr;
                                }
                | typedargslist2 ',' tfpdef typedargslist1  {
                                                                TreeNode* node2 = new TreeNode($2);
                                                                $$ = new TreeNode("typedargslist2");
                                                                $$->addChild($1);
                                                                $$->addChild(node2);
                                                                $$->addChild($3);
                                                                $$->addChild($4);
                                                            }
/* typedargslist3 :                {
                                    $$ = nullptr;
                                }
                | ',' typedargslist4  {
                                            TreeNode* node1 = new TreeNode($1);
                                            $$ = new TreeNode("typedargslist3");
                                            $$->addChild(node1);
                                            $$->addChild($2);
                                        } */
/* typedargslist4 :                {
                                    $$ = nullptr;
                                }
         */
                /* | '*' typedargslist6 {
                                        TreeNode* node1 = new TreeNode($1);
                                        $$ = new TreeNode("typedargslist4");
                                        $$->addChild(node1);
                                        $$->addChild($2);
                } */
                /* |OP_POWER tfpdef typedargslist7 {
                                                    TreeNode* node1 = new TreeNode($1);
                                                    $$ = new TreeNode("typedargslist4");
                                                    $$->addChild(node1);
                                                    $$->addChild($2);
                                                    $$->addChild($3);
                                                
                } */
/* typedargslist6 : tfpdef  typedargslist2 typedargslist5 {
                                                        $$ = new TreeNode("typedargslist6");
                                                        $$->addChild($1);
                                                        $$->addChild($2);
                                                        $$->addChild($3);

                  }
                | typedargslist2 typedargslist5 {
                                                    $$ = new TreeNode("typedargslist6");
                                                    $$->addChild($1);
                                                    $$->addChild($2);
                                                
                } */
/* typedargslist7 : {
                            $$ = nullptr;
                        }
                | ',' {
                                $$ = new TreeNode($1);
                            } */
/* typedargslist5 :                     {
                                        $$ = nullptr;
                                    }
                | ',' typedargslist8 {
                                        TreeNode* node1 = new TreeNode($1);
                                        $$ = new TreeNode("typedargslist5");
                                        $$->addChild(node1);
                                        $$->addChild($2);
                                    
                } */
/* typedargslist8 :  { 
                    $$ = nullptr; 
                } */
                /* | OP_POWER tfpdef typedargslist9{
                                            TreeNode* node1 = new TreeNode($1);
                                            $$ = new TreeNode("typedargslist8");
                                            $$->addChild(node1);
                                            $$->addChild($2);
                                            $$->addChild($3);
                } */
/* typedargslist9 : {
                    $$ = nullptr;
                }
                |',' {
                   $$ = new TreeNode($1);
                
                } */

tfpdef :  NAME tfpdef1 {
                            TreeNode* node1 = new TreeNode($1);
                            $$ = new TreeNode("tfpdef");
                            $$->addChild(node1);
                            $$->addChild($2);
                            /*this tfpdef is a parameter of the function so we have to add it to the symbol table and params*/
                            if (currentTable->lookup(string($1))!=NULL){
                                cout <<"Line "<< yylineno << ":Name Error : Re-definition of name" << string($1) << " is not allowed. Previous defined at line "<< currentTable->lookup(string($1))->get_lineno() << endl;
                                exit(1);
                            }
                            STentry* entry = new STentry(string($1), STentry_Type::ste_none, yylineno, NULL);
                            currentTable->insert(string($1), entry);
                            if ($2 == nullptr){
                                /*implies we dont have a type for the parameter which is error if the parameter is not self*/\
                                if (string($1) != "NAME (self)"){
                                    printf("Line %d:Type Error : No type for the parameter %s \n",entry->get_lineno(), $1);
                                    exit(1);
                                }
                                else {
                                    /*implies we have a type for the parameter to be handled for now let it be*/

                                }
                            }
                            else {
                                /*implies we have a type for the parameter*/
                                find_type(entry, false);
                                type_expect_list.clear();
                                currentTable->push_param(entry);
                                
                            }
                        }
tfpdef1 :':' {
        type_expect = true;
}
test {
                        TreeNode* node1 = new TreeNode($1);
                        $$ = new TreeNode("tfpdef1");
                        $$->addChild(node1);
                        $$->addChild($3);
                        type_expect = false;
                    }
            | {
                     $$ = nullptr;
            }
stmt : simple_stmt    {
                            $$ = $1;
                        }
    | compound_stmt     {
                            $$ = $1;
                        }

simple_stmt : small_stmt simple_stmt2 simple_stmt3 {
                                                        $$ = new TreeNode("simple_stmt");
                                                        $$->addChild($1);
                                                        $$->addChild($2);
                                                        $$->addChild($3);
                                                    
            }
simple_stmt3 : ';' NEWLINE {
                           TreeNode* node1 = new TreeNode($1);
                            TreeNode* node2 = new TreeNode($2);
                            $$ = new TreeNode("simple_stmt3");
                            $$->addChild(node1);
                            $$->addChild(node2); 
                }
                | NEWLINE {
                            TreeNode* node1 = new TreeNode($1);
                            $$ = new TreeNode("simple_stmt3");
                            $$->addChild(node1);
                        
                }
simple_stmt2 :      {
                        $$ = nullptr;
                    }
            | simple_stmt2 ';' small_stmt   {
                                                TreeNode* node2 = new TreeNode($2);
                                                $$ = new TreeNode("simple_stmt2");
                                                $$->addChild($1);
                                                $$->addChild(node2);
                                                $$->addChild($3);
                                            }

small_stmt : expr_stmt  {
                            $$ = $1;
                        }
            | flow_stmt   {
                            $$ = $1;
                        }
            | global_stmt  {
                                $$ = $1;
                            }
            | nonlocal_stmt  {
                                $$ = $1;
                            }
            | assert_stmt   {
                                $$ = $1;
                            }

expr_stmt : testlist_star_expr expr_stmt1 {
                            if ($2 == nullptr){
                                $$ = $1;
                            }
                            else if ($2->children[0]->value == "DELIMITER (:)"){
                                $$ = $2;
                                $$->children[0]->addChildFront($1);
                            
                                /*we have to first get the name of the variable*/
                                TreeNode* temp = $1;
                                // string name = getFirstTerminalValue(temp);
                                vector<TreeNode*> values;
                                getAllTerminalValue(temp, values);
                                for (auto it : values){
                                    //cout << it->value << endl;
                                }
                                string name = values[0]->value;
                                //if name is self then values[2] will have the attribute name
                                if (name == "NAME (self)"){
                                    //this is an attribute of the class
                                    string attr_name = values[2]->value;
                                    //whenever we are in a class our specification says we are definitely inside a method so we have to add the attribute to the symbol table of the class not the function
                                    SymbolTable* classTable;
                                    if (currentTable->get_type() == ST_Type::st_function){
                                        //we are in a function so we have to go to the parent of the function to get the class symbol table
                                        classTable = currentTable->get_parent();
                                    }
                                    else {
                                        classTable = currentTable;
                                    }
                                    if (classTable->lookup(attr_name) != NULL){
                                        cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << attr_name << " is not allowed. Previous defined at line "<< classTable->lookup(attr_name)->get_lineno() << endl;
                                        exit(1);
                                    }
                                    STentry* entry = new STentry(attr_name, STentry_Type::ste_none, yylineno, NULL);
                                    classTable->insert(attr_name, entry);
                                    find_type(entry, false);
                                    entry->set_offset(classTable->get_offset());
                                    if (entry->get_is_list()== true){
                                        vector<TreeNode*> values1;
                                        getAllTerminalValue($2->children[1], values1);
                                        int size = (values1.size() - 2)/2+1;
                                        entry->set_width(size*size_of_type(entry));
                                        classTable->set_offset(classTable->get_offset() + entry->get_width());
                                        classTable->set_size(classTable->get_size()+ entry->get_width());
                                        values1.clear();
                                    }
                                    else {
                                        classTable->set_offset(classTable->get_offset() + size_of_type(entry));
                                        classTable->set_size(classTable->get_size()+ size_of_type(entry));
                                    }
                                    
                                    type_expect_list.clear();
                                }
                                else {
                                    if(currentTable->lookup(name) != NULL){
                                        cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << name << " is not allowed. Previous defined at line "<< currentTable->lookup(name)->get_lineno() << endl; 
                                        exit(1);
                                    }
                                    STentry* entry = new STentry(name, STentry_Type::ste_none, yylineno, NULL);
                                    currentTable->insert(name, entry);
                                    // cout << name << endl;
                                    // for(int i=0; i<type_expect_list.size(); i++){
                                    //     cout << type_expect_list[i] << endl;
                                    // }
                                    find_type(entry, false);
                                    entry->set_offset(currentTable->get_offset());
                                    if (entry->get_is_list()== true){
                                        vector<TreeNode*> values1;
                                        getAllTerminalValue($2->children[1], values1);
                                        int size = (values1.size() - 2)/2+1;
                                        entry->set_width(size*size_of_type(entry));
                                        currentTable->set_offset(currentTable->get_offset() + entry->get_width());
                                        values1.clear();
                                    }
                                    else {
                                        currentTable->set_offset(currentTable->get_offset() + size_of_type(entry));
                                    }
                                    type_expect_list.clear();
                                    }
                                    values.clear();
                                }
                            else {
                                    $$ = $2;
                                    $$->addChildFront($1);
                                    if ($$->value == "DELIMITER (:)") {
                                        TreeNode* temp = $1;
                                        // string name = getFirstTerminalValue(temp);
                                        vector<TreeNode*> values;
                                        getAllTerminalValue(temp, values);
                                        string name = values[0]->value;
                                        if (name == "NAME (self)"){
                                            //this is an attribute of the class
                                            string attr_name = values[2]->value;
                                            //whenever we are in a class our specification says we are definitely inside a method so we have to add the attribute to the symbol table of the class not the function
                                            SymbolTable* classTable;
                                            if (currentTable->get_type() == ST_Type::st_function){
                                                //we are in a function so we have to go to the parent of the function to get the class symbol table
                                                classTable = currentTable->get_parent();
                                            }
                                            else {
                                                classTable = currentTable;
                                            }
                                            if (classTable->lookup(attr_name) != NULL){
                                                cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << attr_name << " is not allowed. Previous defined at line "<< classTable->lookup(attr_name)->get_lineno() << endl;
                                                exit(1);
                                            }
                                            STentry* entry = new STentry(attr_name, STentry_Type::ste_none, yylineno, NULL);
                                            classTable->insert(attr_name, entry);
                                            find_type(entry, false);
                                            entry->set_offset(classTable->get_offset());
                                            if (entry->get_is_list()== true){
                                                //error case as list will always be statically defined and initialised
                                                cout << "Line " << yylineno << ":Type Error : List cannot be defined in this way" << endl;
                                                exit(1);
                                            }
                                            else {
                                                classTable->set_offset(classTable->get_offset() + size_of_type(entry));
                                                classTable->set_size(classTable->get_size()+ size_of_type(entry));
                                            }
                                            type_expect_list.clear();
                                        }
                                        else {
                                            if(currentTable->lookup(name) != NULL){
                                                cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << name << " is not allowed. Previous defined at line "<< currentTable->lookup(name)->get_lineno() << endl;
                                                exit(1);
                                            }
                                            STentry* entry = new STentry(name, STentry_Type::ste_none, yylineno, NULL);
                                            currentTable->insert(name, entry);
                                            // cout << name << endl;
                                            // for(int i=0; i<type_expect_list.size(); i++){
                                            //     cout << type_expect_list[i] << endl;
                                            // }
                                            find_type(entry, false);
                                            entry->set_offset(currentTable->get_offset());
                                            if (entry->get_is_list()== true){
                                                //error case as list will always be statically defined and initialised
                                                cout << "Line " << yylineno << ":Type Error : List cannot be defined in this way" << endl;
                                                exit(1);
                                            }
                                            else {
                                                currentTable->set_offset(currentTable->get_offset() + size_of_type(entry));
                                            }
                                            type_expect_list.clear();
                                            }
                                        values.clear();
                                }
                            }
                            
                        }
expr_stmt1 : ':' {
                /*here we are expecting a type as a name*/
                type_expect = true;
        }
        test {
        /* this test is the type of the variable */
        type_expect = false;
        }
        expr_stmt2 {
                            if ($5 == nullptr){
                                $$ = new TreeNode($1);
                                $$->addChild($3);
                            }
                            else {
                                TreeNode* node1 = new TreeNode($1);
                                node1->addChild($3);
                                $$ = $5;
                                $5->addChildFront(node1);
                            }
                    }
        | augassign testlist {
                                $$=$1;
                                $$->addChild($2);
                            }
        |expr_stmt3 {
                        $$ = $1;
                    }
expr_stmt2 : {
                $$ = nullptr;
            }
            | '=' test {
                    $$ = new TreeNode($1);
                    $$->setlineno(yylineno);
                    $$->setType("assign");
                    $$->addChild($2);
                     }
expr_stmt3 :      {
                    $$ = nullptr;
                }
            | '=' testlist_star_expr expr_stmt3  {
                                                    $$ = new TreeNode($1);
                                                    $$->setlineno(yylineno);  
                                                    $$->setType("assign");
                                                    if($3 != nullptr)
                                                    {
                                                        $3->addChildFront($2);
                                                        $$->addChild($3);
                                                    }
                                                    else
                                                    {
                                                        $$->addChild($2);
                                                    }
                                                }

testlist_star_expr : test testlist_star_expr1 testlist_star_expr2 {
                                                                    $$ = new TreeNode("testlist_star_expr");
                                                                    $$->addChild($1);
                                                                    $$->addChild($2);
                                                                    $$->addChild($3);                                         
                    }
testlist_star_expr2 : {
                        $$ = nullptr;
                    }
                    | ',' {
                            $$ = new TreeNode($1);
                    }
testlist_star_expr1 :      {
                            $$ = nullptr;
                        }
                    | testlist_star_expr1 ',' test   {
                                                        TreeNode* node2 = new TreeNode($2);
                                                        $$ = new TreeNode("testlist_star_expr1");
                                                        $$->addChild($1);
                                                        $$->addChild(node2);
                                                        $$->addChild($3);
                                                    }
 
augassign : OP_PLUS_EQUALS    {
                                $$ = new TreeNode($1);
                                $$->setlineno(yylineno);
                                $$->setType("augassign");
                            }
            | OP_MINUS_EQUALS  {
                                    $$ = new TreeNode($1);
                                    $$->setlineno(yylineno);  
                                    $$->setType("augassign");
                                }
            | OP_MULTIPLY_EQUALS  {
                                       $$ = new TreeNode($1);
                                       $$->setlineno(yylineno);  
                                       $$->setType("augassign");
                                    }
            | OP_DIVIDE_EQUALS   {
                                    $$ = new TreeNode($1);
                                    $$->setlineno(yylineno);  
                                    $$->setType("augassign");
                                }
            | OP_MOD_EQUALS    {
                                    $$ = new TreeNode($1);
                                    $$->setlineno(yylineno);  
                                    $$->setType("augassign");
                                }
            | OP_AND_EQUALS      {
                                    $$ = new TreeNode($1);
                                    $$->setlineno(yylineno);  
                                    $$->setType("augassign");
                                }
            | OP_OR_EQUALS    {
                                   $$ = new TreeNode($1);
                                   $$->setlineno(yylineno);  
                                   $$->setType("augassign");
                                }
            | OP_XOR_EQUALS   {
                                   $$ = new TreeNode($1);
                                   $$->setlineno(yylineno);  
                                   $$->setType("augassign");
                                }
            | OP_LEFT_SHIFT_EQUALS  {
                                       $$ = new TreeNode($1);
                                       $$->setlineno(yylineno);  
                                       $$->setType("augassign");
                                    }
            | OP_RIGHT_SHIFT_EQUALS  {
                                      $$ = new TreeNode($1);
                                      $$->setlineno(yylineno);  
                                      $$->setType("augassign");
                                    }
            | OP_POWER_EQUALS   {
                                    $$ = new TreeNode($1);
                                    $$->setlineno(yylineno);  
                                    $$->setType("augassign");
                                }
            | OP_INT_DIVIDE_EQUALS   {
                                      $$ = new TreeNode($1);
                                      $$->setlineno(yylineno);  
                                      $$->setType("augassign");
                                    }

flow_stmt : break_stmt    {
                            $$ = $1;
                        }
        | continue_stmt   {
                               $$ = $1;
                            }
        | return_stmt    {
                               $$ = $1;
                            }
        | raise_stmt     {
                                 $$ = $1;
                            }

break_stmt : KEYWORD_BREAK    {
                                 $$ = new TreeNode($1);
                            }

continue_stmt : KEYWORD_CONTINUE    {
                                        $$ = new TreeNode($1);
                                    }

return_stmt : KEYWORD_RETURN testlist2 {
                                            TreeNode* node1 = new TreeNode($1);
                                            $$ = new TreeNode("return_stmt");
                                            $$->setlineno(yylineno);
                                            $$->addChild(node1);
                                            $$->addChild($2);

            }
testlist2: {
                $$ = nullptr;
            }
        | testlist {
                        $$ = $1;
        }

raise_stmt : KEYWORD_RAISE raise_stmt1 {
                                            TreeNode* node1 = new TreeNode($1);
                                            $$ = new TreeNode("raise_stmt");
                                            $$->addChild(node1);
                                            $$->addChild($2);
                                        
            }
raise_stmt1 : {
                $$ = nullptr;
            }
            | test raise_stmt2 {
                                    $$ = new TreeNode("raise_stmt1");
                                    $$->addChild($1);
                                    $$->addChild($2);
                                }

raise_stmt2 : {
                $$ = nullptr;
            }
            | KEYWORD_FROM test {
                                    TreeNode* node1 = new TreeNode($1);
                                    $$ = new TreeNode("raise_stmt2");
                                    $$->addChild(node1);
                                    $$->addChild($2);
                                
        }
global_stmt : KEYWORD_GLOBAL NAME global_stmt1   
                                                {  
                                                    TreeNode* node1 = new TreeNode($1);
                                                    TreeNode* node2 = new TreeNode($2);
                                                    $$ = new TreeNode("global_stmt");
                                                    $$->addChild(node1);
                                                    $$->addChild(node2);
                                                    $$->addChild($3);
                                                }
global_stmt1 :                        {
                                        $$ = nullptr;
                                        }
            | global_stmt1 ',' NAME    {
                                            TreeNode* node2 = new TreeNode($2);
                                            TreeNode* node3 = new TreeNode($3);
                                            $$ = new TreeNode("global_stmt1");
                                            $$->addChild($1);
                                            $$->addChild(node2);
                                            $$->addChild(node3);
                                        }

nonlocal_stmt : KEYWORD_NONLOCAL NAME nonlocal_stmt1   
                                                {  
                                                    TreeNode* node1 = new TreeNode($1);
                                                    TreeNode* node2 = new TreeNode($2);
                                                    $$ = new TreeNode("nonlocal_stmt");
                                                    $$->addChild(node1);
                                                    $$->addChild(node2);
                                                    $$->addChild($3);

                                                }
nonlocal_stmt1 :                               {
                                                    $$ = nullptr;
                                                }
                | nonlocal_stmt1 ',' NAME       {
                                                    TreeNode* node2 = new TreeNode($2);
                                                    TreeNode* node3 = new TreeNode($3);
                                                    $$ = new TreeNode("nonlocal_stmt1");
                                                    $$->addChild($1);
                                                    $$->addChild(node2);
                                                    $$->addChild(node3);
                                                    }

assert_stmt : KEYWORD_ASSERT test assert_stmt1 {
                                            TreeNode* node1 = new TreeNode($1);
                                            $$ = new TreeNode("assert_stmt");
                                            $$->addChild(node1);
                                            $$->addChild($2);
                                            $$->addChild($3);
                                        
            }

assert_stmt1 : {
                    $$ = nullptr;
                }
            | ',' test {
                            TreeNode* node1 = new TreeNode($1);
                            $$ = new TreeNode("assert_stmt1");
                            $$->addChild(node1);
                            $$->addChild($2);
                        }
compound_stmt: if_stmt     {
                            $$ = $1;
                        }
            | while_stmt  {
                            $$ = $1;
                            }
            | for_stmt      {
                                $$ = $1;
                            }
            | funcdef     {
                                $$ = $1;
                            }
            | classdef      {
                                $$ = $1;
                            }

if_stmt: KEYWORD_IF test ':' suite if_stmt1 if_stmt2   {
                                                            TreeNode* node1 = new TreeNode($1);
                                                            TreeNode* node3 = new TreeNode($3);
                                                            $$ = new TreeNode("if_stmt");
                                                            $$->addChild(node1);
                                                            $$->addChild($2);
                                                            $$->addChild(node3);
                                                            $$->addChild($4);
                                                            $$->addChild($5);
                                                            $$->addChild($6);
                                                        }
if_stmt1:      {
                    $$ = nullptr;
                }
        | if_stmt1 KEYWORD_ELIF test ':' suite    {
                                                    TreeNode* node2 = new TreeNode($2);
                                                    TreeNode* node4 = new TreeNode($4);
                                                    $$ = new TreeNode("if_stmt1");
                                                    $$->addChild($1);
                                                    $$->addChild(node2);
                                                    $$->addChild($3);
                                                    $$->addChild(node4);
                                                    $$->addChild($5);
                                                }
if_stmt2:          {
                        $$ = nullptr;
                    }
        | KEYWORD_ELSE ':' suite   {
                                        TreeNode* node1 = new TreeNode($1);
                                        TreeNode* node2 = new TreeNode($2);
                                        $$ = new TreeNode("if_stmt2");
                                        $$->addChild(node1);
                                        $$->addChild(node2);
                                        $$->addChild($3);
                                    }

while_stmt: KEYWORD_WHILE test ':' suite while_stmt1   {
                                                            TreeNode* node1 = new TreeNode($1);
                                                            TreeNode* node3 = new TreeNode($3);
                                                            $$ = new TreeNode("while_stmt");
                                                            $$->addChild(node1);
                                                            $$->addChild($2);
                                                            $$->addChild(node3);
                                                            $$->addChild($4);
                                                            $$->addChild($5);
                                                    }
while_stmt1:        {
                        $$ = nullptr;
                    }
            | KEYWORD_ELSE ':' suite   {
                                            TreeNode* node1 = new TreeNode($1);
                                            TreeNode* node2 = new TreeNode($2);
                                            $$ = new TreeNode("while_stmt1");
                                            $$->addChild(node1);
                                            $$->addChild(node2);
                                            $$->addChild($3);
                                        }

for_stmt: KEYWORD_FOR exprlist KEYWORD_IN testlist ':' suite for_stmt1    {
                                                                            TreeNode* node1 = new TreeNode($1);
                                                                            TreeNode* node3 = new TreeNode($3);
                                                                            TreeNode* node5 = new TreeNode($5);
                                                                            $$ = new TreeNode("for_stmt");
                                                                            $$->addChild(node1);
                                                                            $$->addChild($2);
                                                                            $$->addChild(node3);
                                                                            $$->addChild($4);
                                                                            $$->addChild(node5);
                                                                            $$->addChild($6);
                                                                            $$->addChild($7);
                                                                        }
for_stmt1:    {
                    $$ = nullptr;
                }
        | KEYWORD_ELSE ':' suite   {
                                        TreeNode* node1 = new TreeNode($1);
                                        TreeNode* node2 = new TreeNode($2);
                                        $$ = new TreeNode("for_stmt1");
                                        $$->addChild(node1);
                                        $$->addChild(node2);
                                        $$->addChild($3);
                                    }


suite: simple_stmt  {
                        $$ = $1;
                    }
    | NEWLINE INDENT suite1 DEDENT   {
                                        TreeNode* node1 = new TreeNode($1);
                                        TreeNode* node2 = new TreeNode($2);
                                        TreeNode* node4 = new TreeNode($4);
                                        $$ = new TreeNode("suite");
                                        $$->addChild(node1);
                                        $$->addChild(node2);
                                        $$->addChild($3);
                                        $$->addChild(node4);
                                    }
suite1: stmt     {
                    $$ = $1;
                }
        |suite1 stmt    {
                            $$ = new TreeNode("suite1");
                            $$->addChild($1);
                            $$->addChild($2);
                        }

test: or_test test1   {
                        $$ = new TreeNode("test");
                        $$->addChild($1);
                        $$->addChild($2);
                    }
test1:   {  
            $$ = nullptr;
            }
    | KEYWORD_IF or_test KEYWORD_ELSE test   {
                                                TreeNode* node1 = new TreeNode($1);
                                                TreeNode* node3 = new TreeNode($3);
                                                $$ = new TreeNode("test1");
                                                $$->addChild(node1);
                                                $$->addChild($2);
                                                $$->addChild(node3);
                                                $$->addChild($4);
                                                }

or_test: and_test or_test1    {
                                $$ = new TreeNode("or_test");
                                $$->addChild($1);
                                $$->addChild($2);

                                if(($2 != nullptr) && clean_string($2 -> value) == "or")
                                {
                                    $$ = $2;
                                    $$->addChildFront($1);
                                    $$->setType("logical_op");
                                }    
                                else
                                {
                                    $$ = new TreeNode("or_test");
                                    $$->addChild($1);
                                    $$->addChild($2); 
                                }   
                            }
or_test1:    {
                $$ = nullptr;
            }
        | or_test1 KEYWORD_OR and_test  {
                                            TreeNode* node2 = new TreeNode($2);
                                            $$ = new TreeNode("or_test1");
                                            $$->addChild($1);
                                            $$->addChild(node2);
                                            $$->addChild($3);

                                            if($1 == nullptr)
                                            {
                                                TreeNode* node2 = new TreeNode($2);
                                                $$ = node2;
                                                $$->addChild($3);
                                            }
                                            else
                                            {
                                                TreeNode* node2 = new TreeNode($2);
                                                $$ = new TreeNode("or_test1");
                                                $$->addChild($1);
                                                $$->addChild(node2);
                                                $$->addChild($3);
                                            }
                                        }

and_test: not_test and_test1 {
                                // $$ = new TreeNode("and_test");
                                // $$->addChild($1);
                                // $$->addChild($2);   

                                // if($2 != nullptr)
                                //     cout << "->->" << clean_string($2 -> value) << endl;
                                if(($2 != nullptr) && clean_string($2 -> value) == "and")
                                {
                                    $$ = $2;
                                    $$->addChildFront($1);
                                    $$->setType("logical_op");
                                }    
                                else
                                {
                                    $$ = new TreeNode("and_test");
                                    $$->addChild($1);
                                    $$->addChild($2); 
                                }                     
                            }

and_test1: {
                $$ = nullptr;    
            }
        | and_test1 KEYWORD_AND not_test {
                                            // TreeNode* node2 = new TreeNode($2);
                                            // $$ = new TreeNode("and_test1");
                                            // $$->addChild($1);
                                            // $$->addChild(node2);
                                            // $$->addChild($3);

                                            if($1 == nullptr)
                                            {
                                                TreeNode* node2 = new TreeNode($2);
                                                $$ = node2;
                                                $$->addChild($3);
                                            }
                                            else
                                            {
                                                TreeNode* node2 = new TreeNode($2);
                                                $$ = new TreeNode("and_test1");
                                                $$->addChild($1);
                                                $$->addChild(node2);
                                                $$->addChild($3);
                                            }
                                    
                                        } 

not_test: KEYWORD_NOT not_test { 
                                    TreeNode* node1 = new TreeNode($1);
                                    // $$->setlineno(yylineno);
                                    $$ = new TreeNode("not_test");
                                    $$->setlineno(yylineno);
                                    $$->addChild(node1);
                                    $$->addChild($2);
                                }
        | comparison    {
                            $$ = $1;
                        }

comparison:  comparison1 expr{
                                if($1 != nullptr)
                                {
                                    $$ = $1;
                                    $$->addChild($2);
                                }
                                else
                                {
                                    $$ = $2;
                                }
                            }
comparison1: {
                $$ = nullptr;
            }
            | comparison1 expr comp_op {
                                        $$ = $3;
                                        if($1 != nullptr)
                                        {
                                            $$->addChild($1);
                                            $1->addChild($2);
                                        }
                                        else
                                        {
                                            $$->addChild($2);
                                        }
                                    }

comp_op : '<' {
                $$ = new TreeNode($1);
                $$->setlineno(yylineno);  
                $$->setType("relop");
            }
        |'>' {
                $$ = new TreeNode($1);
                $$->setlineno(yylineno);  
                $$->setType("relop");
            }
        | OP_EQUALS {
                        $$ = new TreeNode($1);
                        $$->setlineno(yylineno);  
                        $$->setType("relop");
                    }
        | OP_GREATER_THAN_EQUALS {
                                    $$ = new TreeNode($1);
                                    $$->setlineno(yylineno);  
                                    $$->setType("relop");
                                }
        | OP_LESS_THAN_EQUALS {
                                    $$ = new TreeNode($1);
                                    $$->setlineno(yylineno);  
                                    $$->setType("relop");

                                }
        | OP_NOT_EQUALS {
                            $$ = new TreeNode($1);
                            $$->setlineno(yylineno);  
                             $$->setType("relop");

                        }

expr:  expr1 xor_expr {
                        if($1 != nullptr)
                        {
                            $$ = $1;
                            $$->addChild($2);
                        }
                        else
                        {
                            $$ = $2;
                        }
                    }
expr1 : {
            $$ = nullptr;
        }
        | expr1  xor_expr '|'{
                                $$ = new TreeNode($3);
                                $$->setlineno(yylineno);  
                                $$->setType("binary_op");
                                if($1 != nullptr)
                                {
                                    $$->addChild($1);
                                    $1->addChild($2);
                                }
                                else
                                {
                                    $$->addChild($2);
                                }
                            } 

xor_expr:  xor_expr1 and_expr {
                                if($1 != nullptr)
                                {
                                    $$ = $1;
                                    $$->addChild($2);
                                }
                                else
                                {
                                    $$ = $2;
                                }
                            }
xor_expr1 : {
                $$ = nullptr;
            }
            |xor_expr1 and_expr '^' {
                                        $$ = new TreeNode($3);
                                        $$->setlineno(yylineno);  
                                        $$->setType("binary_op");
                                        if($1 != nullptr)
                                        {
                                            $$->addChild($1);
                                            $1->addChild($2);
                                        }
                                        else
                                        {
                                            $$->addChild($2);
                                        }
                                    }

and_expr:  and_expr1 shift_expr{
                                    if($1 != nullptr)
                                    {
                                        $$ = $1;
                                        $$->addChild($2);
                                    }
                                    else
                                    {
                                        $$ = $2;
                                    }
                                }
and_expr1: {
                $$ = nullptr;
            }
            | and_expr1 shift_expr '&' {
                                        $$ = new TreeNode($3);
                                        $$->setlineno(yylineno);  
                                        $$->setType("binary_op");
                                        if($1 != nullptr)
                                        {
                                            $$->addChild($1);
                                            $1->addChild($2);
                                        }
                                        else
                                        {
                                            $$->addChild($2);
                                        }
                                    }

shift_expr: shift_expr1 arith_expr  {
                                        if($1 != nullptr)
                                        {
                                            $$ = $1;
                                            $$->addChild($2);
                                        }
                                        else
                                        {
                                            $$ = $2;
                                        }
                                    }
shift_expr1 : {
                $$ = nullptr;
            } 
            |shift_expr1 arith_expr shift_expr2 {
                                                    $$ = $3;
                                                    if($1 != nullptr)
                                                    {
                                                        $$->addChild($1);
                                                        $1->addChild($2);
                                                    }
                                                    else
                                                    {
                                                        $$->addChild($2);
                                                    }
                                                }
shift_expr2: OP_LEFT_SHIFT {
                                $$ = new TreeNode($1);
                                $$->setlineno(yylineno);  
                                $$->setType("binary_op");
                            }
            | OP_RIGHT_SHIFT {
                                $$ = new TreeNode($1);
                                $$->setlineno(yylineno);  
                                $$->setType("binary_op");
                            }


arith_expr:  arith_expr1 term{
                                if($1 != nullptr)
                                {
                                    $$ = $1;
                                    $$->addChild($2);
                                }
                                else
                                {
                                    $$ = $2;
                                }
                                
                            }
arith_expr1: {
                $$ = nullptr;
            }
            |arith_expr1 term arith_expr2  {

                                            $$ = $3;
                                            if($1 != nullptr)
                                            {
                                                $$->addChild($1);
                                                $1->addChild($2);
                                            }
                                            else
                                            {
                                                $$->addChild($2);
                                            }
                                        } 
arith_expr2: '+' {
                    $$ = new TreeNode($1);
                    $$->setlineno(yylineno);
                    $$->setType("binary_op");
                }
            |'-' {
                    $$ = new TreeNode($1);
                    $$->setlineno(yylineno);
                    $$->setType("binary_op");
                }

term: term1 factor {
                        if($1 != nullptr)
                        {
                            $$ = $1;
                            $$->addChild($2);
                        }
                        else
                        {
                            $$ = $2;
                        }
                    }
term1:  {
            $$ = nullptr;
        }
        | term1 factor term2 {
                                $$ = $3;
                                if($1 != nullptr)
                                {
                                    $$->addChild($1);
                                    $1->addChild($2);
                                }
                                else
                                {
                                    $$->addChild($2);
                                }
                            }
term2: '*'{ 
            $$ = new TreeNode($1);
            $$->setlineno(yylineno);            
            $$->setType("binary_op");
        }
        |'/'{
            $$ = new TreeNode($1);
            $$->setlineno(yylineno);  
            $$->setType("binary_op");
        }
        |'%'{ 
            $$ = new TreeNode($1);
            $$->setlineno(yylineno);  
            $$->setType("binary_op");
        }
        | OP_INT_DIVIDE{
            $$ = new TreeNode($1);
            $$->setlineno(yylineno);  
            $$->setType("binary_op");
        }   


factor: factor1 factor {
                        $$ = new TreeNode("factor");
                        $$->setlineno(yylineno);
                        $$->addChild($1);
                        $$->addChild($2);
                    }
        | power {
                    $$ = $1;
                }   
factor1: '+' {
                $$ = new TreeNode($1);
                $$->setlineno(yylineno);  
                $$->setType("unary_op");
            }
        |'-'{
            $$ = new TreeNode($1);
            $$->setlineno(yylineno);  
            $$->setType("unary_op");
        }
        |'~' {
            $$ = new TreeNode($1);
            $$->setlineno(yylineno);  
            $$->setType("unary_op");
        }

power: atom_expr power1 { 
                            if($2 != nullptr)
                            {
                                $$ = $2;
                                $2->addChildFront($1);
                            }
                            else
                            {
                                $$ = $1;
                            }
                        }
power1: {
            $$ = nullptr;
        } 
        | OP_POWER factor {
                            $$ = new TreeNode($1);
                            $$->setlineno(yylineno);  
                            $$->setType("binary_op");
                            $$->addChild($2);
                        }

atom_expr: atom atom_expr1 {
                                $$ = new TreeNode("atom_expr");
                                $$->setlineno(yylineno);
                                $$->addChild($1);
                                $$->addChild($2);
                            }
atom_expr1:  {
                $$ = nullptr;
            }
            | atom_expr1 trailer {
                                    $$ = new TreeNode("atom_expr1");
                                    $$->addChild($1);
                                    $$->addChild($2);
                                }

atom : '(' atom1 ')' {
                        TreeNode* node1 = new TreeNode($1);
                        TreeNode* node3 = new TreeNode($3);
                        $$ = new TreeNode("atom");
                        $$->addChild(node1);
                        $$->addChild($2);
                        $$->addChild(node3);
                    }
        | '[' atom1 ']' {
                            TreeNode* node1 = new TreeNode($1);
                            TreeNode* node3 = new TreeNode($3);
                            $$ = new TreeNode("atom");
                            $$->addChild(node1);
                            $$->addChild($2);
                            $$->addChild(node3);
                        }
        | NAME {
                    $$ = new TreeNode($1);
                    if(type_expect == true)
                    {
                        type_expect_list.push_back(string($1));
                    }
                    
                }
        | NUMBER {
                    $$ = new TreeNode($1);
                }
        | atom2 {
                    $$ = $1;
                }
        | KEYWORD_NONE {
                            $$ = new TreeNode($1);
                            if(type_expect == true)
                            {
                                type_expect_list.push_back(string($1));
                            }
                        }
        | KEYWORD_TRUE {
                            $$ = new TreeNode($1);
                        }
        | KEYWORD_FALSE {
                            $$ = new TreeNode($1);

                        }
atom1 : {
            $$ = nullptr;
        }
        | testlist_comp {
                            $$ = $1;
                        }
atom2 : STRING {
                $$ = new TreeNode($1);
            }
        | atom2 STRING {
                            TreeNode* node2 = new TreeNode($2);
                            $$ = new TreeNode("atom2");
                            $$->addChild($1);
                            $$->addChild(node2);
                        }

testlist_comp : test testlist_comp2 testlist_comp1 {
                                                        $$ = new TreeNode("testlist_comp");
                                                        $$->addChild($1);
                                                        $$->addChild($2);
                                                        $$->addChild($3);
                }
testlist_comp1 :  ',' {
                    $$ = new TreeNode($1);
                }
                | {
                    $$ = nullptr;
                }
testlist_comp2 : {
                    $$ = nullptr;
                }
                | testlist_comp2 ',' test {
                                            TreeNode* node2 = new TreeNode($2);
                                            $$ = new TreeNode("testlist_comp2");
                                            $$->addChild($1);
                                            $$->addChild(node2);
                                            $$->addChild($3);
                                        }

trailer : '(' trailer1 {
                        TreeNode* node1 = new TreeNode($1);
                        $$ = new TreeNode("trailer");
                        $$->addChild(node1);
                        $$->addChild($2);
                    }
        | '[' subscriptlist ']' {
                                    TreeNode* node1 = new TreeNode($1);
                                    TreeNode* node3 = new TreeNode($3);
                                    $$ = new TreeNode("trailer");
                                    $$->addChild(node1);
                                    $$->addChild($2);
                                    $$->addChild(node3);
                                }
        | '.' NAME {
                    TreeNode* node1 = new TreeNode($1);
                    node1->setType("binary_op");
                    TreeNode* node2 = new TreeNode($2);
                    $$ = new TreeNode("trailer");
                    $$->addChild(node1);
                    $$->addChild(node2);
                }
trailer1 : arglist ')' {
                            TreeNode* node2 = new TreeNode($2);
                            $$ = new TreeNode("trailer1");
                            $$->addChild($1);
                            $$->addChild(node2);
                        }
        | ')' {
               $$ = new TreeNode($1);
            }
subscriptlist :subscript subscriptlist2 subscriptlist1 {
                                                            $$ = new TreeNode("subscriptlist");
                                                            $$->addChild($1);
                                                            $$->addChild($2);
                                                            $$->addChild($3);
                                                        
                }
subscriptlist1  : {
                    $$ = nullptr;
                }
                | ',' {
                        $$ = new TreeNode($1);
                    
                }
subscriptlist2 : {
                    $$ = nullptr;
                } 
                | subscriptlist2 ',' subscript {
                                                TreeNode* node2 = new TreeNode($2);
                                                $$ = new TreeNode("subscriptlist2");
                                                $$->addChild($1);
                                                $$->addChild(node2);
                                                $$->addChild($3);
                                            }

subscript : test subscript1 {
                                $$ = new TreeNode("subscript");
                                $$->addChild($1);
                                $$->addChild($2);
                            }
            | ':' subscript2 {
                                TreeNode* node1 = new TreeNode($1);
                                $$ = new TreeNode("subscript");
                                $$->addChild(node1);
                                $$->addChild($2);
                            
            }

subscript1 : {
                $$ = nullptr;
            }
            | ':' subscript2 {
                                TreeNode* node1 = new TreeNode($1);
                                $$ = new TreeNode("subscript1");
                                $$->addChild(node1);
                                $$->addChild($2);
            }
subscript2 : test {
                    $$ = $1;
            }
            | {
                $$ = nullptr;
            }
exprlist :  expr exprlist2 exprlist1 {
                                            $$ = new TreeNode("exprlist");
                                            $$->addChild($1);
                                            $$->addChild($2);
                                            $$->addChild($3);
                                        
            }
exprlist1 : {
                $$ = nullptr;
            }
            | ','{
                    $$ = new TreeNode($1);
                }
exprlist2 : {
                $$ = nullptr;
            } 
            | exprlist2 ',' expr {
                                    TreeNode* node2 = new TreeNode($2);
                                    $$ = new TreeNode("exprlist2");
                                    $$->addChild($1);
                                    $$->addChild(node2);
                                    $$->addChild($3);
                                }

testlist : test testlist1 testlist3 {
                                            $$ = new TreeNode("testlist");
                                            $$->addChild($1);
                                            $$->addChild($2);
                                            $$->addChild($3);
                                        }  
testlist3 : ',' {
                $$  = new TreeNode($1);
            }
            | {
                $$ = nullptr;
            
            }
testlist1 :  {
                $$ = nullptr;
            }
            | testlist1 ',' test {
                                    TreeNode* node2 = new TreeNode($2);
                                    $$ = new TreeNode("testlist1");
                                    $$->addChild($1);
                                    $$->addChild(node2);
                                    $$->addChild($3);
                                }

classdef : KEYWORD_CLASS NAME {
                        if (currentTable->lookup(string($2))!=NULL){
                            cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << string($2) << " is not allowed. Previous defined at line "<< currentTable->lookup(string($2))->get_lineno() << endl;
                            exit(1);
                        }
                        SymbolTable* newTable = new SymbolTable(ST_Type::st_class,yylineno, currentTable,STentry_Type::ste_none,string($2));
                        STentry* entry = new STentry(string($2), STentry_Type::ste_class_def, yylineno, (void*)newTable);
                        currentTable->insert(string($2), entry);
                        class_names.push_back(string($2));
                        currentTable = newTable;
                }   
  classdef1 ':' suite {
            TreeNode* node1 = new TreeNode($1);
            TreeNode* node2 = new TreeNode($2);
            TreeNode* node3 = new TreeNode($5);
            $$ = new TreeNode("classdef");
            $$->setlineno(yylineno);
            $$->addChild(node1);
            $$->addChild(node2);
            $$->addChild($4);
            $$->addChild(node3);
            $$->addChild($6);
            currentTable = globalTable;
            }
classdef1 : {
            $$ = nullptr;
            }
    | '(' arglist_class ')'{
                        TreeNode* node1 = new TreeNode($1);
                        TreeNode* node2 = new TreeNode($3);
                        $$ = new TreeNode("classdef1");
                        $$->addChild(node1);
                        $$->addChild($2);
                        $$->addChild(node2);
                    }
arglist_class : argument_class arglist_class1 {
                                                $$ = new TreeNode("arglist_class");
                                                $$->addChild($1);
                                                $$->addChild($2);
            }
arglist_class1 : {
                    $$ = nullptr;
                }
                | arglist_class1 ',' argument_class {
                                    TreeNode* node2 = new TreeNode($2);
                                    $$ = new TreeNode("arglist_class1");
                                    $$->addChild($1);
                                    $$->addChild(node2);
                                    $$->addChild($3);
                }
argument_class : test {
                $$ = $1;
                TreeNode* temp = $1;
                // string name = getFirstTerminalValue(temp);
                vector<TreeNode*> values;
                getAllTerminalValue(temp, values);
                string name = values[0]->value;
                values.clear();
               // this argument is a class to be inherited in my current class
                if (globalTable->lookup(name) == NULL){
                    cout <<"Line "<< yylineno << ":Name Error : Class " << name << " is not defined" << endl;
                    exit(1);
                }
                //copy the symbol table of the class to the current class
                SymbolTable* parentClass = (SymbolTable*)globalTable->lookup(name)->get_nested_table();
                // cout << "offset of currentTable is "  << currentTable->get_offset() << endl; 
                currentTable->copySymbolTable(parentClass);
                // cout << "offset of currentTable is "  << currentTable->get_offset() << endl;
}
arglist: argument arglist1 arglist2 {
                                $$ = new TreeNode("arglist");
                                $$->addChild($1);
                                $$->addChild($2);
                                $$->addChild($3);
        }
arglist2: ',' {
                $$ = new TreeNode($1);
            }
        |{
            $$ = nullptr;
        
        }
arglist1: {
            $$ = nullptr;
        } 
        | arglist1 ',' argument {
                                    TreeNode* node2 = new TreeNode($2);
                                    $$ = new TreeNode("arglist1");
                                    $$->addChild($1);
                                    $$->addChild(node2);
                                    $$->addChild($3);
                                }

argument : test argument1 {
                                // $$ = new TreeNode("argument");
                                // $$->addChild($1);
                                // $$->addChild($2);
                                if ($2 == nullptr){
                                    $$ = $1;
                                }
                                else {
                                    // TreeNode* node1 = new TreeNode($1);
                                    $$ = $2;
                                    $2->addChildFront($1);
                                }
                            }  
            /* | '*' test {
                            TreeNode* node1 = new TreeNode($1);
                            $$ = new TreeNode("argument");
                            $$->addChild(node1);
                            $$->addChild($2);
                        }
            | OP_POWER test {
                                TreeNode* node1 = new TreeNode($1);
                                $$ = new TreeNode("argument");
                                $$->addChild(node1);
                                $$->addChild($2);
                            } */
             
argument1 : {
                $$ =nullptr;
        }
        |'=' test {
                    // TreeNode* node1 = new TreeNode($1);
                    // $$ = new TreeNode("argument1");
                    // $$->addChild(node1);
                    // $$->addChild($2);
                    $$ = new TreeNode($1);
                    $$->setType("assign");
                    $$->setlineno(yylineno);
                    $$->addChild($2);
                    
                }
/* argument : test  {
                $$ = $1;
                TreeNode* temp = $1;
                // string name = getFirstTerminalValue(temp);
                vector<string> values;
                getAllTerminalValue(temp, values);
                string name = values[0];
                values.clear();
               // this argument is a class to be inherited in my current class
                if (globalTable->lookup(name) == NULL){
                    cout <<"Line "<< yylineno << ":Name Error : Class " << name << " is not defined" << endl;
                    exit(1);
                }
                //copy the symbol table of the class to the current class
                SymbolTable* parentClass = (SymbolTable*)globalTable->lookup(name);
                currentTable->copySymbolTable(parentClass);
}*/ 
                            
            /* | '*' test {
                            TreeNode* node1 = new TreeNode($1);
                            $$ = new TreeNode("argument");
                            $$->addChild(node1);
                            $$->addChild($2);
                        }
            | OP_POWER test {
                                TreeNode* node1 = new TreeNode($1);
                                $$ = new TreeNode("argument");
                                $$->addChild(node1);
                                $$->addChild($2);
                            } */
             
%%

void print_options(){
	cout<<"Usage: parser [OPTIONS] file...\n\n";
	cout<<"Options:\n";
	cout<<"\t--help\t\t\tDisplay available options\n";
	cout<<"\t-output <file>\t\tdump the dot script generated in <file> \n";
    cout<<"\t-input <file>\t\tRead the input from <file>\n";
    cout <<"\t-verbose \t\tTo enable verbose\n";
    cout<<"\tIf no output file is specified automatic parser_tree.dot is generated\n";
    cout<<"\tIf no input file is specified, the program will give error\n";
    cout<<"\tIf multiple input file are specified it will process the first file or throw error\n";
	cout<<"\n\n";
}
void print_error(){
	cout<<"\033[1;31mError Found\033[0m"<<endl;
}
void yyerror(const char *error) 
{
    printf("ERROR:%s at line number: %d\n", error, yylineno);
    exit(0);
}
int main(int argc, char* argv[]) {
    string output_file_name,input_file_name;
    FILE* input_file;
    if (argc < 2) {
        print_error();
        cout<<"Too few arguments\n";
        print_options();
        return 0;
    }

    for(int i = 1; i<argc; i++){
		if(!strcmp(argv[i], "--help")){
			print_options();
			return 0;
		}
	}
    for(int i = 1; i<argc; i++){
        if(!strcmp(argv[i], "-output")){
            output_file_name = argv[i+1];
            i++;
        }
        else if(!strcmp(argv[i], "-input")){
            input_file_name = argv[i+1];
            input_file = fopen(argv[i+1], "r");
            i++;
        }
        else if (!strcmp(argv[i],"-verbose")){
            verbose = true;
        }
		else{
            print_error();
            cout<<"Invalid argument\n";
            print_options();
            return 0;
        }
	}
    
    if (!input_file) {
        perror("fopen");
        return 1;
    }
    yyin = input_file;
    if (verbose){
        cout<<"Parsing the file :" << input_file_name <<endl;
    }

    initializeGlobalSymbolTable();
    yyparse();
    
    if(output_file_name.empty()){
        output_file_name = "parser_tree.dot";
    }
    if (verbose) {
        cout << "Starting to clean the AST" << endl;
    }
    cleanParseTree(root); 
    /* createParentAST(root); */
    /* root->printTree(root); */
    if (verbose) {
        cout << "AST cleaned successfully" << endl;
        cout << "Starting to create the dot file" << endl;
    }
    ofstream dotFile(output_file_name.c_str());
    dotFile << "digraph ParseTree {" << endl;
    createParseTreeDot(root, dotFile);
    if (verbose){
        cout << "Dot file created successfully" << endl;
    }
    dotFile << "}" << endl;
    dotFile.close();
    
    // print symbol table
    ofstream outfile1("symbol_table.csv");
    ofstream outfile2("symbol_table.txt");

    if (outfile1.is_open()) {
        outfile1 << "Name," << "Line No.," << "Type," <<  "is_list," << "class_obj_name,"  << "nested_table," << "Offset," << "Width" << endl;
        globalTable->print_table_csv(outfile1);

        outfile1.close();
        if (verbose){
        cout << "Symbol table CSV file generated successfully." << endl;
        }
    } 
    else {
        cout << "Unable to open file for writing." << endl;
        return 0;
    }
    if (outfile2.is_open()) {
      
        globalTable->print_table_txt(outfile2);

        outfile2.close();
        if (verbose){
        cout << "txt file generated successfully." << endl;
        }
    } 
    else {
        cout << "Unable to open file for writing." << endl;
        return 0;
    }

    if(verbose)
        cout << "generating 3AC..." << endl;
    generate_3ac(root, globalTable);
    if(verbose)
        cout << "3AC generated successfully" << endl;
    updatelineofquads();
    print_quads_to_file("quads_output.txt");
    // x86 codegen
    if (verbose)
        cout << "Generating x86 code..." << endl;
    codegen* gen = new codegen();
    gen->gen_global();
    gen->gen_text();
    gen->print_code("asm.s");
    if (verbose)
        cout << "x86 code generated successfully." << endl;
    delete root;
    fclose(input_file);
    return 0;
}
