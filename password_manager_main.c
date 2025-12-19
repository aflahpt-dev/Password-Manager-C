// Online C compiler to run C program online
#include<stdio.h>
#include<string.h>
#define KEY 8
void encrypt(char *str){
    for(int i = 0;str[i] != '\0';i++){
        str[i] ^= KEY;
    }
}void decrypt(char *str){
    for(int i = 0;str[i] != '\0';i++){
        str[i] ^= KEY;
    }
}int masterExists(){
    FILE *fp = fopen("master.dat","r");
    if(fp){
        
        fclose(fp);
        return 1;
    }
    return 0;

}void create_master_password(){
    FILE *fp = fopen("master.dat","w");
    char password[50];
    printf("create master key password: ");
    scanf("%s",password);
    encrypt(password);
    fprintf(fp,"%s",password);
    fclose(fp);
    printf("password has been created succesfully......\n\n");
}int verify_password(){
    FILE *fp = fopen("master.dat","r");
    char stored[50],input[50];

    printf("Enter master key password: ");
    scanf("%s",input);

    fgets(stored,sizeof(stored),fp);
    decrypt(stored);

    if(!strcmp(stored,input)){
        return 1;
        fclose(fp);
    }return 0;
}
int main() {
    int choice;
    char platform[50],username[50],password[50];
    FILE *file;
    

    if(!masterExists()){
        create_master_password();
    }
    if(!verify_password()){
        printf("\nACCESS DENIED!....\n");
        return 0;
    }
    printf("\nACCESS GRANTED......\n");
    
    // Write C code here
    while(1){
        printf("\n\n");
        printf("---------PASSWORD MANAGER-----------");
        printf("\n\n");
        printf("1. ADD PASSWORD\n");
        printf("2. VIEW PASSWORD\n");
        printf("3. SEARCH PASSWORD\n");
        printf("4. DELETE PASSWORD\n");
        printf("5. UPDATE PASSWORD\n");
        printf("6. EXIT\n");
        printf("\n");
        printf("CHOOSE A OPTION: ");
        scanf("%d",&choice);
        printf("\n");
        if(choice == 1){
            file = fopen("data.txt","a");
            printf("ADDING PASSWORD.....\n");
            if(file == NULL){
                printf("Error opening file!...");
                return 1;
            }
            printf("Enter platform (ex: gmail): ");
            scanf("%s",platform);
            printf("Enter Username: ");
            scanf("%s",username);
            printf("Enter Password: ");
            scanf("%s",password);
            encrypt(password);
            fprintf(file,"%s | %s | %s \n",platform,username,password);
            printf("\nnew password added.....");
            fclose(file);
        }
        else if(choice == 2){
            char line[50];
            int count = 1;
            int i = 0;
            printf("VIEWING PASSWORD.....\n");
            file = fopen("data.txt","r");
            if(file == NULL){
                printf("password list is empty.......\n");
                
            }else{
                char *userptr,*platstr,*passstr;
                printf("\n\n------PASSWORD LIST---------\n\n");
                printf("platform |username | password\n");
                printf("---------+---------+---------\n");
                while(fgets(line,sizeof(line),file)){
                    platstr = strtok(line," |");
                    userptr = strtok(NULL, " |");
                    passstr = strtok(NULL, " |");
                    if(passstr){
                        decrypt(passstr);
                    }
                    printf("%d. %s | %s | %s\n",count,platstr,userptr,passstr);
                    count++;
                    
                }
                
            }fclose(file);
        }
        else if (choice == 3){
            char platform[50];
            char line[200];
            int found = 0;
            file=fopen("data.txt","r");
            printf("Enter the platfrom to search: ");
            scanf("%s",platform);
            if(file == NULL)
                printf("password list is empty.....\n");
            else{
                while(fgets(line,sizeof(line),file)){
                    if(strstr(line,platform)!=NULL){
                        printf("found entry %s........\n",platform);
                        printf("%s\n",line);
                        found = 1;
                    }
                
                }fclose(file);
                if(!found)
                    printf("no entry found of : %s\n",platform);
            }
        }
        else if(choice == 4){
            char platform[50];
            char line[100];
            int found = 0;
            FILE *org = fopen("data.txt","r");
            FILE *temp = fopen("temp.txt","w");
            if(org == NULL){
                printf("LIST IS EMPTY...\n");
            }else{
                printf("Enter the platform: ");
                scanf("%s",platform);
                while(fgets(line,sizeof(line),org)){
                    if(strstr(line,platform)==NULL){
                        fprintf(temp,"%s",line);
                    }else{
                        found = 1;
                    }
                
                }fclose(org);
                fclose(temp);
                remove("data.txt");
                rename("temp.txt","data.txt");
                if(found){
                    printf("Entry %s is deleted from list.....\n",platform);
                }else{
                    printf("Entry %s not found in list\n",platform);
                }
            }
        }
        else if(choice == 5){
            char line[100];
            int found = 0;
            FILE *org = fopen("data.txt","r");
            FILE *temp = fopen("temp.txt","w");
            if(org == NULL){
                printf("LIST IS EMPTY...\n");
            }else{
                printf("Enter the platform: ");
                scanf("%s",platform);
                while(fgets(line,sizeof(line),org)){
                    if(strstr(line,platform)==NULL){
                        fprintf(temp,"%s",line);
                    }else{
                        found = 1;
                    }
                
                }fclose(org);
                fclose(temp);
                remove("data.txt");
                rename("temp.txt","data.txt");
                
                if(found){
                    printf("Enter new username: ");
                    scanf("%s",username);
                    printf("Enter new password: ");
                    scanf("%s",password);
                    file = fopen("data.txt","a");
                    fprintf(file,"%s | %s | %s\n",platform,username,password);
                    fclose(file);
                    printf("Entry %s is updated.....\n",platform);
                }else{
                    printf("Entry %s not found in list\n",platform);
                }
            }
        }
        else if(choice == 6){
            printf("EXITING......");
            break;
        }
        else{
            printf("ENTER VALID OPTION.....");
        }
        
    }
    return 0;
}