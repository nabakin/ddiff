#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <dirent.h>
#include <ftw.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct Directory_Node
{
  char *name;
  char *hashes;//Trie *hashes;
} DNode;

typedef struct Node
{
  DNode *data;
  struct Node *next;
} Node;

typedef struct List
{
  Node *head;
} List;

int isDirectory(const char *path)
{
  struct stat statbuf;
  
  if (stat(path, &statbuf) != 0)
    return 0;
  
  return S_ISDIR(statbuf.st_mode);
}

int main(int argc, char **argv)
{
  if (argc != 3 || !isDirectory(argv[1]) || !isDirectory(argv[2]))
    return 1;
  
  struct dirent *dp;
  List *old_hashes = (List*) malloc(sizeof(List));
  Node *current_node;
  DNode *current_dnode;
  DIR *old_dir = opendir(argv[1]);
  DIR *new_dir = opendir(argv[2]);
  
  readdir(old_dir); // Cycle through ".." directory
  dp = readdir(old_dir);
  
  if (dp != NULL)
  {
    current_dnode = (DNode*) malloc(sizeof(DNode));
    current_dnode->name = (char*) malloc(sizeof(char)*strlen(dp->d_name));
    strcpy(current_dnode->name, dp->d_name);
    current_dnode->hashes = NULL;//buildTrie(dp);
    
    old_hashes->head = (Node*) malloc(sizeof(Node));
    old_hashes->head->data = current_dnode;
    old_hashes->head->next = NULL;
    
    current_node = old_hashes->head;
    
    while ((dp = readdir(old_dir)) != NULL)
    {
      current_node->next = (Node*) malloc(sizeof(Node));
      current_node = current_node->next;
      
      current_dnode = (DNode*) malloc(sizeof(DNode));
      current_dnode->name = (char*) malloc(sizeof(char)*strlen(dp->d_name));
      strcpy(current_dnode->name, dp->d_name);
      current_dnode->hashes = NULL;//buildTrie(dp);
      
      printf("DIR: %s\n", current_dnode->name);
      
      current_node->data = current_dnode;
      current_node->next = NULL;
    }
  }
  
  return 0;
}