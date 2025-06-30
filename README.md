## CS 300 – Course-Sorting Project  
Reflection Journal

### 1. What problem was I solving?
I needed a simple command-line program that would read a bunch of course records from a file and then spit them back out in alphanumeric order. Basically, turn a jumbled course list into something you can actually scan without your eyes crossing.

### 2. How did I pick my solution?
I sketched three quick options:
1. **Brute-force bubble sort** (no, thank you).  
2. **Use the STL `sort()` with a custom comparator** (easy, almost too easy).  
3. **Write my own quicksort and selection-sort to compare speeds** (this felt like the real learning moment).

I went with option 3. I coded both algorithms, timed them on the same dataset, and kept quicksort as the default while leaving selection sort in there for reference. That way I proved I understood the trade-offs.

### 3. What did I learn?
* Reading from a CSV file is painless once you wrap it in a tiny helper function.  
* Edge cases matter: blank lines, weird characters, or duplicate course IDs will break everything if you don’t sanitize input.  
* Writing unit-style tests—even in C++—saved me from last-minute fire drills.

### 4. How did this expand my approach to software?
Until now I’d been guilty of “just make it work.” This project nudged me toward “make it work *and* prove it works.” Timing the two algorithms and logging the results showed me data-driven decisions beat gut guesses every time.

### 5. How has this evolved the way I write code?
I’m leaning into:
* **Modularity** – tiny functions that do one thing and do it well.  
* **Readability** – clear variable names over clever one-letter shortcuts.  
* **Adaptability** – if someone hands me a different file format tomorrow, I only touch the parser, not the whole program.

Overall, this little sorter reminded me why I like coding: you feed in chaos, tweak a few lines, and out comes order. Feels good every time.
