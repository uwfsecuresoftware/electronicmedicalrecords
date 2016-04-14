/*
 * This file handles all of the login logic for the project
 */

#include <stdio.h>

#include "Login.h"
#include <stdlib.h>
#include <string.h>
//takes the username and password, checks login file and returns a verdict 
//Returns: permission level of the auth user, 0 if no login 
int loginUser(char* user,char* pass){
    
    FILE *logins = fopen("logins","r");
    LoginT *head = malloc(sizeof(LoginT));
    int count = 0;
    LoginT *temp;
    printf("\nFinding Logins from file!\n");
    while(!feof(logins)){
        LoginT *newElement = malloc(sizeof(LoginT));
        newElement->next=0;
        fscanf(logins,"%s",newElement->username);
        //printf("got username:%s \n",newElement->username);
        fscanf(logins,"%s",newElement->password);
        //printf("got password:%s \n",newElement->password);
        fscanf(logins,"%i",&newElement->permissionLevel);
        //printf("got permissionLevel:%i \n",newElement->permissionLevel);
        
        if(count ==0){
            head = newElement;
            temp = head;
        }
        else {
            temp->next = newElement;
            temp = newElement;
        }
        //temp = newElement->next;
        printf("%i: %s, %s, %i\n",count,newElement->username,newElement->password,newElement->permissionLevel);
        count++;
        
    }
    // run through and see all the usernames+ pass and cmp
    temp = head;
    for (count; count>0; count--){
        printf("Usernames found: %s\n",temp->username);
        printf("compares: %i %i\n",strncmp(user,temp->username,20),
         strncmp(pass,temp->password,20));
        //user,pass);
        if(strncmp(user,temp->username,20)==0){
            if(strncmp(user,temp->username,20)==0){
                return temp->permissionLevel;
            }            
        }
        temp=temp->next;        
    }
    return 0;
    
}