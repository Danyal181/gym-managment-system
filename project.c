#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    char name[50];
    char membershipType[20];
    int feesPaid;
    int attendance;
    char feedback[200];
    bool paymentStatus;
} Member;


typedef struct {
    int id;
    char name[50];
    int *assignedMembers;
    int assignedCount;
    int capacity;
} Trainer;

Member *members = NULL;
Trainer *trainers = NULL;
int memberCount = 0;
int trainerCount = 0;

const char *FILE_NAME = "members.txt";


void loadMembersFromFile();
void saveMembersToFile();
void loginSystem();
void mainMenu();
void addMember();
void viewMembers();
void updateMember();
void deleteMember();
void searchMember();
void assignMembersToTrainers();
void attendanceTracking();
void upgradeDowngradeMembership();
void automaticFeeCalculation();
void memberFeedback();
void generateReports();
void pressAnyKey();
int findMemberIndex(int id);


int main() {
    loadMembersFromFile();
    loginSystem();
    mainMenu();
    free(members);
    for (int i = 0; i < trainerCount; i++) {
        free(trainers[i].assignedMembers);
    }
    free(trainers);
    return 0;
}
  // function  1  : 
void loadMembersFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        file = fopen(FILE_NAME, "w");
        if (!file) {
            printf("Error: Unable to create members file.\n");
            exit(1);
        }
        fclose(file);
        return;
    }

    Member temp;
    while (fscanf(file, "%d,%49[^,],%19[^,],%d,%d,%d,%199[^\n]\n",
                  &temp.id, temp.name, temp.membershipType,
                  &temp.feesPaid, &temp.attendance,
                  (int *)&temp.paymentStatus, temp.feedback) != EOF) {
        members = realloc(members, (memberCount + 1) * sizeof(Member));
        members[memberCount++] = temp;
    }
    fclose(file);
}
// function2 
void saveMembersToFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error: Unable to save members to file.\n");
        return;
    }

    for (int i = 0; i < memberCount; i++) {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n",
                members[i].id, members[i].name, members[i].membershipType,
                members[i].feesPaid, members[i].attendance,
                members[i].paymentStatus, members[i].feedback);
    }
    fclose(file);
}

//functon 3 
void addMember() {
    Member m;
    printf("Enter Member ID: ");
    scanf("%d", &m.id); getchar();
    printf("Enter Name: "); fgets(m.name, sizeof(m.name), stdin);
    m.name[strcspn(m.name, "\n")] = '\0';
    printf("Enter Membership Type (Monthly/Yearly): "); fgets(m.membershipType, sizeof(m.membershipType), stdin);
    m.membershipType[strcspn(m.membershipType, "\n")] = '\0';

    m.feesPaid = 0;
    m.attendance = 0;
    m.paymentStatus = false;
    strcpy(m.feedback, "");

    members = realloc(members, (memberCount + 1) * sizeof(Member));
    members[memberCount++] = m;
    saveMembersToFile();
    printf("Member added successfully!\n");
    pressAnyKey();
}
//function 4 
void viewMembers() {
    printf("\n========== MEMBERS LIST ==========\n");
    for (int i = 0; i < memberCount; i++) {
        printf("ID: %d, Name: %s, Membership Type: %s, Fees Paid: %d, Attendance: %d\n",
               members[i].id, members[i].name, members[i].membershipType, members[i].feesPaid, members[i].attendance);
    }
    pressAnyKey();
}
//function 5
void updateMember() {
    int id;
    printf("Enter Member ID to update: ");
    scanf("%d", &id); getchar();
    int index = findMemberIndex(id);
    if (index != -1) {
        printf("Enter new Name: "); fgets(members[index].name, 50, stdin);
        members[index].name[strcspn(members[index].name, "\n")] = 0;
        printf("Enter new Membership Type: "); fgets(members[index].membershipType, 20, stdin);
        members[index].membershipType[strcspn(members[index].membershipType, "\n")] = 0;
        printf("Enter new Fees Paid: "); scanf("%d", &members[index].feesPaid);
        members[index].paymentStatus = true;
        saveMembersToFile();
        printf("Member updated successfully!\n");
    } else {
        printf("Member not found.\n");
    }
    pressAnyKey();
}
void deleteMember(){
   int id;
   printf("enter member id to delete: ");
   scanf("%d",&id);
   getchar();
   int index=findMemberIndex(id);
   if(index!=-1){
     for(int i=index;i<memberCount-1;i++){
         members[i]=members[i+1];
     }
   memberCount--;
   members=realloc(members,memberCount*sizeof(member));
   saveMembersToFile();
   printf("member deleted successfully!!\n");
   }else{
    printf("member not found");
   }
   pressAnyKey();
void searchMember(){
   int id;
   printf("enter member id to search: ");
   scanf("%d",&id);
   int index = findMemberIndex(id);
   if (index != -1) {
   printf("ID: %d, Name: %s, Membership Type: %s, Fees Paid: %d, Attendance: %d\n", members[index].id, 
       members[index].name, members[index].membershipType, members[index].feesPaid, members[index].attendance);
   }else{
   printf("member not found");
   }
   pressAnyKey();
}
void assignMembersToTrainers() {
    int memberId, trainerId;

    printf("Enter Member ID to assign: ");
    scanf("%d", &memberId);

    printf("Enter Trainer ID to assign to: ");
    scanf("%d", &trainerId);

    int memberExists = findMemberIndex(memberId) != -1;
    int found = 0;

    for (int i = 0; i < trainerCount; i++) {
        if (trainers[i].id == trainerId) {
            found = 1;

            if (trainers[i].assignedCount >= trainers[i].capacity) {
                trainers[i].capacity += 5;
                trainers[i].assignedMembers = realloc(trainers[i].assignedMembers, trainers[i].capacity * sizeof(int));
            }

            trainers[i].assignedMembers[trainers[i].assignedCount++] = memberId;
            printf("Member assigned to trainer successfully!\n");
            break;
        }
    }

    if (!memberExists)
        printf("Member not found.\n");
    else if (!found)
        printf("Trainer not found.\n");

    pressAnyKey();
}
void attendanceTracking() {
    int id;
    printf("Enter Member ID: ");
    scanf("%d", &id);
    int index = findMemberIndex(id);
    if(index!=-1){
      members[index].attendance++;
      saveMembersToFile();
      printf("Attendance recorded. Total: %d\n", members[index].attendance);
    }else{
      printf("member not found.\n");
    }
    pressAnyKey();
}
void upgradeDowngradeMembership() {
    int id;
    printf("Enter Member ID: ");
    scanf("%d", &id);
    int index = findMemberIndex(id);
        if (index != -1) {
        if (strcmp(members[index].membershipType, "Monthly") == 0) {
            strcpy(members[index].membershipType, "Yearly");
            printf("Upgraded to Yearly.\n");
        } else {
            strcpy(members[index].membershipType, "Monthly");
            printf("Downgraded to Monthly.\n");
        }
        saveMembersToFile();
        } else {
          printf("Member not found.\n");
        }
         pressAnyKey();
    }

void loginSystem() {
    char username[20], password[20];
    const char correctUsername[] = "admin";
    const char correctPassword[] = "password";

    printf("========== GYM MANAGEMENT LOGIN ==========\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password. Exiting program...\n");
        exit(1);
    }
    pressAnyKey();
}

