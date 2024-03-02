# TabQueryHash
The program reads tab-delimited files, stores data in a hash table, and enables efficient querying. Uses open addressing with double hashing. Supports printing occupied indices and looking up individuals based on keys. Aim for O(1) time complexity.

Example Usage:
Suppose we have a tab-delimited file example.txt containing information about individuals, including their ID, first name, last name, email, phone number, city, state, and postal code. We want to create a hash table with a size of 71 and use the "State" column as the key for indexing individuals.



$ ./tab_hash_query example.txt 71 State
Commands:
    print
    lookup <key>
    quit

Enter a command:
print
5: Ohio (2),
8: Georgia (1),
12: New York (3),
...

Enter a command:
lookup North Carolina
Id,FirstName,LastName,Email,Phone,City,State,PostalCode
14,Cliff,Dosdale,cdosdaled@myspace.com,336-408-3837,High Point,North Carolina,27264
...

Enter a command:
quit



In this example, the program reads the file example.txt, creates a hash table of size 71, and uses the "State" column as the key. Users can then issue commands to print occupied indices, look up individuals based on specific keys, or quit the program.
