#ifndef _MAMORY_LIST_H_
#define _MAMORY_LIST_H_

struct MemNode;
typedef MemNode mem_node_t;

class MemList{
public:
    MemList();

    ~MemList();
    
    bool push(void *ptr);

    bool erase(void *ptr);

    int find(void *ptr);

    unsigned int size();

    void clear();
    
#ifdef DEBUG
    void print();
#endif

private:
    MemList(const MemList &mem_list);

    MemList operator=(const MemList &mem_list);
    
private:
    mem_node_t *_head;

    mem_node_t *_tail;
    
    unsigned int _size;
    
};

#endif

