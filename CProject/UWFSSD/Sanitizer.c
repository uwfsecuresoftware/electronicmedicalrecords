/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//bounded sanitize, currently removes \n 
void sanitizeInput(char* input,int size){
    int i = 0;
    for(i = 0;i<size;i++){
        if(*input =='\n'){
            *input ='\0';
        }
        input++;
    }
    
}