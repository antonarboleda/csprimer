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

CPU Memory 
- Processors have multiple cores
- Each core can have multiple threads
- Question: What's the difference between a core and a CPU?
- Measure in cycles. 
- A memory access from the L1 cache is ~4 cycles and ~14 cycles for the ~L2 cache. 
Prefetching for the L2 cache might bring down the # of cycles from 14 to 9
- The performance of a memory system isn't characterized by a single number. Instead, it is a mountain of temporal and spatial locality whose elevations can vary over an order of magnitude. Spacial locality can affect the performance of the memory of a system because if items are spatially distanct from each other, it takes more time to process them. Temporal quality corresponds to the size of the data. Larger datasets take more time to process.

CPU Timing
- I used a multipass VM and worked in VIM to test and make changes
- Timing when running in user space and in system (kernel) space is measured
in clock ticks when using the `times()` syscall.
- When running a process on multiple CPU cores, if they run in parallel on separate CPUs, 
they should take the same time. If we run multiple processes on a single CPU, the 
OS will run the programs concurrently. This is one of the main takeaways
from this exercise. One of the core responsibilities of the OS is to switch 
between running processes in a way where they can share the underlying CPU
(across multiple cores if available) without having to explicitly cooperate.
In order to experiment with multiple cores I had to manually increase the 
number of cores on my multipass VM. 
- Learned how to read through through man pages more effectively and use VIM. 
This tutorial was pretty helpful https://www.youtube.com/watch?v=RzAkjX_9B7E
- At companies I've worked at, we've used virtual machines for development and 
this felt similar. A note for my future self - in order to work on this, I mounted
folders from my local FS onto a multipass shell. 
 

