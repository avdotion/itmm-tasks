// TASK: Data structure - Binary search tree
// STATUS: DONE
// MARK: PASSED

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

tree_node *add_leaf(tree_node *wild_tree, char *string) {
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
      wild_tree->left_child = add_leaf(wild_tree->left_child, string);
    } else {
      wild_tree->right_child = add_leaf(wild_tree->right_child, string);
    }
  }
  return wild_tree;
}

void free_leaf(tree_node *tree) {
  if (tree != NULL) {
    free_leaf(tree->left_child);
    free_leaf(tree->right_child);
    free(tree);
  }
}

void tree_print(tree_node *p) {
  if (p != NULL) {
    tree_print(p->left_child);
    printf("%d %s\n", p->count, p->word);
    tree_print(p->right_child);
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
    // 'a' <= symbol && symbol <= 'z' || 'A' <= symbol && symbol <= 'Z'
    if (symbol == ' ' || symbol == '!' || symbol == '?' ||
        symbol == '.' || symbol == ',' || symbol == '\n' ||
        symbol == ';' || symbol == ':' || symbol == '\t') {
      if (letters_in_current_word > 0) {
        char word[letters_in_current_word+1];
        for (int i = 0; i < letters_in_current_word; ++i) {
          (word)[i] = current_word[i];
        }
        word[letters_in_current_word] = 0;
        root = add_leaf(root, word);
        letters_in_current_word = 0;
      }
    } else if (isalpha(symbol)) {
      current_word[letters_in_current_word] = symbol;
      letters_in_current_word++;
    }
  }

  tree_print(root);
  free_leaf(root);

  return 0;
}
