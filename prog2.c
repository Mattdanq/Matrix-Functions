
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "prog2.h"



/**
* 
*  Function "stubs" for Assignment 2 exercises.
*
*  See prog2.h for specifications of function behavior.
*
*/



/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/
char ** alloc_square_mtx(int n) {
  char ** pArray;
  int r = n, c = n;  
  pArray = (char**)malloc((r) * sizeof(char*));
  for (int a = 0; a < c; a++) {
    pArray[a] = (char*)malloc((c) * sizeof(char));
  }
  return pArray;
}

void free_square_mtx(char **m, int n) {
  for (int a = 0; a < n; a++) {
    free(m[a]);
  }
  free(m);
}

void pop_mtx_alpha(char **m, int n){
  int r = n, c = n;
  srand(time(0));
  for (int a = 0; a < r; a++) {
    for (int b = 0; b < c; b++) {
       char randnum = ((rand() % 26) + 97);
       m[a][b] = randnum;
    }
  }
}


void display_mtx(char **m, int n){
  int r = n, c = n;
  srand(time(0));
  for (int a = 0; a < r; a++) {
    for (int b = 0; b < c; b++) {
      printf("%c ",m[a][b]);
    }
    printf("\n");
  }
}

void swap_rows(char **m, int n, int r1, int r2){
  int r = n, c = n;
  if (r1 > n || r2 > n) {
    return;
  }
  char* tempArr;
  tempArr = malloc((n) * sizeof(char));
  for (int a = 0; a < r; a++) {
    tempArr[a] = m[r1][a];
    m[r1][a] = m[r2][a];
  }
  for (int b = 0; b < r; b++) {
    m[r2][b] = tempArr[b];
  }
  free(tempArr);
}

void swap_cols(char **m, int n, int c1, int c2){
  int r = n, c = n;
  if (c1 > n || c2 > n) {
    return;
  }
  char* tempArr;
  tempArr = malloc((n) * sizeof(char));
  for (int a = 0; a < r; a++) {
    tempArr[a] = m[a][c1];
    m[a][c1] = m[a][c2];
  }
  for (int b = 0; b < r; b++) {
    m[b][c2] = tempArr[b];
  }
  free(tempArr);
}


void rotate_right(char **m, int n){
  int buffer = 0;
  if (n % 2 != 0) {
    buffer = 1;
  }
  for (int a = 0; a < (n/2) + buffer; a += 1) {
    char temp_right[n], temp_bottom[n], temp_left[n], temp_top[n];
    //top to right
    int counter = 0;
    for (int b = a; b < n - a; b++) {
      temp_right[counter] = m[b][n - a - 1];
      m[b][n - a - 1] = m[a][b];
      counter++;
    }

    //right to bottom
    counter = 0;
    for (int c = a; c < n - a; c++) {
      temp_bottom[counter] = m[n - a - 1][n - c - 1];
      m[n - a - 1][n - c - 1] = temp_right[counter];
      counter++;
    }
    temp_bottom[0] = temp_right[counter - 1];

    //bottom to left
    counter = 0;
    for (int d = n - a - 1; d > -1 + a; d--) {
      temp_left[counter] = m[d][a];
      m[d][a] = temp_bottom[counter];
      counter++;
    }
    temp_left[0] = temp_bottom[counter - 1];

    //left to top
    counter = 0;
    for (int e = a; e < n - 1; e++) {
      temp_top[counter] = m[a][e];
      m[a][e] = temp_left[counter];
      counter++;
    }
  }
}

void floating_boulders(char **m, int n, int nb) {
  int boulder = 1;
  int allBould = 0;
  int numBoul = nb;
  int r = n, c = n;
  int count = 0;
  srand(time(0));
  if (nb >= n*n) {
    allBould = 1;
  }
  for (int a = 0; a < r; a++){
    for (int b = 0; b < c; b++) {
      if (numBoul <= 0) {
        boulder = 0;
      }
      int randN = rand() % 2;
      if (allBould == 1) {
        m[a][b] = '#';      
      } else if (randN == 1 && boulder != 0) {
        m[a][b] = '#';
        numBoul -= 1;
        count++;
      } else {
        m[a][b] = '.';
      }
    }
  }
}


void mountains(char **m, int n){
  int r = n, c = n;
  srand(time(0));
  for (int a = 0; a < r; a++) {
    for (int b = 0; b < c; b++) {
      int randN = -1;
      if (a == 0) {
        randN = rand() % 2;
      } else {
        if (m[a - 1][b] != '#') {
          randN = rand() % 2;
        }
      }
      if (randN == -1) {
        if (m[a - 1][b] == '#') {
          m[a][b] = '#';
        } else {
          m[a][b] = '.';
        }
      } else if (randN == 1) {
        m[a][b] = '.';
      } else {
        m[a][b] = '#';
      }
    }
  }
}



