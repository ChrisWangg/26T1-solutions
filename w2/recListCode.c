#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// ANSI colour codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

// -----------------------------------------------------------------------------
// Data Types
// -----------------------------------------------------------------------------
struct node {
    int value;
    struct node *next;
};

struct list {
    struct node *head;
};

// -----------------------------------------------------------------------------
// Recursive Function Declarations (node pointer interface)
// -----------------------------------------------------------------------------
int listLength(struct node *l);
int listCountOdds(struct node *l);
bool listIsSorted(struct node *l);
struct node *listDelete(struct node *l, int value);

// -----------------------------------------------------------------------------
// Wrapper Function Declarations (struct list pointer interface)
// -----------------------------------------------------------------------------
int listLengthWrapper(struct list *l);
int listCountOddsWrapper(struct list *l);
bool listIsSortedWrapper(struct list *l);
void listDeleteWrapper(struct list *l, int value);

// -----------------------------------------------------------------------------
// Helper Function Declarations
// -----------------------------------------------------------------------------
struct node *createNode(int value);
struct node *prependNode(int value, struct node *list);
void freeList(struct node *list);
void printList(struct node *list);
static bool checkListStructure(struct node *list, int expected[], int size);

// -----------------------------------------------------------------------------
// Test Suite Function Declarations
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool condition);
static void print_test_suite_header(const char *suite_name);

// --- Test Cases for listLength ---
static void test_listLength_empty(void);
static void test_listLength_single(void);
static void test_listLength_multiple(void);

// --- Test Cases for listCountOdds ---
static void test_listCountOdds_empty(void);
static void test_listCountOdds_allEven(void);
static void test_listCountOdds_allOdd(void);
static void test_listCountOdds_mixed(void);

// --- Test Cases for listIsSorted ---
static void test_listIsSorted_empty(void);
static void test_listIsSorted_single(void);
static void test_listIsSorted_sorted(void);
static void test_listIsSorted_unsorted(void);
static void test_listIsSorted_duplicates(void);

// --- Test Cases for listDelete ---
static void test_listDelete_empty(void);
static void test_listDelete_deleteHead(void);
static void test_listDelete_deleteMiddle(void);
static void test_listDelete_deleteLast(void);
static void test_listDelete_nonexistent(void);
static void test_listDelete_duplicate(void);
static void test_listDelete_single(void);

// --- Test Cases for Wrapper Functions ---
static void test_wrapper_listLength(void);
static void test_wrapper_listCountOdds(void);
static void test_wrapper_listIsSorted(void);
static void test_wrapper_listDelete(void);

// --- Helper to Run All Tests ---
static void run_tests(void);

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main(void) {
    run_tests();
    return 0;
}

// -----------------------------------------------------------------------------
// Test Helper Functions
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool condition) {
    if (condition) {
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    } else {
        printf("%sTest %s: FAILED%s\n", RED, test_name, RESET);
    }
}

static void print_test_suite_header(const char *suite_name) {
    printf("\nTest Suite: %s\n", suite_name);
    printf("-----------------------\n");
}

// Compares list structure to an expected array
static bool checkListStructure(struct node *list, int expected[], int size) {
    struct node *current = list;
    for (int i = 0; i < size; i++) {
        if (current == NULL || current->value != expected[i]) {
            return false;
        }
        current = current->next;
    }
    return current == NULL;
}

// -----------------------------------------------------------------------------
// Test Cases for listLength()
// -----------------------------------------------------------------------------
static void test_listLength_empty(void) {
    print_test_suite_header("listLength - Empty List");
    struct node *list = NULL;
    int len = listLength(list);
    run_test("Empty list length should be 0", len == 0);
}

static void test_listLength_single(void) {
    print_test_suite_header("listLength - Single Node");
    struct node *list = prependNode(10, NULL);
    int len = listLength(list);
    run_test("Single node list length should be 1", len == 1);
    freeList(list);
}

