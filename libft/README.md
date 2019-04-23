# mini libc
Toy C libary with some fun data structures.

## Features

#### Number / string conversions
`atof atoi itoa itoa_base utoa_base`  
#### Predicates
`isalnum isalpha isascii isdigit isprint memcmp strcmp strncmp strnequ`  
#### List linked list manipulation
`lstadd lstdel lstdelone lstfind lstiter lstlen lstmap lstnew lstpush lstpop lstrm`  
#### Raw memory manipulation
`bzero memalloc memccpy memchr memcpy memdel memmove memset`  
#### Simple printing
`putchar putchar_fd putendl putendl_fd puterror putnbr putnbr_fd putstr putstr_fd`  
#### String Manipulation
`strcat strchr strclr strcpy strdel strdup strequ string striter striteri strjoin strlcat 
strlen strmap strmapi strncat strncpy  strnew strnstr strrchr strsplit strstr strsub
strtrim str_has_only
tolower toupper wchar_utf8`  
#### Ulility functions
```
get_next_line
printf
```
### Sorting
```
qsort
compare_str_asc
compare_int_asc
```

## Data Structures

### uvector (unboxed vector)
```
uvector_init
uvector_push
uvector_pop
```
**Use uvectors as strings**
```
strprepend
strappend
````
### vector (boxed vector)
```
vector_init
vector_push
vector_pop
vector_del
```
### map (chained hashmap)
```
map_init
map_set
map_remove
map_get
map_clear
```
