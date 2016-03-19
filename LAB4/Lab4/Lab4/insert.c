//
//  insert.c
//  Lab4
//
//  Created by Admin on 19.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <stdio.h>
#include "function.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


void insertInTable(sqlite3 * db, char* sql, char* zErrMsg)
{
    
    char firstname[15], lastname[15], middlename[15], birthday[15], place[30], address[30], department[10], position[15], startWork[15], photoName[50];
    printf ("\n=======INSERT=======\n");
    printf ("Enter 0 for cancel\n");
    printf ("Enter firstname: ");
    scanf ("%s", firstname);
    if (strcmp(firstname, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf ("Enter lastname: ");
    scanf ("%s", lastname);
    if (strcmp(lastname, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }    printf ("Enter middlename: ");
    scanf ("%s", middlename);
    if (strcmp(middlename, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf ("Enter you birthday: ");
    scanf ("%s", birthday);
    if (strcmp(birthday, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf ("Enter place, where you born: ");
    scanf ("%s", place);
    if (strcmp(place, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf ("Enter you country: ");
    scanf ("%s", address);
    if (strcmp(address, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf ("Enter your department: ");
    scanf ("%s", department);
    if (strcmp(department, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf("Enter your position: ");
    scanf ("%s", position);
    if (strcmp(position, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf ("Enter date of start working: ");
    scanf ("%s", startWork);
    if (strcmp(startWork, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    printf("Enter the name of photo: ");
    scanf("%s", photoName);
    if (strcmp(photoName, "0") == 0)
    {
        printf ("Cancel.");
        return;
    }
    
    
    sql = "INSERT INTO worker(firstname, lastname, middlename, birthday, place, address, department, position, startWork) VALUES(";
    
    char *str = malloc (sizeof(char) * 300);
    strcat(str, sql);
    strcat(str, "'");
    strcat(str, firstname);
    strcat(str, "','");
    strcat(str, lastname);
    strcat(str, "','");
    strcat(str, middlename);
    strcat(str, "','");
    strcat(str, birthday);
    strcat(str, "','");
    strcat(str, place);
    strcat(str, "','");
    strcat(str, address);
    strcat(str, "','");
    strcat(str, department);
    strcat(str, "','");
    strcat(str, position);
    strcat(str, "','");
    strcat(str, startWork);
    strcat(str, "');");
    printf(str);
    
    int rc = -1;
    rc = sqlite3_exec(db, str, callback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK)
    {
        printf ("SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        
    }
    else
    {
        printf ("\nRecords is successfull add!\n");
        
    }
    free(str);
    
    
    //IMG entering
    
    FILE *fp = fopen(photoName, "rb");
    
    if (fp == NULL) {
        
        fprintf(stderr, "Cannot open image file\n");
        return;
    }
    
    fseek(fp, 0, SEEK_END);
    
    int flen = ftell(fp);
    
    fseek(fp, 0, SEEK_SET);
    
    char data[flen+1];
    int size = fread(data, 1, flen, fp);
    fclose(fp);
    
    
    sqlite3_stmt *pStmt;
    
    char str1[150]= "UPDATE worker SET photo = ? WHERE firstname = '";
    strcat(str1, firstname);
    strcat(str1, "' AND lastname = '");
    strcat(str1, lastname);
    strcat(str1, "';");
    printf(str1);
    
    rc = sqlite3_prepare(db, str1, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        
        return;
    }
    
    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);
    
    rc = sqlite3_step(pStmt);
    
    if (rc != SQLITE_DONE) {
        
        printf("execution failed: %s", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(pStmt);
    
    
    // IMG.end
    
    
    
}