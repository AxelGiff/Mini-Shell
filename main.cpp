#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sys/wait.h>
#include <cstring>

#include <unistd.h>

using namespace std;

char** split(const string& str, const char* delimiter) {
    vector<char*> tokens;
    char* copy = new char[str.size() + 1];
    strcpy(copy, str.c_str());

    char* token = strtok(copy, delimiter);
    while (token != nullptr) {
       char* t = new char[strlen(token) + 1];
        strcpy(t, token);
        tokens.push_back(t);
        token = strtok(nullptr, delimiter);
    }

    tokens.push_back(nullptr);

    char** result = new char*[tokens.size()];
    for (size_t i = 0; i < tokens.size(); i++) {
        result[i] = tokens[i];
    }

    delete[] copy;
    return result;
}



int main(){
    string command="";
    char hostname[1024];
    gethostname(hostname,sizeof(hostname));
    std::vector<string> tokens;
    char previousDir[1024] = "";  

    while(true){
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
                cout <<  getenv("USER") << "@" << hostname << ":" << cwd <<  "$" << " ";
        if (!getline(cin,command)) {
                break;
              }
    char** tokens = split(command, " ");
        char* lastDir=getenv("HOME");
         
        if(strcmp(tokens[0],"exit")==0){
            break;
        }else if(strcmp(tokens[0],"cd")==0){
            if(tokens[1]!=nullptr){
                char cwd[1024];
            getcwd(cwd, sizeof(cwd)); 

                if (strcmp(tokens[1], "-") == 0) {
            if (strlen(lastDir) > 0) {
                if (chdir(lastDir) != 0) {
                    perror("failed");
                } else {
                }
            } else {
                cout << "No previous directory\n";
            }
        } else {
            if (chdir(tokens[1]) != 0) {
                perror("failed");
            }
        }
                          strcpy(lastDir, cwd); 
  
            }else{
                const char* home=getenv("HOME");
                 if(home) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));  // Sauvegarde l'actuel avant de changer
        strcpy(previousDir, cwd);   // Met à jour le précédent
        if(chdir(home) != 0) {     // Va vers HOME
            perror("chdir failed");
        }
    }
            }
        }

        else{
        pid_t c_pid = fork();

    
        
    if(c_pid==0){
    execvp(tokens[0], tokens);
         perror("execvp"); 
        exit(1);
    }else{
        wait(nullptr);
    }
      

}

          for (int i = 0; tokens[i] != nullptr; i++) {
            delete[] tokens[i];
        }
        delete[] tokens;
      
    }

    return 0;

}
