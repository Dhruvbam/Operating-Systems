/*-------------------------------------------------------------------------------------------------------------
Purpose:
This program demonstrates how to interact with a local API running on localhost:5000 using the libcurl library in C++.
It sends PUT and GET requests to the /initialize and /modify endpoints, processes the responses, and performs
various actions based on the API's functionality.

Author:
Dhruv Maniar
R11713343

Course:
CS 4352-002

R#:
R11713343
-------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <curl/curl.h>

/*-------------------------------------------------------------------------------
  Function Name: WriteCallback
  Purpose: Callback function for libcurl to write response data into a buffer.
  Type: static size_t
  Parameters: 
    - void *contents: Pointer to the response data.
    - size_t size: Size of each data element.
    - size_t nmemb: Number of data elements.
    - void *userp: Pointer to the buffer where the data should be stored.
  Other important info:
    - This function appends the received data to the buffer and returns the total size of the data written.
-  -------------------------------------------------------------------------------*/
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/*-------------------------------------------------------------------------------
  Function Name: initialize_put
  Purpose: Sends a PUT request to the /initialize endpoint with a specified input value.
  Type: void
  Parameters: 
    - std::string input: The input value to be sent with the PUT request.
  Other important info:
    - This function uses the libcurl library to send the PUT request and handles any errors that occur during the request.
-  -------------------------------------------------------------------------------*/
void initialize_put(std::string input) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the HTTP headers and request data
        struct curl_slist *headers = NULL;
        std::string data = input;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
          curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/initialize");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
          curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        
        // Perform the PUT request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        // Cleanup the curl handle
        curl_easy_cleanup(curl);
    }
    // Cleanup libcurl
    curl_global_cleanup();
}

/*-------------------------------------------------------------------------------
  Function Name: initialize_get
  Purpose: Sends a GET request to the /initialize endpoint and prints the response.
  Type: std::string
  Parameters: None
  Other important info:
    - This function uses the libcurl library to send the GET request, stores the response in a buffer, and prints the response to standard output.
-  -------------------------------------------------------------------------------*/
std::string initialize_get() { 
    std::string buffer; 
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/initialize");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        
        // Create a buffer to store the response data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        
        // Perform the GET request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        // Cleanup the curl handle
        curl_easy_cleanup(curl);
        
        // Print the response
        std::cout << "\nResponse from /initialize: " << buffer << std::endl;
    }
    // Cleanup libcurl
    curl_global_cleanup();
    return buffer;
}

/*-------------------------------------------------------------------------------
  Function Name: modify_put
  Purpose: Sends a PUT request to the /modify endpoint with a specified input value.
  Type: void
  Parameters: 
    - std::string input: The input value to be sent with the PUT request.
  Other important info:
    - This function uses the libcurl library to send the PUT request and handles any errors that occur during the request.
-  -------------------------------------------------------------------------------*/
void modify_put(std::string input) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the HTTP headers and request data
        struct curl_slist *headers = NULL;
        std::string data = input;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/modify");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        
        // Perform the PUT request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        // Cleanup the curl handle
        curl_easy_cleanup(curl);
    }
    // Cleanup libcurl
    curl_global_cleanup();
}

/*-------------------------------------------------------------------------------
  Function Name: modify_get
  Purpose: Sends a GET request to the /modify endpoint and prints the response.
  Type: std::string
  Parameters: None
  Other important info:
    - This function uses the libcurl library to send the GET request, stores the response in a buffer, and prints the response to standard output.
-  -------------------------------------------------------------------------------*/
std::string modify_get() { 
     std::string buffer;
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/modify");
          curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        
        // Create a buffer to store the response data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        
        // Perform the GET request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
          std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        // Cleanup the curl handle
        curl_easy_cleanup(curl);
        
        // Print the response
        std::cout << "\nResponse from /modify: " << buffer << std::endl;
    }
    // Cleanup libcurl
    curl_global_cleanup();
    return buffer;
}

/*-------------------------------------------------------------------------------
  Function Name: main
  Purpose: Entry point of the program.
  Type: int
  Parameters: None
  Other important info:
    - This function performs the following tasks:
      1) Task #1: Print student information (name and R#).
      2) Task #2: Send integer 3360 to /initialize via PUT.
      3) Task #3: Send integer 4 to /modify via PUT.
      4) Task #4: Retrieve data from /initialize via GET and store the value as an integer.
      5) Task #5: Retrieve data from /modify via GET and store the value as an integer.
      6) Task #6: Send the value received from /modify (step #5) to /initialize via PUT.
      7) Task #7: Send the value received from /initialize (step #4) to /modify via PUT.
      8) Task #8: Retrieve data from /initialize via GET and store the value as an integer.
      9) Task #9: Retrieve data from /modify via GET and store the value as an integer.
-  -------------------------------------------------------------------------------*/

int main() {
    // Print student information
    std::cout << "Dhruv Maniar" << std::endl;
    std::cout << "R11713343" << std::endl;

    // Perform the required tasks
    initialize_put("3360");
    std::string response_initialize = initialize_get();

    modify_put("4");
    std::string response_modify = modify_get();

    initialize_put(response_modify);
    initialize_get();

    modify_put(response_initialize);
    modify_get();
    return 0;
}
