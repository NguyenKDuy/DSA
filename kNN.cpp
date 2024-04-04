#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

template<typename T>
DLL<T>::DLL() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}
template<typename T>
DLL<T>::~DLL() {
    clear ();
}
template<typename T>
Node <T> * DLL<T>::returnTail () {
    return this->tail;
}
template<typename T>
Node <T> * DLL<T>::returnHead () {
    return this->head;
}
template<typename T>
void DLL<T>::push_back(T value) {
    if (!this->head) {
        this->head = new Node<T> (value, nullptr, nullptr);
        this->tail = this->head;
    }
    else {
        auto * tmp = new Node <T> (value, this->tail, nullptr);
        this->tail->next = tmp;
        this->tail = tmp;
    }
    this->size++;
}
template<typename T>
void DLL<T>::push_front(T value) {
    if (!this->head) {
        this->head = new Node<T> (value, nullptr, nullptr);
        this->tail = this->head;
    }
    else {
        auto tmp = new Node <T> (value, nullptr, this->head);
        this->head->prev = tmp;
        this->head = tmp;
    }
    this->size++;
}
template<typename T>
void DLL<T>::setValue(int index, const T &value) {
    if (index <0 || index >= size) {
        throw std::out_of_range("get(): Out of range");
    }
    Node <T> *tmp1 = this->head;
    Node <T> * tmp2 = this->tail;
    int n = (this->size + 1)/2;
    if (index < n) { // Chay tu dau len+
        for (int i = 0; i < index; i ++) tmp1 = tmp1->next;
        tmp1->data = value;
    }
    else { // Chay tu sau len
        for (int i = this->size; i >index+1; i--) tmp2 = tmp2->prev;
        tmp2->data = value;
    }
}
template<typename T>
void DLL<T>::insert(int index, T value) {
    if (index < 0 || index > size) return;
    if (index == 0) {
        push_front(value);
    }
    else if (index == size) {
        push_back(value);
    }
    else {
        Node <T> *tmp1 = this->head;
        Node <T> * tmp2 = this->tail;
        int n = (this->size + 1)/2;
        if (index < n) { // Chay tu dau len
            for (int i = 0; i < index - 1; i ++) {
                tmp1 = tmp1->next;
            }
            Node<T> * newN = new Node<T> (value, tmp1, tmp1->next);
            tmp1->next = newN;
            newN->next->prev = newN;
        }
        else { // Chay tu sau len
            for (int i = this->size; i >index + 1; i--) {
                tmp2 = tmp2->prev;
            }
            Node<T> * newN = new Node<T> (value,tmp2->prev->prev, tmp2->prev);
            tmp2->prev->prev->next = newN;
            newN->next->prev = newN;
        }
        size++;
    }
}
template<typename T>
void DLL<T>::remove(int index) {
    if (index < 0 || index > size-1) return;
    Node<T> * del;
    if (index == 0) {
        del = this->head;
        this->head = head->next;
        if (!head) tail= head;
    }
    else if (index == this->size-1) {
        del = this->tail;
        this->tail = tail->prev;
        this->tail->next = nullptr;
    }
    else {
        int N2 = (this->size+1)/2;
        if (index < N2) {
            Node<T> * tmp = this->head;
            for (int i = 0; i < index -1; i++) {
                tmp = tmp->next;
            }
            del = tmp->next;
            tmp->next = del->next;
            del->next ->prev = tmp;
        }
        else {
            Node<T> * tmp = this->tail;
            for (int i = size - 1; i > index + 1; i--) {
                tmp = tmp->prev;
            }
            del = tmp->prev;
            tmp->prev = del->prev;
            del->prev->next = tmp;
        }
    }
    delete del;
    del = nullptr;
    this->size--;
    if (size == 0) {
        this->head = nullptr;
        this->tail = nullptr;
    }
}
template<typename T>
T& DLL<T>::get(int index) const {
    if (index <0 || index >= size) {
        throw std::out_of_range("get(): Out of range");
    }
    Node <T> *tmp1 = this->head;
    Node <T> * tmp2 = this->tail;
    int n = (this->size + 1)/2;
    if (index < n) { // Chay tu dau len+
        for (int i = 0; i < index; i ++) tmp1 = tmp1->next;
        return tmp1->data;
    }
    else { // Chay tu sau len
        for (int i = this->size; i >index+1; i--) tmp2 = tmp2->prev;
        return tmp2->data;
    }
}
template<typename T>
int DLL<T>::length() const {
    return this->size;
}
template<typename T>
void DLL<T>::clear() {
    Node <T> * tmp1 = this->head;
    Node <T> * tmp2 = this->tail;
    while (true) {
        if (tmp1 == tmp2) {
            if (!tmp1) return;
            delete tmp1;
            tmp1 = nullptr;
            tmp2 = nullptr;
            break;
        }
        if (tmp1->next == tmp2) {
            delete tmp1;
            delete tmp2;
            tmp1 = nullptr;
            tmp2 = nullptr;
            break;
        }
        Node <T> * del1 = tmp1;
        Node <T> * del2 = tmp2;
        tmp1 = tmp1->next;
        tmp2 = tmp2->prev;
        delete del1;
        delete del2;
        tmp1->prev = nullptr;
        tmp2->next = nullptr;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template<typename T>
void DLL<T>::reverse() {
    Node<T>* tmp = nullptr;
    Node<T>* curr = this->head;
    while (curr != nullptr) {
        tmp = curr->prev;
        curr->prev = curr->next;
        curr->next = tmp;
        curr = curr->prev;
    }
    if (tmp != nullptr)
        this->head = tmp->prev;
}
template<typename T>
void DLL<T>::print() const {
    Node<T> * tmp = head;
    for(int i = 0; i < size-1; i ++) {
        std::cout << tmp->data<<" ";
        tmp = tmp->next;
    }
    std::cout <<tmp->data;
}

template<typename T>
void DLL<T>::fprint (const char * s) {
    ofstream ofs (s);
    Node <T> * tmp = this->head;
    for(int i = 0; i < size; i ++) {
        if (i == size - 1) ofs <<tmp->data;
        else {
            ofs << tmp->data<<" ";
            tmp = tmp->next;
        }
    }
    ofs.close();
}

template<typename T>
void DLL<T>::swap (int sm_index, int gr_index) {
    T t_data;
    Node<T> * tmp = this->head;
    for (int i = 0; i < sm_index; i ++) {
        tmp = tmp->next;
    }
    Node <T> *swa = tmp;
    t_data = tmp->data;
    for (int i = 0; i < gr_index-sm_index; i ++) {
        tmp = tmp->next;
    }
    swa->data =tmp->data;
    tmp->data = t_data;
}
//-----------------------Iterator
template<typename T>
DLL<T>::Iterator::Iterator(DLL<T> * pList, bool begin) {
    this->pList = pList;
    if (begin) {
        if (this->pList != nullptr) {
            this->curr = this->pList->head;
            this->index = 0;
        }
        else {
            this->curr = nullptr;
            this->index = -1;
        }
    }
    else {
        if (this->pList) {
            this->index = this->pList->size;
        }
        else this->index = 0;
        this->curr = nullptr;
    }
}
template<class T>
typename DLL<T>::Iterator  & DLL<T>::Iterator:: operator = (const Iterator &iterator) {
    this->curr = iterator.curr;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this; // The pointer to the current object.
}
template<typename T>
void DLL<T>::Iterator::set (const T &e) {
    if (this->curr) {
        this->curr->data = e;
    }
    else throw std::out_of_range("Segmentation fault!");
}
template<typename T>
T& DLL<T>::Iterator:: operator*() {
    if (this->curr == nullptr)
        throw std::out_of_range("Segmentation fault!");
    return this->curr->data;
}
template<typename T>
bool DLL<T>::Iterator::operator != (const Iterator & iterator) {
    return !(this->curr == iterator.curr && this->index == iterator.index);
}
template<typename T>
void DLL<T>::Iterator::remove () {
    if (this->curr == nullptr) {
        throw std::out_of_range("Segmentation fault!");
        return;
    }
    if (this->index == 0) {
        this->pList->remove(0);
        this->curr = nullptr;
        this->index = -1;
    }
    else {
        this->curr = curr->prev;
        this->pList->remove(index);
        this->index--;
    }
}            //Remove curr Node.
template<typename T>
typename DLL<T>::Iterator DLL<T>::Iterator::operator++ () {
    if ((this->curr == nullptr) && (this->index == 0 ||this->index == this->pList->size)) {
        throw std::out_of_range("Segmentation fault!");
    }
    else if (this->curr == nullptr && this->index == -1){
        this->curr = this->pList->head;
        this->index = 0;
    }
    else {
        this->curr = this->curr->next;
        this->index++;
    }
    return *this;
}
template<typename T>
const typename DLL<T>::Iterator DLL<T>::Iterator:: operator++ (int) {
    Iterator res = *this;
    if ((this->curr == nullptr) && (this->index == 0 ||this->index == this->pList->size)) {
        throw std::out_of_range("Segmentation fault!");
    }
    else if (this->curr == nullptr && this->index == -1) {
        this->curr = this->pList->head;
        this->index = 0;
    }
    else {
        this->curr = this->curr->next;
        this->index++;
    }
    return res;
}
template<typename T>
int DLL<T>::Iterator::getIndex () const{
    return this->index;
}


//----------------------------------------DATASET----------------------------------------
Dataset::Dataset() {
    this->data = new DLL<DLL<int>*>;
    this->title = new DLL<string>;
    this->row = 0;
    this->col = 0;
}
Dataset::Dataset(DLL<DLL<int>*>* a, DLL<string>* b, int row, int col) {
    this->data = a;
    this->title = b;
    this->row = row;
    this->col = col;
}
Dataset::~Dataset() {
    clear();
}
void Dataset::clear() {
    delete this->title; //1
    DLL<DLL<int>*>::Iterator it = data->begin();
    DLL<DLL<int>*>::Iterator ed = data->end();
    for (; it != ed; it ++) {
        if (*it) delete *(it); //199
    }
    if (data) delete data;
    this->title = nullptr;
    this->data = nullptr;
    this->row = 0;
    this->col = 0;
}
void Dataset::set (const Dataset& other) {
    this->row = other.row;
    this->col = other.col;
    this->title = new DLL<string>;
    this->data = new DLL<DLL<int>*>;
    DLL<string>::Iterator strb = other.title->begin();
    DLL<string>::Iterator stre = other.title->end();
    for (; strb != stre; strb++) {
        this->title->push_back(*strb);
    }
    DLL<DLL<int>*>::Iterator listb = other.data->begin();
    DLL<DLL<int>*>::Iterator liste = other.data->end();
    for (; listb != liste; listb ++) {
        DLL<int>::Iterator tmp = (*listb)->begin();
        DLL<int>::Iterator tmpe = (*listb)->end();
        auto *sto = new DLL<int>;
        for (;tmp != tmpe; tmp++) {
            sto->push_back(*tmp);
        }
        this->data->push_back(sto);
    }
}
//Deep copy
Dataset::Dataset (const Dataset& other) {
    set(other);
}
//Shallow copy
Dataset& Dataset::operator=(const Dataset& other) {
    clear();
    set(other);
    return *this;
}
bool Dataset::loadFromCSV(const char* fileName) {
    ifstream ifs (fileName);
    if (!ifs.is_open()) return false;
    string tmp;
    string lt;
    while (getline(ifs, tmp)) {
        stringstream line (tmp);
        auto *sto = new DLL<int>;
        while (getline (line,lt,',')) {
            if (row == 0) {
                title->push_back(lt); //work
                col++;
            }
            else {
                sto->push_back(stoi(lt));
            }
        }
        if (row != 0)
            data->push_back(sto);
        row++;
    }
    row--;
    ifs.close();
    return true;
}
void Dataset::printHead(int nRows, int nCols) const {
    if (nRows < 0 || nCols < 0) return;
    if (this->row < nRows) nRows = this->row;
    if (this->col< nCols) nCols = this->col;
    DLL<string>::Iterator strb = this->title->begin();
    for (int i = 0; i < nCols; i++) {
        if (i == nCols-1) cout <<*strb <<endl;
        else {
            cout <<*strb<<" ";
            strb++;}
    }
    DLL<DLL<int>*>::Iterator listb = this->data->begin();
    for (int i = 0; i < nRows; i++) {
        DLL<int>::Iterator tmp = (*listb)->begin();
        for (int j = 0; j < nCols; j ++) {
            if (j == nCols-1 && i == nRows-1 ) cout << *tmp;
            else if (j == nCols-1) cout << *tmp <<endl;
            else {
                cout << *tmp<<" ";
                tmp++;}
        }
        if (i != nRows-1) listb++;
    }
}
void Dataset::printTail(int nRows, int nCols) const {
    if (nRows < 0 || nCols < 0) return;
    if (this->row < nRows) nRows = this->row ;
    if (this->col< nCols) nCols = this->col;
    DLL<string>::Iterator strb = this->title->begin();
    for (int i = this->col - nCols; i >0; i--) {
        strb++;
    }
    for (int i = 0; i < nCols; i++) {
        if (i == nCols-1) cout <<*strb <<endl;
        else {
            cout <<*strb<<" ";
            strb++;}
    }
    DLL<DLL<int>*>::Iterator listb = this->data->begin();
    for (int i = this->row - nRows; i >0; i --) {
        listb++;
    }
    for (int i = 0; i < nRows; i++) {
        DLL<int>::Iterator tmp = (*listb)->begin();
        for (int k = this->col - nCols; k >0; k--) {
            tmp++;
        }
        for (int j = 0; j < nCols; j ++) {
            if (j == nCols-1 && i== nRows-1 ) cout << *tmp;
            else if (j == nCols-1) cout << *tmp <<endl;
            else {
                cout << *tmp<<" ";
                tmp++;}
        }
        if (i != nRows-1) listb++;
    }
}
void Dataset::getShape(int& nRows, int& nCols) const {
    nRows = data->length();
    if (data->length() != 0) {
        nCols = data->get(0)->length();
    }
    else throw std::out_of_range("get(): Out of range");
}
void Dataset::columns() const {
    DLL<string>::Iterator strb = this->title->begin();
    for (int i = 0; i < this->col-1; i++) {
        cout <<*strb<<" ";
        strb++;
    }
    cout <<*strb;
}
bool Dataset::drop(int axis, int index, std::string columns) {
    if (axis < 0 || axis > 1) {
        return false;
    }
    if (axis == 0) {
        if (index >= this->data->length() || index < 0 )// not yet
            return false;
        this->data->get(index)->clear(); // just fix
        this->data->remove(index);
        this->row = data->length();
        return true;
    }
    else {
        int ind =0;
        bool find = false;
        DLL<string>::Iterator strb = this->title->begin();
        for (;ind < this->col; ind++) {
            if ((*strb) == columns) {
                find = true;
                break;
            }
            if (ind != this->col - 1) strb++;
        }
        if (!find) return false;
        else {
            this->title->remove(ind);
            this->col = this->title->length();
            DLL<DLL<int>*>::Iterator listb = this->data->begin();
            DLL<DLL<int>*>::Iterator liste = this->data->end();
            for (; listb != liste; listb++) {
                (*listb)->remove(ind);
            }
            return true;
        }
    }
}
Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    Dataset res;
    if (endRow == -1) endRow = this->row-1; // Gia thuyet col tu (0->198), theo index;
    else endRow = min(endRow, this->row-1);
    if (endCol == -1) endCol = this->col-1; // Gia thuyet col tu (0->784), theo index;
    else endCol = min(endCol, this->col-1);
    DLL<string>::Iterator strb = this->title->begin();
    for (int i = startCol; i > 0; i--) {
        strb++;
    }
    for (int i = startCol; i <= endCol; i++) {
        res.title->push_back(*strb);
        if (i != endCol) strb++;
    }
    DLL<DLL<int>*>::Iterator listb = this->data->begin();
    for (int i = startRow; i > 0; i --) {
        listb++;
    }
    for (int i = startRow; i <= endRow; i++) {
        DLL<int>::Iterator tmp = (*listb)->begin();
        for (int j = startCol; j > 0; j--) {
            tmp++;
        }
        DLL<int> *aut = new DLL<int>;
        for (int j = startCol; j <= endCol; j++) {
            aut->push_back(*tmp);
            if (i != endCol) tmp++;
        }
        res.data->push_back(aut);
        if (i != endRow) listb++;
    }
    res.row = endRow - startRow +1;
    res.col = endCol - startCol +1;
    return res;
}
DLL<DLL<int>*> * Dataset::getData() const {
    return this->data;
}
void Dataset::fprint (int index, const char * s) {
    data->get(index)->fprint(s);
}
//------------------------------------------BEGIN: CLASS KNN-------------------------------
kNN::kNN(int k) {this->k = k;}
void kNN::fit(const Dataset& X_train, const Dataset& y_train) {
    this->X_train = X_train;
    this->y_train = y_train;
}
void merge(double arr[], int idx [],int start, int middle, int end) {
    int n1 = middle - start + 1; // Size of sub-array 1
    int n2 = end - middle;      // Size of sub-array 2
    auto* leftArr = new double[n1];
    auto* rightArr = new double[n2];
    int* leftArr1 = new int[n1];
    int* rightArr1 = new int[n2];
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[start + i];
        leftArr1[i] = idx[start + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[middle + 1 + j];
        rightArr1[j] = idx[middle + 1 + j];
    }
    int i = 0, j = 0, mergedIndex = start;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[mergedIndex] = leftArr[i];
            idx[mergedIndex] = leftArr1[i];
            i++;
        } else {
            arr[mergedIndex] = rightArr[j];
            idx[mergedIndex] = rightArr1[j];
            j++;
        }
        mergedIndex++;
    }
    while (i < n1) {
        arr[mergedIndex] = leftArr[i];
        idx[mergedIndex] = leftArr1[i];
        i++;
        mergedIndex++;
    }
    while (j < n2) {
        arr[mergedIndex] = rightArr[j];
        idx[mergedIndex] = rightArr1[j];
        j++;
        mergedIndex++;
    }
    delete[] leftArr;
    delete[] rightArr;
    delete[] leftArr1;
    delete[] rightArr1;
}
void mergeSort(double array[], int idx [],int const begin, int const end)
{
    if (begin >= end)
        return;
    int mid = begin + (end - begin) / 2;
    mergeSort(array, idx ,begin, mid);
    mergeSort(array, idx ,mid + 1, end);
    merge(array, idx,begin, mid, end);
}

