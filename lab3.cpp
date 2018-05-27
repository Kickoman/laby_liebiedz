#include <iostream> // cin, cout
#include <cstdlib> // srand
#include <ctime> // time

using namespace std;

/*
    in fact, the english equivalent for "очередь" is "queue",
    but since the methodical material doesn't contain this word,
    it became a kind of distinctive feature of my laboratory works.
    so I named your queue struct as "List", cuz it's literal translation
    of the russian word that is used in lectures.
*/
struct List
{
    int info; // the same thing's with the word "info"
              // I don't find it appropriate in this context
              // but the word "value" that's much more suitable
              // has also became a distinctive feature (DV) of my labs, i guess
    List *next = NULL, *prev = NULL;
}; // no global variables, dude! that's bad practice and also it'll help u at the exams

/*
    well, i wanna explain everything now.
    but i won't do it.
*/

void clearMemory(List **first, List **last)
{
    List *prev = *first, *cur = *first;
    while (cur) {
        cur = cur->next;
        delete prev;
        prev = cur;
    }
    *first = *last = NULL;
}

void addToBack(List** first, List **last, int value)
{
    List *temp = new List;
    temp->info = value;
    if (*first == NULL) {
        *first = *last = temp;
    }
    else {
        (*last)->next = temp;
        temp->prev = *last;
        *last = temp;
    }
}

void addToFront(List **first, List **last, int value)
{
    List *temp = new List;
    temp->info = value;
    if (*first == NULL) {
        *first = *last = temp;
    }
    else {
        (*first)->prev = temp;
        temp->next = *first;
        *first = temp;
    }
}

void print(List *startPoint, int dir = 0) // assuming 0 as direct printing and any other as reverse printing
{
    List *cur = startPoint;
    while (cur) {
        cout << cur->info << " ";
        cur = (dir ? cur->prev : cur->next); // ternary operator
    }                                        // works like (condition ? that'll be executed if the condition is true : otherwise)
    cout << "\n";
}

void delFromBack(List **first, List **last)
{
    if (*first == *last)
    {
        delete *first;
        *last = NULL;
        return;
    }

    List *tmp = (*last)->prev;
    delete *last;
    *last = tmp;
    (*last)->next = NULL;
}

void delFromFront(List **first, List **last)
{
    if (*first == *last)
    {
        delete *first;
        *last = NULL;
        return;
    }

    List *tmp = (*first)->next;
    delete *first;
    *first = tmp;
    (*first)->prev = NULL;
}

void sortValues(List *first, List *last, int dir = 0)
{
    List *edge = NULL, *cur;
    int tmp;
    do {
        for (cur = first; cur->next != edge; cur = cur->next)
            if ((cur->info > cur->next->info) == ! (bool) dir) {
                tmp = cur->info;
                cur->info = cur->next->info;
                cur->next->info = tmp;
            }
        edge = cur;
    } while (first->next != edge);
}

void sortPointers(List **first, List **last, int dir = 0)
{
    addToBack(&(*first), &(*last), 0); // Kastuś, ty daŭbajob, što za chujnia?
    addToFront(&(*first), &(*last), 0);

    List *edge = *last, *cur, *tmp;
    if ((*first)->next->next == *last) return;
    do {
        for (cur = *first; cur->next->next != edge; cur = cur->next)
            if ((cur->next->info > cur->next->next->info) == ! (bool) dir) {
                tmp = cur->next->next;
                cur->next->next = tmp->next;
                tmp->next->prev = cur->next;
                tmp->next = cur->next;
                cur->next->prev = tmp;
                tmp->prev = cur;
                cur->next = tmp;
            }
        edge = cur->next;
    } while ((*first)->next->next != edge);

    delFromBack(&(*first), &(*last));
    delFromFront(&(*first), &(*last));
}

void individual(List **first, List **last)
{
    // find max element and delete it
    List *maximum = *first;
    List *current = (*first)->next;
    while (current) {
        if (current->info > maximum->info)
            maximum = current;
        current = current->next;
    }

    if (maximum == *first)
    {
        delFromFront(first, last);
    } else if (maximum == *last) {
        delFromBack(first, last);
    } else {
        maximum->prev->next = maximum->next;
        maximum->next->prev = maximum->prev;
        delete maximum;
    }
}

int main()
{
    List *_begin = NULL, *_end = NULL;
    srand((unsigned int)time(NULL));

    bool ok = true;
    while (ok) {
        int cmd;
        cout << "\t1 - Add\n"
                "\t2 - Print\n"
                "\t3 - Sort\n"
                "\t4 - Clear Memory\n"
                "\t5 - Individual Task\n"
                "\t0 - Quit\n";
        cout << "\nYour decision: ";
        cin >> cmd;

        int value;
        switch (cmd) {
        case 1:
            cout << "\t\t1 - Add to Front\n"
                    "\t\t2 - Add to Back\n";
            cout << "Your decision: ";
            cin >> cmd;

            cout << "Value: ";
            cin >> value;
            if (cmd == 1) addToFront(&_begin, &_end, value);
            else          addToBack(&_begin, &_end, value);
            break;
        case 2:
            cout << "\t\t1 - Print from Front\n"
                    "\t\t2 - Print from Back\n";
            cout << "Your decision: ";
            cin >> cmd;
            if (cmd == 1) print(_begin);
            else          print(_end, 1);
            break;
        case 3:
            cout << "\t\t1 - Sort from beginning\n"
                    "\t\t2 - Sort from end\n";
            cout << "Your decision: ";
            cin >> cmd;
            if (cmd == 1) {
                cout << "\t\t\t1 - Sort values\n"
                        "\t\t\t2 - Sort pointers\n";
                cout << "Your decision: ";
                cin >> cmd;
                if (cmd == 1) sortValues(_begin, _end);
                else          sortPointers(&_begin, &_end);
            } else {
                cout << "\t\t\t1 - Sort values\n"
                        "\t\t\t2 - Sort pointers\n";
                cout << "Your decision: ";
                cin >> cmd;
                if (cmd == 1) sortValues(_begin, _end, 1);
                else          sortPointers(&_begin, &_end, 1);
            }
            break;
        case 5:
            individual(&_begin, &_end);
            print(_begin); // output the result
            break;
        case 0:
            ok = false;
            break;
        default:
            cout << "Unknown command\n\n";
        }
    }

    return 0;
}
