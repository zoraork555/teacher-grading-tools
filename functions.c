// Ashton Johnson 11797181 CS110
// This file contains five functions that accompany main.c in looking through the grades for a zyBooks chapter
// getMin finds the column specified and then grabs each element in the column and compares it to see if it is the lowest grade
// getMax finds the column specified and then grabs each element in the column and compares it to see if it is the highest grade
// getAvg finds the column specified and then grabs each element in the column and averages them
// getCount finds the column specified and then grabs each element in the column to see if it is equal to or above a threshold grade given in the call
// getGrade checks the first two elements of each row to see if the given name is there. It grabs the wight of each section from the titles in the first row. If the name is found, it grabs the other elements in the line into a total and averages the based on the weight.
// The first four functions ignore blank cells and the last one runs blank cells as zeroes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Given a csv file, return the minimum of the specified column, excluding blanks
// return -1.0 if the column is optional
// return -2.0 if the column does not exist
double getMin(char csvfile[], char column[]) {
  FILE *fp=fopen(csvfile, "r");
  char type, line[3001], tempLine[30];
  int chap, sec, columns=2, col, test=0;
  double min=1000000;
  sscanf(column, "%c%d.%d", &type, &chap, &sec);
    fgets(line, 3001, fp); //grab first line
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp; //initialize a temp var
    char *token = strsep(&start, ","); // get rid of first two columns (first name, last name)
    token = strsep(&start, ",");

    while (1) { //get each element of current line
      token = strsep(&start, ","); // following lines grab the chapter, section, and type from each column title
      if (token==NULL) break;
      char *tamp1 = strsep(&token, ".");
      char *tamp2 = strsep(&token, " ");
      char *tamp3 = strsep(&token, "-");
      tamp3 = strsep(&token, " ");
      tamp3 = strsep(&token, " ");
      int currChap = atoi(tamp1);
      int currSec = atoi(tamp2);
      char currType = tamp3[0];

      if (currChap==chap && currSec==sec && currType==type) { // checks to see if the grabbed info is the same as what was called for
        col=columns;
        test=1;
        break;
      }
      columns++;
    }
    strncpy(tempLine, line, 30); // holds last line for comparison in order to break
    if (test==0) return -2.0; // if the column called wasn't found, return that

  char *tok;
  double current;
  while (1) {
    fgets(line, 3001, fp); // get each line after first
    if ((strncmp(line, tempLine, 28)==0)) break;
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp;
    for (int i=0; i<=col; ++i) { //go to element of found column
      tok = strsep(&start, ",");
    }
    if (strcmp(tok, "N/A\0")==0 || strcmp(tok, "N/A\n")==0) return -1.0; // if N/A return optional
    if (tok[0]!=13 && tok[0]!=0) { // if not null character or not carriage end
      current = atof(tok);
      //printf("%f -%d-\n", current, tok[0]);
      if (current<min) min=current;
    }
    strncpy(tempLine, line, 30);
  }
  fclose(fp);
  return min; //return calculation
}

// Given a csv file, return the maximum of the specified column, excluding blanks
// return -1.0 if the column is optional
// return -2.0 if the column does not exist
double getMax(char csvfile[], char column[]) {
  FILE *fp=fopen(csvfile, "r");
  char type, line[3001], tempLine[30];
  int chap, sec, columns=2, col, test=0;
  double max=-1000000;
  sscanf(column, "%c%d.%d", &type, &chap, &sec);
    fgets(line, 3001, fp);
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp;
    char *token = strsep(&start, ",");
    token = strsep(&start, ",");

    while (1) { //get each element of current line
      token = strsep(&start, ",");
      if (token==NULL) break;
      char *tamp1 = strsep(&token, ".");
      char *tamp2 = strsep(&token, " ");
      char *tamp3 = strsep(&token, "-");
      tamp3 = strsep(&token, " ");
      tamp3 = strsep(&token, " ");

      int currChap = atoi(tamp1);
      int currSec = atoi(tamp2);
      char currType = tamp3[0];

      if (currChap==chap && currSec==sec && currType==type) {
        col=columns;
        test=1;
        break;
      }
      columns++;
    }
    strncpy(tempLine, line, 30);
    if (test==0) return -2.0;

  char *tok;
  double current;
  while (1) { // get each line after first
    fgets(line, 3001, fp);
    if ((strncmp(line, tempLine, 28)==0)) break;
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp;
    for (int i=0; i<=col; ++i) { //go to element of found column
      tok = strsep(&start, ",");
    }
    if (strcmp(tok, "N/A\0")==0 || strcmp(tok, "N/A\n")==0) return -1.0;
    if (tok[0]!=13 && tok[0]!=0) {
      current = atof(tok);
      if (current>max) max=current;
      //printf("%f -%d- %f\n", current, tok[0], max);
    }
    strncpy(tempLine, line, 30);
  }
  fclose(fp);
  return max; //return calculation
}

