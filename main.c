#include <stdio.h>
#include <stdlib.h>
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

/**
 * Get the size of a file.
 * @param filename The name of the file to check size for
 * @return The filesize, or 0 if the file does not exist.
 */
long long getFileSize(char *filepath)
{
  struct stat st;

  if(stat(filepath, &st) != 0) {
    return 0;
  }

  return st.st_size;
}

long long getFolderSize(char *path)
{
  DIR *dir = opendir(path);
  struct dirent *dp = readdir(dir);
  long long dirsize = 0;

  if (dp != NULL)
  {
    while ((dp = readdir(dir)) != NULL)
    {
      char *name = concat(path, "/", dp->d_name);

      if (isDirectory(name))
        dirsize += getFolderSize(name);
      else
        dirsize += getFileSize(name);
    }
  }

  return dirsize;
}

int *parseData(int data, int tailSize)
{
  int *parsedData = malloc(sizeof(int)*tailSize);
  
  for (int i=tailSize; i>0; i--)
  {
    parsedData[i-1] = data % 10;
    data /= 10;
  }
  
  return parsedData;
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

  char *old_dir = argv[1];
  char *new_dir = argv[2];

  struct dirent *dp;
  TNode *head, *current_node;

  print_dir(argv[1]);

  char *large_dir;
  char *small_dir;

  if (getFolderSize(argv[1]) > getFolderSize(argv[2]))
  {
    large_dir = argv[1];
    small_dir = argv[2];
  }
  else
  {
    large_dir = argv[2];
    small_dir = argv[1];
  }

  FSTrie *small_dir_trie = populateFilesizeTree(small_dir);

  /*readdir(small_dir); // Cycle through ".." directory
  dp = readdir(small_dir);

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
