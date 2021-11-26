
int login(char username[30],  char password[30]){
    const int NOT_AUTH=0;
    const int LOGGED_IN = 1;
    puts("Login function called");
    printf("%s\n", username);
    printf("%s\n", password);
    puts(username);
    if(strcmp(username,"bekzod")==0){
        if(strcmp(password,"123")==0){
            return LOGGED_IN;
        }
    }



    return NOT_AUTH;
}