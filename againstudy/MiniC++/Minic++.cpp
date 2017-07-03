//listing 1
// Recursive descent parser for integer expressions. 
// 
#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cctype> 
#include "mccommon.h" 
 
using namespace std; 
 
// Keyword lookup table. 
// Keywords must be entered lowercase. 
struct commands { 
  char command[20]; 
  token_ireps tok; 
} com_table[] = { 
  "if", IF,  
  "else", ELSE, 
  "for", FOR, 
  "do", DO, 
  "while", WHILE, 
  "char", CHAR, 
  "int", INT, 
  "return", RETURN, 
  "switch", SWITCH, 
  "break", BREAK, 
  "case", CASE, 
  "cout", COUT, 
  "cin", CIN, 
  "", END  // mark end of table 
}; 
 
// This structure links a library function name 
// with a pointer to that function. 
struct intern_func_type { 
  char *f_name; // function name 
  int (*p)();   // pointer to the function 
} intern_func[] = { 
  "getchar", call_getchar, 
  "putchar", call_putchar, 
  "abs", call_abs, 
  "rand", call_rand, 
  "", 0  // null terminate the list 
}; 
 
// Entry point into parser. 
void eval_exp(int &value) 
{ 
  get_token(); 
 
  if(!*token) { 
    throw InterpExc(NO_EXP); 
  } 
 
  if(*token == ';') { 
    value = 0; // empty expression 
    return; 
  } 
 
  eval_exp0(value); 
 
  putback(); // return last token read to input stream 
} 
 
// Process an assignment expression. 
void eval_exp0(int &value) 
{ 
  // temp holds name of var receiving the assignment. 
  char temp[MAX_ID_LEN+1];  
 
  tok_types temp_tok; 
 
  if(token_type == IDENTIFIER) { 
    if(is_var(token)) { // if a var, see if assignment 
      strcpy(temp, token); 
      temp_tok = token_type; 
      get_token(); 
      if(*token == '=') { // is an assignment 
        get_token(); 
        eval_exp0(value); // get value to assign 
        assign_var(temp, value); // assign the value 
        return; 
      } 
      else { // not an assignment 
        putback(); // restore original token 
        strcpy(token, temp); 
        token_type = temp_tok; 
      } 
    } 
  } 
  eval_exp1(value); 
} 
 
// Process relational operators. 
void eval_exp1(int &value) 
{ 
  int partial_value; 
  char op; 
  char relops[] = { 
    LT, LE, GT, GE, EQ, NE, 0 
  }; 
 
  eval_exp2(value); 
 
  op = *token; 
  if(strchr(relops, op)) { 
    get_token(); 
    eval_exp2(partial_value); 
 
    switch(op) { // perform the relational operation 
      case LT: 
        value = value < partial_value; 
        break; 
      case LE: 
        value = value <= partial_value; 
        break; 
      case GT: 
        value = value > partial_value; 
        break; 
      case GE: 
        value = value >= partial_value; 
        break; 
      case EQ: 
        value = value == partial_value; 
        break; 
      case NE: 
        value = value != partial_value; 
        break; 
    } 
  } 
} 
 
// Add or subtract two terms. 
void eval_exp2(int &value) 
{ 
  char  op; 
  int partial_value; 
  char okops[] = { 
    '(', INC, DEC, '-', '+', 0 
  }; 
 
  eval_exp3(value); 
 
  while((op = *token) == '+' || op == '-') { 
    get_token(); 
 
    if(token_type == DELIMITER && 
       !strchr(okops, *token)) 
         throw InterpExc(SYNTAX); 
 
    eval_exp3(partial_value); 
 
    switch(op) { // add or subtract 
      case '-': 
        value = value - partial_value; 
        break; 
      case '+': 
        value = value + partial_value; 
        break; 
    } 
  } 
} 
 
// Multiply or divide two factors. 
void eval_exp3(int &value) 
{ 
  char  op; 
  int partial_value, t; 
  char okops[] = { 
    '(', INC, DEC, '-', '+', 0 
  }; 
 
  eval_exp4(value); 
 
  while((op = *token) == '*' || op == '/' 
         || op == '%') { 
    get_token(); 
 
    if(token_type == DELIMITER && 
       !strchr(okops, *token)) 
         throw InterpExc(SYNTAX); 
 
    eval_exp4(partial_value); 
 
    switch(op) { // mul, div, or modulus 
      case '*': 
        value = value * partial_value; 
        break; 
      case '/': 
        if(partial_value == 0) 
          throw InterpExc(DIV_BY_ZERO);        
        value = (value) / partial_value; 
        break; 
      case '%': 
        t = (value) / partial_value; 
        value = value - (t * partial_value); 
        break; 
    } 
  } 
} 
 
// Is a unary +, -, ++, or --. 
void eval_exp4(int &value) 
{ 
  char  op; 
  char temp; 
 
  op = '\0'; 
  if(*token == '+' || *token == '-' || 
     *token == INC || *token == DEC) 
  { 
    temp = *token; 
    op = *token; 
    get_token(); 
    if(temp == INC) 
      assign_var(token, find_var(token)+1); 
    if(temp == DEC) 
      assign_var(token, find_var(token)-1); 
  } 
 
  eval_exp5(value); 
  if(op == '-') value = -(value); 
} 
 
// Process parenthesized expression. 
void eval_exp5(int &value) 
{ 
 
  if((*token == '(')) { 
    get_token(); 
 
    eval_exp0(value); // get subexpression 
 
    if(*token != ')') 
      throw InterpExc(PAREN_EXPECTED); 
    get_token(); 
  } 
  else 
    atom(value); 
} 
 
