#include "postfix.h"
#include <math.h>

int is_operator(char * token) {
   if (*token == '+' || *token == '-' || *token == 'X' || *token == 'x'|| *token == '/' || *token == '^') {
        if (*(token+1) == '\0') {
            return 1;
        }
   }
   return 0;
}

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

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  struct double_stack * stack;
  stack = double_stack_new(nargs*2);
  for(int i=0;i<nargs;i++){
    if(is_operand(args[i])){
	double_stack_push(stack, atof(args[i]));
    }
    else if(is_operator(args[i])){
        char * token = args[i];
	if(*token =='+'){
	  double value2 = double_stack_pop(stack);
	  double value1 = double_stack_pop(stack);
	  double_stack_push(stack,(value1+value2));
	} else if(*token =='-'){
	    double value2 = double_stack_pop(stack);
	    double value1 = double_stack_pop(stack);
	    double_stack_push(stack,(value1-value2));
	} else if(*token =='/'){
	  double value2 = double_stack_pop(stack);
	  double value1 = double_stack_pop(stack);
	  double_stack_push(stack,(value1/value2));
	} else if(*token=='x' || *token=='X'){
	  double value2 = double_stack_pop(stack);
	  double value1 = double_stack_pop(stack);
	  double_stack_push(stack,(value1*value2));
	} else if(*token == '^'){
	  double value2 = double_stack_pop(stack);
	  double value1 = double_stack_pop(stack);
	  double ans = pow(value1, value2);
	  double_stack_push(stack,ans);
	}
    }
  }
    double ans = double_stack_pop(stack);
    return ans;
  
}
  
  
