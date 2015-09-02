#ifndef _HTTP1_RESHET_H_
#define _HTTP1_RESHET_H_

#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include "configure.h"

class HTTP1_Response {
public:
    HTTP1_Response() {};
    ~HTTP1_Response() {};
    static std::string make_response(std::vector<std::string> &header, std::vector<std::string> &message_body);
    //static std::vector<std::string>& make_header(int version, int body_length, std::ifstream &output_file);
    static std::vector<std::string>& make_header(int version, int body_length, int is_file_exist, std::string path);
    static void make_body (std::vector<std::string> &body_content, int &body_content_length, std::ifstream &output_file);
};

#endif
