/*
 * This file handles all of the login logic for the project
 */

#include <stdio.h>

#include "Login.h"
#include "Sanitizer.h"
#include <stdlib.h>
#include <string.h>

int MAX_ATTEMPTS = 5;
int MAX_BUFF=20;
//handles the login logic for lock out and attempts/ uses loginUser()
int loginMain(){
    int attempts = 0;
    int verify=-1;
    char usernameBuffer[20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    char passwordBuffer[20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    
    while (attempts<MAX_ATTEMPTS){
        attempts++;
        printf("ENTER USER: ");
        fgets(usernameBuffer,20,stdin);
        printf("\nENTER PASSWORD: ");
        fgets(passwordBuffer,20,stdin);
        sanitizeInput(usernameBuffer,20);
        sanitizeInput(passwordBuffer,20);
        verify=loginUser(usernameBuffer,passwordBuffer);
        if(verify>0)return verify;
    }
    //TODO: Lock out
    printf("YOU HAVE LOGGED IN UNSUCCESSFULLY 5 TIMES");
    return verify;
}


//takes the username and password, checks login file and returns a verdict 
//Returns: permission level of the auth user, 0 if no login 
int loginUser(char* user,char* pass){
    
    FILE *logins = fopen("logins","r");
    LoginT *head = malloc(sizeof(LoginT));
    int count = 0;
    LoginT *temp = malloc(sizeof(LoginT));
    //printf("\nFinding Logins from file!\n");
    while(!feof(logins)){
        LoginT *newElement = malloc(sizeof(LoginT));
        newElement->next=0;
        fscanf(logins,"%s",newElement->username);
        //printf("got username:%s \n",newElement->username);
        fscanf(logins,"%s",newElement->password);
        //printf("got password:%s \n",newElement->password);
        fscanf(logins,"%i",&newElement->permissionLevel);
       // printf("got permissionLevel:%i \n",newElement->permissionLevel);
        
        if(count ==0){
            head = newElement;
            temp = head;
        }
        else {
            temp->next = newElement;
            temp = newElement;
        }
        //temp = newElement->next;
        //printf("%i: %s, %s, %i\n",count,newElement->username,newElement->password,newElement->permissionLevel);
        count++;
        
    }
    // run through and see all the usernames+ pass and cmp
    temp = head;
    
    //Don't judge this - it keeps the warnings down
    for (count = count; count>0; count--){
       // printf("Usernames found: %s\n",temp->username);
       // printf("compares: %i %i\n",strncmp(user,temp->username,20),strncmp(pass,temp->password,20));
        //user,pass);
        if(strncmp(user,temp->username,20)==0){
            if(strncmp(pass,temp->password,20)==0){
                return temp->permissionLevel;
            }            
        }
        temp=temp->next;        
    }
    return 0;
    
}


