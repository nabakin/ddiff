#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>

#define DIGIT_SIZE 10

typedef struct TrieNode
{
  struct TrieNode *children;
} TNode;

int isDirectory(const char *path)
{
  struct stat statbuf;
  
  if (stat(path, &statbuf) != 0)
    return 0;
  
  return S_ISDIR(statbuf.st_mode);
}

char* concat(char *s1, char *s2, char *s3)
{
  int s1_length = strlen(s1);
  int s2_length = strlen(s2);
  int s3_length = strlen(s3);
  char *result = malloc(s1_length+s2_length+s3_length+1);

  int i;
  for (i=0; i<s1_length; i++)
    result[i] = s1[i];
  
  int j;
  for (j=0; j<s2_length; j++)
    result[i+j] = s2[j];
  
  i = i+j;
  
  for (j=0; j<s3_length; j++)
    result[i+j] = s3[j];
  
  result[i+j] = '\0';

  return result;
}

long long getFileSize(char *filepath)
{
  struct stat st;
  stat(filepath, &st);
  
  return st.st_size;
}

void print_dir(char *path)
{
  struct dirent *dp;
  DIR *dir = opendir(path);
  
  readdir(dir); // Cycle through ".." directory
  dp = readdir(dir);
  
  if (dp != NULL)
  {
    //head = (TNode*) malloc(sizeof(TNode));
    //head->children = (TNode*) malloc(sizeof(TNode)*DIGIT_SIZE);
    //current_node = head;
    
    while ((dp = readdir(dir)) != NULL)
    {
      char *name = concat(path, "/", dp->d_name);
      
      if (isDirectory(name))
      {
        printf("DIR: %s %s\n", dp->d_name, name);
        print_dir(name);
      }
      else
      {
        int digits = 4;
        int size = getFileSize(name) % ((int) pow(10, digits));
        printf("FILE: %s %d\n", dp->d_name, size);
      }
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 3 || !isDirectory(argv[1]) || !isDirectory(argv[2]))
    return 1;
  
  //struct dirent *dp;
  TNode *head, *current_node;
  
  print_dir(argv[1]);
  /*DIR *old_dir = opendir(argv[1]);
  DIR *new_dir = opendir(argv[2]);
  
  readdir(old_dir); // Cycle through ".." directory
  dp = readdir(old_dir);
  
  if (dp != NULL)
  {
    head = (TNode*) malloc(sizeof(TNode));
    head->children = (TNode*) malloc(sizeof(TNode)*DIGIT_SIZE);
    current_node = head;
    
    while ((dp = readdir(old_dir)) != NULL)
    {
      char *name = concat(concat(argv[1], "/"), dp->d_name);
      if (isDirectory(name))
        printf("DIR: %s %s\n", dp->d_name, name);
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
  }*/
  
  return 0;
}