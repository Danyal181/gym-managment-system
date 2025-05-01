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



      
      
      




 