Dataset kNN::predict(const Dataset& X_test) {
    int size = X_train.getData()->length();
//    if (k > size) throw std::out_of_range("get(): Out of range");
    auto *cmp = new double [size];
    int * Ind = new int [size];
    auto t_data = new DLL<DLL<int>*>;
    DLL<DLL<int>*>::Iterator t_beg = X_test.getData()->begin();
    DLL<DLL<int>*>::Iterator t_end = X_test.getData()->end();
    for (; t_beg!=t_end; t_beg++) {
        DLL<DLL<int>*>::Iterator beg = X_train.getData()->begin();
        DLL<DLL<int>*>::Iterator end = X_train.getData()->end();// Tim label cho tung phan tu trong test
        int cnt = 0;
        for (; beg!=end; beg++, cnt++){                        //Chay tung hang, tinh khoang cach voi 1 phan tu cua test.
            //TUng cot cua 1 ptu trong test
            DLL<int>::Iterator t_bn = (*t_beg)->begin();
            DLL<int>::Iterator t_en = (*t_beg)->end();
            //Tung cot cua 1 ptu trong train
            DLL<int>::Iterator tr_bn = (*beg)->begin();
            DLL<int>::Iterator tr_en = (*beg)->end();
            double pred = 0;
            for (;tr_bn!=tr_en; tr_bn++,t_bn++) {
                pred += pow(((*tr_bn)-(*t_bn)),2);
            }
            pred = sqrt(pred);
            cmp[cnt] = pred;
            Ind[cnt] = cnt;
        }
        mergeSort(cmp, Ind, 0,size-1);
        int arr[10]{0};
        for (int i = 0; i < k; i ++) {
            int label = y_train.getData()->get(Ind[i])->get(0);
            ++arr[label];
        }
        double max = 0;
        int ind_r = 0;
        for (int j = 0; j < 10;j ++) {
            if (arr[j]> max)
            {
                max= arr[j];
                ind_r = j;
            }
        }
        auto * t_label = new DLL<int>;
        t_label->push_back(ind_r);
        t_data->push_back(t_label);
    }
    auto * tmp = new DLL<string>;
    tmp->push_back("label");
    Dataset y_pred (t_data,tmp,t_data->length(),1);
    delete[] cmp;
    delete[] Ind;
    return y_pred;
}