static void test_listLength_multiple(void) {
    print_test_suite_header("listLength - Multiple Nodes");
    struct node *list = NULL;
    list = prependNode(3, list);
    list = prependNode(2, list);
    list = prependNode(1, list); // List: 1 -> 2 -> 3
    int len = listLength(list);
    run_test("Multiple nodes list length should be 3", len == 3);
    freeList(list);
}

// -----------------------------------------------------------------------------
// Test Cases for listCountOdds()
// -----------------------------------------------------------------------------
static void test_listCountOdds_empty(void) {
    print_test_suite_header("listCountOdds - Empty List");
    struct node *list = NULL;
    int count = listCountOdds(list);
    run_test("Empty list odd count should be 0", count == 0);
}

static void test_listCountOdds_allEven(void) {
    print_test_suite_header("listCountOdds - All Even Numbers");
    struct node *list = NULL;
    list = prependNode(4, list);
    list = prependNode(2, list);
    list = prependNode(6, list);
    int count = listCountOdds(list);
    run_test("All even list odd count should be 0", count == 0);
    freeList(list);
}

static void test_listCountOdds_allOdd(void) {
    print_test_suite_header("listCountOdds - All Odd Numbers");
    struct node *list = NULL;
    list = prependNode(5, list);
    list = prependNode(3, list);
    list = prependNode(1, list);
    int count = listCountOdds(list);
    run_test("All odd list odd count should be 3", count == 3);
    freeList(list);
}

static void test_listCountOdds_mixed(void) {
    print_test_suite_header("listCountOdds - Mixed Numbers");
    struct node *list = NULL;
    list = prependNode(4, list); // even
    list = prependNode(3, list); // odd
    list = prependNode(2, list); // even
    list = prependNode(1, list); // odd, List: 1 -> 2 -> 3 -> 4
    int count = listCountOdds(list);
    run_test("Mixed list odd count should be 2", count == 2);
    freeList(list);
}

// -----------------------------------------------------------------------------
// Test Cases for listIsSorted()
// -----------------------------------------------------------------------------
static void test_listIsSorted_empty(void) {
    print_test_suite_header("listIsSorted - Empty List");
    struct node *list = NULL;
    bool sorted = listIsSorted(list);
    run_test("Empty list should be sorted", sorted == true);
}

static void test_listIsSorted_single(void) {
    print_test_suite_header("listIsSorted - Single Node");
    struct node *list = prependNode(10, NULL);
    bool sorted = listIsSorted(list);
    run_test("Single node list should be sorted", sorted == true);
    freeList(list);
}

static void test_listIsSorted_sorted(void) {
    print_test_suite_header("listIsSorted - Sorted List");
    struct node *list = NULL;
    list = prependNode(3, list);
    list = prependNode(2, list);
    list = prependNode(1, list); // List: 1 -> 2 -> 3
    bool sorted = listIsSorted(list);
    run_test("List 1->2->3 should be sorted", sorted == true);
    freeList(list);
}

static void test_listIsSorted_unsorted(void) {
    print_test_suite_header("listIsSorted - Unsorted List");
    struct node *list = NULL;
    list = prependNode(2, list);
    list = prependNode(3, list);
    list = prependNode(1, list); // List: 1 -> 3 -> 2
    bool sorted = listIsSorted(list);
    run_test("List 1->3->2 should not be sorted", sorted == false);
    freeList(list);
}

static void test_listIsSorted_duplicates(void) {
    print_test_suite_header("listIsSorted - Duplicates in Sorted Order");
    struct node *list = NULL;
    list = prependNode(2, list);
    list = prependNode(1, list);
    list = prependNode(1, list); // List: 1 -> 1 -> 2 (non-decreasing order)
    bool sorted = listIsSorted(list);
    run_test("List 1->1->2 should be sorted", sorted == true);
    freeList(list);
}

// -----------------------------------------------------------------------------
// Test Cases for listDelete()
// -----------------------------------------------------------------------------
static void test_listDelete_empty(void) {
    print_test_suite_header("listDelete - Empty List");
    struct node *list = NULL;
    list = listDelete(list, 5);
    run_test("Deleting from empty list should yield empty list", list == NULL);
}