// Find value of number, variable, or function. 
void atom(int &value) 
{ 
  int i; 
  char temp[MAX_ID_LEN+1]; 
 
  switch(token_type) { 
    case IDENTIFIER: 
      i = internal_func(token); 
      if(i != -1) { 
        // Call "standard library" function. 
        value = (*intern_func[i].p)(); 
      } 
      else if(find_func(token)) { 
        // Call programmer-created function. 
        call(); 
        value = ret_value; 
      } 
      else { 
        value = find_var(token); // get var's value 
        strcpy(temp, token); // save variable name 
 
        // Check for ++ or --. 
        get_token(); 
        if(*token == INC || *token == DEC) { 
          if(*token == INC) 
            assign_var(temp, find_var(temp)+1); 
          else 
            assign_var(temp, find_var(temp)-1); 
        } else putback();          
      } 
 
      get_token(); 
      return; 
    case NUMBER: // is numeric constant 
      value = atoi(token); 
      get_token(); 
 
      return; 
    case DELIMITER: // see if character constant 
      if(*token == '\'') { 
        value = *prog; 
        prog++; 
        if(*prog!='\'') 
          throw InterpExc(QUOTE_EXPECTED); 
 
        prog++; 
        get_token(); 
 
        return ; 
      } 
      if(*token==')') return; // process empty expression 
      else throw InterpExc(SYNTAX);  // otherwise, syntax error 
    default: 
      throw InterpExc(SYNTAX); // syntax error 
  } 
} 
 
// Display an error message. 
void sntx_err(error_msg error) 
{ 
  char *p, *temp; 
  int linecount = 0; 
 
  static char *e[]= { 
    "Syntax error", 
    "No expression present", 
    "Not a variable", 
    "Duplicate variable name", 
    "Duplicate function name", 
    "Semicolon expected", 
    "Unbalanced braces", 
    "Function undefined", 
    "Type specifier expected", 
    "Return without call", 
    "Parentheses expected", 
    "While expected", 
    "Closing quote expected", 
    "Division by zero", 
    "{ expected (control statements must use blocks)", 
    "Colon expected" 
  }; 
 
  // Display error and line number. 
  cout << "\n" << e[error]; 
  p = p_buf; 
  while(p != prog) { // find line number of error 
    p++; 
    if(*p == '\r') { 
      linecount++; 
    } 
  } 
  cout << " in line " << linecount << endl; 
 
  temp = p; 
  while(p > p_buf && *p != '\n') p--; 
 
  // Display offending line. 
  while(p <= temp) 
    cout << *p++; 
 
  cout << endl; 
} 
 
// Get a token. 
tok_types get_token() 
{ 
 
  char *temp; 
 
  token_type = UNDEFTT; tok = UNDEFTOK; 
 
  temp = token; 
  *temp = '\0'; 
 
  // Skip over white space. 
  while(isspace(*prog) && *prog) ++prog; 
 
  // Skip over newline. 
  while(*prog == '\r') { 
    ++prog; 
    ++prog; 
    // Again, skip over white space. 
    while(isspace(*prog) && *prog) ++prog; 
  } 
 
  // Check for end of program. 
  if(*prog == '\0') { 
    *token = '\0'; 
    tok = END; 
    return (token_type = DELIMITER); 
  } 
 
  // Check for block delimiters. 
  if(strchr("{}", *prog)) {  
    *temp = *prog; 
    temp++; 
    *temp = '\0'; 
    prog++; 
    return (token_type = BLOCK); 
  } 
 
  // Look for comments. 
  if(*prog == '/') 
    if(*(prog+1) == '*') { // is a /* comment 
      prog += 2; 
      do { // find end of comment 
        while(*prog != '*') prog++; 
        prog++; 
      } while (*prog != '/'); 
      prog++; 
      return (token_type = DELIMITER); 
    } else if(*(prog+1) == '/') { // is a // comment 
      prog += 2; 
      // Find end of comment. 
      while(*prog != '\r' && *prog != '\0') prog++; 
      if(*prog == '\r') prog +=2; 
      return (token_type = DELIMITER); 
    } 
 
  // Check for double-ops. 
  if(strchr("!<>=+-", *prog)) {  
    switch(*prog) { 
      case '=': 
        if(*(prog+1) == '=') { 
          prog++; prog++; 
          *temp = EQ; 
          temp++; *temp = EQ; temp++; 
          *temp = '\0'; 
        } 
        break; 
      case '!': 
        if(*(prog+1) == '=') { 
          prog++; prog++; 
          *temp = NE; 
          temp++; *temp = NE; temp++; 
          *temp = '\0'; 
        } 
        break; 
      case '<': 
        if(*(prog+1) == '=') { 
          prog++; prog++; 
          *temp = LE; temp++; *temp = LE; 
        } 
        else if(*(prog+1) == '<') { 
          prog++; prog++; 
          *temp = LS; temp++; *temp = LS; 
        } 
        else { 
          prog++; 
          *temp = LT; 
        } 
        temp++; 
        *temp = '\0'; 
        break; 
      case '>': 
        if(*(prog+1) == '=') { 
          prog++; prog++; 
          *temp = GE; temp++; *temp = GE; 
        } else if(*(prog+1) == '>') { 
          prog++; prog++; 
          *temp = RS; temp++; *temp = RS; 
        } 
        else { 
          prog++; 
          *temp = GT; 
        } 
        temp++; 
        *temp = '\0'; 
        break; 
      case '+': 
        if(*(prog+1) == '+') { 
          prog++; prog++; 
          *temp = INC; temp++; *temp = INC; 
          temp++; 
          *temp = '\0'; 
        } 
        break; 
      case '-': 
        if(*(prog+1) == '-') { 
          prog++; prog++; 
          *temp = DEC; temp++; *temp = DEC; 
          temp++; 
          *temp = '\0'; 
        } 
        break; 
    } 
 
    if(*token) return(token_type = DELIMITER); 
  } 
 
  // Check for other delimiters. 
  if(strchr("+-*^/%=;:(),'", *prog)) { 
    *temp = *prog; 
    prog++; 
    temp++; 
    *temp = '\0'; 
    return (token_type = DELIMITER); 
  } 
 
  // Read a quoted string. 
  if(*prog == '"') { 
    prog++; 
    while(*prog != '"' && *prog != '\r' && *prog) { 
      // Check for \n escape sequence. 
      if(*prog == '\\') { 
        if(*(prog+1) == 'n') { 
          prog++; 
          *temp++ = '\n'; 
        } 
      } 
      else if((temp - token) < MAX_T_LEN)  
        *temp++ = *prog; 
 
      prog++; 
    } 
    if(*prog == '\r' || *prog == 0) 
      throw InterpExc(SYNTAX); 
    prog++; *temp = '\0'; 
    return (token_type = STRING); 
  } 
 
  // Read an integer number. 
  if(isdigit(*prog)) { 
    while(!isdelim(*prog)) { 
      if((temp - token) < MAX_ID_LEN)  
        *temp++ = *prog; 
      prog++; 
    } 
    *temp = '\0'; 
    return (token_type = NUMBER); 
  } 
 
  // Read identifier or keyword. 
  if(isalpha(*prog)) { 
    while(!isdelim(*prog)) { 
      if((temp - token) < MAX_ID_LEN)  
        *temp++ = *prog; 
      prog++; 
    } 
    token_type = TEMP; 
  } 
 
  *temp = '\0'; 
 
  // Determine if token is a keyword or identifier. 
  if(token_type == TEMP) { 
    tok = look_up(token); // convert to internal form 
    if(tok) token_type = KEYWORD; // is a keyword 
    else token_type = IDENTIFIER; 
  } 
 
  // Check for unidentified character in file. 
  if(token_type == UNDEFTT) 
    throw InterpExc(SYNTAX); 
 
  return token_type; 
} 
 
