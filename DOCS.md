# Learn Yex

## NOTE:
This tutorial assumes that you have previous experience with programming and
already has the yex language installed.

* [Basics](#basics)
  * [Primitives](#Primitives)
    * [Numbers](#Numbers)
    * [Strings](#Strings)
    * [Bool](#Booleans)
    * [Nulls](#Nulls)
  * [Structuring a program](#structuring-a-program)
* [Variables](#variables)
  * [Globals](#globals)
  * [Locals](#locals)
* [Lists](#lists)
  * [Creating lists](#creating-lists)
  * [Operating on lists](#operating-on-lists)
* [Functions](#Functions)
  * [Creating functions](#creating-functions)
    * [Named functions](#named-functions)
    * [Anonymous functions](#anonymous-functions)
  * [Tail calls](#tail-calls)
* [Control flow](#control-flow)
  * [Conditional execution](#conditional-execution)
    * [If and else](#if-and-else)
  * [Sequential execution](#sequential-execution)
    * [The sequence operator](#the-sequence-operator)
* [Builtin functions](#builtin-functions)

## Basics

### Primitives

Yex has the following primitive types:
  * fn - Functions
  * num - 64 bits floating-point numbers
  * str - Strings
  * sym - Compile-time hashed strings
  * bool - Booleans (true and false)
  * list - Singly linked lists
  * nil - Null values

Them all support the equality `==` operator.

#### Numbers
Open the repl and start typing:

```
yex> type(1)
>> "num"
yex> 2+2
>> 2
yex> 2-2
>> 0
yex> 2*2
>> 4
yex> 2/2
>> 1
```

As you can see, numbers support all the basic math operations, they also support
the xor, shift-left, shift-right, and and or, bitwise operators:

```
yex> 2 ^^^ 3
>> 1
yex> 2 >>> 3
>> 0
yex> 2 <<< 3
>> 16
yex> 2 &&& 3
>> 2
yex> 2 ||| 3
>> 3
```

#### Strings

Strings in yex are represented as UTF-8 encoded strings, they support
concatenation, on the repl:

```
yex> type("Example")
>> "str"
yex> "Hello"
>> "Hello"
yex> "Hello " + "World"
>> "Hello World"
```

#### Symbols

Symbols in yex are represented as 64 bit unsigned integers. They are created
using `:name` and are hashed at compile time, on the repl:

```
yex> type(:symbol)
>> "sym"
yex> :sym
>> :sym
```

They don't support any operators except for comparison.

#### Booleans

Booleans in yex are just `true` and `false`, there is no magic behind the
scenes.

```
yex> type(true)
>> "bool"
yex> true
>> true
yex> false
>> false
```

#### Nulls

Null values in yex can be created using the `nil` keyword.

```
yex> type(nil)
>> "nil"
yex> nil
>> nil
```

### Structuring a program

A yex program is just a lot of `let`s. There is no way of using expressions in
the top-level and there isn't any main function, so we usually create a
`let _ = ...` to denotate the entry point, since it's going to
be evaluated when the code runs.

But, what is a `let`? Let's see it now.

## Variables

In yex everything is immutable, so, when you assign a variable, you can't change
it's value, (but shadowing is still supported).

### Globals

Global variables are created using the `let` keyword, open a file and type this:

```
let number = 42
let _ = puts(number)
```

Run it with the yex binary. It should print 42.

### Locals

Since, everything in yex is an expression, local variables declarations also
need to be one. For this we use the `let name = expression in expression` constructor, which explicity
defines a expression to be runned after the declaration.

Open a file and type:

```
let _ =
  let number = 42
  in puts(number)
```

Run it with the yex binary. It should print 42.

You can create multiple locals just using a lot of `let ... in` expression,
like:

```
let _ =
  let a = 21
  in let b = 21
  in puts(a + b)
```

And, yes, this prints 42.

## Lists

In yex, lists are data types that let you have a collection of values of divergent types.

### Creating lists

Like in most other languages, lists can be instantiated using brackets, open the
repl and type:

```
yex> type([])
>> "list"
yex> [1, "hello", :symbol, [3, 4], true, nil]
>> [1, "hello", :symbol, [3, 4], true, nil]
```

### Operating on lists

Lists support the following operations:
  * head() - returns the first element of the list
  * tail() - returns the tail of the list, (all elements except for the first)
  * `::` - This is the cons operator, it add a new element at the start of the
    list without mutating it.

On the repl:

```
yex> head([1, 2, 3])
>> 1
yex> tail([1, 2, 3])
>> [2, 3]
yex> 0 :: [1, 2, 3]
>> [0, 1, 2, 3]
```

## Functions

### Creating functions

#### Named Functions

Named functions are created using the `let` keyword, like variables. Open the
repl and type:

```
yex> let mul a b = a * b
>> nil
yex> mul(2, 3)
>> 6
yex> type(mul)
>> "fn"
```

So, let me explain, first, we declare the function `mul`, receiving `a` and `b`
as parameters. After the `=` it specifies the function's body.

#### Anonymous Functions

You can create anonymous functions using the `fn` keyword. Open the repl and
type:

```
yex> let mul = fn a b = a * b
>> nil
yex> mul(2, 3)
>> 6
yex> type(mul)
>> "fn"
```

### Tail calls

Tail calls are an specific type of recursion where it just jump to some
instructions before, you can create them using the `become` keyword, like:

```
let until_0 num =
  if num == 0 then
    0
  else
    become until_0(num - 1)
```

Tail calls just use a jump instruction, so they are faster than normal recursive
functions. A important detail about tail calls is that they can only be used to
do recursion, they can't call any arbitrary function.

## Controw flow

### Conditional execution

#### If and else

Yex supports if and else control flow structures, open the repl and type:

```
yex> if true then 1 else 2
>> 1
yex> if false then 1 else if true then 2 else 3
>> 2
```

The format itself is just: `ìf condition then expression else expression`, since
if itself is an expression, the `else if` pattern is just a `if` expression
after the `else`.

### The sequence operator

Since everything in yex is an expression, it isn't really a easy thing to run
multiple side-effect-only functions chained, you could probably think about
using let to concat them, but this looks really bad. So, yex provides the `>>`
operator, which ignores the result of a computation and runs the next
computation.

Open a file and type:

```
let _ =
  puts("Hello")
  >> puts("World")
```

This should print:


```
Hello
World
```

## Builtin functions

| Name      | Description                                       |
|-----------|---------------------------------------------------|
| `print`   | prints a value without adding the new line        |
| `puts`    | prints a value with a newline at the end          |
| `str`     | converts a value to string                        |
| `input`   | Reads the input from the console                  |
| `head`    | Returns the first element of a list               |
| `tail`    | Returns the tail of a list                        |
| `type`    | Returns the string representation of value type's |
| `inspect` | Returns the intern representation of the value    |