*This project has been created as part of the 42 curriculum by maherraz*

# ft_printf - 42 Project

## Description

**ft_printf** is a custom implementation of the standard C library function `printf`. This project aims to recreate the behavior of the original `printf` function, handling various format specifiers and returning the exact number of characters printed.

The function prototype is:
```c
int ft_printf(const char *format, ...);
```

### Supported Format Specifiers:
- `%c` - Prints a single character
- `%s` - Prints a string
- `%p` - Prints a pointer address in hexadecimal format
- `%d` - Prints a decimal (base 10) number
- `%i` - Prints an integer in base 10
- `%u` - Prints an unsigned decimal (base 10) number
- `%x` - Prints a number in hexadecimal (base 16) lowercase format
- `%X` - Prints a number in hexadecimal (base 16) uppercase format
- `%%` - Prints a percent sign

## Instructions

### Compilation

To compile the library, simply run:

```bash
make
```

This will generate a static library file `libftprintf.a`.

Available Makefile rules:
- `make all` - Compile the library
- `make clean` - Remove object files
- `make fclean` - Remove object files and the library
- `make re` - Recompile everything from scratch

### Usage

Include the header in your C files:

```c
#include "ft_printf.h"
```

Link the library when compiling your program:

```bash
cc -o your_program your_program.c -L. -lftprintf
```

### Example

```c
#include "ft_printf.h"

int main(void)
{
    int count;
    
    count = ft_printf("Hello %s, you are %d years old!\n", "Alice", 25);
    ft_printf("Printed %d characters\n", count);
    
    ft_printf("Char: %c\n", 'A');
    ft_printf("String: %s\n", "Hello World");
    ft_printf("Pointer: %p\n", &count);
    ft_printf("Decimal: %d\n", 123);
    ft_printf("Integer: %i\n", -456);
    ft_printf("Unsigned: %u\n", 789);
    ft_printf("Hex lowercase: %x\n", 255);
    ft_printf("Hex uppercase: %X\n", 255);
    ft_printf("Percent sign: %%\n");
    
    return (0);
}
```

## 🔍 Detailed Function Analysis

### 1. **ft_printf.c - Main Function**

```c
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;

	if (!format)
		return (0);
	va_start(args, format);
	i = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			i += ft_manage_conversion(args, *format);
		}
		else
			i += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (i);
}
```

**Algorithm Analysis:**
- **Initialization Phase**: Uses `va_start` to initialize the argument list pointer
- **Parsing Loop**: Iterates character by character through the format string
- **Decision Making**: 
  - If character is '%', it's a format specifier → increment pointer and call dispatcher
  - If regular character → print directly with `ft_putchar`
- **Count Accumulation**: Each function call returns characters printed, which are added to total
- **Cleanup**: `va_end` properly cleans up the argument list

**Why this approach?** This linear parsing approach is efficient and mirrors how the original printf works - scanning the string once and acting on each character.

### 2. **ft_manage_conversion - Dispatcher Function**

```c
static int	ft_manage_conversion(va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	if (c == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	if (c == '%')
		return (ft_putchar('%'));
	return (write(1, "%", 1) + write(1, &c, 1));
}
```

**Algorithm Analysis:**
- **Type Extraction**: Uses `va_arg` to retrieve the next argument of the expected type
- **Routing Logic**: Simple if-else ladder routes to appropriate printing function
- **Return Propagation**: Immediately returns the count from the called function
- **Error Handling**: Unknown specifiers print "%" followed by the character

**Advantages:**
- **Separation of Concerns**: Main loop doesn't need to know about conversion details
- **Extensibility**: New specifiers can be added by adding one if statement
- **Type Safety**: Each conversion knows exactly what type to extract

### 3. **ft_putnbr.c - Number Printing with Recursion**