// Return a token to input stream. 
void putback() 
{ 
  char *t; 
 
  t = token; 
  for(; *t; t++) prog--; 
} 
 
// Look up a token's internal representation in the 
// token table. 
token_ireps look_up(char *s) 
{ 
  int i; 
  char *p; 
 
  // Convert to lowercase. 
  p = s; 
  while(*p) { *p = tolower(*p); p++; } 
 
  // See if token is in table. 
  for(i=0; *com_table[i].command; i++) { 
    if(!strcmp(com_table[i].command, s)) 
      return com_table[i].tok; 
  } 
 
  return UNDEFTOK; // unknown command 
} 
 
// Return index of internal library function or -1 if 
// not found. 
int internal_func(char *s) 
{ 
  int i; 
 
  for(i=0; intern_func[i].f_name[0]; i++) { 
    if(!strcmp(intern_func[i].f_name, s))  return i; 
  } 
  return -1; 
} 
 
// Return true if c is a delimiter. 
bool isdelim(char c) 
{ 
  if(strchr(" !:;,+-<>'/*%^=()", c) || c == 9 || 
     c == '\r' || c == 0) return true; 
  return false; 
}

listing 2
// A Mini C++ interpreter. 
 
#include <iostream> 
#include <fstream> 
#include <new> 
#include <stack> 
#include <vector> 
#include <cstring> 
#include <cstdlib> 
#include <cctype> 
#include "mccommon.h" 
 
using namespace std; 
 
char *prog;  // current execution point in source code  
char *p_buf; // points to start of program buffer 
 
// This structure encapsulates the info 
// associated with variables. 
struct var_type { 
  char var_name[MAX_ID_LEN+1]; // name 
  token_ireps v_type; // data type 
  int value; // value  
}; 
 
// This vector holds info for global variables. 
vector<var_type> global_vars; 
 
// This vector holds info for local variables 
// and parameters. 
vector<var_type> local_var_stack; 
 
// This structure encapsulates function info. 
struct func_type { 
  char func_name[MAX_ID_LEN+1]; // name 
  token_ireps ret_type; // return type 
  char *loc; // location of entry point in program  
}; 
 
// This vector holds info about functions. 
vector<func_type> func_table; 
 
// Stack for managing function scope. 
stack<int> func_call_stack; 
 
// Stack for managing nested scopes. 
stack<int> nest_scope_stack; 
 
char token[MAX_T_LEN+1]; // current token 
tok_types token_type; // token type 
token_ireps tok; // internal representation 
 
int ret_value; // function return value 
 
bool breakfound = false; // true if break encountered 
 
int main(int argc, char *argv[]) 
{ 
  if(argc != 2) { 
    cout << "Usage: minicpp <filename>\n"; 
    return 1; 
  } 
 
  // Allocate memory for the program. 
  try { 
    p_buf = new char[PROG_SIZE]; 
  } catch (bad_alloc exc) { 
    cout << "Could Not Allocate Program Buffer\n"; 
    return 1; 
  } 
 
  // Load the program to execute. 
  if(!load_program(p_buf, argv[1])) return 1; 
 
  // Set program pointer to start of program buffer. 
  prog = p_buf; 
 
  try { 
    // Find the location of all functions 
    // and global variables in the program. 
    prescan(); 
 
    // Next, set up the call to main(). 
 
    // Find program starting point. 
    prog = find_func("main"); 
 
    // Check for incorrect or missing main() function. 
    if(!prog) {  
      cout << "main() Not Found\n"; 
      return 1; 
    } 
 
    // Back up to opening (. 
    prog--; 
 
    // Set the first token to main 
    strcpy(token, "main"); 
 
    // Call main() to start interpreting. 
    call(); 
  }  
  catch(InterpExc exc) { 
    sntx_err(exc.get_err()); 
    return 1; 
  } 
  catch(bad_alloc exc) { 
    cout << "Out Of Memory\n"; 
    return 1; 
  } 
 
  return ret_value; 
} 
 
// Load a program. 
bool load_program(char *p, char *fname) 
{ 
  int i=0; 
 
  ifstream in(fname, ios::in | ios::binary); 
  if(!in) { 
    cout << "Cannot Open file.\n"; 
    return false; 
  } 
 
  do { 
    *p = in.get(); 
    p++; i++; 
  } while(!in.eof() && i < PROG_SIZE); 
 
  if(i == PROG_SIZE) { 
    cout << "Program Too Big\n"; 
    return false; 
  } 
 
  // Null terminate the program. Skip any EOF 
  // mark if present in the file. 
  if(*(p-2) == 0x1a) *(p-2) = '\0'; 
  else *(p-1) = '\0'; 
 
  in.close(); 
 
  return true; 
} 
 