void mainMenu() {
    int choice;
    do {
        printf("\n========== GYM MANAGEMENT MENU ==========\n");
        printf("1. Add Member\n");
        printf("2. View Members\n");
        printf("3. Update Member\n");
        printf("4. Delete Member\n");
        printf("5. Search Member\n");
        printf("6. Assign Members to Trainers\n");
        printf("7. Attendance Tracking\n");
        printf("8. Upgrade/Downgrade Membership\n");
        printf("9. Automatic Fee Calculation\n");
        printf("10. Member Feedback\n");
        printf("11. Generate Reports\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addMember(); break;
            case 2: viewMembers(); break;
            case 3: updateMember(); break;
            case 4: deleteMember(); break;
            case 5: searchMember(); break;
            case 6: assignMembersToTrainers(); break;
            case 7: attendanceTracking(); break;
            case 8: upgradeDowngradeMembership(); break;
            case 9: automaticFeeCalculation(); break;
            case 10: memberFeedback(); break;
            case 11: generateReports(); break;
            case 12:
                saveMembersToFile();
                printf("Exiting program...\n");
                exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 12);
}
void automaticFeeCalculation() {
    int id;
    printf("Enter Member ID: ");
    scanf("%d", &id); getchar();
    int index = findMemberIndex(id);
    if (index != -1) {
        int fee = strcmp(members[index].membershipType, "Yearly") == 0 ? 1200 : 100;
        printf("Fee: $%d\nEnter Amount Paid: ", fee);
        scanf("%d", &members[index].feesPaid);
        members[index].paymentStatus = members[index].feesPaid >= fee;
        printf("Payment Status: %s\n", members[index].paymentStatus ? "Paid" : "Pending");
        saveMembersToFile();
    } else {
        printf("Member not found.\n");
    }
    pressAnyKey();
}

void memberFeedback() {
    int id;
    printf("Enter Member ID: ");
    scanf("%d", &id); getchar();
    int index = findMemberIndex(id);
    if (index != -1) {
        printf("Enter Feedback: ");
        fgets(members[index].feedback, sizeof(members[index].feedback), stdin);
        members[index].feedback[strcspn(members[index].feedback, "\n")] = 0;
        printf("Feedback recorded.\n");
        saveMembersToFile();
    } else {
        printf("Member not found.\n");
    }
    pressAnyKey();
}
void generateReports() {
    printf("\n========== MEMBER REPORT ==========");
    for (int i = 0; i < memberCount; i++) {
        printf("\nID: %d, Name: %s, Type: %s, Paid: %d, Attendance: %d, Feedback: %s",
               members[i].id, members[i].name, members[i].membershipType,
               members[i].feesPaid, members[i].attendance, members[i].feedback);
    }
    pressAnyKey();
}

int findMemberIndex(int id) {
    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == id)
            return i;
    }
    return -1;
}






      
      
      




 

