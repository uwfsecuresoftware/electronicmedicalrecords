/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//Level- 1 patient, 2 nurse, 3 doc, 4 admin



#include <stdio.h>
#include "Login.h"
#include "User.h"
#include "utility.h"
#include "Sanitizer.h"
void displayMainMenu(int level, int remind,char* username, char* uuid){
    
   
    //level =4;
    remind =0;

   int choice =0;
   char temp[2];
   char usernameBuffer[20];
   char uuidBuffer[33];

  do{  
	  
	while(getchar()!='\n');//clean buffer
    choice =0;
    printf("WELCOME TO THE UWF SSD SECURE MEDICAL RECORDS \n");
    printf("Your Permission Level is: %i\n",level);
    
    if(level == 1){//patient
        printf("[1] View personal records\n");
        printf("[2] Edit personal info\n");
	    printf("[9] Exit Menu \n");
    	
	if(remind == 0){
        	printf("You have no reminders\n");
    	}else{
        //Reminders funct
    	}

	if(fgets( temp,2,stdin) == NULL){};
		sanitizeInt(temp,2);
	    choice = temp[0] -48;

	    //scanf(" %d", &choice);
    	switch(choice){
	    case 1://View pers rec funct
	    displayPatient(uuid);
            break;
            case 2://Edit personal info funct
            break;
	    case 9:
	        printf("Exiting menu \n");
		break;
	    default:
	        printf("Invalid input\n");
	    break;
    	}	
    }else if(level ==2){//nurse
        printf("[1] View Patient records\n");
	    printf("[2] Update Patient records \n");
        printf("[3] Record vitals\n"); 
        printf("[9] Exit menu \n");
	if(fgets( temp,2,stdin) == NULL){};
	choice = temp[0] -48;


	switch(choice){
	    case 1://View patients info
	    break;
	    case 2://view update patient records 
                while(getchar()!='\n');// clean out buffer
                initializeString(uuidBuffer,33);
                if(fgets(uuidBuffer,32,stdin)){};
                sanitizeInput(uuidBuffer, 32);
                editPatient(uuidBuffer);
	    break;
	    case 3://Record vitals funct
	    break;
	    case 9://exit
	        printf("Exiting menu \n");
		break;
	    default:
	        printf("Invalid input");
	    break;
	}
    }else if(level == 3){//Doc
        printf("[1] View Patient records\n");
	printf("[2] Update Patient records \n");
	printf("[3] Medical Reconciliation \n");
	printf("[4] Transfer of care \n");
	printf("[9] Exit menu \n");

	if(fgets( temp,2,stdin) == NULL){};
    choice = temp[0] -48;

	switch(choice){
	    case 1://View patients info
	    break;
	    case 2://Update rec
	    break;
	    case 3://Medical rec
	    break;
	    case 4://Transfer 
	    break;
	    case 9://exit
	        printf("Exiting \n");
		break;
	    default:
	        printf("Invalid input\n");
	    break;

	}

    }else if(level == 4){//admin

	printf("[1] Set up new User account \n");
	//printf("[2] Deactivate User account \n");
        printf("[2] Unlock User account\n");
	printf("[9] Exit menu \n");
        if(fgets( temp,2,stdin) == NULL){};
        choice = temp[0] -48;

        
	switch(choice){
	    case 1://Setup user
                createUser();
	    break;
	    //case 2://remove user
                //if(deleteUser()){};
	    //break;
            case 2:
                while(getchar()!='\n');// clean out buffer
                initializeString(usernameBuffer,20);
                if(fgets(usernameBuffer,20,stdin)){};
                sanitizeInput(usernameBuffer, 20);
                unlock(usernameBuffer);
                break;
	    case 9:
	        printf("Exiting menu \n");
		break;
	    default:
	        printf("Invalid input \n");
		break;
	}

    }
  }while(choice != 9);   
}
