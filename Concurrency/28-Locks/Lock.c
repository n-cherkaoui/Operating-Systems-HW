int main(int argc, char *argv[])
{
}

// Fetches a value from memory and places it in a register
int loadLinked(int* address) {
    int reg = *address;
    return reg;
}

// Updates the value at the load-linked address if no intervening store to address has taken place
// On success, Returns 1 and updates the value at ptr to value
// On failure, ptr is not updated and 0 is returned
int storeConditional(int* address) {
    if (loadLinked(address) == 1) {
        return 0;
    }
    else {
        *address = 1;
        return 1;
    }
}

typedef struct __lock_t
{
    int flag;
} lock_t;

void init(lock_t *lock)
{
    // 0: lock is available, 1: lock is held
    lock->flag = 0;
}

void lock(lock_t *lock)
{
    while (storeConditional(&lock->flag) == 0)
        ; // spin-wait (do nothing)
}

void unlock(lock_t *lock)
{
    lock->flag = 0;
}