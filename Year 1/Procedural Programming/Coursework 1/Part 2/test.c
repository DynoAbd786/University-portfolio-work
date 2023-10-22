#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// set a constant integer to the MAX number of STUDENTS in spec sheet
#define STUDENT_MAX 100

// set a constant integer to the MIN number of STUDENTS in spec sheet
#define STUDENT_MIN 1

// set a constant integer to the MAX number of SCORES per students in spec sheet
#define SCORES_MAX 8

// set a constant integer to the MIN number of SCORES per students in spec sheet
#define SCORES_MIN 1

// structure definition for the student, including the ID, scores, average and memory location of next student (singly linked list)
typedef struct student
{
  int id;
  float scores[SCORES_MAX];
  int average;
  struct student *next;
}
node;

// function prototype
void free_list(node *student);


int main(int argc, char *argv[]) 
{
  // check if file is given in command line
  if (argc != 4)
  {
    printf("Incorrect arguments given. Expecting nStudents nGrades fileName. Exiting.\n");
    return 1;
  } 

  // obtain input for amount of students to check
  // atoi to convert char * input to int
  const int STUDENT_INPUT = atoi(argv[1]);

  // check if the input falls out of bounds. if so, terminate
  if (STUDENT_INPUT < STUDENT_MIN || STUDENT_INPUT > STUDENT_MAX)
  {
    printf("Requires 1 to 100 students. Exiting.\n");
    return 2;
  }

  // obtain input for amount of scores to check
  // atoi to convert char * input to int
  const int SCORES_INPUT = atoi(argv[2]);

  // check if the input falls out of bounds. if so, terminate
  if (SCORES_INPUT < SCORES_MIN || SCORES_INPUT > SCORES_MAX)
  {
    printf("Requires 1 to 8 grades. Exiting.\n");
    return 3;
  }


  // attempt to open file 
  FILE *input;
  input = fopen(argv[3], "r");
  printf("Input file. Opening.\n");

  // if the file dosent exist, then terminate
  if (input == NULL)
  {
    printf("Input file does not exist. Exiting.\n");
    return 4;
  }


  // reading from file:
  // set NULL address for the 1st loop in linked list
  node *address = NULL;
  node *tmp = NULL;

  // repeat for every known student
  for (int i = 0; i < STUDENT_INPUT; i++)
  {
    // malloc new node to represent 1 student and its respective data, as per spec requirements
    node *student = malloc(sizeof(node));

    // get student ID
    fscanf(input, "%i", &student->id);

    // get student scores using fscanf to get 1 number to 1 score 
    for (int j = 0; j < SCORES_INPUT; j++)
    {
      fscanf(input, "%f", &student->scores[j]);
    }

    // checking if the file is being read from the 1st time
    if (address == NULL)
    {
      // set the address to be tha address of the student node
      // 1st loop sets node->next to NULL
      address = student;
      tmp = student;
      
    }

    else
    {
      // link nodes together while looping through the list via a queue.
      tmp->next = student;
      tmp = student;
    }   
  }

  tmp->next = NULL;

  // close input file
  printf("Input file. Closing.\n");
  fclose(input);


  // checking data
  printf("Checking data.\n");

  // set a check node to the position of the 1st student in the linked list
  node *check = address;

  // repeat for all students
  for (int i = 0; i < STUDENT_INPUT; i++)
  {
    // check if student ID is correct. if not, exit and free memory
    if (check->id < 2022000 || check->id > 2022099)
    {
      printf("Found an invalid student id: %d. Exiting.\n", check->id);
      free_list(address);
      return 5;
    }

    // checking scores
    for (int j = 0; j < SCORES_INPUT; j++)
    {
      // check for exclusive grades
      if (check->scores[j] == -1)
      {
        // ignore but dont edit any -1 values
        // To be used as idenfiers for the exclusive grades
        continue;
      }

      // check for grades out of bounds. if there are, exit and free memory
      if (check->scores[j] < 0 || check->scores[j] > 100)
      {
        printf("Found an invalid grade: id %i grade %i. Exiting.\n", check->id, (int)check->scores[j]);
        free_list(address);
        return 6;
      }

      // check if grade is set below 20 and set it to 20
      else if (check->scores[j] < 20)
      {
        printf("Correcting student %i grade %i\n", check->id, (int)check->scores[j]);
        check->scores[j] = 20;
      }

      // check if grade is set above 90 and set it to 90
      else if (check->scores[i] > 90)
      {
        printf("Correcting student %i grade %i\n", check->id, (int)check->scores[j]);
        check->scores[j] = 90;
      }
    }
    check = check->next;
  }

  node *avg_node = address;
  printf("i");
  // compute average for each student
  printf("Computing averages.\n");
  printf("i");
  
  // set a node to the position of the 1st student to take scores and store average values
  
  // node *avg_node = address;
  // printf("i");

  // repeat for all students 
  for (int i = 0; i < STUDENT_INPUT; i++)
  {
    // sum variable to find the total of all scores
    float sum = 0.0;

    // amt_grades to represent amount of greades to be used in calculations
    float amt_grade = 0.0;

    // loop for all scores
    for (int j = 0; j < SCORES_INPUT; i++)
    {
      // identify all NULL values and ignore
      if (avg_node->scores[i] != -1)
      {
        // take addition of grades and amount of grades
        
        sum = sum + avg_node->scores[i];
        amt_grade++;
      }
    }

    // during testing if there was an input for all -1 scores, the program would result in an undefined result
    // this check will ensure if there is any 0's in the math, the average output is 0
    if (sum == 0 || amt_grade == 0)
    {
      avg_node->average = 0;
    }
    else
    {
      // calculate average and round using roundf function from math.h and
      // save average to its respected student via memory access
      avg_node->average = roundf(sum / amt_grade);
    }

    // loop to next data point within the linked list
    printf("%i %f %f %f %f %i \n", avg_node->id, avg_node->scores[0], avg_node->scores[1], avg_node->scores[2], avg_node->scores[3], avg_node->average);
    avg_node = avg_node->next;
  }


  // opening output file
  printf("Output file. Opening.\n");
  FILE *output;
  output = fopen("averages.txt", "w");

  // writing to averages.txt
  // set a tracker node called output
  node *output_node = address;

  // repeat for every student
  for (int i = 0; i < STUDENT_INPUT; i++)
  {
    // output to file
    fprintf(output, " %i %i\n", output_node->id, output_node->average);

    // move to the next node
    node *output_node = output_node->next;
  }

  // free all nodes
  free_list(address);


  // close output file
  printf("Output file. Closing.\n");
  fclose(output);

  return 0;
}




// this function is necessary for when the code has to stop due to any ID's or scores that may be out of bounds from the spec
// this function frees the linked list
// it takes in the 1st element in the linked list as a parameter and returns nothing
void free_list(node *student)
{
  // repeat for all elements in linked list
  while (student->next != NULL)
  {
    // set a temp node to the student node
    node *tmp = student;

    // set student to the next node in linked list
    student = student->next;

    // free the temp node
    free(tmp);
  }
  // free the student node once while loop is complete
  free(student);

  // return nothing, terminate function
  return;
}











