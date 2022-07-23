#ifndef QUEUE_H
#define QUEUE_H

using namespace std;

#define MAX 1000 

// TODO: Implement all methods
template <typename T>
class queue {

	T* data;
	int top;
	int capacity;

public:
	queue(int size = MAX){
        data = new T[size];
        capacity = size;
        top = - 1;
	};
	~queue(){
	    delete []data;
	    data = nullptr;
	};

	void push(T x){

        if(size()>=capacity) {

            ++capacity;

            T *temp = new T[capacity];

            for (int i = 0; i < capacity - 1; ++i){
                temp[i] = data[i];
            }

            delete[] data;

            data = temp;

            data[++top] = x;

            cout << x << " pushed" << endl;
        } else {

            T *temp = new T[top + 2];

            for (int i = 0; i < top + 1; ++i) {
                temp[i] = data[i];
            }

            delete[] data;

            data = temp;

            data[++top] = x;

            cout << x << " pushed" << endl;

        }
    };

	void pop(){
	    try{
	        if(!empty()){
                int x = data[0];
	            for(int i = 0; i < top + 1; ++i){
	                data[i]=data[i+1];
	            }
	            top--;
                cout << x << " removed, data[0]: " << front()<< endl;
	        }else {
	            throw logic_error("Stack Vacio");
	        }

	    }
	    catch(std::exception& e){
	        cout<<e.what()<<endl;
	    }

	};
	T front(){
        try {
            if(!empty()){
                return data[0];
            } else {
                throw logic_error("Stack Vacio");
            }
        }
        catch (std::exception& e){
            cout<<e.what()<<endl;
        }

	};
    T back(){
        try {
            if(!empty()){
                return data[top];
            } else {
                throw logic_error("Stack Vacio");
            }
        }
        catch (std::exception& e){
            cout<<e.what()<<endl;
        }
    };

	int size(){
        return top + 1;
	};
	bool empty(){
        if( top < 0 ){
            return true;
        }else return false;
	};
};

#endif