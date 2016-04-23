/*
 * This file handles all of the login logic for the project
 */

#include <stdio.h>

#include "Login.h"
#include "Sanitizer.h"
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include <errno.h>


int MAX_ATTEMPTS = 5;
int MAX_BUFF = 20;
//handles the login logic for lock out and attempts/ uses loginUser()

struct LoginT* loginMain() {
    int attempts = 0;
    LoginT* verify=NULL;
    char usernameBuffer[20] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    char passwordBuffer[20] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

    printf("ENTER USER: ");
    
    if(fgets(usernameBuffer, 20, stdin) == NULL) {
        //Something happened.
    }
    
    sanitizeInput(usernameBuffer, 20);
    while (attempts < MAX_ATTEMPTS) {
        attempts++;
        printf("\nENTER PASSWORD: ");
        
        if(fgets(passwordBuffer, 20, stdin) == NULL) {
            //Something happened
        }
        
        sanitizeInput(passwordBuffer, 20);
        verify = loginUser(usernameBuffer, passwordBuffer);
        if (verify != NULL)return verify;
    }
    //Lock out
    lockout(usernameBuffer);
    printf("YOU HAVE LOGGED IN UNSUCCESSFULLY 5 TIMES");
    return verify;
}


//takes the username and password, checks login file and returns a verdict 
//Returns: permission level of the auth user, 0 if no login 

struct LoginT* loginUser(char* user, char* pass) {

    FILE *logins = fopen("logins", "r");
    LoginT *head = malloc(sizeof (LoginT));
    int count = 0;
    LoginT *temp = malloc(sizeof (LoginT));
    if(temp == NULL) {
        //Bad malloc
    }
    //printf("\nFinding Logins from file!\n");
    while (!feof(logins)) {
        LoginT *newElement = malloc(sizeof (LoginT));
        if(newElement == NULL) {
            //Bad malloc
        }
        newElement->next = 0;
        
        if(fscanf(logins, "%19s ", newElement->username) == 0) {
            //Error happened during reading
        }
        //printf("got username:%s \n",newElement->username);
        if(fscanf(logins, "%19s ", newElement->password) == 0) {
            //Error happened during reading;
        }
        //printf("got password:%s \n",newElement->password);
        
        errno = 0;
        
        char number[2] = {'\0', '\0'};
        if(fgets(number, 2, logins) == NULL) {
            //Error
        }
        
        newElement->permissionLevel = (int) strtol(number, NULL, 10);

        // printf("got permissionLevel:%i \n",newElement->permissionLevel);
        if(fscanf(logins, "%32s ", newElement->uuid) == 0) {
            //Error happened during reading
        }

        if (count == 0) {
            head = newElement;
            temp = head;
        } else {
            temp->next = newElement;
            temp = newElement;
        }
        //temp = newElement->next;
        printf("%i: %s, %s, %i\n",count,newElement->username,newElement->password,newElement->permissionLevel);
        count++;

    }
    fclose(logins);
    // run through and see all the usernames+ pass and cmp
    temp = head;

    //Don't judge this - it keeps the warnings down
    for (count = count; count > 0; count--) {
         printf("Usernames found: %s\n",temp->username);
         printf("compares: %i %i\n",strncmp(user,temp->username,20),strncmp(pass,temp->password,20));
        //user,pass);
        if (strncmp(user, temp->username, 20) == 0) {
            if (strncmp(pass, temp->password, 20) == 0) {
                if (isLocked(user) < 0) {
                    fprintf(stderr,"returning");
                    return temp;
                }

            }
        }
        temp = temp->next;
    }
    return NULL;

}
//prompts user for account info then generates a UUID and appends to logins file as well as generating a blank UUID file 

