#include <stdio.h>
#include<stdlib.h>
#include <string.h>

// Structure to represent a student
struct student {
    char f_name[50];
    char l_name[50];
    int roll_no;
    char course[50];
};

// Function to add student details
void addstudent() {
    struct student n;

    
    printf("Enter First Name: ");
    scanf("%s",n.f_name );
    printf("Enter Last Name: ");
    scanf("%s", n.l_name);
    printf("Enter Roll Number: ");
    scanf("%d", &n.roll_no);
    printf("Enter Course: ");
    scanf("%s", n.course);

    FILE *fp = fopen("data.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(fp, "%s %s %d %s\n",n.f_name, n.l_name,n.roll_no ,n.course);

    fclose(fp);

    printf("Student  details added successfully\n");
}

// to find  by roll number
void findbyrollnumber() {
    int rollNumber;
    printf("Enter Roll Number to find: ");
    scanf("%d", &rollNumber);

    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(0);
    }

    struct student n;
    while (fscanf(fp, "%s %s %d  %s \n",n.f_name, n.l_name,&n.roll_no,n.course) != EOF)
      { if (n.roll_no == rollNumber) 
        {
            printf("Student found:\n");
            printf("Roll Number: %d\n", n.roll_no);
            printf("Name: %s %s\n", n.f_name, n.l_name);
            printf("Course: %s\n", n.course);
            break;
        }else {
          printf("not found ");
        }
    }
    fclose(fp);   
    }
// to find by first name
void findbyfname() {
    char firstName[30];
    printf("Enter first name to find: ");
    scanf("%s", firstName);

    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(0);
    }

    struct student n;
    

    while (fscanf(fp, "%s %s %d %s \n",n.f_name, n.l_name,&n.roll_no,n.course)!= EOF) 
    {
        if (strcmp(n.f_name, firstName) == 0) {
            
            printf("Student found:\n");
            printf("Name: %s %s\n", n.f_name, n.l_name);
            printf("Roll Number: %d\n", n.roll_no);
            printf("Course: %s\n", n.course);
        }else{
          printf("not found ");
        }
    }
    fclose(fp);    
}

// to find students in a course
void countbycourse() {
    char course[30];
    printf("Enter course to find students: ");
    scanf("%s", course);

    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(0);
    }

    struct student n;
  
    printf("Students registered in %s\n", course);

    while (fscanf(fp, "%s %s %d %s \n",n.f_name, n.l_name,&n.roll_no,n.course)!= EOF){
      if (strcmp(n.course, course) == 0) 
        {   
            printf("Roll Number: %d",n.roll_no);
            printf("Name: %s %s\n", n.f_name, n.l_name);
        }
    }

    fclose(fp);
}
//total number of students

void total() {
    FILE *fp = fopen("student_data.txt", "r");
    if (fp == NULL) {
        printf("No file found \n");
    }

    int total = 0;
    struct student n;

    while (fscanf(fp, "%s %s %d %s \n",n.f_name, n.l_name, &n.roll_no,n.course) != EOF) {
        total++;
    }

    fclose(fp);

    printf("Total number of students: %d\n", total);
}

//  delete a student by roll number
void deletestudent() {
    int rollNumber;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &rollNumber);

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        exit(1);
    }

    struct student n;
    int found = 0;

    while (fscanf(file, "%s %s %d %s \n",n.f_name, n.l_name,&n.roll_no,n.course) != EOF) {
        if (n.roll_no == rollNumber) {
            found = 1;
            printf("Student deleted successfully!\n");
        } else {
          fscanf(temp, "%s %s %d %s \n",n.f_name, n.l_name,&n.roll_no,n.course);
        }
    }

    fclose(file);
    fclose(temp);

    remove("student_data.txt");
    rename("temp.txt", "student_data.txt");

    if (!found) {
        printf("No student found with the given Roll Number.\n");
    }
}

// Function to update student information
void updatestudent() {
    int rollNumber;
    printf("Enter Roll Number to update: ");
    scanf("%d", &rollNumber);

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        exit(1);
    }

    struct student n;
    int found = 0;

    while (fscanf(file, "%s %s %d %s \n",n.f_name, n.l_name,&n.roll_no,n.course) != EOF) {
        if (n.roll_no == rollNumber) {
            found = 1;
            printf("Enter updated details:\n");
            printf("Enter First Name: ");
            scanf("%s", n.f_name);
            printf("Enter Last Name: ");
            scanf("%s", n.l_name);
            printf("Enter Course: ");
            scanf("%s", n.course);
        }
      fprintf(temp, "%s %s %d %s \n",n.f_name, n.l_name, n.roll_no,n.course);
    }

    fclose(file);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "student_data.txt");

    if (!found) {
        printf("No student found with the given Roll Number.\n");
    } else {
        printf("Student information updated successfully!\n");
    }
}

//main function
int main() {
    int choice;

    do {
        printf("\nStudent Information Management System\n");
        printf("1. Add Student Details\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Find Student by First Name\n");
        printf("4. Find Students by Course\n");
        printf("5. Count of Students\n");
        printf("6. Delete Student\n");
        printf("7. Update Student\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addstudent();
                break;
            case 2:
                findbyrollnumber();
                break;
            case 3:
                findbyfname();
                break;
            case 4:
                countbycourse();
                break;
            case 5:
                total();
                break;
            case 6:
                deletestudent();
                break;
            case 7:
                updatestudent();
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

return 0;
}

