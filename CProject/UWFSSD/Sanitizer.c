/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//bounded sanitize, currently removes \n and %
void sanitizeInput(char* input,int size){
    int i = 0;
    for(i = 0;i<size;i++){
        if(*input =='\n'){
            *input ='\0';
        }else if(*input=='%'){
            *input =' ';
        }
        input++;
    }
    
}

void sanitizeSpace(char* input,int size){
    int i = 0;
    for(i = 0;i<size;i++){
        if(*input ==' '){
            *input ='_';
        }
        input++;
    }
}

void sanitizeInt(char* input, int size){
    int i = 0;
    for(i = 0;i<size;i++){
        if(*input -48 >9||input -48<0){
            *input ='0';
        }
        input++;
    }
    
}