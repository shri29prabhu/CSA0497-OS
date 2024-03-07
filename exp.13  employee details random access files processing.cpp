#include <stdio.h>
#include <stdlib.h>
struct Employee {
    int empId;
    char empName[30];
    float empSalary;
};
void addEmployee(FILE *file) {
    struct Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.empId);
    printf("Enter Employee Name: ");
    scanf("%s", emp.empName);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.empSalary);
    fseek(file, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Employee details added successfully!\n");
}
void displayEmployee(FILE *file) {
    struct Employee emp;
    int empId;
    printf("Enter Employee ID to display details: ");
    scanf("%d", &empId);
    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);
    if (emp.empId != 0) {
        printf("Employee ID: %d\n", emp.empId);
        printf("Employee Name: %s\n", emp.empName);
        printf("Employee Salary: %.2f\n", emp.empSalary);
    } else {
        printf("Employee not found!\n");
    }
}
void updateEmployee(FILE *file) {
    struct Employee emp;
    int empId;
    printf("Enter Employee ID to update details: ");
    scanf("%d", &empId);
    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);
    if (emp.empId != 0) {
        printf("Enter new Employee Name: ");
        scanf("%s", emp.empName);
        printf("Enter new Employee Salary: ");
        scanf("%f", &emp.empSalary);
        fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
        fwrite(&emp, sizeof(struct Employee), 1, file);

        printf("Employee details updated successfully!\n");
    } else {
        printf("Employee not found!\n");
    }
}
int main() {
    FILE *file;
    int choice;
    file = fopen("employee.dat", "r+");
    if (file == NULL) {
        file = fopen("employee.dat", "w+");
        if (file == NULL) {
            printf("Error creating/opening file!\n");
            exit(1);
        }
    }
    do {
        printf("\n1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                displayEmployee(file);
                break;
            case 3:
                updateEmployee(file);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);
    fclose(file);
    return 0;
}

