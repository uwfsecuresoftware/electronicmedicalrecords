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

/*
 * 
 */
int main(int argc, char** argv) {
    
    char usernameBuffer[20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    char passwordBuffer[20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    
    fgets(usernameBuffer,20,stdin);
    fgets(passwordBuffer,20,stdin);
    
    displayMainMenu();
    printf("%i",loginUser(usernameBuffer,passwordBuffer));
    return (EXIT_SUCCESS);
}