double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
    DLL<DLL<int>*>::Iterator it1 = y_pred.getData()->begin();
    DLL<DLL<int>*>::Iterator it2 = y_test.getData()->begin();
    DLL<DLL<int>*>::Iterator it1_e = y_pred.getData()->end();
    int row, col;
    y_test.getShape(row,col);
    int count = 0;
    for (;it1!=it1_e; it1++,it2++) {
        if ((*it1)->get(0)  == (*it2)->get(0)) count++; // Neu y_ test hoac y_pred = 0 thi se throw
    }
    double a = static_cast<double>(count)/row;
    return a;
}
//------------------------------------------END: CLASS KNN------------------------------------
void train_test_split(Dataset& X, Dataset& y, double test_size,
                      Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {
    int row, col;
    X.getShape(row, col);
    int testsize = (1-test_size)*row;
    if (testsize == 0) {
        X_test = (X.extract(testsize,-1,0,-1));
        y_test = y.extract(testsize,-1,0,-1);
    }
    else if (testsize == row-1) {
        X_train = X.extract(0,-1,0,-1);
        y_train = y.extract(0,-1,0,-1);
    }
    else {
        X_train = X.extract(0, testsize - 1, 0, -1);
        X_test = (X.extract(testsize, -1, 0, -1));
        y_train = y.extract(0, testsize - 1, 0, -1);
        y_test = y.extract(testsize, -1, 0, -1);
    }
}