static void test_listDelete_deleteHead(void) {
    print_test_suite_header("listDelete - Delete Head Node");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // List: 3 -> 2 -> 1
    list = listDelete(list, 3);  // Delete head (value 3)
    int expected[] = {2, 1};
    bool structureOk = checkListStructure(list, expected, 2);
    run_test("Deleting head should update list structure", structureOk);
    freeList(list);
}

static void test_listDelete_deleteMiddle(void) {
    print_test_suite_header("listDelete - Delete Middle Node");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // List: 3 -> 2 -> 1
    list = listDelete(list, 2);  // Delete middle node (value 2)
    int expected[] = {3, 1};
    bool structureOk = checkListStructure(list, expected, 2);
    run_test("Deleting middle node should update list structure", structureOk);
    freeList(list);
}

static void test_listDelete_deleteLast(void) {
    print_test_suite_header("listDelete - Delete Last Node");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // List: 3 -> 2 -> 1
    list = listDelete(list, 1);  // Delete last node (value 1)
    int expected[] = {3, 2};
    bool structureOk = checkListStructure(list, expected, 2);
    run_test("Deleting last node should update list structure", structureOk);
    freeList(list);
}

static void test_listDelete_nonexistent(void) {
    print_test_suite_header("listDelete - Non-existent Value");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // List: 3 -> 2 -> 1
    struct node *original = list;
    list = listDelete(list, 4);  // Value 4 does not exist
    int expected[] = {3, 2, 1};
    bool structureOk = checkListStructure(list, expected, 3);
    bool sameAddress = (list == original);
    run_test("Deleting non-existent value should not change structure", structureOk);
    run_test("List pointer should remain unchanged", sameAddress);
    freeList(list);
}

static void test_listDelete_duplicate(void) {
    print_test_suite_header("listDelete - Delete First Occurrence in Duplicates");
    struct node *list = NULL;
    list = prependNode(2, list);
    list = prependNode(3, list);
    list = prependNode(3, list); // List: 3 -> 3 -> 2
    list = listDelete(list, 3);  // Should delete first occurrence (the head)
    int expected[] = {3, 2};
    bool structureOk = checkListStructure(list, expected, 2);
    run_test("Deleting first occurrence from duplicates", structureOk);
    freeList(list);
}

static void test_listDelete_single(void) {
    print_test_suite_header("listDelete - Delete Single Node");
    struct node *list = prependNode(5, NULL);
    list = listDelete(list, 5);
    run_test("Deleting the only node should yield empty list", list == NULL);
    freeList(list);
}

// -----------------------------------------------------------------------------
// Test Cases for Wrapper Functions (struct list pointer)
// -----------------------------------------------------------------------------
static void test_wrapper_listLength(void) {
    print_test_suite_header("Wrapper listLength");
    struct list l;
    l.head = NULL;
    // Build list: 1 -> 2 -> 3
    l.head = prependNode(3, l.head);
    l.head = prependNode(2, l.head);
    l.head = prependNode(1, l.head);
    int len = listLengthWrapper(&l);
    run_test("Wrapper listLength should return 3", len == 3);
    freeList(l.head);
}

static void test_wrapper_listCountOdds(void) {
    print_test_suite_header("Wrapper listCountOdds");
    struct list l;
    l.head = NULL;
    // Build list: 5 -> 4 -> 3 -> 2 (i.e. list: 5,4,3,2)
    l.head = prependNode(2, l.head);
    l.head = prependNode(3, l.head);
    l.head = prependNode(4, l.head);
    l.head = prependNode(5, l.head);
    int count = listCountOddsWrapper(&l);
    // In list 5,4,3,2, odd numbers are 5 and 3 → count = 2
    run_test("Wrapper listCountOdds should return 2", count == 2);
    freeList(l.head);
}

