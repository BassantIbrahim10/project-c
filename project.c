#include<stdio.h>
#include<string.h>
#include <stdlib.h>

struct student {
	int id;             //student ID
	char name[50];      //student name
	int age;            //student age
	float gpa;          //student GPA
};
struct node {
	struct student data;
	struct node *next;
};
struct node *head = NULL;

void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	int choose, id;
	float av = 0.0;
	//continuously displays the menu options
	while (1) {
		printf("\n -------------------Menu Options:-----------------------\n");
		printf("1. Add a Student\n");
		printf("2. Display All Students\n");
		printf("3. Search for a Student by ID\n");
		printf("4. Update Student Information\n");
		printf("5. Calculate Average GPA\n");
		printf("6. Find Student with Highest GPA\n");
		printf("7. Delete a Student\n");
		printf("8. Exit\n");
		printf("Enter your choice:");
		scanf("%d", &choose);
		printf("*************************\n");
		//switch case for the user to select a certain function
		switch (choose) {
		case 1: {struct student newStudent;
	    printf("Enter name of the student:");
	    scanf("%s", newStudent.name);
	    printf("Enter ID of the student:");
	    scanf("%d", &newStudent.id);
	    printf("Enter age of the student:");
	    scanf("%d", &newStudent.age);
	    printf("Enter gpa of the student:");
	    scanf("%f", &newStudent.gpa);
	    addStudent(&newStudent);
	    break;
		}
		case 2:
			displayStudents();
			break;
		case 3:
			printf("enter student id to search for:");
			scanf("%d", &id);
			printf("*************************\n");
			searchStudentByID(id);
			break;
		case 4:
			printf("enter student id to update:");
			scanf("%d", &id);
			printf("*************************\n");
			updateStudent(id);
			break;
		case 5:
			av = calculateAverageGPA();
			printf("the average gpa=%f", av);
			break;
		case 6:
			searchHighestGPA();
			break;
		case 7:
			printf("enter student id to delete: ");
			scanf("%d", &id);
			deleteStudent(id);
			break;
		case 8:
			printf("exiting...");
			 exit(0);   //properly exit the program
		default:
			printf("invalid choice\n");
		}
	}

	return 0;
}
void addStudent(const struct student *const ptr) {
    // Allocate a new node
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("ERROR: Memory allocation failed.\n");
        return;
    }
    // Copy student data into the new node
    newNode->data = *ptr;
    newNode->next = NULL;

    // Check if the list is empty
    if (head == NULL) {
        head = newNode;
        printf("Student record added successfully.\n");
        return;
    }
    // Check if the id already exists
    struct node *current = head;
    while (current != NULL) {
        if (current->data.id == ptr->id) {
    		printf("*************************\n");
            printf("The ID already exists.\n");
    		printf("*************************\n");
            free(newNode);
            return;
        }
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }
    // Append the new node at the end of the list
    current->next = newNode;
    printf("Student record added successfully.\n");
}

void displayStudents(void) {
	struct node *temp = head;
	//check if list is empty
	if (head == NULL) {
		printf("There are no students\n");
		printf("*************************\n");
		return;
	}
	//loop in the linked list till the last element
	while (temp != NULL) {
		printf("ID=%d, Name=%s, Age=%d, GPA=%f\n", temp->data.id,
				temp->data.name, temp->data.age, temp->data.gpa);
		temp = temp->next;
	}

}
void searchStudentByID(int id) {
	struct node *current = head;
	//loop in the linked list till the last element
	while (current != NULL) {
		//check if the id is found
		if (current->data.id == id) {
			printf("ID=%d, Name=%s, Age=%d, GPA=%f\n", current->data.id,
					current->data.name, current->data.age, current->data.gpa);
			return;
		}
		//move to next element
		current = current->next;
	}

	printf("the student was not found.");
}
void updateStudent(int id) {
	struct node *current = head;
	//loop in the linked list till the last element
	while (current != NULL) {
		//check if the id is found
		if (current->data.id == id) {
			printf(" the student is found and his information will be updated\n");
			//ask the user to enter new info
			printf("ENTER THE NEW INFORMATION ↓↓↓\n");
			printf("enter the new name:");
			scanf("%s", current->data.name);
			printf("enter the new age:");
			scanf("%d", &current->data.age);
			printf("enter the new gpa:");
			scanf("%f", &current->data.gpa);
			return;
		}
		//move to next element
		current = current->next;
	}
	printf("the student was not found.");
}
float calculateAverageGPA(void) {
	float sum = 0.0;
	int count = 0;
	float average = 0.0;
	struct node *current = head;
	if (head == NULL)
	//linked list is empty and there is no gpa to be calculated
	{
		return 0.0;
	}
	//loop in the linked list till the last element
	while (current != NULL) {
		sum += current->data.gpa;
		count++;
		//move to next element
		current = current->next;
	}
	//calculate and return the average
	average = sum / count;
	return average;
}
void searchHighestGPA(void) {
    float max = 0.0;
    struct node *current = head;
    //define a max node to have the info of student of highest gpa
    struct node *maxNode = NULL;
    //check if list is empty
    if (head == NULL) {
		printf("*************************\n");
        printf("The list is empty\n");
        return;
    }
    while (current != NULL) {
        if (current->data.gpa > max) {
            max = current->data.gpa;
            //put data of the node (current) in maxNode
            maxNode = current;
        }
		//move to next element
        current = current->next;
    }
    if (maxNode != NULL) {
        printf("The information of the student with highest gpa:\n");
        printf("ID=%d, Name=%s, Age=%d, GPA=%f\n", maxNode->data.id, maxNode->data.name, maxNode->data.age, maxNode->data.gpa);
    }
}
void deleteStudent(int id) {
	struct node *current = NULL;
	struct node *prev = NULL;
	struct node *DeleteNode = NULL;
	//check if the linked list is empty
	if (head == NULL) {
		printf("Linked List is empty");
		return;
	}
	//check the first node in the linked list
	if (head->data.id == id) {
		DeleteNode = head;
		head = head->next;
		printf("the id:%d is found and deleted successfully \n", id);
		free(DeleteNode);
		return;
	}
	//check the rest of nodes in the linked list
	current = head->next;
	prev = head;
	while (current != NULL) {
		if (current->data.id == id) {

			DeleteNode = current;
			prev->next = current->next;
			printf("the id:%d is found and deleted successfully \n", id);
			free(DeleteNode);
			return;
		}
		prev = current;
		current = current->next;
	}

	if (DeleteNode == NULL) {
		printf("%d was not found in the List.", id);
	}

}
