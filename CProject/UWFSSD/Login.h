/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Login.h
 * Author: qwex
 *
 * Created on April 12, 2016, 8:03 PM
 */

#ifndef LOGIN_H
#define LOGIN_H

int loginMain();
int loginUser(char* , char*);
int createUser();

typedef struct{
    char username[20];
    char password[20];
    int permissionLevel;
    char uuid[33];
    struct LoginT *next;
}LoginT;

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* LOGIN_H */

