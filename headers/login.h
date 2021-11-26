



int login(char username[30],  char password[30]){
    int user_id = 0;
    const int NOT_AUTH=-1;
    const int LOGGED_IN = 1;
    const int IS_ADMIN;
    printf("%s\n", username);
    printf("%s\n", password);
    puts(username);
    connect_to_database();


    all_users();

    user_id = get_user_id(username, password);

    printf("\nUser id is : %d\n", user_id);

    if(user_id>0){
        disconnect();
        return LOGGED_IN;
    }

    if(user_id==0){
        disconnect();
        return IS_ADMIN;
    }


    disconnect();
    return NOT_AUTH;
}