```c
static int	ft_putnbr_base(unsigned long number)
{
	int	count;

	count = 0;
	if (number >= 10)
		count += ft_putnbr_base(number / 10);
	count += ft_putchar((number % 10) + '0');
	return (count);
}

int	ft_putnbr(int nb)
{
	int		count;
	long	n;

	count = 0;
	n = nb;
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	count += ft_putnbr_base((unsigned long)n);
	return (count);
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	if (nb == 0)
		return (ft_putchar('0'));
	return (ft_putnbr_base((unsigned long)nb));
}
```

**Recursive Algorithm Deep Dive:**

The recursive approach for printing numbers is the core algorithmic choice of this project. Here's why it's brilliant:

**How it works for number 123:**<br>

Call Stack Visualization:
```
Level 3: ft_putnbr_base(1) → prints '1' → returns 1
              ↑
Level 2: ft_putnbr_base(12) → prints '2' → returns 1 + 1 = 2
              ↑
Level 1: ft_putnbr_base(123) → prints '3' → returns 2 + 1 = 3
```

**Step-by-step execution:**
1. `ft_putnbr(123)` calls `ft_putnbr_base(123)`
2. `123 >= 10` → recursive call to `ft_putnbr_base(12)`
3. `12 >= 10` → recursive call to `ft_putnbr_base(1)`
4. `1 < 10` → base case: print '1' (count=1), return 1
5. Back to `ft_putnbr_base(12)`: print '2' (count=1+1=2), return 2
6. Back to `ft_putnbr_base(123)`: print '3' (count=2+1=3), return 3

**Advantages of Recursion for Number Printing:**

| Aspect              | Recursive Approach                  | Iterative Approach                  |
|---------------------|-------------------------------------|-------------------------------------|
| **Digit Order**     | Prints naturally from left to right | Requires buffer and reversal        |
| **Code Complexity** | Simple, mathematical                | More complex with buffer management |
| **Memory**          | Uses stack (O(log n))               | Uses heap/stack buffer (O(n))       |
| **Readability**     | Elegant and clear                   | Often harder to follow              |

**Why recursion wins here:**
- **Mathematical Elegance**: The recursion mirrors how we think about numbers: 123 = 12*10 + 3
- **No Buffer Needed**: No need to allocate memory to store digits
- **Automatic Ordering**: The call stack naturally ensures most significant digits print first
- **Clean Counting**: Each level adds its count, making total accumulation trivial

### 4. **ft_print_hex.c - Hexadecimal Conversion**

```c
int	ft_print_hex(unsigned int n, int maj)
{
	char	*base;
	int		len;

	len = 0;
	if (maj)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		len += ft_print_hex(n / 16, maj);
	len += ft_putchar(base[n % 16]);
	return (len);
}
```

**Algorithm Analysis:**
- **Base Selection**: Chooses between uppercase or lowercase hexadecimal digits
- **Base-16 Recursion**: Similar to decimal but divides by 16 instead of 10
- **Character Mapping**: Uses the remainder as index into the base string

**Example for n=255, maj=0 (lowercase):**
```
ft_print_hex(255) → 255 >= 16 → call ft_print_hex(15)
ft_print_hex(15) → 15 < 16 → print base[15] = 'f' → return 1
Back to ft_print_hex(255) → print base[15] = 'f' → return 1+1=2
Result: "ff" (2 characters)
```

### 5. **ft_print_pointer.c - Pointer Address Printing**

```c
static int	ft_putpt_base(unsigned long addr, char *base)
{
	int	len;

	len = 0;
	if (addr >= 16)
		len += ft_putpt_base(addr / 16, base);
	len += ft_putchar(base[addr % 16]);
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	int				len;
	unsigned long	addr;

	len = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	addr = (unsigned long)ptr;
	write(1, "0x", 2);
	len += 2;
	len += ft_putpt_base(addr, "0123456789abcdef");
	return (len);
}
```

**Algorithm Analysis:**
- **NULL Handling**: Special case prints "(nil)" (standard printf behavior)
- **Type Conversion**: Casts void pointer to unsigned long for manipulation
- **Prefix Addition**: Prints "0x" to indicate hexadecimal format
- **Recursive Conversion**: Uses same base-16 logic as hex printing