int createUser() {
    char usernameBuffer[20];
    initializeString(usernameBuffer, 20);

    char passwordBuffer[20];
    initializeString(passwordBuffer, 20);

    char num[10];
    initializeString(num, 10);

    char uuid[33];
    initializeString(uuid, 33);
    generateUUID(uuid);

    char filePath[50] = {'r', 'e', 'c', 'o', 'r', 'd', 's', '/', '\0'};
    //printf("THIS IS THE UUID:: %s",uuid);

    int numInt = -1;

    if(fgets(usernameBuffer, 20, stdin) == NULL) { // clears input buffer 
        //error
    } 
    printf("Enter Username: ");
    
    if(fgets(usernameBuffer, 20, stdin) == NULL) {
        //error
    }
    sanitizeInput(usernameBuffer, 20);
    sanitizeSpace(usernameBuffer, 20);

    printf("Enter Password: ");
    
    if(fgets(passwordBuffer, 20, stdin) == NULL) {
        //error
    }
    sanitizeInput(passwordBuffer, 20);
    sanitizeSpace(passwordBuffer, 20);

    while (numInt < 0 || numInt > 5) {//verifies that the permission level is valid 0-5
        printf("Enter Permission level: ");
        if(fgets(num, 10, stdin) == NULL) {
            //error
        }
        sanitizeInput(num, 1);
        numInt = (int) ((num[0] - 48));
    }
    //fprintf(stderr,"\n%s%s",filePath,uuid);
    strncat(filePath, uuid, 33);
    //printf("%s",filePath);

    FILE *newUUIDFile = fopen(filePath, "w+");
    fclose(newUUIDFile);

    FILE *logins = fopen("logins", "a");
    fprintf(logins, "\n%s", usernameBuffer);
    fprintf(logins, " %s", passwordBuffer);
    fprintf(logins, " %i", numInt);
    fprintf(logins, " %s", uuid);
    fclose(logins);
}
//lockouts selected user by adding them to locokout file

void lockout(char* user) {
    FILE *lockoutFile = fopen("lockout", "a");
    fprintf(lockoutFile, "\n%s", user);
    fclose(lockoutFile);
}
//reads locokut file and removes from linked list

int unlock(char* user) {
    FILE *lockoutFile = fopen("lockout", "r");
    
    lockOutT *head = malloc(sizeof (lockOutT));
    lockOutT *temp = malloc(sizeof (lockOutT));
    lockOutT *newElement = malloc(sizeof (lockOutT));
    lockOutT *prev = malloc(sizeof (lockOutT));
    
    if(head == NULL || temp == NULL || newElement == NULL || prev == NULL) {
        //Malloc error
    }
    int count = 0;
    int saveCount = 0;
    fprintf(stderr, "inivar \n");
    while (!feof(lockoutFile)) {
        newElement = malloc(sizeof (lockOutT));
        
        if(newElement == NULL) {
            //Malloc error
        }
        newElement->next = 0;
        if(fscanf(lockoutFile, "%19s", newElement->username) == 0) {
            //Read error
        }
        fprintf(stderr, "found: %s", newElement->username);
        if (count == 0) {
            head = newElement;
            temp = head;
        } else {
            temp->next = newElement;
            temp = newElement;
        }
        count++;
    }
    saveCount = count;
    temp = head;
    prev = head;
    sanitizeInput(user, 20);
    for (count = count; count > 0; count--) {
        fprintf(stderr, "loop %i", strncmp(user, temp->username, 20));
        sanitizeInput(temp->username, 20);

        if (strncmp(user, temp->username, 20) == 0) {
            prev->next = temp->next;
            fprintf(stderr, "found!!! \n");
        }
        prev = temp;
        if (temp->next != 0)
            temp = temp->next;
    }
    fclose(lockoutFile);
    temp = head;
    lockoutFile = fopen("lockout", "w");
    for (count = count; count <= saveCount; count++) {
        fprintf(stderr, "%i-> %s", count, temp->username);
        if (temp->next != 0) {
            if (count == 0)
                fprintf(lockoutFile, "%s", temp->username);
            fprintf(lockoutFile, "\n%s", temp->username);
            temp = temp->next;
        }

    }
    fclose(lockoutFile);
}
//checks if the username is inside lockout -100 if not 100 if

