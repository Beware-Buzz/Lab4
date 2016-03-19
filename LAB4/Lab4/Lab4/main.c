//
//  main.c
//  Lab4
//
//  Created by Admin on 19.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <stdio.h>
#include "function.h"

sqlite3 *db;
char *zErrMsg = 0;
int rc = 0;
char* sql;

void showMenu();
int init();
void exitProgram();



int main(int argc, const char * argv[])
{
    if (init() == 1)
    {
        printf("\nEmergency closing.\n");
        return 1;
    }
    showMenu();
    
    exitProgram();
    
    return 0;
}

int init()
{
    // open database
    rc = sqlite3_open("/Users/admin/Desktop/LAB4/untitled.db", &db);
    
    if (rc == 1)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    else
    {
        printf("Opened database successfully!\n");
        return 0;
    }
}


void showMenu()
{
    int choice = -1;
    
    while (choice < 0 || choice > 5)
    {
        printf("\n==========\nMAIN MENU\n==========\n");
        printf("1. Insert data in DataBase\n");
        printf("2. Select data from DataBase\n");
        printf("3. Delete data from DataBase\n");
        printf("4. Get parameterized query\n");
        printf("5. Get photo\n");
        printf("0. Exit\n");
        printf("Enter your number: ");
        scanf("%d", &choice);
        
        
        switch (choice) {
            case 0:
                exitProgram();
                exit(0);
                break;
            case 1:
                insertInTable(db, sql, zErrMsg);
                break;
            case 2:
                selectFromTable(db, sql, zErrMsg);
                break;
            case 3:
                deleteFromTable(db, sql, zErrMsg);
                break;
            case 4:
                param(db, sql, zErrMsg);
                break;
            case 5:
                getPhoto(db, sql, zErrMsg);
                break;
            default:
                printf("Invalid parameter.");
                break;
                
        }
        
        choice = -1;
    }
}

void exitProgram()
{
    sqlite3_close(db);
}
