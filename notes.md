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


