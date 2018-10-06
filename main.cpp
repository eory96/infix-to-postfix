//
//  main.cpp
//  3. infix to postfix(stack)
//
//  Created by 김대교 on 2018. 9. 13..
//  Copyright © 2018년 김대교. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define EOS '$'
#define YES 1
#define NO 0
#define SIZE 100

int is_operator(char x){
    if(x=='('||x==')'||x=='*'||x=='/'||x=='%'||x=='+'||x=='-'||x=='$')
        return YES;
    else
        return NO;
}

class token{
    int isp;
    int icp;
    public : char op;
    public : void set_token(char x);
    public : int get_isp();
    public : int get_icp();
};

void token::set_token(char x){
    op=x;
    if(op=='('){
        isp=0;
        icp=20;
    }
    else if(op==')'){
        isp=19;
        icp=19;
    }
    else if(op=='*'||op=='/'||op=='%'){
        isp=13;
        icp=13;
    }
    else if(op=='+'||op=='-'){
        isp=12;
        icp=12;
    }
    else{
        isp=0;
        icp=0;
    }
}

int token::get_icp(){
    return icp;
}

int token::get_isp(){
    return isp;
}

class myStack{
    token s[SIZE];
    int top;
public :
    myStack(){
        top=0;
    }
    void push(token x);
    token pop();
    token top_element();
};

void myStack::push(token x){
    s[top]=x;
    top++;
}

token myStack::pop(){
    token temp;
    top--;
    temp = s[top];
    
    return temp;
}

token myStack::top_element(){
    token a;
    top--;
    a = s[top];
    top++;
    return a;
}



int main(int argc, const char * argv[]) {
    myStack s1;
    string input,output;
    token t1,t2,t3;
    
    cout<<"infix를 입력하여 주세요 : ";
    cin>>input;
    
    if(input[input.length()-1]!='$')
        input+='$';
    
    t1.set_token('$');
    s1.push(t1);
    
    
    for(int k=0;k<input.length();k++){
        if(is_operator(input[k])!=YES){
            output+=input[k];
        }else{
            t2.set_token(input[k]);
            if(t2.op==')'){
                while (t3.op!='(') {
                    t3=s1.pop();
                    if(t3.op!='(' && t3.op!=')')
                        output+=t3.op;
                }
            }
            else{
                while(s1.top_element().get_isp()>=t2.get_icp()){
                t3=s1.pop();
                if(t3.op!='(' && t3.op!=')')
                    output+=t3.op;
                if(s1.top_element().get_icp()==0)
                    break;
                }
            }
                s1.push(t2);
        }
    }
    
    cout<<"postfix는 다음과 같습니다 : "<<output;
    
    cout<<endl;
    
    return 0;
}
