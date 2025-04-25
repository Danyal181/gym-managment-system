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
