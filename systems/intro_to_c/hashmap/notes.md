Plan
[x] Choose Hash Function

[] Choose open addressing vs chaining
    [] Draw out a plan for each
    [] Linear probing

[] Implement
[] Stretch goals. Expansion. 


Going to choose the multiplication method for simplicity. But leaving a note here
for myself that the tabulation method looks interesting at the bottom of the article.
One experiment to do is to compare the speed of the 2 hash functions.

Linear probing
- I'll be choosing a linear probing method with a P(x) = 1x. I watched
this video https://www.youtube.com/watch?v=Ma9XOInZJWM and think this 
would be the most straight forward approach


Hash Function
https://sites.cs.queensu.ca/courses/cisc235/Record/20200312b%20-%20Choosing%20a%20Hashing%20Function.pdf

Mid square method - pg 7, satisfies the 4 properties pretty well. If size(key)
is small, then we'll encounter collisions because hashed output will result in 0

Multiplication Method - very popular

Collision

There are 2 main ideas
1. Chaining - at each location you have a chain or linked list
2. Open addressing - 10 minute. 1 haphazard - deletions. If you 
always place things at the next location, then you'll get more and more collisions


Stretch goals
- expand the underlying array if we start to get a lot of collisions
- support non-string keys
- try different hash functions
- switch from chaining to open addressing
- use a sophisticated rehashing scheme to avoid clustered collisions
- implement some features from Python dicts, such as reducing space use,
maintaing key ordering etc. see https://www.youtube.com/watch?v=npw4s1QTmPg
for ideas

