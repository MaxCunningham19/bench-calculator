#include "infix.h"
/*
int is_operand(char * token){
  int i=0;
  while(1){
    if((*(token+i)== '-' && *(token+i+1) != '\0') || *(token+i)== '0' || *(token+i)== '1' || *(token+i)== '2' || *(token+i)== '3' || *(token+i)== '4' ||*(token+i)== '5' ||
       *(token+i)== '6' ||*(token+i)== '7' ||*(token+i)== '8' ||*(token+i)== '9' || (*(token+i)=='.' && i!=0)){
      i++;
    } else if (*(token+i)=='\0' && i!=0){
      return 1;
    } else{
      return 0;
    }
  }
}

int is_operator(char * token) {
   if (*token == '+' || *token == '-' || *token == 'X' || *token == 'x'|| *token == '/' || *token == '^') {
        if (*(token+1) == '\0') {
            return 1;
        }
   }
   return 0;
}*/

int equal_or_higher_precidence(char* stack, char* token){
  if(*token =='+' || *token == '-'){
    return 1;
  }
  if(*stack =='^'){
    return 1;
  }
  if(*stack =='X' || *stack == '/'){
    if(*token=='^'){
      return 0;
    } else {
      return 1;
    }
  }
  return 0;
}

int is_left_bracket(char* arg){
  if(*arg=='('){
    return 1;
  }
  return 0;
}

int is_right_bracket(char* arg){
  if(*arg==')'){
    return 1;
  }
  return 0;
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
  char** output = (char**) malloc(sizeof(char*) * nargs);
  int outputNum = 0;
  char** stack = (char**) malloc(sizeof(char*)*nargs);
  int stackPointer = 0;

  for(int i=0;i<nargs;i++){
    if(is_operand(args[i])){
      output[outputNum] = args[i];
      outputNum++;
    }
    else if (is_left_bracket(args[i])){
      stack[stackPointer] = args[i];
      stackPointer++;
    }
    else if(is_operator(args[i])){
        int tmpStackPointer = stackPointer - 1;
        while(tmpStackPointer>=0 && is_operator(stack[tmpStackPointer]) && equal_or_higher_precidence(stack[tmpStackPointer], args[i])){
	  stackPointer--;
	  output[outputNum] = stack[stackPointer];
	  outputNum++;
	  tmpStackPointer--;
        }
      
      stack[stackPointer] = args[i];
      stackPointer++;
    }
    else if(is_right_bracket(args[i])){
        int tmpStackPointer = stackPointer - 1;
        while(tmpStackPointer>=0 && stack[tmpStackPointer] != '('){
	  stackPointer--;
	  output[outputNum] = stack[stackPointer];
	  outputNum++;
	  tmpStackPointer--;
        }
	if(tmpStackPointer>=0){
	  stackPointer--;//pop left bracket;
	}
    }
  }

  while(stackPointer>0){
    stackPointer--;
    output[outputNum] = stack[stackPointer];
    outputNum++;
  }

  
  return evaluate_postfix_expression(output, outputNum);
}


/*for each token in the input string {
  if ( token is a number ) {
    append token to the output string
  }
  else if (token is a left bracket) {
    push bracket to stack
  }
  else if ( token in an operator ) {
    while ( there is operator  op  on top of the stack  AND op has equal or higher precedence than token ) {
      pop stack and append op to the output string
    }
    push token operator to stack
  }
  else if ( token is right bracket ) {
    while ( top of stack != left bracket ) {
      pop operator from stack and append to output string
    pop left bracket
  }
}
pop remaining stack items and append each of them to the end of your reverse Polish notation expression.*/
