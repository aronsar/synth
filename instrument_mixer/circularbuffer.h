#ifndef CIRCULAR_BUFFER_HPP_
#define CIRCULAR_BUFFER_HPP_

#include <memory>
#include <mutex>


template<class T> class CircularBuffer
{
public:
    explicit CircularBuffer(size_t size);

    void put(T item);
    T get();
    void copy_to(T *dest_buffer, int dest_buffer_size);
    void reset();
    bool empty() const;
    bool full() const;
    size_t capacity() const;
    size_t size() const;

private:
    std::mutex mutex_;
    std::unique_ptr<T[]> buf_;
    size_t head_ = 0;
    size_t tail_ = 0;
    const size_t max_size_;
    bool full_ = 0;
};

template<class T> CircularBuffer<T>::CircularBuffer(size_t size) :
    buf_(std::unique_ptr<T[]>(new T[size])),
    max_size_(size)
{
}

template<class T> void CircularBuffer<T>::put(T item)
{
    std::lock_guard<std::mutex> lock(mutex_);
    buf_[head_] = item;

    if(full_)
        tail_ = (tail_ + 1) % max_size_;

    head_ = (head_ + 1) % max_size_;
    full_ = head_ == tail_;
}

template<class T> T CircularBuffer<T>::get()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if(empty())
        return T();

    //Read data and advance the tail (we now have a free space)
    T val = buf_[tail_];
    full_ = false;
    tail_ = (tail_ + 1) % max_size_;

    return val;
}

template<class T> void CircularBuffer<T>::copy_to(T *dest_buffer, int dest_buffer_size)
{
    std::lock_guard<std::mutex> lock(mutex_);

    for (int i = 0; i < dest_buffer_size; i++)
        dest_buffer[i] = buf_[(i+tail_) % max_size_];
}

template<class T> void CircularBuffer<T>::reset()
{
    std::lock_guard<std::mutex> lock(mutex_);
    head_ = tail_;
    full_ = false;
}

template<class T> bool CircularBuffer<T>::empty() const
{
    //if head and tail are equal, we are empty
    return (!full_ && (head_ == tail_));
}

template<class T> bool CircularBuffer<T>::full() const
{
    //If tail is ahead the head by 1, we are full
    return full_;
}

template<class T> size_t CircularBuffer<T>::capacity() const
{
    return max_size_;
}

template<class T> size_t CircularBuffer<T>::size() const
{
    size_t size = max_size_;
    if(!full_)
    {
        if(head_ >= tail_)
            size = head_ - tail_;

        else
            size = max_size_ + head_ - tail_;
    }

    return size;
}

#endif
