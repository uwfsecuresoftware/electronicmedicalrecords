/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: qwex
 *
 * Created on April 12, 2016, 7:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "MainMenu.h"
#include "Login.h"
#include "Sanitizer.h"

/*
 * 
 */
int main(int argc, char** argv) {
    LoginT * login = loginMain();
    printf("%s",login->username);
   if(login!=NULL){
       displayMainMenu(login->permissionLevel,0,login->username,login->uuid);
   }
       
    
    return (EXIT_SUCCESS);
}

