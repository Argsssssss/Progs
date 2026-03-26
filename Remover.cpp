#include <iostream>
#include <dirent.h>
using namespace std;
void file_list(const char* _dir){
    string _remove = "rm ";
    
    DIR *dir = opendir(_dir);
    if (dir != NULL) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            if(ent->d_name[0] != '.'){
                _remove += ent->d_name;
                system(_remove.c_str());
                system("clear");
                _remove = "rm ";

            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Error opening directory\n");
    }
}

int main() {
    file_list(".");
    return 0;
}