// Find the location of all functions in the program 
// and store global variables.  
void prescan() 
{ 
  char *p, *tp; 
  char temp[MAX_ID_LEN+1]; 
  token_ireps datatype;  
  func_type ft; 
 
  // When brace is 0, the current source position 
  // is outside of any function.  
  int brace = 0;  
 
  p = prog; 
 
  do { 
    // Bypass code inside functions 
    while(brace) { 
      get_token(); 
      if(tok == END) throw InterpExc(UNBAL_BRACES); 
      if(*token == '{') brace++; 
      if(*token == '}') brace--; 
    } 
 
    tp = prog; // save current position 
    get_token(); 
 
    // See if global var type or function return type. 
    if(tok==CHAR || tok==INT) {  
      datatype = tok; // save data type 
      get_token(); 
 
      if(token_type == IDENTIFIER) { 
        strcpy(temp, token); 
        get_token(); 
 
        if(*token != '(') { // must be global var 
          prog = tp; // return to start of declaration 
          decl_global(); 
        } 
        else if(*token == '(') { // must be a function 
 
          // See if function already defined. 
          for(unsigned i=0; i < func_table.size(); i++) 
            if(!strcmp(func_table[i].func_name, temp)) 
              throw InterpExc(DUP_FUNC); 
 
          ft.loc = prog; 
          ft.ret_type = datatype; 
          strcpy(ft.func_name, temp); 
          func_table.push_back(ft); 
 
          do { 
            get_token(); 
          } while(*token != ')'); 
          // Next token will now be opening curly  
          // brace of function. 
        } 
        else putback(); 
      } 
    } 
    else { 
      if(*token == '{') brace++; 
      if(*token == '}') brace--; 
    } 
  } while(tok != END); 
  if(brace) throw InterpExc(UNBAL_BRACES); 
  prog = p; 
} 
 
// Interpret a single statement or block of code. When 
// interp() returns from its initial call, the final 
// brace (or a return) in main() has been encountered. 
void interp() 
{ 
  int value; 
  int block = 0; 
 
  do { 
    // Don't interpret until break is handled. 
    if(breakfound) return; 
 
    token_type = get_token(); 
 
    // See what kind of token is up. 
    if(token_type == IDENTIFIER || 
       *token == INC || *token == DEC) 
    { 
      // Not a keyword, so process expression.  
      putback();  // restore token to input stream for 
                  // further processing by eval_exp() 
      eval_exp(value); // process the expression 
      if(*token != ';') throw InterpExc(SEMI_EXPECTED); 
    } 
    else if(token_type==BLOCK) { // block delimiter? 
      if(*token == '{') { // is a block 
        block = 1; // interpreting block, not statement 
        // Record nested scope. 
        nest_scope_stack.push(local_var_stack.size()); 
      } 
      else { // is a }, so reset scope and return 
        // Reset nested scope. 
        local_var_stack.resize(nest_scope_stack.top()); 
        nest_scope_stack.pop(); 
        return; 
      } 
    } 
    else // is keyword 
      switch(tok) { 
        case CHAR: 
        case INT:     // declare local variables 
          putback(); 
          decl_local(); 
          break; 
        case RETURN:  // return from function call 
          func_ret(); 
          return; 
        case IF:      // process an if statement 
          exec_if(); 
          break; 
        case ELSE:    // process an else statement 
          find_eob(); // find end of else block 
                      // and continue execution 
          break; 
        case WHILE:   // process a while loop 
          exec_while(); 
          break; 
        case DO:      // process a do-while loop 
          exec_do(); 
          break; 
        case FOR:     // process a for loop 
          exec_for(); 
          break; 
        case BREAK:   // handle break 
          breakfound = true; 
 
          // Reset nested scope. 
          local_var_stack.resize(nest_scope_stack.top()); 
          nest_scope_stack.pop(); 
          return; 
        case SWITCH:  // handle a switch statement 
          exec_switch(); 
          break; 
        case COUT:    // handle console output 
          exec_cout(); 
          break; 
        case CIN:     // handle console input 
          exec_cin(); 
          break; 
        case END: 
          exit(0); 
      } 
  } while (tok != END && block); 
  return; 
} 
 
// Return the entry point of the specified function. 
// Return NULL if not found. 
char *find_func(char *name) 
{ 
  unsigned i; 
 
  for(i=0; i < func_table.size(); i++) 
    if(!strcmp(name, func_table[i].func_name)) 
      return func_table[i].loc; 
 
  return NULL; 
} 
 
// Declare a global variable. 
void decl_global() 
{ 
  token_ireps vartype; 
  var_type vt; 
 
  get_token(); // get type 
 
  vartype = tok; // save var type 
 
  // Process comma-separated list. 
  do { 
    vt.v_type = vartype; 
    vt.value = 0; // init to 0 
    get_token(); // get name 
 
    // See if variable is a duplicate. 
    for(unsigned i=0; i < global_vars.size(); i++) 
      if(!strcmp(global_vars[i].var_name, token)) 
        throw InterpExc(DUP_VAR); 
 
    strcpy(vt.var_name, token); 
    global_vars.push_back(vt); 
 
    get_token(); 
  } while(*token == ','); 
 
  if(*token != ';') throw InterpExc(SEMI_EXPECTED); 
} 
 
// Declare a local variable. 
void decl_local() 
{ 
  var_type vt; 
 
  get_token(); // get var type 
  vt.v_type = tok; // store type 
 
  vt.value = 0; // init var to 0 
 
  // Process comma-separated list. 
  do { 
    get_token(); // get var name 
 
    // See if variable is already the name 
    // of a local variable in this scope. 
    if(!local_var_stack.empty()) 
    for(int i=local_var_stack.size()-1; 
        i >= nest_scope_stack.top(); i--) 
    { 
      if(!strcmp(local_var_stack[i].var_name, token)) 
        throw InterpExc(DUP_VAR); 
    } 
 
    strcpy(vt.var_name, token); 
    local_var_stack.push_back(vt); 
    get_token(); 
  } while(*token == ','); 
 
  if(*token != ';') throw InterpExc(SEMI_EXPECTED); 
} 
 
