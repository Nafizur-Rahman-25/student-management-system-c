#include<stdio.h>
#include<string.h>


struct student
{
    int id;
    char name[100];
    float cgpa;
};

struct student students[100];
int totalStudent = 0;

void addStudents()
{
    printf("Enter your ID :");
    scanf("%d",&students[totalStudent].id);

    for(int i  =0 ; i <totalStudent ; i++)
    {
        if(students[i].id ==  students[totalStudent].id)
        {
            printf("This ID already exist, please give a new one\n");
            return ;
        }
    }

    printf("Enter your name :");
    getchar();
    fgets(students[totalStudent].name , 100 , stdin);
    students[totalStudent].name[strcspn(students[totalStudent].name,"\n")] = '\0';

    printf("Enter your CGPA :");
    scanf("%f",&students[totalStudent].cgpa);

    totalStudent++;

    printf("Student Added Successfully\n");
}

void viewStudents()
{
    if(totalStudent == 0)
    {
        printf("No Student Found");
        return ;
    }
    int i ;
    for( i = 0; i < totalStudent ; i++)
    {
        printf("\nID : %d\n",students[i].id);
        printf("Name : %s\n",students[i].name);
        printf("CGPA : %.2f\n",students[i].cgpa);
    }
}

void searchStudents()
{
    int id ;
    int found = 0;

    printf("Please give student id : ");
    scanf("%d",&id);

    for(int i = 0; i< totalStudent ; i++)
    {
        if( students[i].id == id)
        {
            printf("\nStudent Found\n");
            printf("\n");
            printf("Student ID:%d\n",students[i].id);
            printf("Student Name:%s\n",students[i].name);
            printf("Student CGPA:%.2f\n",students[i].cgpa);
            found = 1;
            break;
        }
    }
    if( found == 0)
    {
        printf("Student Not Found\n");
    }
}

void deleteStudent()
{
    int found = 0;
    int id;
    printf("Pleaes give student id\n");
    scanf("%d",&id);
    for(int i = 0; i <totalStudent ;i++)
    {
        if(students[i].id == id)
        {
            found = 1;
            int index = i;
            for(int j = index ; j<totalStudent-1; j++)
            {
                students[j] = students[j+1];
            }
            totalStudent--;
            break;
        }
    }
    if(found == 0)
    {
        printf("Student ID = %d not found",id);
    }
    else
        printf("Successfully Deleted Student id:%d",id);
}

void saveStudents()
{
    FILE *fp;
    fp = fopen("students.txt","w");
    fprintf(fp,"%d\n",totalStudent);

    for(int i = 0; i< totalStudent ; i++)
    {
        fprintf(fp,"%d\n",students[i].id);
        fprintf(fp,"%s\n",students[i].name);
        fprintf(fp,"%.2f\n",students[i].cgpa);
    }
    fclose(fp);
}

void loadStudents()
{
    FILE *fp;
    fp = fopen("students.txt","r");
    if( fp == NULL)
        return;
    fscanf(fp,"%d",&totalStudent);
    fgetc(fp);

    for(int i = 0; i< totalStudent ; i++)
    {
        fscanf(fp,"%d",&students[i].id);
        fgetc(fp);

        fgets(students[i].name , 100 , fp);
        students[i].name[strcspn(students[i].name,"\n")] = '\0';

        fscanf(fp ,"%f",&students[i].cgpa);
        fgetc(fp);
    }
    fclose(fp);
}

void updateStudent()
{
    int id;
    int found = 0;
    printf("Please give your student ID\n");
    scanf("%d",&id);
    for(int  i =0 ; i < totalStudent ; i++)
    {
        if(students[i].id == id)
        {
            found = 1;
            printf("Please enter new name\n");
            getchar();
            fgets(students[i].name,100,stdin);
            students[i].name[strcspn(students[i].name,"\n")] = '\0';
            printf("Please enter new CGPA\n");
            scanf("%f",&students[i].cgpa);
            saveStudents();
            printf("Student info has been upated successfully\n");
            break;
        }
    }
    if(found == 0)
    {
        printf("Student not found\n");
    }
}


int main()
{
    loadStudents();
    int choice;
    while(1)
    {
        printf("\n=======================\n");
        printf(" Student Management System\n");
        printf("=======================\n");
        printf("\n");
        printf("Total Student = %d\n",totalStudent);
        printf("\n");
        printf("1. Add Students\n");
        printf("2. View Students\n");
        printf("3. Search Students\n");
        printf("4. Delete Students\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");


        printf("Please, give your choice.\n");
        
        if( scanf("%d",&choice) != 1)
        {
            printf("Please give valid input\n");
            while(getchar() != '\n');
            continue;
        }
        if(choice<1 || choice>6)
        {
            printf("Please give your choice between 1 to 6\n");
            continue;
        }
        printf("your choice is : %d\n",choice);

        
        if(choice == 1 )
        {
            addStudents();
            saveStudents();
        }
        printf("\n");
        if(choice == 2 )
        {
            viewStudents();
        }
        printf("\n");
        if( choice == 3)
        {
            searchStudents();
        }
        if(choice == 4)
        {
            deleteStudent();
            saveStudents();
        }
        if(choice == 5)
        {
            updateStudent();
        }
        if(choice == 6)
        {
            saveStudents();
            printf("Good Bye ['-']\n ");
            break;
        }
    }
    return 0;
}