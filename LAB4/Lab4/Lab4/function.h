//
//  function.h
//  Lab4
//
//  Created by Admin on 19.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#ifndef function_h
#define function_h
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void insertInTable(sqlite3 *, char*, char*);
void selectFromTable(sqlite3 *, char*, char*);
void deleteFromTable(sqlite3*, char*, char*);
void doIt(char*, sqlite3*, char*);
void param(sqlite3*, char*, char*);
void getPhoto(sqlite3*, char*, char*);
static int callback(void *, int , char **, char **);

#endif /* function_h */
