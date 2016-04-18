/*
 * This file handles all of the login logic for the project
 */

#include <stdio.h>

#include "Login.h"
#include "Sanitizer.h"
#include <stdlib.h>
#include <string.h>
#include "utility.h"


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
        fscanf(logins,"%s",&newElement->uuid);
        
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
//prompts user for account info then generates a UUID and appends to logins file as well as generating a blank UUID file 
int createUser(){
    char usernameBuffer[20];
    initializeString(usernameBuffer,20);
    
    char passwordBuffer[20];
    initializeString(passwordBuffer,20);
    
    char num[10];
    initializeString(num,10);
    
    char uuid[33];
    initializeString(uuid,33);
    generateUUID(uuid);
    
    char filePath[50]={'r','e','c','o','r','d','s','/','\0'};
    //printf("THIS IS THE UUID:: %s",uuid);
    
    int numInt = -1;
   
    fgets(usernameBuffer,20,stdin);// clears input buffer 
    printf("Enter Username: ");
    fgets(usernameBuffer,20,stdin);
    sanitizeInput(usernameBuffer,20);
    
    printf("Enter Password: ");
    fgets(passwordBuffer,20,stdin);
    sanitizeInput(passwordBuffer,20);
    
    while(numInt<0||numInt>5){//verifies that the permission level is valid 0-5
        printf("Enter Permission level: ");
        fgets(num,10,stdin);
        numInt = (int)((num[0]-48));
    }
    //fprintf(stderr,"\n%s%s",filePath,uuid);
    strncat(filePath,uuid,33);
    //printf("%s",filePath);
    
    FILE *newUUIDFile = fopen(filePath,"w+");
    fclose(newUUIDFile);
    
    FILE *logins = fopen("logins","a");
    fprintf(logins,"\n%s",usernameBuffer);
    fprintf(logins," %s",passwordBuffer);
    fprintf(logins," %i",numInt);
    fprintf(logins," %s", uuid);
    fclose(logins);    
}
