#include "http_server.hh"

#include <vector>

#include <sys/stat.h>

#include <fstream>
#include <sstream>

vector<string> split(const string &s, char delim) {
  vector<string> elems;

  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    if (!item.empty())
      elems.push_back(item);
  }

  return elems;
}

HTTP_Request::HTTP_Request(string request) {
  vector<string> lines = split(request, '\n');
  vector<string> first_line = split(lines[0], ' ');

  this->HTTP_version = "1.0"; // We'll be using 1.0 irrespective of the request
 
 
  /*
   TODO : extract the request method and URL from first_line here
  */
  this->method = "GET";
  this->url = first_line[1];
  // cout<< "this is the url\n";
  cout<<"Here is the method "<<this->method<<endl;
  //printf("Here is the message: %s", first_line[1].c_str());
  if (this->method != "GET") {
    cerr << "Method '" << this->method << "' not supported" << endl;
    exit(1);
  }
}

HTTP_Response *handle_request(string req) {
  HTTP_Request *request = new HTTP_Request(req);

  HTTP_Response *response = new HTTP_Response();

  string url = string("html_files") + request->url;
  cout<< "this is the url\n";
  cout<<url<<endl;
  response->HTTP_version = "1.0";

  struct stat sb;
  if (stat(url.c_str(), &sb) == 0) // requested path exists
  {
    //string err = "Hello no file is found for the resquested URL ";
    response->status_code = "200";
    response->status_text = "OK";
    response->content_type = "text/html";
    //response->content_length = to_string(err.size());
    //response->body = err;

    string body;
    std::ifstream f(url);
       std::stringstream buf;
       buf <<f.rdbuf();
       body = buf.str();
       response->content_length = to_string(sb.st_size);
       response->body= body;

    if (S_ISDIR(sb.st_mode)) {
      /*
      In this case, requested path is a directory.
      TODO : find the index.html file in that directory (modify the url
      accordingly)
      */
     cout << "in the st_mode";

     if(stat((url+"index.html").c_str(),&sb) == 0 )
     {
       std::ifstream f(url+"index.html");
       std::stringstream buf;
       buf <<f.rdbuf();
       body = buf.str();
       response->content_length = to_string(sb.st_size);
       response->body= body;

     }
     else {
       std::ifstream f(url);
       std::stringstream buf;
       buf <<f.rdbuf();
       body = buf.str();
       response->content_length = to_string(sb.st_size);
       response->body= body;

     }
    }

    /*
    TODO : open the file and read its contents
    */

    /*
    TODO : set the remaining fields of response appropriately
    */
  }

  else {
    string err = "404 File Not Found";
    response->status_code = "404";
    response->status_text = "File Not Found";
    response->content_type = "text/html";
    response->content_length = to_string(err.size());
    response->body = err;
    

    /*
    TODO : set the remaining fields of response appropriately
    */
  }

  delete request;

  return response;
}

string HTTP_Response::get_string() {
  /*
  TODO : implement this function
  */
   string res = "HTTP/";
   res = res+this->HTTP_version+" "+this->status_code+" "+this->status_text+"\r\n";
   res = res+"Content-Type: "+this->content_type+"\r\n"+"Content-Length: "+this->content_length+"\r\n\n";
   res = res+this->body;
   //cout << res<<endl;
   return res;
 //return "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 20\n\nHello world123!";
}
