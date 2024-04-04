#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
template<typename T>
class Node {
public:
    T data;
    Node * next;
    Node * prev;
    Node (T _data, Node* _prev , Node * _next) {
        this->data = _data;
        this->next = _next;
        this->prev = _prev;
    }
};
template<typename T>
class List {
public:
    class Iterator;
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual void fprint (const char * s) = 0; // be added
    virtual Node <T> * returnHead () = 0;
    virtual Node <T> * returnTail () = 0;
    virtual void setValue (int ind, const T& value) = 0;
    virtual bool empty () = 0;
};
template <typename T>
class DLL : public List<T> {

private:
    Node<T> *head;
    Node<T> *tail;
    int size;
public:
    class Iterator;
    DLL();
    ~DLL();
    void setValue (int ind, const T& value);
    bool empty () {
        if (this->head == nullptr) return true;
        return false;
    }
    void push_back(T value) ;
    void push_front(T value) ;
    void insert(int index, T value) ;
    void remove(int index) ;
    T& get(int index) const ;
    int length() const  ;
    void clear() ;
    void print() const;
    void reverse() ;
    void fprint (const char * s) ; // be added
    Node <T> * returnHead ();
    Node <T> * returnTail ();
    void swap (int sm_index, int gr_index);
    Iterator begin()
    {
        return Iterator (this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Iterator {
    private:
        DLL<T> * pList;
        Node<T> * curr;
        int index;
    public:
        Iterator ( DLL<T> * pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        int getIndex () const;
//        Iterator operator-- (int);
//        Iterator operator-- ();
        const Iterator operator++ (int);
        Iterator operator++ ();
        void remove ();
//        bool operator < (const Iterator & iterator);
        bool operator != (const Iterator & iterator);
        T &operator*();
        void set (const T &e);
    };

};
class Dataset {
private:
    DLL<DLL<int>*>* data;
    DLL<string> * title;
    int row;
    int col;
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset(DLL<DLL<int>*>* a, DLL<string>* b, int row, int col);
    void clear();
    void set (const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool    loadFromCSV(const char* fileName);
    void    printHead(int nRows = 5, int nCols = 5) const;
    void    printTail(int nRows = 5, int nCols = 5) const;
    void    getShape(int& nRows, int& nCols) const;
    void    columns() const;
    bool    drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    DLL<DLL<int>*>* getData() const;
    void fprint (int index, const char * s);
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset y_train;
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size,
                      Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

void merge(double arr[], int idx [],int start, int middle, int end);
void mergeSort(double array[], int idx [],int const begin, int const end);
// Please add more or modify as needed