int isLocked(char* user) {

    FILE *lockoutFile = fopen("lockout", "r");
    lockOutT *head = malloc(sizeof (lockOutT));
    lockOutT *temp = malloc(sizeof (lockOutT));
    lockOutT *newElement = malloc(sizeof (lockOutT));
    lockOutT *prev = malloc(sizeof (lockOutT));
    
    if(head == NULL || temp == NULL || newElement == NULL || prev == NULL) {
        //Malloc error
    }
    
    int count = 0;
    int saveCount = 0;
    //fprintf(stderr,"initVars");

    while (!feof(lockoutFile)) {
        newElement = malloc(sizeof (lockOutT));
        
        if(newElement == NULL) {
            //Malloc error
        }
        newElement->next = 0;
        if(fscanf(lockoutFile, "%19s", newElement->username) == 0) {
            //Error
        }
        //fprintf(stderr,"\n Locked Out user: %s",newElement->username);
        if (count == 0) {
            head = newElement;
            temp = head;
        } else {
            temp->next = newElement;
            temp = newElement;
        }
        count++;
    }
    saveCount = count;
    temp = head;
    for (count = count; count > 0; count--) {
        //fprintf(stderr,"\n Locked Out user: %s",temp->username);
        if (strncmp(user, temp->username, 20) == 0) {
            return 100;
        }
        prev = temp;
        temp = temp->next;
    }
    fclose(lockoutFile);
    return -100;

}
//prompts and deletes user

int deleteUser() {
    FILE *logins = fopen("logins", "r");
    LoginT *head = malloc(sizeof (LoginT));
    LoginT *temp = malloc(sizeof (LoginT));
    LoginT *newElement = malloc(sizeof (LoginT));
    LoginT *prev = malloc(sizeof (LoginT));
    
    if(head == NULL || temp == NULL || newElement == NULL || prev == NULL) {
        //Malloc error
    }
    int count = 0;
    int saveCount = 0;
    int numRmv = 0;
    char usernameBuffer[20];
    initializeString(usernameBuffer, 20);

    while (getchar() != '\n'); // clean out buffer
    printf("ENTER USER: ");
    
    if(fgets(usernameBuffer, 20, stdin) == NULL) {
        //Error
    }
    sanitizeInput(usernameBuffer, 20);



    while (!feof(logins)) {
        newElement = malloc(sizeof (LoginT));
        
        if(newElement == NULL) {
            //Error
        }
        newElement->next = 0;
        
        if(fscanf(logins, "%19s", newElement->username) == 0) {
            //Error
        }
        printf("got username:%s \n", newElement->username);
        
        if(fscanf(logins, "%19s", newElement->password) == 0) {
            //Error
        }
        printf("got password:%s \n", newElement->password);
        
        char number[2] = {'\0', '\0'};
        if(fgets(number, 2, logins) == NULL) {
            //Error
        }
        
        newElement->permissionLevel = (int) strtol(number, NULL, 10);
        
        printf("got permissionLevel:%i \n", newElement->permissionLevel);
        
        if(fscanf(logins, "%19s", &newElement->uuid) == 0) {
            //Error
        }
        printf("got puuid:%s \n", newElement->uuid);


        if (count == 0) {
            head = newElement;
            temp = head;
        } else {
            temp->next = newElement;
            temp = newElement;
        }
        //temp = newElement->next;
        //printf("%i: %s, %s, %i\n",count,newElement->username,newElement->password,newElement->permissionLevel);
        count++;

    }
    fclose(logins);
    fprintf(stderr, "\nFinding CorrectLogin to do \n");
    // run through and see all the usernames+ pass and cmp
    temp = head;
    saveCount = count;
    if (strncmp(usernameBuffer, head->username, 20) == 0) {
        head=head->next;
        count = 0;
        numRmv++;
    } else {
        for (count = saveCount; count > 0; count--) {
            if (strncmp(usernameBuffer, temp->username, 20) == 0) {
                fprintf(stderr, "\nFOUND!!! %s", temp->username);
                prev->next = temp->next;
                numRmv++;
                temp = prev->next;
            }
            else {
                prev = temp;
                temp = temp->next;
            }
        }
    }
    //temp->next=0;
    temp = head;
    logins = fopen("logins", "w+");
    for (count = count; count < saveCount - numRmv; count++) {
        fprintf(stderr, "\n%s,!\n", temp->username);
        if (count == 0)fprintf(logins, "%s", temp->username);
        else fprintf(logins, "\n%s", temp->username);
        fprintf(logins, " %s", temp->password);
        fprintf(logins, " %i", temp->permissionLevel);
        fprintf(logins, " %s", temp->uuid);
        if (temp->next != 0) {
            temp = temp->next;
        }
    }
    fclose(logins);
}