static void test_wrapper_listIsSorted(void) {
    print_test_suite_header("Wrapper listIsSorted");
    struct list l;
    l.head = NULL;
    // Build sorted list: 1 -> 2 -> 3
    l.head = prependNode(3, l.head);
    l.head = prependNode(2, l.head);
    l.head = prependNode(1, l.head);
    bool sorted = listIsSortedWrapper(&l);
    run_test("Wrapper listIsSorted should return true for sorted list", sorted == true);
    freeList(l.head);
}

static void test_wrapper_listDelete(void) {
    print_test_suite_header("Wrapper listDelete");
    struct list l;
    l.head = NULL;
    // Build list: 3 -> 2 -> 1
    l.head = prependNode(1, l.head);
    l.head = prependNode(2, l.head);
    l.head = prependNode(3, l.head);
    listDeleteWrapper(&l, 2);
    int expected[] = {3, 1};
    bool structureOk = checkListStructure(l.head, expected, 2);
    run_test("Wrapper listDelete should delete the value", structureOk);
    freeList(l.head);
}

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void) {
    // listLength tests
    test_listLength_empty();
    test_listLength_single();
    test_listLength_multiple();

    // listCountOdds tests
    test_listCountOdds_empty();
    test_listCountOdds_allEven();
    test_listCountOdds_allOdd();
    test_listCountOdds_mixed();

    // listIsSorted tests
    test_listIsSorted_empty();
    test_listIsSorted_single();
    test_listIsSorted_sorted();
    test_listIsSorted_unsorted();
    test_listIsSorted_duplicates();

    // listDelete tests
    test_listDelete_empty();
    test_listDelete_deleteHead();
    test_listDelete_deleteMiddle();
    test_listDelete_deleteLast();
    test_listDelete_nonexistent();
    test_listDelete_duplicate();
    test_listDelete_single();

    // Wrapper tests
    test_wrapper_listLength();
    test_wrapper_listCountOdds();
    test_wrapper_listIsSorted();
    test_wrapper_listDelete();
}

// -----------------------------------------------------------------------------
// Implementation of Recursive Functions
// -----------------------------------------------------------------------------

// Recursively compute the length of a linked list
int listLength(struct node *l) {
    if (l == NULL) return 0;
    return 1 + listLength(l->next);
}

// Recursively count the number of odd numbers in a linked list
int listCountOdds(struct node *l) {
    if (l == NULL) return 0;
    if (l->value % 2 == 1) return 1 + listCountOdds(l->next);
    return listCountOdds(l->next);
}

// Recursively check if a list is sorted in ascending order (1->1->2->X is fine)
bool listIsSorted(struct node *l) {
    if (l == NULL || l->next == NULL)
        return true;
    if (l->value > l->next->value) return false;
    return listIsSorted(l->next);
}

// Recursively delete the first instance of a value from the list
struct node *listDelete(struct node *l, int value) {
    if (l == NULL) return NULL;
    if (l->value == value) {
        struct node *nextNode = l->next;
        free(l);
        return nextNode;
    }
    l->next = listDelete(l->next, value);
    return l;
}

// -----------------------------------------------------------------------------
// Implementation of Wrapper Functions (using struct list pointer)
// -----------------------------------------------------------------------------
int listLengthWrapper(struct list *l) {
    return listLength(l->head);
}

int listCountOddsWrapper(struct list *l) {
    return listCountOdds(l->head);
}

bool listIsSortedWrapper(struct list *l) {
    return listIsSorted(l->head);
}

void listDeleteWrapper(struct list *l, int value) {
    l->head = listDelete(l->head, value);
}

// -----------------------------------------------------------------------------
// Helper Functions to Manage Linked Lists
// -----------------------------------------------------------------------------
struct node *createNode(int value) {
    struct node *newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

struct node *prependNode(int value, struct node *list) {
    struct node *newNode = createNode(value);
    newNode->next = list;
    return newNode;
}

void freeList(struct node *list) {
    while (list != NULL) {
        struct node *temp = list;
        list = list->next;
        free(temp);
    }
}

void printList(struct node *list) {
    while (list != NULL) {
        printf("%d -> ", list->value);
        list = list->next;
    }
    printf("NULL\n");
}
