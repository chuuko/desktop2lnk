/*
 * desktop2lnk
 * An utility to convert mainstream desktop shortcuts to iDesk shortcuts
 * By chuuko
 * License: BSD-3
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>


using namespace std;

int scanForInvalidChar(std::string input)
{

    //desktop2lnk doesn't support non-ASCII characters yet

    std::string allowed_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012346789.:-,;_?!*<>#&@()=[]{}+%§*/";

    //How do I escape "" and ''?

    int j = 0;
    for(int i =0; i<input.length();i++)
    {

        if(input.at(i)==allowed_characters.at(j))
        {
            j = 0;
        }
        else
        {
            j++;
        }
        if(j>allowed_characters.length())
        {
            return(1);
        }
        else
        {
            return(0);
        }
    }
}

int main(int argc, char **argv)
{
    //TODO: Implement spaces in path names

    if(argv[1]==NULL)
    {
        cout << "No input" << endl;
        return 2;
    }

    std::string aDir = std::getenv("PWD");
    std::string filename;
    filename = argv[1];

    std::string home = getenv("HOME");

    if(filename.substr(0,home.length())==home)
    {
        filename = filename.substr(home.length()+1);
    }

    if(filename.substr(0,2)=="./")
    {
        filename = filename.substr(2);
    }

    //TODO: Resolve ../

    if(scanForInvalidChar(filename)==0)
    {

    }
    else
    {
        cout<<"Invalid character in filename"<<endl;
        return 2;
    }

    //TODO: Implement custom errors

    if(scanForInvalidChar(aDir)==0)
    {

    }
    else
    {
        cout << "Invalid character in file path"<<endl;
        return 2;
    }

    if(filename.length()<8||filename.substr(filename.find("."),8)!=".desktop")
    {
        return 2;
    }

    //Open .desktop file

    ifstream dfile;
    dfile.open(std::string(aDir+"/"+filename));
    if(!dfile)
    {
        cout<< "ERROR: file not found at "<< std::string(aDir+"/"+filename) << endl;
        return 2;
    }

    //Parse .desktop file

    string b;

    const char *newl = "\n";

    vector<std::string> desktopS;

    int c = 1;

    std::string name, exec, icon;

    while(std::getline(dfile,b,*newl))
    {
        if(scanForInvalidChar(b)==0)
        {

        }
        else
        {
            cout<<"ERROR: invalid character in file"<<endl;
            return 1;
        }

        desktopS.resize(c);
        desktopS.reserve(c);
        desktopS[c-1] = b;

        if(!(desktopS[0]==std::string("[Desktop Entry]")))
        {
            cout<<"Invalid desktop entry file"<<endl;
            return 1;
        }
        if(b.substr(0,4)==std::string("Name"))
        {
            name = b.substr(5);
        }
        if(b.substr(0,4)==std::string("Icon"))
        {
            icon = b.substr(5);
        }
        if(b.substr(0,4)==std::string("Exec"))
        {
            exec = b.substr(5);
        }
        c++;
    }

    dfile.close();

    //Write .lnk file

    std::string lnkDir = getenv("HOME")+std::string("/.idesktop");

    std::ofstream lnk;

    lnk.open(std::string(lnkDir+"/"+name+".lnk"));

    lnk << "table Icon" << endl << "  Caption: " << name << endl << "  Command: " << exec << endl << "  Icon: " << icon << endl <<
           "  Width: 48" << endl << "  Height: 48" << endl << "  X: 100" << endl << "  Y: 100" << endl << "end" << endl;

    lnk.close();

    return 0;
}