// Call a function. 
void call() 
{ 
  char *loc, *temp; 
  int lvartemp; 
 
  // First, find entry point of function. 
  loc = find_func(token); 
 
  if(loc == NULL) 
    throw InterpExc(FUNC_UNDEF); // function not defined 
  else { 
    // Save local var stack index. 
    lvartemp = local_var_stack.size(); 
 
    get_args(); // get function arguments 
    temp = prog; // save return location 
 
    func_call_stack.push(lvartemp); // push local var index 
 
    prog = loc; // reset prog to start of function 
    get_params(); // load the function's parameters with 
                  // the values of the arguments 
 
    interp(); // interpret the function 
 
    prog = temp; // reset the program pointer 
 
    if(func_call_stack.empty()) throw InterpExc(RET_NOCALL); 
 
    // Reset local_var_stack to its previous state. 
    local_var_stack.resize(func_call_stack.top());  
    func_call_stack.pop(); 
  } 
} 
 
// Push the arguments to a function onto the local 
// variable stack. 
void get_args() 
{ 
  int value, count, temp[NUM_PARAMS]; 
  var_type vt; 
 
  count = 0; 
  get_token(); 
  if(*token != '(') throw InterpExc(PAREN_EXPECTED); 
 
  // Process a comma-separated list of values. 
  do { 
    eval_exp(value); 
    temp[count] = value; // save temporarily 
    get_token(); 
    count++; 
  } while(*token == ','); 
  count--; 
 
  // Now, push on local_var_stack in reverse order. 
  for(; count>=0; count--) { 
    vt.value = temp[count]; 
    vt.v_type = ARG; 
    local_var_stack.push_back(vt); 
  } 
} 
 
// Get function parameters. 
void get_params() 
{ 
  var_type *p; 
  int i; 
 
  i = local_var_stack.size()-1; 
 
  // Process comma-separated list of parameters. 
  do {  
    get_token(); 
    p = &local_var_stack[i]; 
    if(*token != ')' ) { 
      if(tok != INT && tok != CHAR) 
        throw InterpExc(TYPE_EXPECTED); 
 
      p->v_type = tok; 
      get_token(); 
 
      // Link parameter name with argument already on 
      // local var stack. 
      strcpy(p->var_name, token); 
      get_token(); 
      i--; 
    } 
    else break; 
  } while(*token == ','); 
 
  if(*token != ')') throw InterpExc(PAREN_EXPECTED); 
} 
 
// Return from a function. 
void func_ret() 
{ 
  int value; 
 
  value = 0; 
 
  // Get return value, if any. 
  eval_exp(value); 
 
  ret_value = value; 
} 
 
// Assign a value to a variable. 
void assign_var(char *vname, int value) 
{ 
  // First, see if it's a local variable. 
  if(!local_var_stack.empty()) 
    for(int i=local_var_stack.size()-1; 
        i >= func_call_stack.top(); i--) 
    { 
      if(!strcmp(local_var_stack[i].var_name, 
                 vname)) 
      { 
        if(local_var_stack[i].v_type == CHAR) 
          local_var_stack[i].value = (char) value; 
        else if(local_var_stack[i].v_type == INT) 
          local_var_stack[i].value = value; 
        return; 
      } 
    } 
 
  // Otherwise, try global vars. 
  for(unsigned i=0; i < global_vars.size(); i++) 
    if(!strcmp(global_vars[i].var_name, vname)) { 
      if(global_vars[i].v_type == CHAR) 
        global_vars[i].value = (char) value; 
      else if(global_vars[i].v_type == INT) 
        global_vars[i].value = value; 
      return; 
    } 
 
  throw InterpExc(NOT_VAR); // variable not found 
} 
 
// Find the value of a variable. 
int find_var(char *vname) 
{ 
  // First, see if it's a local variable. 
  if(!local_var_stack.empty()) 
    for(int i=local_var_stack.size()-1; 
        i >= func_call_stack.top(); i--) 
    { 
      if(!strcmp(local_var_stack[i].var_name, vname)) 
        return local_var_stack[i].value; 
    } 
 
  // Otherwise, try global vars. 
  for(unsigned i=0; i < global_vars.size(); i++) 
    if(!strcmp(global_vars[i].var_name, vname)) 
      return global_vars[i].value; 
 
  throw InterpExc(NOT_VAR); // variable not found 
} 
 
// Execute an if statement. 
void exec_if() 
{ 
  int cond; 
 
  eval_exp(cond); // get if expression. 
 
  if(cond) { // if true, process target of IF 
    // Confirm start of block. 
    if(*token != '{')  
      throw InterpExc(BRACE_EXPECTED); 
 
    interp(); 
  } 
  else { 
    // Otherwise skip around IF block and 
    // process the ELSE, if present. 
 
    find_eob(); // find start of next line 
    get_token(); 
 
    if(tok != ELSE) { 
      // Restore token if no ELSE is present. 
      putback();   
      return; 
    } 
 
    // Confirm start of block. 
    get_token(); 
    if(*token != '{')  
      throw InterpExc(BRACE_EXPECTED); 
    putback(); 
 
    interp(); 
  } 
} 
 
// Execute a switch statement. 
void exec_switch() 
{ 
  int sval, cval; 
  int brace; 
 
  eval_exp(sval); // Get switch expression. 
 
  // Check for start of block. 
  if(*token != '{')  
    throw InterpExc(BRACE_EXPECTED); 
 
  // Record new scope. 
  nest_scope_stack.push(local_var_stack.size()); 
 
  // Now, check case statements. 
  for(;;) { 
    brace = 1; 
    // Find a case statement. 
    do { 
      get_token(); 
      if(*token == '{') brace++; 
      else if(*token == '}') brace--;  
    } while(tok != CASE && tok != END && brace); 
 
    // If no matching case found, then skip. 
    if(!brace) break; 
 
    if(tok == END) throw InterpExc(SYNTAX); 
 
    // Get value of the case statement. 
    eval_exp(cval); 
 
    // Read and discard the : 
    get_token(); 
 
    if(*token != ':') 
      throw InterpExc(COLON_EXPECTED); 
 
    // If values match, then interpret. 
    if(cval == sval) { 
      brace = 1; 
      do { 
        interp(); 
 
        if(*token == '{') brace++; 
        else if(*token == '}') brace--; 
      } while(!breakfound && tok != END && brace); 
 
      // Find end of switch statement. 
      while(brace) { 
        get_token(); 
        if(*token == '{') brace++; 
        else if(*token == '}') brace--; 
      } 
      breakfound = false; 
 
      break; 
    } 
  }  
} 
 
