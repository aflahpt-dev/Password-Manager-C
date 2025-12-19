// PASSWORD MANAGER IN C
// Features:
// - Master password authentication
// - Add / View / Search / Delete / Update passwords
// - File-based storage
// - Basic XOR encryption (learning purpose)

#include <stdio.h>
#include <string.h>

// XOR encryption key (for learning purposes only)
#define KEY 8


// ---------------- ENCRYPTION / DECRYPTION ----------------

// Encrypts a string using XOR cipher
void encrypt(char *str){
    for(int i = 0; str[i] != '\0'; i++){
        str[i] ^= KEY;
    }
}

// Decrypts a string using XOR cipher (same logic as encrypt)
void decrypt(char *str){
    for(int i = 0; str[i] != '\0'; i++){
        str[i] ^= KEY;
    }
}


// ---------------- MASTER PASSWORD FUNCTIONS ----------------

// Checks whether master password file exists
int masterExists(){
    FILE *fp = fopen("master.dat","r");
    if(fp){
        fclose(fp);
        return 1;   // master password already created
    }
    return 0;       // first run
}

// Creates master password on first run
void create_master_password(){
    FILE *fp = fopen("master.dat","w");
    char password[50];

    printf("create master key password: ");
    scanf("%s", password);

    encrypt(password);                 // encrypt before storing
    fprintf(fp, "%s", password);

    fclose(fp);
    printf("password has been created successfully......\n\n");
}

// Verifies master password before giving access
int verify_password(){
    FILE *fp = fopen("master.dat","r");
    char stored[50], input[50];

    printf("Enter master key password: ");
    scanf("%s", input);

    fgets(stored, sizeof(stored), fp);
    decrypt(stored);                   // decrypt stored password

    fclose(fp);

    // Compare input with decrypted stored password
    if(strcmp(stored, input) == 0){
        return 1;                      // access granted
    }
    return 0;                          // access denied
}


// ---------------- MAIN PROGRAM ----------------

int main(){
    int choice;
    char platform[50], username[50], password[50];
    FILE *file;

    // Master password setup and verification
    if(!masterExists()){
        create_master_password();
    }

    if(!verify_password()){
        printf("\nACCESS DENIED!....\n");
        return 0;
    }

    printf("\nACCESS GRANTED......\n");

    // Main menu loop
    while(1){
        printf("\n\n---------PASSWORD MANAGER-----------\n\n");
        printf("1. ADD PASSWORD\n");
        printf("2. VIEW PASSWORD\n");
        printf("3. SEARCH PASSWORD\n");
        printf("4. DELETE PASSWORD\n");
        printf("5. UPDATE PASSWORD\n");
        printf("6. EXIT\n");
        printf("\nCHOOSE A OPTION: ");
        scanf("%d", &choice);
        printf("\n");

        // ---------------- ADD PASSWORD ----------------
        if(choice == 1){
            file = fopen("data.txt","a");

            if(file == NULL){
                printf("Error opening file!...\n");
                return 1;
            }

            printf("Enter platform (ex: gmail): ");
            scanf("%s", platform);
            printf("Enter Username: ");
            scanf("%s", username);
            printf("Enter Password: ");
            scanf("%s", password);

            encrypt(password);   // encrypt password before saving

            fprintf(file, "%s | %s | %s \n", platform, username, password);
            fclose(file);

            printf("\nnew password added.....\n");
        }

        // ---------------- VIEW PASSWORDS ----------------
        else if(choice == 2){
            char line[50];
            int count = 1;

            printf("VIEWING PASSWORD.....\n");
            file = fopen("data.txt","r");

            if(file == NULL){
                printf("password list is empty.......\n");
            } else {
                char *platstr, *userptr, *passstr;

                printf("\n\n------PASSWORD LIST---------\n\n");
                printf("platform |username | password\n");
                printf("---------+---------+---------\n");

                while(fgets(line, sizeof(line), file)){
                    // Split line into tokens
                    platstr = strtok(line, " |");
                    userptr = strtok(NULL, " |");
                    passstr = strtok(NULL, " |");

                    if(passstr){
                        decrypt(passstr);   // decrypt password before display
                    }

                    printf("%d. %s | %s | %s\n",
                           count, platstr, userptr, passstr);
                    count++;
                }
            }
            fclose(file);
        }

        // ---------------- SEARCH PASSWORD ----------------
        else if(choice == 3){
            char line[200];
            int found = 0;

            file = fopen("data.txt","r");
            printf("Enter the platform to search: ");
            scanf("%s", platform);

            if(file == NULL){
                printf("password list is empty.....\n");
            } else {
                while(fgets(line, sizeof(line), file)){
                    if(strstr(line, platform) != NULL){
                        printf("found entry %s........\n", platform);
                        printf("%s\n", line);
                        found = 1;
                    }
                }
                fclose(file);

                if(!found)
                    printf("no entry found of : %s\n", platform);
            }
        }

        // ---------------- DELETE PASSWORD ----------------
        else if(choice == 4){
            char line[100];
            int found = 0;

            FILE *org = fopen("data.txt","r");
            FILE *temp = fopen("temp.txt","w");

            if(org == NULL){
                printf("LIST IS EMPTY...\n");
            } else {
                printf("Enter the platform: ");
                scanf("%s", platform);

                while(fgets(line, sizeof(line), org)){
                    if(strstr(line, platform) == NULL){
                        fprintf(temp, "%s", line);
                    } else {
                        found = 1;
                    }
                }

                fclose(org);
                fclose(temp);

                remove("data.txt");
                rename("temp.txt","data.txt");

                if(found)
                    printf("Entry %s is deleted from list.....\n", platform);
                else
                    printf("Entry %s not found in list\n", platform);
            }
        }

        // ---------------- UPDATE PASSWORD ----------------
        else if(choice == 5){
            char line[100];
            int found = 0;

            FILE *org = fopen("data.txt","r");
            FILE *temp = fopen("temp.txt","w");

            if(org == NULL){
                printf("LIST IS EMPTY...\n");
            } else {
                printf("Enter the platform: ");
                scanf("%s", platform);

                while(fgets(line, sizeof(line), org)){
                    if(strstr(line, platform) == NULL){
                        fprintf(temp, "%s", line);
                    } else {
                        found = 1;
                    }
                }

                fclose(org);
                fclose(temp);

                remove("data.txt");
                rename("temp.txt","data.txt");

                if(found){
                    printf("Enter new username: ");
                    scanf("%s", username);
                    printf("Enter new password: ");
                    scanf("%s", password);

                    file = fopen("data.txt","a");
                    fprintf(file, "%s | %s | %s\n",
                            platform, username, password);
                    fclose(file);

                    printf("Entry %s is updated.....\n", platform);
                } else {
                    printf("Entry %s not found in list\n", platform);
                }
            }
        }

        // ---------------- EXIT ----------------
        else if(choice == 6){
            printf("EXITING......\n");
            break;
        }

        // ---------------- INVALID INPUT ----------------
        else{
            printf("ENTER VALID OPTION.....\n");
        }
    }

    return 0;
}
