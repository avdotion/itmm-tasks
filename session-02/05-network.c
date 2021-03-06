// TASK: PERT
// STATUS: DONE
// MARK: PASSED
// COMMENT: The script shows only one critical path (it's easy to display all).

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Graph;
struct Vertex;

typedef struct LinkedListNode {
  void* data;
  struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* newLinkedListNode(void* data) {
  LinkedListNode *linked_list_node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
  linked_list_node->data = data;
  linked_list_node->next = NULL;
  return linked_list_node;
}

typedef struct LinkedList {
  int size;
  LinkedListNode* chain;
} LinkedList;

LinkedList* newLinkedList() {
  LinkedList *linked_list = (LinkedList*)malloc(sizeof(LinkedList));
  linked_list->chain = newLinkedListNode("_HEAD");
  linked_list->chain->next = newLinkedListNode("_TAIL");
  linked_list->size = 0;
  return linked_list;
}

void* getByIndexLinkedList(LinkedList* linked_list, int index) {
  if (index <= linked_list->size) {
    LinkedListNode* current = linked_list->chain->next;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  } else {
    return NULL;
  }
}

bool appendLinkedList(void* data, LinkedList* linked_list, int index) {
  if (index > linked_list->size) {
    return false;
  } else {
    LinkedListNode* current = linked_list->chain;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    LinkedListNode* node = newLinkedListNode(data);
    node->next = current->next;
    current->next = node;
  }
  linked_list->size++;
  return true;
}

bool removeLinkedList(LinkedList* linked_list, int index) {
  if (index >= linked_list->size) {
    return false;
  } else {
    LinkedListNode* current = linked_list->chain;
    for (int i = 0; i <= index; ++i) {
      current = current->next;
    }
    current->data = current->next->data;
    current->next = current->next->next;
  }
  linked_list->size--;
  return true;
}

void printLinkedList(LinkedList* linked_list, char* (*handler)(void*)) {
  printf("[ ");
  LinkedListNode* current = linked_list->chain;
  for (int i = 0; i < linked_list->size; ++i) {
    current = current->next;
    char* t = (*handler)(current->data);
    printf("\'%s\', ", t);
  }
  printf("]\n");
}

char* toStringDefault(void* ptr) {
  static char buffer[10];
  sprintf(buffer, "%s", ptr);
  return buffer;
}

typedef struct Vertex {
  int label;
  LinkedList* successors;
  LinkedList* predecessors;
} Vertex;

typedef struct Edge {
  Vertex* from;
  Vertex* to;
  int weight;
} Edge;

Vertex* newVertex(int label) {
  Vertex *vertex = (Vertex*)malloc(sizeof(Vertex));
  vertex->label = label;
  vertex->successors = newLinkedList();
  vertex->predecessors = newLinkedList();
  return vertex;
}

Edge* newEdge(Vertex* from, Vertex* to, int weight) {
  Edge *edge = (Edge*)malloc(sizeof(Edge));
  edge->from = from;
  edge->to = to;
  edge->weight = weight;
  return edge;
}

void linkVertices(Vertex* rise, Vertex* fall, int weight) {
  Edge* arrow = newEdge(rise, fall, weight);
  appendLinkedList(arrow, rise->successors, 0);
  appendLinkedList(arrow, fall->predecessors, 0);
}

char* toStringEdge(void* ptr) {
  static char buffer[16];
  Edge* edge = (Edge*)ptr;
  sprintf(buffer, "<%d, %d, %d>", edge->from->label, edge->to->label, edge->weight);
  return buffer;
}

void printVertex(Vertex* vertex) {
  printf("vertex {\n");
  printf("  label: \"%d\",\n", vertex->label);
  printf("  pointer: %p,\n", vertex);
  printf("  successors: ");
  printLinkedList(vertex->successors, &toStringEdge);
  printf("  predecessors: ");
  printLinkedList(vertex->predecessors, &toStringEdge);
  printf("}\n");
}

int get_int() {
  char buffer[20];
  char *ptr;

  scanf("%s", buffer);
  return (int)strtol(buffer, &ptr, 10);
}

typedef struct Graph {
  Vertex** vertices;
} Graph;

Graph* newGraph(size_t vertices_count) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->vertices = malloc(vertices_count * sizeof(Vertex));
  for (int i = 0; i < vertices_count; ++i) {
    graph->vertices[i] = newVertex(i + 1);
  }
  return graph;
}