// Given a csv file, return the average of the specified column, excluding blanks
// return -1.0 if the column is optional
// return -2.0 if the column does not exist
double getAvg(char csvfile[], char column[]) {
  FILE *fp=fopen(csvfile, "r");
  char type, line[3001], tempLine[30];
  int chap, sec, columns=2, col, test=0;
  double total=0;
  sscanf(column, "%c%d.%d", &type, &chap, &sec);
    fgets(line, 3001, fp);
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp;
    char *token = strsep(&start, ",");
    token = strsep(&start, ",");

    while (1) { //get each element of current line
      token = strsep(&start, ",");
      if (token==NULL) break;
      char *tamp1 = strsep(&token, ".");
      char *tamp2 = strsep(&token, " ");
      char *tamp3 = strsep(&token, "-");
      tamp3 = strsep(&token, " ");
      tamp3 = strsep(&token, " ");

      int currChap = atoi(tamp1);
      int currSec = atoi(tamp2);
      char currType = tamp3[0];

      if (currChap==chap && currSec==sec && currType==type) {
        col=columns;
        test=1;
        break;
      }
      columns++;
    }
    strncpy(tempLine, line, 30);
    if (test==0) return -2.0;

  int rows=0;
  char *tok;
  double current;
  while (1) { // get each line after first
    fgets(line, 3001, fp);
    if ((strncmp(line, tempLine, 28)==0)) break;
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp;
    for (int i=0; i<=col; ++i) { //go to element of found column
      tok = strsep(&start, ",");
    }
    if (strcmp(tok, "N/A\0")==0 || strcmp(tok, "N/A\n")==0) return -1.0;
    if (tok[0]!=13 && tok[0]!=0) { // for each element, add to total as long as it's not null or carriage end; count times
      current = atof(tok);
      //printf("%f -%d-\n", current, tok[0]);
      total+=current;
      ++rows;
    }
    strncpy(tempLine, line, 30);
  }
  fclose(fp);
  return (total/rows);
}

// Given a csv file, return the number of students with their column value >= threshold, excluding blanks
// return -1 if the column is optional
// return -2 if the column does not exist
int getCount(char csvfile[], char column[], double threshold) {
  FILE *fp=fopen(csvfile, "r");
  char type, line[3001], tempLine[30];
  int chap, sec, columns=2, col, test=0;
  int count=0;
  sscanf(column, "%c%d.%d", &type, &chap, &sec);
    fgets(line, 3001, fp);
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp;
    char *token = strsep(&start, ",");
    token = strsep(&start, ",");

    while (1) { //get each element of current line
      token = strsep(&start, ",");
      if (token==NULL) break;
      char *tamp1 = strsep(&token, ".");
      char *tamp2 = strsep(&token, " ");
      char *tamp3 = strsep(&token, "-");
      tamp3 = strsep(&token, " ");
      tamp3 = strsep(&token, " ");

      int currChap = atoi(tamp1);
      int currSec = atoi(tamp2);
      char currType = tamp3[0];

      if (currChap==chap && currSec==sec && currType==type) {
        col=columns;
        test=1;
        break;
      }
      columns++;
    }
    strncpy(tempLine, line, 30);
    if (test==0) return -2.0;

  char *tok;
  double current;
  while (1) { // get each line after first
    fgets(line, 3001, fp);
    if ((strncmp(line, tempLine, 28)==0)) break;
    char temp[strlen(line)+1];
    strcpy(temp, line);
    char *start=temp;
    for (int i=0; i<=col; ++i) { //go to element of found column
      tok = strsep(&start, ",");
    }

    if (strcmp(tok, "N/A\0")==0 || strcmp(tok, "N/A\n")==0) return -1.0;
    //if (strncmp(tok, "N/A", 3)==0 || strncmp(tok, "N/A", 3)==0) return -1.0;
    if (tok[0]!=13 && tok[0]!=0) { // for each element, increase count if it meets or breaks the threshold
      current = atof(tok);
      //printf("%f -%d-\n", current, tok[0]);
      if (current>=threshold) ++count;
    }
    strncpy(tempLine, line, 30);
  }
  fclose(fp);
  return count;
}

// Given a csv file, return the weighted average of the specified student
// A blank cell is viewed as 0 for this function
// return -2.0 if there is no such student.
double getGrade(char csvfile[], char first[], char last[]) {
  FILE *fp=fopen(csvfile, "r");
  char line[3001], tempLine[30];
  int test=0, co=0;
  double count=0, weight[100];

  fgets(line, 3001, fp);
  char temp[strlen(line)+1];
  strcpy(temp, line);
  char *start=temp;
  char *token = strsep(&start, ",");
  token = strsep(&start, ",");

  while (1) { //get each element of current line grab the weight for each column and put it in an array
    token = strsep(&start, ",");
    if (token==NULL) break;
    char *tamp1 = strsep(&token, "(");
    tamp1 = strsep(&token, ")");
    weight[co] = atof(tamp1);
    count+=atof(tamp1);
    ++co;
  }

    while (1) { //get each element of current line
      fgets(line, 3001, fp);
      if (strncmp(line, tempLine, 28)==0) break;
      char temp[strlen(line)+1];
      strcpy(temp, line);
      char *start=temp;
      char *token;
      char *tamp1 = strsep(&start, ","); // grab first and last
      if (tamp1==NULL) break;
      char *tamp2 = strsep(&start, ",");

      char first1[strlen(first)+1], last1[strlen(last)+1];
      strcpy(first1, first);
      strcpy(last1, last);
      if (last1[0]>=97 && last1[0]<=122) last1[0]-=32; // make the first letter of first and last name capital if they aren't
      if (first1[0]>=97 && first1[0]<=122) first1[0]-=32;
      if ((strcmp(tamp1, last1)==0) && (strcmp(tamp2, first1)==0)) { // check to see if this row is the right one
        test=1;
      }
      if (test==1) { // if it is the right one
        double total=0;
        double num;
        co=0;
        while (1) {
          token = strsep(&start, ",");
          if (token==NULL) {
            fclose(fp);
            return (total/count);
          }
          if (strcmp(token, "N/A")!=0) { //as long as the cell isnt optional
            num = atof(token);
            total+=(num * weight[co]); // add points * weight of column
          }
          co++;
        }
      }
      strncpy(tempLine, line, 30); // store beginning of last line for break comparison
    }
  fclose(fp);
  return -2.0; //name wasn't found
}
