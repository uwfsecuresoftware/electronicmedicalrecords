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
    //Lock out
    lockout(usernameBuffer);
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
                if(isLocked(user)<0){
                    return temp->permissionLevel;
                }
                
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
        sanitizeInput(num,1);
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
//lockouts selected user by adding them to locokout file
int lockout(char* user){
    FILE *lockout = fopen("lockout","a");
    fprintf(lockout,"\n%s",user);
    fclose(lockout);
}
//reads locokut file and removes from linked list
int unlock(char* user){
    FILE *lockout = fopen("lockout","r");
    lockOutT *head = malloc(sizeof(lockOutT));
    lockOutT *temp = malloc(sizeof(lockOutT));
    lockOutT *newElement = malloc(sizeof(lockOutT));
    lockOutT *prev = malloc(sizeof(lockOutT));
    int count = 0;
    int saveCount=0;
    
    while(!feof(lockout)){
        newElement = malloc(sizeof(lockOutT));
        newElement->next= 0;
        fscanf(lockout,"%s",newElement->username);
        if(count ==0){
            head = newElement;
            temp = head;
        }
        else {
            temp->next = newElement;
            temp = newElement;
        }
        count++;
    }
    saveCount=count;
    for (count = count; count>0; count--){
        if(strncmp(user,temp->username,20)==0){
            prev->next=temp->next;
        }
        prev= temp;
        temp=temp->next;
    }
    fclose(lockout);
    temp=head;
    lockout = fopen("lockout","w");
    for(count=count;count<=saveCount;count++){
        fprintf(lockout,"%s",temp->username);
        temp=temp->next;
    }
}
//checks if the username is inside lockout -100 if not 100 if
int isLocked(char* user){
    
    FILE *lockout = fopen("lockout","r");
    lockOutT *head = malloc(sizeof(lockOutT));
    lockOutT *temp = malloc(sizeof(lockOutT));
    lockOutT *newElement = malloc(sizeof(lockOutT));
    lockOutT *prev = malloc(sizeof(lockOutT));
    int count = 0;
    int saveCount=0;
     //fprintf(stderr,"initVars");
    
    while(!feof(lockout)){
        newElement = malloc(sizeof(lockOutT));
        newElement->next= 0;
        fscanf(lockout,"%s",newElement->username);
        //fprintf(stderr,"\n Locked Out user: %s",newElement->username);
        if(count ==0){
            head = newElement;
            temp = head;
        }
        else {
            temp->next = newElement;
            temp = newElement;
        }
        count++;
    }
    saveCount=count;
    temp=head;
    for (count = count; count>0; count--){
        //fprintf(stderr,"\n Locked Out user: %s",temp->username);
        if(strncmp(user,temp->username,20)==0){
            return 100;
        }
        prev= temp;
        temp=temp->next;
    }
    fclose(lockout);
    return -100;
    
}
//prompts and deletes user
int deleteUser(){
    
}