// Execute a while loop. 
void exec_while() 
{ 
  int cond; 
  char *temp; 
 
  putback(); // put back the while 
  temp = prog; // save location of top of while loop 
 
  get_token(); 
  eval_exp(cond); // check the conditional expression 
 
  // Confirm start of block. 
  if(*token != '{')  
    throw InterpExc(BRACE_EXPECTED); 
 
  if(cond) 
    interp(); // if true, interpret 
  else { // otherwise, skip to end of loop 
    find_eob(); 
    return; 
  } 
 
  prog = temp; // loop back to top 
 
  // Check for break in loop. 
  if(breakfound) { 
    // Find start of loop block. 
    do { 
      get_token(); 
    } while(*token != '{' && tok != END); 
 
    putback(); 
    breakfound = false; 
    find_eob(); // now, find end of loop 
    return; 
  } 
} 
 
// Execute a do loop. 
void exec_do() 
{ 
  int cond; 
  char *temp; 
 
 
  // Save location of top of do loop. 
  putback(); // put back do 
  temp = prog; 
 
  get_token(); // get start of loop block 
 
  // Confirm start of block. 
  get_token(); 
  if(*token != '{')  
    throw InterpExc(BRACE_EXPECTED); 
  putback(); 
 
  interp(); // interpret loop 
 
  // Check for break in loop. 
  if(breakfound) { 
    prog = temp; 
    // Find start of loop block. 
    do { 
      get_token(); 
    } while(*token != '{' && tok != END); 
 
    // Find end of while block.     
    putback(); 
    find_eob(); 
 
    // Now, find end of while expression. 
    do { 
      get_token(); 
    } while(*token != ';' && tok != END); 
    if(tok == END) throw InterpExc(SYNTAX); 
 
    breakfound = false; 
    return; 
  } 
 
  get_token(); 
  if(tok != WHILE) throw InterpExc(WHILE_EXPECTED); 
 
  eval_exp(cond); // check the loop condition 
 
  // If true loop; otherwise, continue on. 
  if(cond) prog = temp; 
} 
 
// Execute a for loop. 
void exec_for() 
{ 
  int cond; 
  char *temp, *temp2; 
  int paren ; 
 
  get_token(); // skip opening ( 
  eval_exp(cond); // initialization expression 
 
  if(*token != ';') throw InterpExc(SEMI_EXPECTED); 
  prog++; // get past the ; 
  temp = prog; 
 
  for(;;) { 
    // Get the value of the conditional expression. 
    eval_exp(cond); 
 
    if(*token != ';') throw InterpExc(SEMI_EXPECTED); 
    prog++; // get past the ; 
    temp2 = prog; 
 
    // Find start of for block. 
    paren = 1; 
    while(paren) { 
      get_token(); 
      if(*token == '(') paren++; 
      if(*token == ')') paren--; 
    } 
 
    // Confirm start of block. 
    get_token(); 
    if(*token != '{')  
      throw InterpExc(BRACE_EXPECTED); 
    putback(); 
 
    // If condition is true, interpret 
    if(cond) 
      interp(); 
    else { // otherwise, skip to end of loop  
      find_eob(); 
      return; 
    } 
 
    prog = temp2; // go to increment expression 
 
    // Check for break in loop. 
    if(breakfound) { 
      // Find start of loop block. 
      do { 
        get_token(); 
      } while(*token != '{' && tok != END); 
 
      putback(); 
      breakfound = false; 
      find_eob(); // now, find end of loop 
      return; 
    } 
 
    // Evaluate the increment expression. 
    eval_exp(cond); 
 
    prog = temp; // loop back to top 
  } 
} 
 
// Execute a cout statement. 
void exec_cout() 
{ 
  int val; 
 
  get_token(); 
  if(*token != LS) throw InterpExc(SYNTAX); 
 
  do { 
    get_token(); 
 
    if(token_type==STRING) { 
      // Output a string. 
      cout << token; 
    } 
    else if(token_type == NUMBER || 
            token_type == IDENTIFIER) { 
      // Output a number. 
      putback(); 
      eval_exp(val); 
      cout << val; 
    } 
    else if(*token == '\'') { 
      // Output a character constant. 
      putback(); 
      eval_exp(val); 
      cout << (char) val; 
    } 
 
    get_token(); 
  } while(*token == LS); 
 
  if(*token != ';') throw InterpExc(SEMI_EXPECTED); 
} 
 
// Execute a cin statement. 
void exec_cin() 
{ 
  int val; 
  char chval; 
  token_ireps vtype; 
 
  get_token(); 
  if(*token != RS) throw InterpExc(SYNTAX); 
 
  do { 
    get_token(); 
    if(token_type != IDENTIFIER)  
      throw InterpExc(NOT_VAR); 
 
      vtype = find_var_type(token); 
 
      if(vtype == CHAR) { 
        cin >> chval; 
        assign_var(token, chval); 
      } 
      else if(vtype == INT) { 
        cin >> val; 
        assign_var(token, val); 
      } 
 
      get_token();       
  } while(*token == RS); 
 
  if(*token != ';') throw InterpExc(SEMI_EXPECTED); 
} 
 
// Find the end of a block. 
void find_eob() 
{ 
  int brace; 
 
  get_token(); 
  if(*token != '{') 
    throw InterpExc(BRACE_EXPECTED); 
 
  brace = 1; 
 
  do { 
    get_token(); 
    if(*token == '{') brace++; 
    else if(*token == '}') brace--; 
  } while(brace && tok != END); 
 
  if(tok==END) throw InterpExc(UNBAL_BRACES); 
} 
 
