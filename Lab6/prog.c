#include <stdio.h>
void bad(){
    char* new_name = "Quick brown fox jumped over the lazy dog";
    unsigned char *temp;
    temp = (unsigned char *) (&new_name);
    *((char **) (temp + 0x20)) = new_name;

    *((int **) (temp + 0x20)) = 1000;
    
    temp = (unsigned char *) (&new_name);
   *((unsigned long *) (temp + 0x18)) += 0x1E; 
}

int main(){
    struct{
        char *name;
        int age;
    } student = {.name = "John", .age = 22};
    bad();
    printf("student.name = %s\nstudent.age = %d\n", student.name, student.age);
}