**Why separate helper function?** The `ft_putpt_base` function is necessary because pointers can be larger than unsigned int, so we need a separate implementation that works with unsigned long.

### 6. **ft_putstr.c - String Printing with Recursion**

```c
int	ft_putstr(char *str)
{
	if (!str)
	{
		return (ft_putstr("(null)"));
	}
	if (*str == '\0')
		return (0);
	ft_putchar(*str);
	return (1 + ft_putstr(str + 1));
}
```

**Recursive String Algorithm:**
```
Example: ft_putstr("Hi")

Level 1: str="Hi" → print 'H' → return 1 + ft_putstr("i")
Level 2: str="i"  → print 'i' → return 1 + ft_putstr("")
Level 3: str=""   → base case → return 0
Result: 1 + 1 + 0 = 2 characters printed
```

**Advantages of Recursive String Printing:**
- **Elegant Termination**: Base case at null terminator
- **Natural Progression**: Each call advances the pointer
- **Simple Counting**: 1 (current char) + result of rest

## Resources

### Primary Documentation
- **[man 3 stdarg](https://man7.org/linux/man-pages/man3/stdarg.3.html)** - Official documentation for variadic functions (primary reference for va_list, va_start, va_arg, va_end)
- **man 3 printf** - Standard printf behavior reference

### Educational Resources Used

1. **Variadic Functions Understanding**:
   - Studied the stdarg.h documentation to understand how variable arguments work in C
   - Learned about stack layout and argument passing conventions
   - Understood why va_arg needs the type parameter

2. **Recursion Concepts**:
   - Studied recursive algorithms for number base conversion
   - Understood call stack behavior and return value propagation
   - Analyzed time complexity: O(log n) for number printing

3. **Format String Parsing**:
   - Researched how printf parses format strings
   - Understood the importance of handling edge cases (NULL, empty strings)

### AI Usage Disclosure

Artificial Intelligence was used as a supplementary learning tool:

1. **Concept Clarification**:
   - Helped explain the mechanics of va_list and why it must be used with va_start/va_end
   - Clarified recursion vs iteration trade-offs for number printing
   - Explained pointer casting for the %p specifier

2. **Debugging Assistance**:
   - Helped identify off-by-one errors in counting
   - Suggested proper handling of INT_MIN edge case
   - Assisted in understanding recursive return value accumulation

3. **Documentation Structure**:
   - Helped organize technical explanations
   - Assisted in creating clear algorithm descriptions

**Important Note**: All code was written, understood, and debugged by the author. AI was used strictly as a learning aid, similar to consulting documentation or tutorials, not to generate solutions without comprehension.

## ✅ Testing Strategy

The project has been tested with:
- **Tripouille's printfTester** - All mandatory tests pass
- **Edge Cases**:
  - NULL strings and pointers
  - INT_MIN and LONG_MIN values
  - Empty format strings
  - Multiple consecutive format specifiers
  - Mixed regular text and specifiers

## 📁 Repository Structure

```
.
├── Makefile           # Compilation rules with standard targets
├── ft_printf.h        # Header with function prototypes and includes
├── ft_printf.c        # Main function and conversion dispatcher
├── ft_putchar.c       # Single character output
├── ft_putstr.c        # String output with recursion
├── ft_putnbr.c        # Signed and unsigned decimal output
├── ft_print_hexa.c    # Hexadecimal output (lowercase/uppercase)
├── ft_print_pointer.c # Pointer address output with 0x prefix
└── README.md          # Comprehensive documentation
```

## ⚠️ Important Notes

- The function returns `0` if format string is `NULL` (implementation choice)
- All output uses the `write` system call (2) for consistency
- Follows 42 Norm coding standards strictly
- No undefined behavior: all edge cases explicitly handled
- Return value always matches number of characters written

## 🎯 Key Takeaways

1. **Recursion is powerful** for problems with natural hierarchical structure (numbers, strings)
2. **Variadic functions** require careful handling but enable flexible interfaces
3. **Modular design** makes the code maintainable and extensible
4. **Edge cases matter** - robust software handles unexpected inputs gracefully