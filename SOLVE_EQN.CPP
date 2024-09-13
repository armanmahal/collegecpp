#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define MAX 100
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

class Stack {
    int top;
    int arr[MAX];

public:
    Stack() {
	top = -1;
    }

    void push(int value) {
	if (top >= MAX - 1) {
	    cout << "Stack Overflow" << endl;
	} else {
	    arr[++top] = value;
	}
    }

    void pop() {
	if (top < 0) {
	    cout << "Stack Underflow" << endl;
	} else {
	    top--;
	}
    }

    int peek() {
	if (top < 0) {
	    cout << "Stack is Empty" << endl;
	    return -1;
	} else {
	    return arr[top];
	}
    }

    int isEmpty() {
	if(top<0) return 1;
	return 0;
    }
};

class Expression{
 private:
  char exp[MAX]; // expression
  char pfe[MAX]; // postfix expression
  int x; // given variable
  int checkxTaken; // to check if x input done
  int checkExpTaken; // to check if expression input done
  int expContainsX; // to check if expression contains 'x'
  int ans; // answer
  
  // function to convert string to integer:
  int sti(char str[]);
  
  // function to get length of input expression:
  int len();
  
  // function to convery given infix exp. to postfix:
  void convertToPostFix();

  // function to solve postfix expression:
  void solve();

 public:
  Expression(){
   checkxTaken = 0;
   checkExpTaken = 0;
   expContainsX = 1;
  }

  void expIn(){
   checkxTaken = 0;
   cout<<"Enter Expression : ";
   gets(exp);
   checkExpTaken = 1;
   convertToPostFix();
  }

  void expOut(){
   if(checkExpTaken == 0){
    cout<<RED<<"No Expression Given"<<RESET<<endl;
    return ;
   }
   cout<<YELLOW<<"Expression:    	         "<<exp<<endl;
   cout<<"PF Expression:    	 "<<pfe<<RESET<<endl;
  }

  void variableIn(){
   cout<<"Enter 'x' : ";
   cin>>x;
   checkxTaken = 1;
  }
  void variableOut(){
   if(checkxTaken == 0){
     cout<<RED<<"No variable Given"<<RESET<<endl;
     return;
   }
   cout<<YELLOW<<"Variable:    	         "<<x<<RESET<<endl;
  }

  void answerOut(){
   if(checkxTaken == 0 && checkExpTaken == 0 ){
    return;
   }
   else if(checkExpTaken == 1 && checkxTaken == 0 && expContainsX==1 ){
    return;
   }
   solve();
   cout<<GREEN<<"Answer:    	         "<<ans<<RESET<<endl;
  }
};

