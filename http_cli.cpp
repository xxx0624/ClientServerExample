#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <algorithm>
#include <string>
using namespace std;

typedef pair<string, string> hostname_path;
typedef pair<hostname_path, int> hostname_path_port;

hostname_path_port parse(string url){
    // extract http part
    int hostname_start_pos = 0;
    string http_str = url.substr(0, 7);// 7 is for "http://"
    if(http_str.compare("http://") == 0){
        hostname_start_pos = 7;
    }
    string https_str = url.substr(0, 8); // 8 is for "https://"
    if(http_str.compare("https://") == 0){
        hostname_start_pos = 8;
    }
    // extract port if it exists
    int port_start_pos = -1, port = -1, port_end_pos = -1;
    for(int i = hostname_start_pos; i < url.length(); i ++){
        if(url[i] == '/'){
            break;
        }
        if(url[i] == ':'){ // maybe port exists
            port_start_pos = i + 1;
            for(int j = i + 1; j < url.length(); j ++){
                if(url[j] == '/'){
                    break;
                }
                port_end_pos = j;
            }
            if(port_end_pos >= port_start_pos){
                string port_str = url.substr(port_start_pos, 1 + port_end_pos - port_start_pos);
                try{
                    port = stoi(port_str);
                } catch (...){
                    cerr << "invalid url:" << endl;
                    exit(-1);
                }
            }
            break;
        }
    }
    if(port == -1){
        port_start_pos = -1;
        port_end_pos = -1;
    }
    // extract path
    int path_start_pos;
    for(path_start_pos = max(hostname_start_pos, port_end_pos); path_start_pos < url.length(); path_start_pos ++){
        if(url[path_start_pos] == '/') {
            break;
        }
    }
    string path = "/";
    if(path_start_pos >= 0 && path_start_pos < url.length() && url[path_start_pos] == '/'){
        path += url.substr(path_start_pos + 1, url.length() - 1 - path_start_pos);
    }
    // extract hostname
    int hostname_end_pos = min(path_start_pos, (int)(url.length()) - 1);
    if(port != -1){
        hostname_end_pos = port_start_pos - 2;
    }
    string hostname = url.substr(hostname_start_pos, hostname_end_pos - hostname_start_pos + 1);

    hostname_path_port res;
    hostname_path part1;
    part1.first = hostname;
    part1.second = path;
    res.first = part1;
    res.second = port;
    return res;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Usage:./http_cli URL" << endl;
        return EXIT_FAILURE;
    }

    string url = argv[1];
    hostname_path_port res = parse(url);
    cout << "hostname:" << res.first.first << endl;
    cout << "path:" << res.first.second << endl;
    cout << "port:" << res.second << endl;

    return 0;
}