// Determine if an identifier is a variable. Return 
// true if variable is found; false otherwise. 
bool is_var(char *vname) 
{ 
  // See if vname a local variable. 
  if(!local_var_stack.empty()) 
    for(int i=local_var_stack.size()-1; 
        i >= func_call_stack.top(); i--) 
    { 
      if(!strcmp(local_var_stack[i].var_name, vname)) 
        return true; 
    } 
 
  // See if vname is a global variable. 
  for(unsigned i=0; i < global_vars.size(); i++) 
    if(!strcmp(global_vars[i].var_name, vname)) 
      return true; 
 
  return false; 
} 
 
// Return the type of variable. 
token_ireps find_var_type(char *vname) 
{ 
  // First, see if it's a local variable. 
  if(!local_var_stack.empty()) 
    for(int i=local_var_stack.size()-1; 
        i >= func_call_stack.top(); i--) 
    { 
      if(!strcmp(local_var_stack[i].var_name, vname)) 
        return local_var_stack[i].v_type; 
    } 
 
  // Otherwise, try global vars. 
  for(unsigned i=0; i < global_vars.size(); i++) 
    if(!strcmp(global_vars[i].var_name, vname)) 
        return local_var_stack[i].v_type; 
 
  return UNDEFTOK; 
}

listing 3
// ***** Internal Library Functions ***** 
 
// Add more of your own, here. 
 
#include <iostream> 
#include <cstdlib> 
#include <cstdio> 
#include "mccommon.h" 
 
using namespace std; 
 
// Read a character from the console. 
// If your compiler supplies an unbuffered 
// character intput function, feel free to 
// substitute it for the call to cin.get(). 
int call_getchar() 
{ 
  char ch; 
 
  ch = getchar(); 
 
  // Advance past ()   
  get_token(); 
  if(*token != '(') 
    throw InterpExc(PAREN_EXPECTED); 
 
  get_token(); 
  if(*token != ')') 
    throw InterpExc(PAREN_EXPECTED); 
 
  return ch; 
} 
 
// Write a character to the display. 
int call_putchar() 
{ 
  int value; 
 
  eval_exp(value); 
 
  putchar(value); 
 
  return value; 
} 
 
// Return absolute value. 
int call_abs() 
{ 
  int val; 
 
  eval_exp(val); 
 
  val = abs(val); 
 
  return val; 
} 
 
// Return a randome integer. 
int call_rand() 
{ 
   
  // Advance past ()   
  get_token(); 
  if(*token != '(') 
    throw InterpExc(PAREN_EXPECTED); 
 
  get_token(); 
  if(*token != ')') 
    throw InterpExc(PAREN_EXPECTED); 
 
  return rand(); 
}

listing 4
// Common declarations used by parser.cpp, minicpp.cpp, 
// or libcpp.cpp, or by other files that you might add. 
// 
const int MAX_T_LEN  = 128;   // max token length 
const int MAX_ID_LEN = 31;    // max identifier length 
const int PROG_SIZE  = 10000; // max program size 
const int NUM_PARAMS = 31;    // max number of parameters 
 
// Enumeration of token types. 
enum tok_types { UNDEFTT, DELIMITER, IDENTIFIER, 
                 NUMBER, KEYWORD, TEMP, STRING, BLOCK }; 
 
// Enumeration of internal representation of tokens. 
enum token_ireps { UNDEFTOK, ARG, CHAR, INT, SWITCH, 
                   CASE, IF, ELSE, FOR, DO, WHILE, BREAK, 
                   RETURN, COUT, CIN, END }; 
 
// Enumeration of two-character operators, such as <=. 
enum double_ops { LT=1, LE, GT, GE, EQ, NE, LS, RS, INC, DEC }; 
 
// These are the constants used when throwing a 
// syntax error exception. 
// 
// NOTE: SYNTAX is a generic error message used when 
// nothing else seems appropriate. 
enum error_msg 
     { SYNTAX, NO_EXP, NOT_VAR, DUP_VAR, DUP_FUNC, 
       SEMI_EXPECTED, UNBAL_BRACES, FUNC_UNDEF, 
       TYPE_EXPECTED, RET_NOCALL, PAREN_EXPECTED, 
       WHILE_EXPECTED, QUOTE_EXPECTED, DIV_BY_ZERO, 
       BRACE_EXPECTED, COLON_EXPECTED }; 
 
extern char *prog;  // current location in source code 
extern char *p_buf; // points to start of program buffer 
 
extern char token[MAX_T_LEN+1]; // string version of token 
extern tok_types token_type; // contains type of token 
extern token_ireps tok; // internal representation of token 
 
extern int ret_value; // function return value 
 
extern bool breakfound; // true if break encountered 
 
// Exception class for Mini C++. 
class InterpExc { 
  error_msg err; 
public: 
  InterpExc(error_msg e) { err = e; } 
  error_msg get_err() { return err; } 
}; 
 
// Interpreter prototypes. 
void prescan(); 
void decl_global(); 
void call(); 
void putback(); 
void decl_local(); 
void exec_if(); 
void find_eob(); 
void exec_for(); 
void exec_switch(); 
void get_params(); 
void get_args(); 
void exec_while(); 
void exec_do(); 
void exec_cout(); 
void exec_cin(); 
void assign_var(char *var_name, int value); 
bool load_program(char *p, char *fname); 
int find_var(char *s); 
void interp(); 
void func_ret(); 
char *find_func(char *name); 
bool is_var(char *s); 
token_ireps find_var_type(char *s); 
 
// Parser prototypes. 
void eval_exp(int &value); 
void eval_exp0(int &value); 
void eval_exp1(int &value); 
void eval_exp2(int &value); 
void eval_exp3(int &value); 
void eval_exp4(int &value); 
void eval_exp5(int &value); 
void atom(int &value); 
void sntx_err(error_msg error); 
void putback(); 
bool isdelim(char c); 
token_ireps look_up(char *s); 
int find_var(char *s); 
tok_types get_token(); 
int internal_func(char *s); 
bool is_var(char *s); 
 
// "Standard library" prototypes. 
int call_getchar(); 
int call_putchar(); 
int call_abs(); 
int call_rand();

listing 5
/* Mini C++ Demonstration Program #1. 
 
   This program demonstrates all features 
   of C++ that are recognized by Mini C++. 
*/ 
 
