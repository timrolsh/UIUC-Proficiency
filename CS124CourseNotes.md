# CS 124

## Exam Comments/Reflection

The exam is significantly easier and a solid knowledge of AP Computer Science A topics with some additional understanding of basic data structures like linked lists and trees is more than enough to get a high pass on this exam. Most of the content in these notes is additional content that I needed to review, brush up on, learn, or Java language specific stuff, but most of it did not appear on the exam. Quick sort is implemented in C++ because I was studying for CS 128 at the same time but the algorithm is language agnostic.

## Exam Format

* 20 mcqs, 6 programming questions

## General Topics

**Declaration**: Declaring a variable:

```java
int a;
```

**Initialization**: Initializing a variable value

```java
a = 12;
```

**Literal**: Constant character, string, number, etc. that appears in your code and is hardcoded, the number 12 the previous initialization is a literal

**Maps and Sets in Java**: Maps are key value lookup with O(1) time, sets are unique values with O(1) lookup time

```java
// declare and initialize a map
HashMap<String, Integer> map = new HashMap<>();
map.put("test", 1);
System.out.println(map.get("test"));
for (String key : map) {
    System.out.println(key + ": " + map.get(key));
}
HashSet<String> set = new HashSet<>();
```

**Polymorphism and Constructors**: The first line of a child constructor will be the implicit call to a super no arg constructor of the parent class, happens recursively

* when you type cast it goes to the lowest type and works its way as far down as it can

## Anonymous Classes

Not like traditional named classes, they are basically subclasses stored in a variable of type original class and they extend/implement an interface or another class, good for packing it into a variable like you would a callback function

```java
public class Person {
    public String getType() {
        return "Person";
    }
}

Person student = new Person() {
    @Override
    public String getType() {
        return "Student";
    }
};
```

**Functional Interfaces**: Specific type of interface that has only one member and it is a function and then you can implement that function with a clean one liner right into a type of that interface, for example:

```java
interface Modify {
  int modify(int value);
}
Modify first = (value) -> value + 1;
Modify second = (value) -> {
 return value + 1;
}
first.modify(2);
```

## Basic Sorting Algorithms

**Bubble Sort**: Loop by pairs, if left > right, swap and go to the next pair, keep looping until everything is sorted, $O(n^2)$ time
**Insertion Sort**: Loop through array, if you find element thats out of place, shift it over until it is in the right place (it is greater than the element to its left), $O(n^2)$ time
**Merge Sort**: Split array into halves, recurisvely until you'r eat arayas of size 1, combine those, then work upwards combining sorted arrays, $\displaystyle\text{O(}{n}\times{{\log}_{{2}}{\left({n}\right)}}\text{)}$ time, $\displaystyle{O}{\left({n}\right)}$ space
**Stable Sort**: Type of sort where if values are the same their order sorted does not change from their order originally in the array

## Quick Sort

* Pick value called a pivot/partition and divide the array into 2 parts, values in the array larger than the pivot, values smaller than the pivot
  * pivot can be the first choice for simplicity
* Continues until all arrays that need to be sorted are size 1, then that it is the base case for the recursion and it can end
**Implementation**

```cpp
// The range of left and right is inclusive of the size of the list
void quickSortHelper(vector<int>& items, int leftRangeIndex, int rightRangeIndex) {
    // Base case: Array size we are sorting is 1, so we can exit here and we know its sorted
    if (leftRangeIndex < 0 || rightRangeIndex >= items.size() ||
        leftRangeIndex >= rightRangeIndex) {
        return;
    }
    // Array of length 2
    if (leftRangeIndex == rightRangeIndex - 1) {
        // unsorted, sort first before exiting
        if (items[leftRangeIndex] > items[rightRangeIndex]) {
            int temp = items[leftRangeIndex];
            items[leftRangeIndex] = items[rightRangeIndex];
            items[rightRangeIndex] = temp;
        }
        return;
    }
    // This variable will stor the correct index of where the pivot ultimately needs to be
    int slow = leftRangeIndex + 1;
    for (int fast = leftRangeIndex + 1; fast <= rightRangeIndex; ++fast) {
        if (items[fast] < items[leftRangeIndex]) {
            int temp = items[slow];
            items[slow] = items[fast];
            items[fast] = temp;
            ++slow;
        }
    }
    --slow;
    int temp = items[leftRangeIndex];
    items[leftRangeIndex] = items[slow];
    items[slow] = temp;
    quickSortHelper(items, leftRangeIndex, slow - 1);
    quickSortHelper(items, slow + 1, rightRangeIndex);
}

void quickSort(vector<int>& items) {
    quickSortHelper(items, 0, items.size() - 1);
}
```

**Average Time Complexity**: $\displaystyle{O}{\left({n}{{\log}_{{2}}{n}}\right)}$

**Average Space Complexity**: $\displaystyle{O}{\left({{\log}_{{2}}{n}}\right)}$ due to recursive calls on the stack frame, you will do about about $\displaystyle{{\log}_{{2}}{n}}$ calls recursively if you're about pivoting by half each time on average

## Hashing

* Map data of any size and convert it to a unique data of the same size
* Hash functions should be uniform (different inputs give different outputs)
* Hash functions should be deterministic: Same input gives same out
**Hash Function Properties Review**: Deterministic, uniform, and same size
* Two objects with identical attributes are expected to have identical hashcodes
* Java's default provided compiler hashcode implementation does not follow this standard
* Hash codes are integers in java
Java built in method for identical object properties producing identical hashes

```java
import java.util.Objects;
@Override
public int hashCode() {
 return Objects.hash(property_one, property_two, etc);
}
```

**Applications of Hashing**: File/Download scanning, identifying, and verification, hashing of git commits and git content fingerprinting (hashing files that have changed and they produced different hashes meaning they are different, more efficient to compare than all contents of the file)
**Collisions**: Two different objects produce the same hash/hashcode

## Implementing Maps

* You use a hash table for fast lookups of hash codes of objects
**Hash Table Structure**: Array of nodes and each node in the array acts as a bucket where you can easily access other nodes
* Do an $\displaystyle{O}{\left({1}\right)}$ lookup in hash table index by getting the index of a node by doing hash code % table array size and going to that index
* Once you find the index, look through the linked list of the node at that index and retrieve value, insert value, put, modify, delete accordingly as needed

## Streams

* Better way of working with ordered/linear collections (arrays, lists, etc.) of data that is more convenient to write than simple for loops

```java
import java.util.stream.Stream;
// Make a stream list of items
Stream items = Stream.of(1,2,5);
items.forEach((element) -> {
System.out.println(element);
})
```

* `forEach` returns void, just loops through and doesn't return a stream
* `map` is equivalent of void except it returns a new stream with each element being the output of whatever operation you performed on the original stream inputs
* `filter` is similar to map, returns a new stream but only of the elements that evaluate to the true boolean condition returned by the callback function

**Generics**: Go inside the brackets and let you make objects that store different types, i.e. list of strings or map of strings and ints, etc.
