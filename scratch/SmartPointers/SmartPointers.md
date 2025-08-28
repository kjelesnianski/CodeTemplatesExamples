Prefer std::make_unique and std::make_shared:
These functions offer exception safety and can be more efficient than direct new calls.

Use unique_ptr for exclusive ownership:
If an object has a single clear owner, unique_ptr is the appropriate choice.

Use shared_ptr for shared ownership:
When multiple parts of your code need to share access to and ownership of an
object, shared_ptr is suitable.

Use weak_ptr to break circular dependencies:
Employ weak_ptr in situations where shared_ptr could create reference cycles,
preventing proper deallocation.

Avoid raw pointers for ownership:
Minimize the use of raw pointers for managing dynamically allocated memory; let
smart pointers handle deallocation.

Access raw pointer (if necessary):
Use the get() method of smart pointers to obtain a raw pointer to the managed
object, but treat this raw pointer as non-owning.

Smart pointers. The idea of them to control an ownership of pointer and
automatic memory deallocation.

Unique pointer is a kind of smart pointers that implements simple mechanism of
handling one raw pointer by one owner. The pointer inside cant be copied
accidentally to another one. After stack being deallocated the pointer inside
will be deleted also.

In C++ implementation of smart pointers they works absolutely the same way as
raw pointers

The ownership can be also taken using function release with the help of which
you can get the pointer and std::uniques_ptr will not hold it. However, I would
not suggest to use this function because it could be unsafe.
(Look at unique_ptr_unsafe.cpp)


==================================================================================
==================================================================================
## Shared Pointers

Spoiler: After deeper look you will understand that this type of pointer works
almost the same way as abstract garbage collector but allocated memory being
freed right after the moment it is not needed.

The idea of shared pointer is to make it possible for all the owners(more than
one) to point to the same data.

Important: the memory is deallocated only in case of last shared_ptr object
will be deleted so anyone wants this data to continue existing.


==================================================================================
==================================================================================
## Weak Pointers

std::weak_ptr is same as std::shared_ptr but it does not own memory so it can
be freed even if there is weak pointer that points to it.

So, weak pointer does not own memory and it can be safely freed

### Trap with Shared Pointers
Imagine you have two objects where each has shared pointer to another as a
field. We used them for some time and they are needed to be deallocated.
Object1 calls destructor and tries to deallocate first its field of shared
pointer of Object2, then destructor of Object2 is called and it deallocates
first its field of shared pointer of Object1. Oh no, that’s a trap!
(Look at weak_ptr_trap.cpp)