void linkGraph(Graph* graph, int vertex_index, int destination_index, int edge_weight) {
  linkVertices(
    graph->vertices[vertex_index],
    graph->vertices[destination_index],
    edge_weight
  );
}

LinkedList* get_predecessors(Graph* graph, int vertex_index) {
  return graph->vertices[vertex_index]->predecessors;
}

LinkedList* get_successors(Graph* graph, int vertex_index) {
  return graph->vertices[vertex_index]->successors;
}

void printArray(int* array, size_t size) {
  printf("[ ");
  for (int i = 0; i < size; ++i) {
    printf("%d ", array[i]);
  }
  printf("]\n");
}

int main() {
  printf("How many edges do you have? ");
  int edges_count = get_int();
  printf("How many vertices do you have? ");
  int vertices_count = get_int();
  Graph* network = newGraph(vertices_count);
  printf("The graph has been implemented; type graph-data in such format (from to weight):\n");
  for (int i = 0; i < edges_count; ++i) {
    int vertex_index = get_int() - 1;
    int destination_index = get_int() - 1;
    int edge_weight = get_int();
    linkGraph(
      network,
      vertex_index,
      destination_index,
      edge_weight
    );
  }

  for (int i = 0; i < vertices_count; ++i) {
      printVertex(network->vertices[i]);
  }

  // Critical Path
  // https://en.wikipedia.org/wiki/Program_evaluation_and_review_technique
  LinkedList* critical_path_left = newLinkedList();
  LinkedList* critical_path_right = newLinkedList();

  // Early Time (ES)
  // E(y) = max(E(x) + t(x, y))
  //       (x,y)
  int early_times[vertices_count];
  early_times[0] = 0;

  for (int vertex_index = 1; vertex_index < vertices_count; ++vertex_index) {
    int result = 0;
    Edge* critical_path_left_item = 0;
    LinkedList* predecessors = get_predecessors(network, vertex_index);
    for (int i = 0; i < predecessors->size; ++i) {
      Edge* predecessor = (Edge*)getByIndexLinkedList(predecessors, i);
      int predecessor_index = predecessor->from->label - 1;
      if (early_times[predecessor_index] + predecessor->weight > result) {
        result = early_times[predecessor_index] + predecessor->weight;
        critical_path_left_item = predecessor;
      }
    }
    appendLinkedList(critical_path_left_item, critical_path_left, critical_path_left->size);
    early_times[vertex_index] = result;
  }
  printf("E[%d] = %d\n", vertices_count, early_times[vertices_count - 1]);
  // Late Time
  // L(y) = min(L(y) - t(x, y))
  //       (x,y)
  int late_times[vertices_count];
  late_times[vertices_count - 1] = early_times[vertices_count - 1];

  for (int vertex_index = vertices_count - 2; vertex_index >= 0; --vertex_index) {
    int result = early_times[vertices_count - 1];
    Edge* critical_path_right_item = 0;
    LinkedList* successors = get_successors(network, vertex_index);
    for (int i = 0; i < successors->size; ++i) {
      Edge* successor = (Edge*)getByIndexLinkedList(successors, i);
      int successor_index = successor->to->label - 1;
      if (late_times[successor_index] - successor->weight < result) {
        result = late_times[successor_index] - successor->weight;
        critical_path_right_item = successor;
      }
    }
    appendLinkedList(critical_path_right_item, critical_path_right, critical_path_right->size);
    late_times[vertex_index] = result;
  }

  printf("L[%d] = %d\n", 0, late_times[0]);
  printf("Possible Critical Path:\n");

  // Finding critical paths
  LinkedList* critical_path = newLinkedList();
  Edge* current_edge = (Edge*)getByIndexLinkedList(critical_path_left, critical_path_left->size - 1);
  do {
    appendLinkedList(current_edge, critical_path, 0);
    for (int i = 0; i < critical_path_left->size; ++i) {
      Edge* temp_edge = (Edge*)getByIndexLinkedList(critical_path_left, i);
      if (temp_edge->to == current_edge->from) {
          current_edge = temp_edge;
          break;
      }
    }
  } while (current_edge->from->label != 1);

  appendLinkedList(current_edge, critical_path, 0);
  printLinkedList(critical_path, &toStringEdge);
  return 0;
}