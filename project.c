// Developed By Dhaval Gohel, Jenil Gandhi, Chirag prajapati

#include<stdio.h>

#include<conio.h>

#include<string.h>

#include<stdint.h>

#include<stdbool.h>

#include<stdlib.h>

#define AI_PAPER "ai.txt"
#define BLOCKCHAIN_PAPER "blockchain.txt"
#define CRYPTOCURRENCY_PAPER "cryptocurrency.txt"
#define MAHABHARAT_PAPER "mahabharat.txt"
#define POLITICS_PAPER "politics.txt"

#define AI_ANSWER "ai_ans.txt"
#define BLOCKCHAIN_ANSWER "blockchain_ans.txt"
#define CRYPTOCURRENCY_ANSWER "cryptocurrency_ans.txt"
#define MAHABHARAT_ANSWER "mahabharat_ans.txt"
#define POLITICS_ANSWER "politics_ans.txt"

#define MAX_NO_OF_STUDENTS 20
#define MAX_NO_OF_SUBJECTS 5
#define MAX_NO_OF_QUESTIONS 5

char * Subjects[MAX_NO_OF_SUBJECTS] = {
  "Artificial Intelligence",
  "Blockchain",
  "Cryptocurrency",
  "Mahabharat",
  "Politics"
};

typedef struct student {
  int enrollno;
  char name[25];
  int marks[5];
}
student_t;

student_t student[MAX_NO_OF_STUDENTS];
FILE * fp;
int record_ans[MAX_NO_OF_QUESTIONS];
int ans_key[MAX_NO_OF_QUESTIONS];

int find_enrollment_no(int input) {
  for (int i = 0; i < MAX_NO_OF_STUDENTS; i++) {

    if (student[i].enrollno == input) {
      return i;
    }
  }
  return -1;
}

void print_student_scorecard(int num) {
  printf("Students Report Card eno %d\n",student[num].enrollno);
  for (int i = 0; i < MAX_NO_OF_SUBJECTS; i++) {
    printf(" Subject : %s  Marks : %d \n", Subjects[i], student[num].marks[i+1]);
  }
}

void display_questions(const char * path) {
  char ch;
  fp = fopen(path, "r");
  if (fp == NULL) {
    printf("File operation Failed\n");
  } else {
    do {
      /* Read single character from file */
      ch = fgetc(fp);

      /* Print character read on console */
      putchar(ch);

    } while (ch != EOF); /* Repeat this if last read character is not EOF */

    /* Done with this file, close file to release resource */
    fclose(fp);
  }
}

void answer_key(const char * path) {
  int i = 0;
  fp = fopen(path, "r");
  if (fp == NULL) {
    printf("File operation Failed\n");
  } else {
    while (fscanf(fp, "%d", & ans_key[i]) != EOF) {
      ++i;
    }
  }
  fclose(fp);
}

int record_answers(int num, int subject_code) {
  int score = 0;
  printf("\nRecord answers\n");
  for (int i = 0; i < MAX_NO_OF_QUESTIONS; i++) {
    printf("Enter Answer of Question:%d\n", i);
    scanf("%d", & record_ans[i]);
    if (ans_key[i] == record_ans[i]) {
      score++;
    }
  }
  printf("total Score = %d\n", score);
  student[num].marks[subject_code] = score;
  return true;
}

int main(void) {
  int input, subject_code, num;
  char option = '\0';
  int n = 0, ret_val;
  int value = false;
  printf("============================== Welcome To General Knowledge Quiz ==============================\n\n");
  printf("============================== Created By Algo Massiahs =======================================\n\n");

  while (value != -1) {
    printf("Enter y/Y to enter new students details or press n/N to take test continue\n");
    scanf("%c", &option);
    
    if (option == 'Y' || option == 'y') {
      printf("\nEnter your name\t:");
      scanf("%s", student[n].name);
      printf("\nEnter roll no.\t:");
      scanf("%d", & student[n].enrollno);
      printf("\n\nstudent name = %s student id = %d \n ", student[n].name, student[n].enrollno);
      n++;
    } else if (option == 'n' || option == 'N') {
      printf("\nEnter student enrollment no \n");
      scanf("%d", & input);
      num = find_enrollment_no(input);
      if (num == -1) {
        printf("student record not found \n");
      } else {
        printf("\n\nLogged in as:%s \n", strupr(student[num].name)); //name displays in upper case//
        printf("\n Enter your option \n1)Take Test \n2)View previous score\n");
        scanf("%d", &input);
        if (input == 1) {
          printf("Enter subject Code to give exam \n \
                1)Artificial Intelligence\n \
                2)Blockchain \n \
                3)Cryptocurrency\n \
                4)Mahabharat\n \
                5)Politics\n \
                6)\texit\n");
          scanf("%d", & input);
          switch (input) {
          case 1:
            display_questions(AI_PAPER);
            answer_key(AI_ANSWER);
            subject_code = 1;
            break;
          case 2:
            display_questions(BLOCKCHAIN_PAPER);
            answer_key(BLOCKCHAIN_ANSWER);
            subject_code = 2;
            break;
          case 3:
            display_questions(CRYPTOCURRENCY_PAPER);
            answer_key(CRYPTOCURRENCY_ANSWER);
            subject_code = 3;
            break;
          case 4:
            display_questions(MAHABHARAT_PAPER);
            answer_key(MAHABHARAT_ANSWER);
            subject_code = 4;
            break;
          case 5:
            display_questions(POLITICS_PAPER);
            answer_key(POLITICS_ANSWER);
            subject_code = 5;
            break;
          case 6:
            value = -1;
            exit(0);
            break;
          default:
            printf("Invalid response: Please enter valid response\n");
          }
          ret_val = record_answers(num, subject_code);
          if (ret_val != true) {
            printf("Failed to record answers\n");
          }

        } 
        else if (input == 2) {
          print_student_scorecard(num);
        }
      }
    }
    continue;
  }
  return 0;
}