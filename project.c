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