void Expression :: convertToPostFix(){
   expContainsX = 0;
   char temp[MAX];
   Stack s;
   int index = 0;
   int length = len();

   for(int i = 0;i < length ; i++){

    // if a number:
    if( (int)exp[i] <= 57 && (int)exp[i] >= 48 ){
     while( (int)exp[i] <= 57 && (int)exp[i] >= 48 && i < length ){
      pfe[index++] = exp[i];
      i++;
     }
     pfe[index++] = ' '; // to differentiate numbers from each other
     i--;
    }

    // if x:
    else if(exp[i] == 'x'){
     pfe[index++] = 'x';
     expContainsX = 1;
    }

    // if + or - :
    else if(exp[i] == '+' || exp[i] == '-'){
     // remove all the operators from top of stack
     // which have more or equal precedence that + or -
     // and add them to expression:
     while(s.peek()=='^' || s.peek() == '*' || s.peek() == '/' ||
     s.peek() == '+' || s.peek() == '-' && s.isEmpty() == 0){
      pfe[index++] = s.peek();
      s.pop();
     }
     s.push(exp[i]);
    }

    // if * or / :
    else if(exp[i] == '*' || exp[i] == '/'){
     // remove all the operators from top of stack
     // which have more or equal precedence that * or /
     // and add them to expression:
     while(s.peek() == '^' || s.peek() == '*' || s.peek() == '/'
     && s.isEmpty() == 0){
      pfe[index++] = s.peek();
      s.pop();
     }
     s.push(exp[i]);

    }

    // if ^ :
    else if(exp[i] == '^'){
     // remove all the operators from top of stack
     // which have more or equal precedence that ^
     // and add them to expression:
     while(s.peek() == '^' && s.isEmpty() == 0){
      pfe[index++] = s.peek();
      s.pop();
     }
     s.push(exp[i]);
    }

    // if ( :
    else if(exp[i] == '('){
     // push it to stack:
     s.push('(');
    }
    // if ) :
    else if(exp[i] == ')'){
     // pop all the operators from the top of the stack
     // ans push them to the expression
     // until a open bracket is encountered

     while(s.peek() != '(' && s.isEmpty() == 0){
      pfe[index++] = s.peek();
      s.pop();
     }
     // popping the opening bracket:
     if(s.isEmpty() == 0){
      s.pop();
     }
    }

    else{
     cout<<"Not A Valid Expression."<<endl;
     exp[0] = '\0';
     pfe[0] = '\0';
     checkExpTaken = 0;
     getch();
     return;
    }
   }

   // emptying the stack after loop:
   while(s.isEmpty() == 0){
    pfe[index++] = s.peek();
    s.pop();
   }

   // terminating the pf expression string:
   pfe[index] = '\0';
}

void Expression :: solve(){
   int i = 0;
   Stack s;

   while(pfe[i] != '\0'){

    // if empty space:
    if(pfe[i] == ' '){
     i++;
     continue;
    }

    // if a number:
    else if( (int)pfe[i] <= 57 && (int)pfe[i] >= 48 ){
     char num[100];
     int index = 0;
     while( (int)pfe[i] <= 57 && (int)pfe[i] >= 48 ){
      num[index++] = pfe[i];
      i++;
     }
     num[index] = '\0';
     // pushing it to stack:
     s.push(sti(num));
    }

    // if x:
    else if(pfe[i] == 'x'){
     s.push(x);
     i++;
    }

    // if an operator:
    else{
     int oprndOne = s.peek();
     s.pop();
     int oprndTwo = s.peek();
     s.pop();
     int toPush = 0;
     if(pfe[i] == '+'){
      toPush = oprndTwo+oprndOne;
     }
     else if(pfe[i] == '-'){
      toPush = oprndTwo-oprndOne;
     }
     else if(pfe[i] == '/'){
      toPush = oprndTwo/oprndOne;
     }
     else if(pfe[i] == '*'){
      toPush = oprndTwo*oprndOne;
     }
     else if(pfe[i] == '^'){
      toPush = pow(oprndTwo,oprndOne);
     }
     s.push(toPush);
     i++;
    }
   }
   ans = s.peek();
}

int Expression :: len(){
   int temp = 0;
   while(exp[temp] != '\0'){
    temp++;
   }
   return temp;
}

int Expression :: sti(char str[]){
   int result = 0;
   int i = 0;
   while (str[i] != '\0') {
    result = result * 10 + (str[i] - '0');
    i++;
   }
   return result;
}

int main(){
 clrscr();

 Expression e;

 while(1){
  clrscr();

  e.expOut();
  e.variableOut();
  e.answerOut();

  int choice;
  cout<<endl<<"1. Give Expression"<<endl;
  cout<<"2. Give 'x'"<<endl;
  cout<<"3. Exit"<<endl<<endl;
  cout<<"Enter Choice >>> ";
  cin>>choice;

  switch(choice){
   case 1:
    e.expIn();
    break;

   case 2:
    e.variableIn();
    break;

   case 3:
    return 0;

   default:
    cout<<RED<<"Enter Valid"<<RESET<<endl;
    getch();
  }
 }
}
