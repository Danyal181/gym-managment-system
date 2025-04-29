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

 

