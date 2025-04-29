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

 

