#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

//Lucas Osacar Discovery: 
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

//urlDecode from https://stackoverflow.com/questions/154536/encode-decode-urls-in-c/4823686#4823686
string urlDecode(string str){
    string ret;
    char ch;
    int i, ii, len = str.length();

    for (i=0; i < len; i++){
        if(str[i] != '%'){
            if(str[i] == '+')
                ret += ' ';
            else
                ret += str[i];
        }else{
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        }
    }
    return ret;
}


unordered_map<string, string> generateUriMap(string uri)
{
    unordered_map<string, string> m;
    string equal = "=";
    string ampersand = "&";
    size_t pos = 0;
    string key;
    string value;
    while ((pos = uri.find(equal)) != std::string::npos) 
    {
        key = uri.substr(0, pos);
        //key=urlDecode(key);
        uri.erase(0, pos + equal.length());
        value = uri.substr(0,uri.find(ampersand));
        //value=urlDecode(value);
        uri.erase(0, uri.find(ampersand) + ampersand.length());
        m[key]= value;
    }
    return m;
}



int main()
{ 
    cout << "Content-type:text/html;charset=UTF-8\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Hello World - Third CGI Program</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";

    cout << "<form action='hello_world_cgi_refact_03.cgi' method='post'>";
    cout << "<label>Introduzca su nombre:</label>\n";
    cout << "<input type='text' name='name'>\n";
    cout << "<label>Introduzca su apellido:</label>\n";
    cout << "<input type='text' name='surname'>\n";
    cout << "<input type='submit' name='sbmt' value='enviar'>\n";
    cout << "</form>\n";

    string str = "";
    cin >> str;
    if (str != "")
    {
        unordered_map<string,string> uriMap = generateUriMap(str);
        uriMap["name"]=urlDecode(uriMap["name"]);
        uriMap["surname"]=urlDecode(uriMap["surname"]);
        cout << "<h2>Hello! your name is: " << uriMap["name"] << "</h2>\n";
        cout << "<h2>your surname is: " << uriMap["surname"] << "</h2>\n";
    }

    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}
