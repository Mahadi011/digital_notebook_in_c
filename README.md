# digital_notebook
to compile type make in comand terminal
to run have to run from command terminal
have to type
./memo -h 
        Show this help.
./memo -o 
        open the file ot work with.
./memo -i 
        Init a new empty database. For example:
        memo -i "memo.csv" 
        Create a new empty database with the name "memo.csv"
./memo -a 
        Append at the end of the database the following message.
        memo -a "This message will be included at the end of the database"
./memo -s 
        Search and find specific entries in the database.
        memo -s "09-11-2022" will show all entries at a this given date.
        memo -s "programming" will show all entries containing the word
              "programming".
./memo -d 
        Delete an entry in the database.
        memo -d 123 will delete entry number 123.
