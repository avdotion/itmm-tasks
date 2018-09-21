// TASK: Data structure - Binary search tree
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100

typedef struct _tree_node {
  char *word;
  int count;
  struct _tree_node *left_child;
  struct _tree_node *right_child;
} tree_node;

tree_node *addLeaf(tree_node *wild_tree, char *string) {
  if (wild_tree == NULL) {
    wild_tree = (tree_node *)malloc(sizeof(tree_node));
    wild_tree->word = strdup(string);
    wild_tree->count = 1;
    wild_tree->left_child = wild_tree->right_child = NULL;
  } else {
    int cond = strcmp(string, wild_tree->word);
    if (cond == 0) {
      wild_tree->count++;
    } else if (cond < 0) {
      wild_tree->left_child = addLeaf(wild_tree->left_child, string);
    } else {
      wild_tree->right_child = addLeaf(wild_tree->right_child, string);
    }
  }
  return wild_tree;
}

void freeLeaf(tree_node *tree) {
  if (tree != NULL) {
    freeLeaf(tree->left_child);
    freeLeaf(tree->right_child);
    free(tree);
  }
}

void treePrint(tree_node *p) {
  if (p != NULL) {
    treePrint(p->left_child);
    printf("%d %s\n", p->count, p->word);
    treePrint(p->right_child);
  }
}
int main() {
  FILE *text;
  text = fopen("15-test.txt", "r");

  tree_node *root;
  root = NULL;

  char current_word[MAX_WORD_LENGTH];
  int letters_in_current_word = 0;

  char symbol;
  while ((symbol = (char)fgetc(text)) != EOF) {
    if (symbol == ' ' || symbol == '!' || symbol == '?' ||
        symbol == '.' || symbol == ',' || symbol == '\n' ||
        symbol == ';' || symbol == ':') {
      if (letters_in_current_word > 0) {
        char word[letters_in_current_word+1];
        for (int i = 0; i < letters_in_current_word; ++i) {
          (word)[i] = current_word[i];
        }
        word[letters_in_current_word] = 0;
        root = addLeaf(root, word);
        letters_in_current_word = 0;
      }
    } else if (isalpha(symbol)) {
      current_word[letters_in_current_word] = symbol;
      letters_in_current_word++;
    }
  }

  treePrint(root);
  freeLeaf(root);

  return 0;
}
