#define _CRT_SECURE_NO_DEPRECATE
#define CURL_STATICLIB
#include <iostream>
#include <Windows.h>
#include <string>
#include "curl/curl.h"
#include <stdio.h>
#pragma comment(lib, "Shell32.lib")
#include <shellapi.h>
#include <stdlib.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <tchar.h>
#include <urlmon.h>
#include <fstream>
#include <TlHelp32.h>
#include <fcntl.h>
#include <io.h>
#include "cryptopp/zlib.h"
#include "XorString.h"
#include "VMProtectSDK.h"
#include "c_xor.hpp"
#include "VMProtectSDK.h"

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

using namespace std;

string admintoken = ""; //Input admin api token here
string programkey = ""; //Input program key here

void menu();

int main() {
    menu();
}

void menu() {
    system("CLS");
    system("color 3");
    system("title cAuth Admin Key Generator");
    std::cout << "cAuth Menu : ";
    std::cout << "\n\n[ a ] Generate Keys";
    std::cout << "\n[ b ] Delete Keys";
    std::cout << "\n[ c ] View unused Keys";
    std::cout << "\n[ d ] Reset User's HWID";
    std::cout << "\n[ e ] Ban/Unban User";
    std::cout << "\n[ + ] Option : ";
    string ans;
    std::cin >> ans;
    if (ans == "a") {
        system("CLS");
        string amount;
        string days;
        string level;
        string type;
        std::cout << "Enter amount of Keys to Generate : ";
        std::cin >> amount;
        std::cout << "\nEnter amount of Days : ";
        std::cin >> days;
        std::cout << "\nEnter Token level : ";
        std::cin >> level;
        std::cout << "\nEnter Key Type : (GUID, Big Normal, Normal) (Case Sensitive) : ";
        std::cin >> type;
        CURL* curl;
        FILE* fp;
        CURLcode res;
        curl = curl_easy_init(); //api link + type 

        curl_easy_setopt(curl, CURLOPT_URL, "https://cauth.me/api/admin_handler.php?type=gen_token");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla cAuth"); //ALL requests needs the user-agent Mozilla cAuth

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, "sha256//Mk6vhbkCoRzUhXoUryC8tjIxmehtu4uLVhwqGQM9Cmc=");

        std::string values =
            "&admin_token=" + admintoken + "&program_key=" + programkey + "&token_amount=" + amount + "&token_days=" + days + "&token_level=" + level + "&token_type=" + type; //Include admin token and program key

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
        res = curl_easy_perform(curl);
        std::cout << "\nGenerated Keys Successfully - Press enter to go back to menu (Remember to copy the keys idot)";
        system("pause");
        Sleep(4000);

        main();

    }
    if (ans == "b") {
        system("CLS");
        string token;
        std::cout << "Enter token to Delete : ";
        std::cin >> token;
        CURL* curl;
        FILE* fp;
        CURLcode res;
        curl = curl_easy_init(); //api link + type 

        curl_easy_setopt(curl, CURLOPT_URL, "https://cauth.me/api/admin_handler.php?type=delete_token");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla cAuth"); //ALL requests needs the user-agent Mozilla cAuth

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, "sha256//Mk6vhbkCoRzUhXoUryC8tjIxmehtu4uLVhwqGQM9Cmc=");

        std::string values =
            "&admin_token=" + admintoken + "&program_key=" + programkey + "&token=" + token; //Include admin token and program key

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
        res = curl_easy_perform(curl);
        std::cout << "\nDeleted Key Successfully!";
        system("pause");
        Sleep(4000);

        main();
    }
    if (ans == "c") {
        system("CLS");
        std::cout << "Press Enter to show all unused Keys : ";
        system("pause");
        CURL* curl;
        FILE* fp;
        CURLcode res;
        curl = curl_easy_init(); //api link + type 

        curl_easy_setopt(curl, CURLOPT_URL, "https://cauth.me/api/admin_handler.php?type=view_unused_tokens");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla cAuth"); //ALL requests needs the user-agent Mozilla cAuth

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, "sha256//Mk6vhbkCoRzUhXoUryC8tjIxmehtu4uLVhwqGQM9Cmc=");

        std::string values =
            "&admin_token=" + admintoken + "&program_key=" + programkey; //Include admin token and program key

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
        res = curl_easy_perform(curl);
        std::cout << "\nShowed all Keys Successfully! Press Enter to return to menu.";
        system("pause");
        Sleep(4000);

        main();
    }
    if (ans == "d") {
        system("CLS");
        string username;
        string gusername = "&username=";
        std::cout << "Enter Username to Reset HWID : ";
        std::cin >> username;
        CURL* curl;
        FILE* fp;
        CURLcode res;
        curl = curl_easy_init(); //api link + type 

            curl_easy_setopt(curl, CURLOPT_URL, "https://cauth.me/api/admin_handler.php?type=reset_user_hwid");
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla cAuth"); //ALL requests needs the user-agent Mozilla cAuth

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, "sha256//Mk6vhbkCoRzUhXoUryC8tjIxmehtu4uLVhwqGQM9Cmc=");

            std::string values =
                "&admin_token=" + admintoken + "&program_key=" + programkey + gusername + username; //Include admin token and program key

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
            res = curl_easy_perform(curl);
            std::cout << "\nReset HWID Successfully!";
            Sleep(4000);

        main();
    }
    if (ans == "e") {
        system("CLS");
        string username;
        string gusername = "&username=";
        std::cout << "Enter Username to Ban/Unban : ";
        std::cin >> username;
        CURL* curl;
        FILE* fp;
        CURLcode res;
        curl = curl_easy_init(); //api link + type 

        curl_easy_setopt(curl, CURLOPT_URL, "https://cauth.me/api/admin_handler.php?type=ban_user");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla cAuth"); //ALL requests needs the user-agent Mozilla cAuth

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, "sha256//Mk6vhbkCoRzUhXoUryC8tjIxmehtu4uLVhwqGQM9Cmc=");

        std::string values =
            "&admin_token=" + admintoken + "&program_key=" + programkey + gusername + username; //Include admin token and program key

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
        res = curl_easy_perform(curl);
        std::cout << "\nBanned/Unbanned user successfully!";
        Sleep(4000);

        main();
    }

}