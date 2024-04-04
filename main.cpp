#include "kNN.hpp"
#include <chrono>

void tc1(){
    auto start_time = std::chrono::high_resolution_clock::now();
    Dataset dataset;
    cout << dataset.loadFromCSV("C:\\Users\\My Laptop\\Documents\\init\\mnist.csv");
    int nRows, nCols;

    kNN knn(5);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    cout<<"y_pred"<<endl;
    y_pred.printTail(10,10);
    cout<<endl;
    cout<<"y test"<<endl;
    y_test.printTail(10,10);
    cout <<endl;
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    double duration_seconds = static_cast<double>(duration) / 1000000.0;
    std::cout << "Thoi gian chay: " << duration_seconds << " giay" << std::endl;
}
void tc1004()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->push_back(0);
    row->push_back(2);

    cout << row->length() << endl;
    row->print();
}
void tc1006()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int> *row = dataset.getData()->get(0);

    row->push_back(1);
    row->push_back(0);
    row->push_back(0);

    cout << row->length() << endl;
    row->print();
}
void tc_knn_p(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("C:\\Users\\My Laptop\\Documents\\init\\mnist.csv");
    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
}
void tc1144()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("C:\\Users\\My Laptop\\Documents\\init\\mnist.csv");
    dataset.getShape(nRows, nCols);
    bool result = dataset.drop(0, nRows);
    cout << "Drop(0, nRows) result: " << result << endl;
}
void tc_knn_score(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

//    dataset.columns();
//    cout <<endl;
    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
    cout << "Accuracy: " << accuracy << endl;

}
void tc1158()
{
    int nRows, nCols;
    Dataset dataset;

    dataset.loadFromCSV("mnist.csv");
    dataset.columns();
    Dataset dataset_extract = dataset.extract(0, -2, 0, -1);
    Dataset dataset_extract2 = Dataset(dataset_extract);
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}
void tc1187()
{
    tc_knn_score(10, -1);
}
void tc1205()
{
    int nRows, nCols;
    Dataset dataset;
    cout <<dataset.loadFromCSV("C:\\Users\\My Laptop\\Documents\\init\\mnist.csv");
    Dataset dataset_extract = dataset.extract(0, 10, 0, -1);
    Dataset dataset_extract2 = Dataset(dataset_extract);
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

int main() {
    tc1();

return 0;

}
