


node *read_flip(node *student);






// since the chosen method to store the files in the linked list is via a stack, the data values are back to front
// as per the spec, this will result in the output of a file that dosent match the reference file
// (all data values are back to front, so 1st entry becomes the last outputted value)
// this function will provide the memory addresses starting with the 1st node created in the linked list and ending with the last
// function takes the student node as input and returns a node
node *read_flip(node *student)
{
  //repeat for all students within linked list until last element is found (1st created node)
  while (student->next != NULL)
  {
    // set a temp node to store the student node
    node *tmp = student;

    // look at next node in linked list
    student = student->next;

    // if there is no next node (if the linked list has reached the end)
    if (student->next == NULL)
    {
      // unlink the node before and the current student node
      // unlinking here isnt problematic since the student node is free'd immediately after input to output file
      // unlinking necessary so that the function can be called multiple times to then obtain the 2nd, 3rd, etc... nodes
      tmp->next = NULL;

      // return the student node
      return student;
      
    }
    
  }
  // return the final node if while loop hasnt run
  return student;
}
