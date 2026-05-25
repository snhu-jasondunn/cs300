# CS-300 Data Structures and Algorithms Portfolio README

## Student Reflection

### What was the problem you were solving in the projects for this course?

The primary problem solved throughout this course was designing and implementing efficient data structures and algorithms to manage, organize, search, and display data. In the ABC University advising project, the goal was to create a program that could load course information from a CSV file, store the data in an appropriate data structure, and allow academic advisors to quickly retrieve and display course information and prerequisites. Additional projects focused on implementing linked lists, hash tables, and binary search trees to manage municipal auction bid data efficiently.

The projects emphasized choosing the correct data structure based on the operations required, such as searching, sorting, inserting, deleting, and traversing data. Efficiency and scalability were important because larger datasets required faster retrieval and organization methods.

---

### How did you approach the problem? Consider why data structures are important to understand.

I approached each problem by first analyzing the requirements of the application and determining which data structure would best support the needed operations. For example:

- **Vectors** were useful for simple sequential storage and iteration.
- **Linked Lists** provided flexibility for inserting and removing elements dynamically.
- **Hash Tables** allowed fast average-case searching and retrieval using keys.
- **Binary Search Trees** enabled ordered storage and efficient traversal for sorted output.

Understanding data structures is important because the performance of a program depends heavily on how data is organized and accessed. Choosing the wrong structure can make a program inefficient, especially as the amount of data grows. Throughout the course, I learned how algorithm complexity and runtime efficiency directly impact software performance and user experience.

For the final advising program, I selected a hash table implementation because it provided fast lookup times for searching courses by course number while still allowing the program to scale effectively with larger datasets.

---

### How did you overcome any roadblocks you encountered while going through the activities or project?

One of the main roadblocks I encountered was correctly parsing CSV data and handling edge cases such as missing prerequisites or improperly formatted lines. I overcame this by carefully validating the input data and adding checks before storing information in the data structures.

Another challenge involved implementing traversal and sorting functionality in the binary search tree. Understanding recursive logic and tree traversal algorithms required additional practice and debugging. I solved these issues by breaking the problem into smaller parts, testing functions individually, and comparing outputs against expected results.

Debugging memory management and pointer-related issues in linked lists and trees was also challenging. To overcome this, I spent time tracing program execution step-by-step and ensuring nodes were correctly created, linked, and deleted.

---

### How has your work on this project expanded your approach to designing software and developing programs?

This project expanded my understanding of how important planning and design are before writing code. I learned the value of creating pseudocode and evaluating multiple data structures before implementing a solution. Instead of immediately writing code, I now focus more on analyzing requirements, evaluating efficiency, and considering long-term maintainability.

The projects also improved my ability to think algorithmically. I became more comfortable breaking complex problems into smaller, manageable tasks and designing solutions incrementally. Additionally, I gained a better understanding of runtime complexity and how software design decisions affect scalability and performance.

---

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

My programming style became significantly more organized throughout this course. I learned to write cleaner and more maintainable code by:

- Using meaningful variable and function names
- Separating logic into reusable functions
- Adding comments to explain important sections of code
- Following consistent formatting and indentation practices
- Designing modular programs that are easier to modify and expand

I also learned the importance of adaptability in software development. By using structured designs and appropriate data structures, programs can more easily accommodate future changes or additional features. The use of pseudocode and modular functions made debugging and testing more efficient while improving overall readability.

Overall, this course strengthened both my technical programming skills and my ability to design software solutions thoughtfully and efficiently.
