If you get stuck, you can:

- Watch or re-watch any related explainer videos
- Watch more of the solution, for instance the planning step
- Ask questions below or on Discord
- See how I implement the encoder, and implement the decoder yourself
- Watch the solution but implement it yourself from scratch tomorrow
- Translate my solution into another language

12/12/23
Little Endian vs Big Endian
- Big Endian is like reading from left to right where the higher order 
val is on the left. Used in network Protocols
- Little Endian has the low order value on the left. Intel uses Little Endian.
- When reading hexadecimal, you can use hexdump -C ./my_raw_bytes

1/22/23
**CPU microarchitecture and low‑level performance**
*Main takeaways*
- You can use wider registers in order to utilize the architecture of 
the microprocessor to parallelize operations if you are CPU bound. 
- Do more work in each operation doing pairwise additions. 
- This is a more in depth look inside the interface of a CPU and it's microarchitecture. 
The diagram is useful and can be applied to many concepts in computer science when 
it comes to parallelization and performance optimization
- Compilers are amazing and can do a good job of doing branch prediction. If else 
statements slow down a program because of branch prediction. Each mispredicted 
branch has to be flushed.

1/24 CPU Caches https://csprimer.com/watch/cpu-caches/
- When programming, be aware of CPU caches to improve program performance.
- Space is time. If you make something smaller, it fits into cache or storage
better and it will take less time to process, load, etc...
- Hertz = # times per second. Giga = billion. 4 Gigahertz == 4 billion times per second
- The size of numerical types do matter. If you smaller data types, the operations
on those values will be faster. If a cache line is 64 bytes, you can fit 16 4 byte
integers in the cache line. If you use 2 byte shorts, you can fit 32 of them 
inside the cache line.
- array of structs vs struct of arrays. If you load an array of structs
into memory i.e. Struct User{age, height, name} but only need their name, 
the cache line will be filled with properties that you don't really need. 
Can you organize the to have a usernames[], userheights[], userages[]? Think 
of aggregation or analytical procedures that you need to do. Columnmar 
databases are organized this way
- Pointer chasing. In a relational DB or ORM, you go from memory address 
to memory address, following pointers to find a value
- One of the reasons python, ruby and JS are slow is because the data 
structures that are used are heterogeneous and use pointers as the interface
to different types. So you get a pointer chasing effect which ignores the use
of cache utilization.
- Linked list is bascially pointer chasing. Every time you follow a new pointer, 
it is a cache miss to load that data and you don't utilize any caching.

1/25/24
- Performance Engineering guide https://en.algorithmica.org/hpc/cpu-cache/
- Casey Muratori's Performance Aware course looks like something to take 
after the CS Primer's OS course!
- Going to read CSAPP and and the perf guide on algorithmica.org before starting
the python module
- Try and get down to the data you need when passing between methods, loading
data from memory to use locality and have data be closer together.
- A main reason of why python is slow is due to pointer chasing. The data structures
like Classes and hash tables use pointers rather than a C array which you have 
to explicitly declare a type.