int i, j; // global vars  
char ch; 
 
int main() 
{ 
  int i, j; // local vars  
 
  // Call a "standard library' function. 
  cout << "Mini C++ Demo Program.\n\n"; 
 
  // Call a programmer-defined function. 
  print_alpha(); 
 
  cout << "\n"; 
 
  // Demonstrate do and for loops. 
  cout << "Use loops.\n"; 
  do { 
    cout << "Enter a number (0 to quit): "; 
    cin >> i; 
 
    // Demonstrate the if 
    if(i < 0 ) { 
      cout << "Numbers must be positive, try again.\n"; 
    } 
    else { 
      for(j = 0; j <= i; ++j) { 
        cout << j << " summed is "; 
        cout << sum(j) << "\n"; 
      } 
    } 
  } while(i != 0); 
 
  cout << "\n"; 
 
  // Demonstrate the break in a loop. 
  cout << "Break from a loop.\n"; 
  for(i=0; i < 100; i++) { 
    cout << i << "\n"; 
    if(i == 5) { 
      cout << "Breaking out of loop.\n"; 
      break; 
    } 
  } 
 
  cout << "\n"; 
 
  // Demonstrate the switch 
  cout << "Use a switch.\n"; 
  for(i=0; i < 6; i++) { 
    switch(i) { 
      case 1: // can stack cases 
      case 0: 
        cout << "1 or 0\n"; 
        break; 
      case 2: 
        cout << "two\n"; 
        break; 
      case 3: 
        cout << "three\n"; 
        break; 
      case 4: 
        cout << "four\n"; 
        cout << "4 * 4 is "<< 4*4 << "\n"; 
//        break; // this break is optional 
      // no case for 5 
    } 
  } 
  cout << "\n"; 
 
  cout << "Use a library function to generate "  
       << "10 random integers.\n"; 
  for(i=0; i < 10; i++) { 
    cout << rand() << " "; 
  } 
 
  cout << "\n"; 
  cout << "Done!\n"; 
 
  return 0; 
} 
 
// Sum the values between 0 and num. 
// This function takes a parameter. 
int sum(int num) 
{ 
  int running_sum; 
 
  running_sum = 0; 
 
  while(num) { 
    running_sum = running_sum + num; 
    num--; 
  } 
  return running_sum; 
} 
 
// Print the alphabet. 
int print_alpha() 
{ 
  cout << "This is the alphabet:\n"; 
 
  for(ch = 'A'; ch<='Z'; ch++) { 
    putchar(ch); 
  } 
  cout << "\n"; 
 
  return 0; 
}

listing 6
// Nested loop example. 
int main() 
{ 
  int i, j, k; 
 
  for(i = 0; i < 5; i = i + 1) { 
    for(j = 0; j < 3; j = j + 1) { 
      for(k = 3; k ; k = k - 1) { 
        cout << i <<", "; 
        cout << j << ", "; 
        cout << k << "\n"; 
      } 
    } 
  } 
 
  cout << "done"; 
 
  return 0; 
}

listing 7
// Assigments as operations. 
int main() 
{ 
  int a, b; 
 
  a = b = 5; 
 
  cout << a << " " << b << "\n"; 
 
  while(a=a-1) { 
    cout << a << " ";  
    do { 
      cout << b << " "; 
    } while((b=b-1) > -5); 
    cout << "\n"; 
  } 
 
  return 0; 
}

listing 8
// This program demonstrates a recursive function. 
 
// A recursive function that returns the 
// factorial of i. 
int factr(int i) 
{ 
  if(i<2) { 
    return 1; 
  } 
  else { 
     return i * factr(i-1); 
  } 
} 
 
int main() 
{ 
  cout << "Factorial of 4 is: "; 
  cout << factr(4) << "\n"; 
 
  cout << "Factorial of 6 is: "; 
  cout << factr(6) << "\n"; 
 
  return 0; 
}

listing 9
// A more rigorous example of function arguments.  
 
int f1(int a, int b) 
{ 
  int count; 
 
  cout << "Args for f1 are "; 
  cout << a << " " << b << "\n"; 
 
  count = a; 
  do { 
    cout << count << " "; 
  } while(count=count-1); 
 
  cout << a << " " << b 
       << " " << a*b << "\n"; 
 
  return a*b; 
} 
 
int f2(int a, int x, int y) 
{ 
  cout << "Args for f2 are "; 
  cout << a << " " << x << " " 
       << y << "\n"; 
  cout << x / a << " "; 
  cout << y*x << "\n"; 
 
  return 0; 
} 
 
int main() 
{ 
  f2(10, f1(10, 20), 99); 
 
  return 0; 
}

listing 10
// Exercise the loop statements. 
int main() 
{ 
  int a; 
  char ch; 
 
  // The while. 
  cout << "Enter a number: "; 
  cin >> a; 
  while(a) { 
    cout << a*a << " "; 
    --a; 
  } 
  cout << "\n"; 
 
  // The do-while. 
  cout << "\nEnter characters, 'q' to quit.\n"; 
  do { 
    // Use two "standard library" functions. 
    ch = getchar(); 
    putchar(ch); 
  } while(ch != 'q'); 
  cout << "\n\n"; 
 
  // the for. 
  for(a=0; a<10; ++a) { 
     cout << a << " "; 
  } 
 
  cout << "\n\nDone!\n"; 
 
  return 0; 
}

listing 11
// Demonstrate nested scopes. 
 
int x; // global x 
 
int main() 
{ 
  int i; 
 
  i = 4; 
 
  x = 99; // global x is 99 
 
  if(i == 4) { 
    int x; // local x 
    int num; // local to if statement 
 
    x = i * 2; 
    cout << "Outer local x before loop: " 
         << x << "\n"; 
 
    while(x--) { 
      int x; // another local x 
 
      x = 18; 
      cout << "Inner local x: " << x << "\n"; 
    }  
 
    cout << "Outer local x after loop: " 
         << x << "\n"; 
  } 
 
  // Can't refer to num here because it is local 
  // to the preceding if block. 
//  num = 10;  
 
  cout << "Global x: " << x << "\n"; 
}

