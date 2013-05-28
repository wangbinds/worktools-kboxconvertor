#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "keybox.h"

#define KEYBOX_FILE_NAME "KeyBox.txt"
#define DEST_FILE_NAME_FORMAT "keybox_csv_%d.csv"
#define BUFFER_LENGTH 512
//#define NUMBER_OF_KEYBOXES 300000
//#define NUMBER_OF_EACH_FILE 50000
#define NUMBER_OF_KEYBOXES 45
#define NUMBER_OF_EACH_FILE 9

using namespace std;

int main(int argc, char *argv[])
{
    char buffer[BUFFER_LENGTH];
    char destFileName[20];
    char *srcFileName = KEYBOX_FILE_NAME;
    FILE* src = NULL;
    FILE* dest = NULL;
    Keybox keybox;
    cout<<"KeyboxConvertor opened"<<endl<<endl;

    //check command line parameters
    if(argc > 2)
    {
        cout<<"wrong command line parameters"<<endl;
        cout<<"Usage: KeyboxConvertor [sourceFile]"<<endl;
        cout<<"to convert android keybox"<<endl;
        cout<<"If you do not provide the source file,\nthe default is KeyBox.txt in the Current directory"<<endl;
        return 1;
    }
    //if there are tow command line parameters
    //the second is the input file path
    if(argc == 2)
    {
        srcFileName = argv[1];
        cout<<"the input file path is : "<<srcFileName<<endl;
    }
    
    if((src = fopen(srcFileName, "r")) == NULL)
    {
           cout<<"KeyboxConvertor open source file FAILED"<<endl;
           goto finally;
    }
    for(int i=0; i<NUMBER_OF_KEYBOXES; i++)
    {
        //open a new destination file to write
        if( i%NUMBER_OF_EACH_FILE == 0 )
        {
            if(dest != NULL)
            {
                fclose(dest);
                dest = NULL;
            }
            sprintf(destFileName, DEST_FILE_NAME_FORMAT, i/NUMBER_OF_EACH_FILE);
            cout<<"KeyboxConvertor : create dest file "<<destFileName<<endl;
            if((dest = fopen(destFileName, "wb")) == NULL)
            {
                cout<<"KeyboxConvertor open destination file FAILED"<<endl;
                goto finally;
            }
        }
        
        //read a line from source file 
        memset(buffer, 0,  BUFFER_LENGTH);
        if(fgets(buffer, BUFFER_LENGTH, src) == NULL)
        {
            cout<<"KeyboxConvertor read file FAILED"<<endl;
            goto finally;
        }
        //cout<<"KeyboxConvertor handle keybox : "<<buffer<<endl;
        keybox.init(buffer);
        memset(buffer, 0,  BUFFER_LENGTH);
        int length = keybox.convertToCsv(buffer);
        char deviceID[DEVICEID_SIZE_IN_KEYBOX];
        keybox.getDeviceID(deviceID);
        printf("KeyboxConvertor : converting keybox %s\r\n", deviceID);
        
        //write the formated keybox to destination file
        fwrite(buffer, 1, length, dest);
    }
    cout<<"Keyboxconvertor convert all keybox successfully"<<endl;
    
finally:
    //Finally : close all opened files
    if(src != NULL) fclose(src);
    if(dest != NULL) fclose(dest);
    
    //system("PAUSE");
    return EXIT_SUCCESS;
}