void sink(char **m, int n){
  int r = n, c = n;
  for (int b = 0; b < c; b++) {
    for (int a = 0; a < r; a++) {
      if (m[a][b] != '.') {
        m[a][b] = '.';
        a = r;
      }
    }
  }
}



void gravity(char **m, int n){
  int r = n, c = n;
  for (int b = 0; b < c; b++) {// iterates through column
    int gravity = 0;
    int counter = 0;
    char **colHold = malloc((n) * sizeof(char*));
    for (int a = 0; a < r; a++) {//iterates through row
      if (m[a][b] == '.') {
        gravity = 1;
      } else {
        colHold[counter] = &m[a][b];
        counter++;
      }
    }
    
    if (gravity == 1) {
      char** temp = realloc(colHold, counter * sizeof(char*));
      colHold = temp;
      int counter2 = 0;
      for (int a = r - 1; a > -1; a--) { //iterates through row
        if (a >= (r - counter)) {
          m[a][b] = *colHold[counter - 1 - counter2];
        } else {
          m[a][b] = '.';
        }
      }
      //free(temp);
    }
    
    free(colHold);
  }
}




/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


void str_trim(char *s) {
  /*
  char temp1 = s[0];
  s[0] = s[1];
  s[1] = temp1;
  

  printf("test\n");
  printf("at0:%c", s[0]);
  printf("at1%c",s[1]);
  printf("%c", temp1);
  printf("\ntest\n");
  */
  //*s = malloc(strlen(s) * sizeof(char));
  int leading = 0;
  int trailing = 0;
  
  for (int a = 0; a < strlen(s); a++) {
    if (!isspace(s[a])) {
      leading = a;
      break;
    }
  }
  
  for (int b = 0; b < strlen(s) - leading; b++) {
    char temp1 = s[leading + b];
    s[leading + b] = s[b];
    s[b] = temp1;
  }
 
  for (int a = strlen(s); a > -1; a--) {
    if (!isspace(s[a])) {
      s[a - 2] = '\0';
      break;
    }
  }

}


int str_search(char *s, char *pattern) {
  int checker = 0;
  for (int a = 0; a < strlen(s); a++) {
    checker = 0;
    if (s[a] == pattern[0]) {
      for (int b = 1; b < strlen(pattern); b++) {
        char hold1 = s[a+b];
        char hold2 = pattern[b];
        if (hold1 != hold2){
          b = strlen(pattern);
          checker = 0;
        } else {
          checker = 1;
        }
      }
      if (checker == 1) {
        return a;
      }
    }
  }
  return -1;  
}





#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
              // IT DOESN"T CHANGE HOW YOUR PROGRAM
              // WORKS, BUT IT GIVES US A WAY TO CALL
              // YOUR FUNCTIONS FROM OUR CODE FOR
              // TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main(){



  // test driver
  char **m;
  char **boulder;
  char **mountain;
  int testi = 9;

  printf("Making a Square Matrix...\n");
  m = alloc_square_mtx(testi);

  printf("Populating Square Matrix...\n");
  pop_mtx_alpha(m, testi);

  printf("\nDisplaying Current Matrix\n");
  display_mtx(m, testi);

  printf("\nSwapped Row 3 and 6 in the Square Matrix\n");
  swap_rows(m, testi, 2, 6);
  display_mtx(m, testi);

  printf("\nSwapped Column 6 and 7 in the Square Matrix\n");
  swap_cols(m, testi, 6, 7);
  display_mtx(m, testi);
  
  printf("\nRotating Square Matrix\n");
  rotate_right(m, testi);
  display_mtx(m, testi);
  free_square_mtx(m,testi);

  printf("\nShowing 20 Boulder Landscape\n");
  boulder = alloc_square_mtx(9);
  floating_boulders(boulder, 9, 20);
  display_mtx(boulder, 9);

  printf("\nShowing Mountain Landscape\n");
  mountain = alloc_square_mtx(9);
  mountains(mountain, 9);
  display_mtx(mountain, 9);

  printf("\nSinking Current Mountain\n");
  sink(mountain, 9);
  display_mtx(mountain, 9);

  printf("\nApplying Gravity to the Mountain\n");
  gravity(boulder, 9);
  display_mtx(boulder, 9);
  free_square_mtx(mountain, 9);
  free_square_mtx(boulder, 9);
  
  printf("\nMessing with the string name\n");
  printf("\nBefore:| val ue |\n");
  char name[] = " val ue ";
  str_trim(name);
  printf("Now:|");

  for (int a = 0; a < strlen(name); a++) {
    printf("%c", name[a]);
  }
  printf("|\n");
  
  printf("\nNOOAFSFAbowFasfdasbow - bow\n");
  char a[] = "bow";
  char b[] = "NOOAFSFAbwFasfdasbo";
  int nut = str_search(b, a);
  printf("Index:%i",nut);

  return 0;
}


#endif        // DO NOT REMOVE THIS LINE!!!
