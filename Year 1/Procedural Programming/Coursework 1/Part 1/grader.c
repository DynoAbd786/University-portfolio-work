#include <stdio.h>
#include <math.h>

// set a constant integer to the set number of students in spec sheet
#define STUDENT_MAX 32

// set a constant integer to the set number of scores per students in spec sheet
#define SCORES_MAX 4

// structure definition for the student, including the ID, 4 scores and average
typedef struct student
{
  int id;
  float scores[SCORES_MAX];
  int average;
}
student;

// pre-set array to represent 32 students
student students[STUDENT_MAX];


int main(int argc, char *argv[]) 
{

  // check if file is given in command line
  if (argc != 2)
  {
    printf("No input file name given. Exiting.\n");
    return 1;
  } 


  // attempt to open file 
  FILE *input;
  input = fopen(argv[1], "r");
  printf("Input file. Opening.\n");

  // if the file dosent exist, then terminate
  if (input == NULL)
  {
    printf("Input file does not exist. Exiting.\n");
    return 2;
  }


  // reading from file:
  // repeat for every known student
  for (int i = 0; i < STUDENT_MAX; i++)
  {
    // get student ID
    fscanf(input, "%i", &students[i].id);

    // get student scores using fscanf to get 1 number to 1 score 
    for (int j = 0; j < SCORES_MAX; j++)
    {
      fscanf(input, "%f", &students[i].scores[j]);
    }
  }

  // close input file
  printf("Input file. Closing.\n");
  fclose(input);


  // checking data
  printf("Checking data.\n");

  // repeat for all students
  for (int i = 0; i < STUDENT_MAX; i++)
  {
    // check if student ID is correct
    if (students[i].id < 2022000 || students[i].id > 2022099)
    {
      printf("Found an invalid student id: %d. Exiting.\n", students[i].id);
      return 3;
    }

    // checking scores
    for (int j = 0; j < SCORES_MAX; j++)
    {
      // check for grades out of bounds
      if (students[i].scores[j] < 0 || students[i].scores[j] > 100)
      {
        printf("Found an invalid grade: id %i grade %i. Exiting.\n", students[i].id, (int)students[i].scores[j]);
        return 4;
      }

      // check if grade is set below 20 and set it to 20
      else if (students[i].scores[j] < 20)
      {
        printf("Correcting student %i grade %i\n", students[i].id, (int)students[i].scores[j]);
        students[i].scores[j] = 20;
      }

      // check if grade is set above 90 and set it to 90
      else if (students[i].scores[j] > 90)
      {
        printf("Correcting student %i grade %i\n", students[i].id, (int)students[i].scores[j]);
        students[i].scores[j] = 90;
      }
    }
  }


  // compute average for each student
  printf("Computing averages.\n");

  // repeat for all students 
  for (int i = 0; i < STUDENT_MAX; i++)
  {
    // sum variable to find the total of all scores
    float sum = 0;

    for (int j = 0; j < SCORES_MAX; j++)
    {
      sum = sum + students[i].scores[j];
    }

    // calculate average and round using roundf function from math.h and
    // save average to its respected student
    students[i].average = roundf(sum/4.0);
  }


  // opening output file
  printf("Output file. Opening.\n");
  FILE *output;
  output = fopen("averages.txt", "w");

  // writing to averages.txt
  // repeat for every student
  for (int i = 0; i < STUDENT_MAX; i++)
  {
    // output to file
    fprintf(output, " %i %i\n", students[i].id, students[i].average);
  }

  // close output file
  printf("Output file. Closing.\n");
  fclose(output);

  return 0;
}

