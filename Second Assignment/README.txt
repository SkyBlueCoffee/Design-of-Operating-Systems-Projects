There are ten input files, each contains some information about the book. Your task is to create multiple threads, one for each input file, and search for the entered book name and display the result.
The ten input .txt files are as follows:
1. crime.txt: includes the information about the movies that belong to genre crime.
2. fantasy.txt: includes the information about the movies that belong to genre fantasy.
3. history.txt: includes the information about the movies that belong to genre history.
4. horror.txt: includes the information about the movies that belong to genre horror.
5. psychology.txt: includes the information about the movies that belong to genre psychology.
6. romance.txt: includes the information about the movies that belong to genre romance.
7. science.txt: includes the information about the movies that belong to genre science.
8. sports.txt: includes the information about the movies that belong to genre sports.
9. thriller.txt: includes the information about the movies that belong to genre thriller.
10. travel.txt: includes the information about the movies that belong to genre travel.

All of these files contain the same metadata, and they are described below:
a) title: the name of the book.
b) genre: a thematic or stylistic categorization of a book.
c) rating: the percentage of professional critic reviews that are positive for a given book.
d) summary: brief summary about the book.

Examples:
i) ./a.out crime.txt
The main thread just creates one new thread and that thread will look into crime.txt file for the requested
book name.

ii) ./a.out sports.txt fantasy.txt
The main thread creates two new threads. One thread will search for the requested book information in
the sports.txt file while another thread will search in the fantasy.txt file.
Your program needs to ask the user to enter a list of the book name. This list can contain N number of
book name, where the value of N is given by the user. Once the user provides this list of book names, the
program (to be more specific, the main thread) should create a number of threads depending upon how
many filenames has been entered as the command-line argument. Each thread will have its own input file
and all of these newly created threads will search for the entered book name in their respective input file.

Once a thread finds the book(s), it needs to send the corresponding book(s) information to the main
thread. Once all the book information is found, the main thread will then need to do the following tasks:
i) cancel all the running threads.
ii) display the message that the thread cancellation signal has been sent to the target threads.
You should clearly specify the corresponding target thread ID as well.
iii) display the corresponding information (title, genre, rating and summary) to the screen.
iv) join all the threads.

If the thread cannot find the given book in its input file (in other words, the given book name is not present
in any of the input file), then the main thread needs to display the appropriate message:
Book (<give book name>) not found!

The target threads should use deferred cancelation. The target threads should define the cancellation
point and before getting cancelled they needs to do the following tasks:
i) close its opened file
ii) after closing the file, display the message:
File <give filename> closed successfully.