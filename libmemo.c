#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#include"memo.h"


int help_function(char *str)
{
    FILE *file;
// Opening file in read mode
file = fopen("help.txt","r");

char buffre[MAX_LINE];
  if(file==NULL)
    {
        printf("Error to open file.\n");
        return 1;
    }

while(!feof(file))
{
    //reading line by line
    fgets(buffre,MAX_LINE,file);
    //printing lines in terminal
    printf("%s",buffre);

}
printf("\n");
//closing file
fclose(file);
}


int new_database(char *str)
{
    
   FILE *name_file, *data_file, *current_file;
   
   //opening name_file to store file names
    name_file=fopen("name_file.txt","a+");

    char file_name[30];
    char option;
    if(name_file==NULL)
    {
        printf("Error to open file.\n");
        return 1;
    }
   
    while(!feof(name_file))
    {
       fscanf(name_file,"%s",file_name);
        
        //for checking if the filename exists in name_file
        if(strcmp(file_name,str)==0)
        {
             
            break;

        }
           
    }
    //if file name exists it will ask for options
    if(strcmp(file_name,str)==0)
    {
        printf("file is already exist over write [y n]: ");
        scanf(" %c",&option);
        if(option=='y')
        {
            data_file=fopen(str,"w");
            fclose(data_file);
            
        }
        else
        {   //if option is n then it will ask for new name
            printf("Enter the file name: ");
            scanf(" %s",str);
            //call this new_database function with new filename
            new_database(str);
        }
    }
    else
    {
        //if file name dose not exist it will store the name in name_file
        //and creat a new file
        data_file= fopen(str,"w");
        fprintf(name_file,"%s\n",str);
        fclose(data_file);
    }
    
    fclose(name_file);

    //Writing file name in current file also
    current_file = fopen("current_file.txt","w");
    if(current_file==NULL)
    {
        printf("Error to open file.\n");
        return 1;
    }
    fprintf(current_file,"%s",str);

    fclose(current_file);
    

 }


 int append_in_darabase(char *str)
 {  //Opening file in read and append mode
    FILE *file,*current_file;
    char filename[30];

    if(current_file==NULL)
    {
        printf("Error to open file.\n");
        return 1;
    }
    
    current_file = fopen("current_file.txt","r");
    // accessing filename from current file
    while(!feof(current_file))
    {
        fgets(filename,30,current_file);

    }
    fclose(current_file);


    //opening that file as append+ mode
    file=fopen(filename,"a+");
    int id,i,len;
    char buffer[MAX_LINE];
    char c_id[MAX_LINE];

    if(file == NULL)
    {
        printf("Error to opening the file.");
    }
    //for take the last line of file
    while(!feof(file))
    {
        fgets(buffer,100,file);
    }
    //checking it is the frist entry in the file
    if(buffer[0]=='\0')
    {
        id=0;
    }
    else
    {   //finding the id
        len=strlen(buffer);
        for(i=0;i<len;i++)
        {
            if (buffer[i]==',')
                break;
            c_id[i]=buffer[i];
        }
        //converting string to int
        id=strtol(c_id,'\0',10);
            
    }

   
  
    // taking t in time function
    time_t t;
    //taking current time in t
    t = time(NULL);

    //Putting local time in struct tm
    struct tm tm = *localtime(&t);


    id++;
    
    fprintf(file,"%d,",id);
    fprintf(file,"%d-%d-%d ", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900); //month count started from january and year from 1900
    fprintf(file,"%d:%d:%d,", tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(file,"\"%s\"\n",str);

    //closing opend file
    fclose(file);
 }


int delete_entry(char *str)
{
    FILE *current_file;
    char filename[30];
    //acccessing filename from current file
    current_file=fopen("current_file.txt","r");
    
    if(current_file==NULL)
    {
        printf("Error to open file.\n");
        return 1;
    }
    while(!feof(current_file))
    {
        fgets(filename,30,current_file);

    }
    fclose(current_file);

    //Opening file read and temp write mode
    FILE *file, *temp;
        file = fopen(filename,"r");
        temp = fopen("temp____file___.txt","w");

    
    char buffer[MAX_LINE];
    int i,len;
    char temp_arr[20];
    bool keep_reading =true;

    //checking for error opening
    if(file==NULL && temp == NULL)
    {
        printf("Error to open file.\n");
        return 1;
    }
    
    
    
    do{
        //reading file line by line
        fgets(buffer,MAX_LINE,file);

        //checking for end of file
        if(feof(file))
        {
            keep_reading=false; 
        }
        else
        { 
        //making a new array  from buffer till frist ','
        len =strlen(buffer);
        for(i=0;i<len;i++)
        {
            if(buffer[i]==',')
                break;
            temp_arr[i]=buffer[i];
        }
        //comparing the new array with given value
        if(strcmp(temp_arr,str)!=0)
        {
            //writing in temp file which are not same
            fprintf(temp,"%s",buffer);
        }
        }

        
    }while (keep_reading);
 
        
    //closing file
    fclose(file);
    fclose(temp);

    //updating memo file
    remove(filename);
    rename("temp____file___.txt",filename);
    

}


int search_function(char *str)
{   //Opening file in read mode
    FILE *file,*current_file;
    char filename[30];

    if(current_file==NULL)
    {
        printf("Error to open file.\n");
        return 1;
    }
    //to access filename from current file function
    current_file = fopen("current_file.txt","r");
    
    while(!feof(current_file))
    {
        fgets(filename,30,current_file);

    }
    fclose(current_file);

    file = fopen(filename,"r");

    char buffer[MAX_LINE];
    //checking error to open the file
    if(file==NULL)
    {
        printf("Error to open file.");
    }
    bool keep_reading =true;
    
    
    do{
        //reading file line by line
        fgets(buffer,MAX_LINE,file);
        
        ////checking for end of file
        if(feof(file))
        {
            keep_reading=false; 
        }
        else
        {   //comparing buffer with given string and
            // if it same then printing whole string in terminal
            if((strstr(buffer,str)!=NULL))
            {
                printf("%s",buffer);
            }

        }

        
    }while (keep_reading);
  
    fclose(file);
}




