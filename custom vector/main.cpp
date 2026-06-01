#include <iostream>

class intvec{
    private:
        int* data_ = nullptr;
        size_t size_ = 0;
        size_t capacity_ = 0;

    public:
        intvec(size_t capacity = 10){
            capacity_ = capacity;
            data_ = new int[capacity];
        }

        size_t size() const {
            return size_;
        }

        size_t capacity() const {
            return capacity_;
        }

        int& operator[](std::size_t index){
            return data_[index];
        }

        void push_back(int i){
            if(size_ < capacity_){
                data_[size_] = i;
                size_++;
            }
            else{
                int* newdata_ = new int[capacity_ * 2];
                for(size_t i = 0; i < size_; i++){
                    newdata_[i] = data_[i];
                }
                delete[] data_;
                data_ = newdata_;
                capacity_ *= 2;

                data_[size_] = i;
                size_++;
            }
        }
};

int main(){
    intvec v{5};
    for(int i = 0; i < 10; i++){
        v.push_back(i);
        std::cout <<  "v[i]: " << v[i] << " size: " << v.size() << " capacity: " << v.capacity() << std::endl;
    }

    intvec v2 = v;
    v[5] = 420;
    for(std::size_t i = 0; i < 10; i++){
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

    for(std::size_t i = 0; i < 10; i++){
        std::cout << v2[i] << " ";
    }
    std::cout << "\n";
}
