#include <stdio.h>
#include <stdlib.h>

#define MOD10 1000000000
#define MOD16 16

long long Atoi(unsigned char s[], unsigned int size, unsigned int type)
{

	/*
		Translating from a string to a number
	*/

	int i = 0;
	int j = size - 1;
	long long res = 0;
	long long n = 1;

	int symbol[6] = { 10, 11, 12, 13, 14, 15 };

	for (i = j; i + 1; --i)
	{
		char _s = s[i];
		if (_s >= '0' && _s <= '9')
		{
			res += (_s - '0') * n;
			n *= 10;
		}
		else if (_s >= 'A' && _s <= 'F')
		{
			res += symbol[_s - 'A'] * n;
			n *= 10;
		}
		else if (_s >= 'a' && _s <= 'f')
		{
			res += symbol[_s - 'a'] * n;
			n *= 10;
		}
		else
		{
			printf("\n!ERROR!\nInvalid input\n");
			return 0;
		}
	}

	return res;
}

typedef struct BigInt
{

	/*
		The structure of a large number
	*/

	long long* number;
	int count;
	int size;
	int num_type;
	unsigned char* base_str;
	int sign;

} BigInt;

static void _swap(unsigned char* arr, unsigned int size)
{

	/*
		Swap the direction of the string
	*/

	unsigned char temp;
	for (unsigned int i = 0, j = size - 1; i < size / 2; ++i, --j)
	{
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

static int _swapped = 0;
// Changing numbers when subtracting (bool)

static void _inc_count_bigint(BigInt* x)
{

	/*
		Increase the counter
	*/

	x->count += 1;
	while (x->count >= x->size)
	{
		x->size *= 2;
	}
	//x->size *= 2;
	x->number = (long long*)realloc(x->number, x->size * sizeof(long long));
	memset(x->number + x->count, 0, (x->size - x->count) * sizeof(long long));
}

static void _set_count_bigint(BigInt* x, BigInt* y)
{

	/*
		Equate the counter
	*/

	if (x->size < y->size)
	{
		x->size = y->size;
		x->number = (long long*)realloc(x->number, x->size * sizeof(long long));
		memset(x->number + x->count, 0, (x->size - x->count) * sizeof(long long));
	}

	if (y->size < x->size)
	{
		y->size = x->size;
		y->number = (long long*)realloc(y->number, y->size * sizeof(long long));
		memset(y->number + y->count, 0, (y->size - y->count) * sizeof(long long));
	}

	if (x->count < y->count)
	{
		x->count = y->count;
	}
}

static void _clr_count_bigint(BigInt* x)
{

	/*
		Clearing the counter
	*/

	if (x->count == 0)
	{
		return; // null
	}
	int i = x->count - 1;
	for (; i > 0; --i)
	{
		if (x->number[i] != 0)
			break;
	}
	x->count = i + 1;
}

extern BigInt* new_bigint(unsigned char* str);
extern void free_bigint(BigInt* x);

extern void add_bigint_10(BigInt* x, BigInt* y); // Addition in the 10th number system
extern void sub_bigint_10(BigInt* x, BigInt* y); // Subtraction in the 10th number system
extern void mul_bigint_10(BigInt* x, BigInt* y); // Multiplication in the 10th number system
extern void exp_bigint_10(BigInt* x, BigInt* y); // Exponentiation in the 10th number system

extern void add_bigint_16(BigInt* x, BigInt* y); // Addition in the 16th number system
extern void sub_bigint_16(BigInt* x, BigInt* y); // Subtraction in the 16th number system
extern void mul_bigint_16(BigInt* x, BigInt* y); // Multiplication in the 16th number system

extern void print_bigint(BigInt* x);
extern int cmp_bigint(BigInt* x, BigInt* y); // Compare large numbers
extern int cmp_bigint_types(BigInt* x, BigInt* y); // Compare types of large numbers
extern void swap_bigint(BigInt* x, BigInt* y); // Swap large numbers

int main(void)
{
	unsigned char num1[1000];
	unsigned char num2[1000];
	unsigned char op;

	printf("Number one:\n");
	scanf("%s", num1);

	BigInt* x = new_bigint(num1);

	printf("\nNumber two:\n");
	scanf("%s", num2);
	
	BigInt* y = new_bigint(num2);

	if (cmp_bigint_types(x, y) == 1)
	{
		printf("\nSelect an operation: + | - | * | ^\n");
		scanf("\n%c", &op);

		if (!(op == '+' || op == '-' || op == '*' || op == '^'))
		{
			printf("\n!ERROR!\nInvalid operation\n");

			free_bigint(x);
			free_bigint(y);

			return 0;
		}

		switch (op)
		{

		case '+':
			printf("\nResult:\n");
			add_bigint_10(x, y);
			print_bigint(x);
			break;
		case '-':
			printf("\nResult:\n");
			sub_bigint_10(x, y);
			print_bigint(x);
			break;
		case '*':
			printf("\nResult:\n");
			mul_bigint_10(x, y);
			print_bigint(x);
			break;
		case '^':
			printf("\nResult:\n");
			exp_bigint_10(x, y);
			print_bigint(x);
			break;
		default:
			break;
		}
	}
	else if (cmp_bigint_types(x, y) == 2)
	{

		printf("\nSelect an operation: + | - | *\n");
		scanf("\n%c", &op);

		if (!(op == '+' || op == '-' || op == '*'))
		{
			printf("\n!ERROR!\nInvalid operation\n");

			free_bigint(x);
			free_bigint(y);

			return 0;
		}

		switch (op)
		{

		case '+':
			printf("\nResult:\n");
			add_bigint_16(x, y);
			print_bigint(x);
			break;
		case '-':
			printf("\nResult:\n");
			sub_bigint_16(x, y);
			print_bigint(x);
			break;
		case '*':
			printf("\nResult:\n");
			mul_bigint_16(x, y);
			print_bigint(x);
			break;
		default:
			break;
		}
	}
	else
	{
		printf("\n!ERROR!\nUnequal types\n");

		free_bigint(x);
		free_bigint(y);

		return 0;
	}
	
	free_bigint(x);
	free_bigint(y);

	return 0;
}

extern int cmp_bigint_types(BigInt* x, BigInt* y)
{

	/*
		Compare types of large numbers
	*/

	if (x->num_type == y->num_type)
		if (x->num_type == 10)
			return 1;
		else return 2;
	return 0;
}

extern int cmp_bigint(BigInt* x, BigInt* y)
{

	/*
		Compare large numbers
	*/

	_set_count_bigint(x, y);
	for (int i = x->count - 1; i != -1; --i)
	{
		if (x->number[i] < y->number[i])
			return -1;
		if (x->number[i] > y->number[i])
			return 1;
	}
	return 0;
}

extern void swap_bigint(BigInt* x, BigInt* y)
{

	/*
		Swap large numbers
	*/

	BigInt t = *x;
	*x = *y;
	*y = t;
	return;
}

//--------------------------------------------------  10

extern void add_bigint_10(BigInt* x, BigInt* y)
{

	/*
		Addition in the 10th number system
	*/

	_set_count_bigint(x, y);

	if (x->sign == -1 || y->sign == -1)
	{
		if (cmp_bigint(x, y) == -1)
			swap_bigint(x, y);

		if (x->sign == -1)
		{
			if (y->sign == -1)
			{
				// continue
			}
			else
			{
				y->sign = -1;
				sub_bigint_10(x, y);
				return;
			}
		}
		else if (y->sign == -1)
		{
			if (x->sign == -1)
			{
				// continue
			}
			else
			{
				x->sign = -1;
				sub_bigint_10(x, y);
				return;
			}
		}
	}

	int cf = 0;
	for (int i = 0; i < x->count; ++i)
	{
		long long temp = cf + x->number[i] + y->number[i];
		x->number[i] = temp % MOD10;
		cf = temp / MOD10;
	}
	if (cf)
	{
		x->number[x->count] = cf;
		_inc_count_bigint(x);
	}
	_clr_count_bigint(x);
}

extern void sub_bigint_10(BigInt* x, BigInt* y)
{

	/*
		Subtraction in the 10th number system
	*/

	if (cmp_bigint(x, y) == -1)
	{
		if (y->sign == -1)
			y->sign = 1;
		else
			y->sign = -1;
		swap_bigint(x, y);
		_swapped = 1;
		sub_bigint_10(x, y);
		return;
	}

	if (x->sign == -1 || y->sign == -1 || _swapped)
	{
		if (x->sign == -1)
		{
			if (_swapped)
			{
				if (y->sign == -1)
				{
					add_bigint_10(x, y);
					return;
				}
				else
				{
					//continue
				}
			}
			else
			{
				if (y->sign == -1)
				{
					y->sign = 1;
					// continue
				}
				else
				{
					y->sign = -1;
					add_bigint_10(x, y);
					return;
				}			
			}
			
		}
		else if (_swapped)
		{
			if (y->sign == -1)
			{
				//continue
			}
			else
			{
				y->sign = 1;
				add_bigint_10(x, y);
				return;
			}
		}
		else
		{
			if (y->sign == -1)
			{
				y->sign = 1;
				add_bigint_10(x, y);
				return;
			}
			else
			{
				//continue
			}
		}
	}

	_set_count_bigint(x, y);
	int cf = 0;
	for (int i = 0; i < x->count; ++i)
	{
		long long temp = MOD10 + x->number[i] - (cf + y->number[i]);
		x->number[i] = temp % MOD10;
		cf = (temp >= MOD10) ? 0 : 1;
	}
	_clr_count_bigint(x);
	_swapped = 0;
}

extern void mul_bigint_10(BigInt* x, BigInt* y)
{

	/*
		Multiplication in the 10th number system
	*/

	BigInt* c = new_bigint("");
	c->count = x->count + y->count - 1;
	c->num_type = x->num_type;
	_inc_count_bigint(c);
	memset(c->number, 0, c->count * sizeof(long long));
	for (int i = 0; i < x->count; ++i)
	{
		for (int j = 0, cf = 0; j < y->count || cf; ++j)
		{
			long long cur = c->number[i + j] + x->number[i] * 1ll * ((j < y->count) ? y->number[j] : 0) + cf;
			c->number[i + j] = cur % MOD10;
			cf = cur / MOD10;
		}
	}

	if ((x->sign == -1 && y->sign == -1) || (x->sign == 1 && y->sign == 1))
		c->sign = 1;
	else
		c->sign = -1;

	_clr_count_bigint(c);
	swap_bigint(x, c);
	free_bigint(c);
}

extern void exp_bigint_10(BigInt* x, BigInt* y)
{

	/*
		Exponentiation in the 10th number system
	*/

	if (!y->number[y->count - 1] && !(y->count - 1))
	{
		BigInt* c = new_bigint("1");
		swap_bigint(x, c);
		return;
	}
	BigInt* c = new_bigint(x->base_str);
	--y->number[y->count - 1];
	while (y->count)
	{
		while (y->number[y->count - 1])
		{
			mul_bigint_10(x, c);
			--y->number[y->count - 1];
		}
		--y->count;
	}
}

//--------------------------------------------------  16

extern void add_bigint_16(BigInt* x, BigInt* y)
{

	/*
		Addition in the 16th number system
	*/

	_set_count_bigint(x, y);

	if (x->sign == -1 || y->sign == -1)
	{
		if (cmp_bigint(x, y) == -1)
			swap_bigint(x, y);

		if (x->sign == -1)
		{
			if (y->sign == -1)
			{
				// continue
			}
			else
			{
				y->sign = -1;
				sub_bigint_16(x, y);
				return;
			}
		}
		else if (y->sign == -1)
		{
			if (x->sign == -1)
			{
				// continue
			}
			else
			{
				x->sign = -1;
				sub_bigint_16(x, y);
				return;
			}
		}
	}

	int cf = 0;
	for (int i = 0; i < x->count; ++i)
	{
		long long temp = cf + x->number[i] + y->number[i];
		x->number[i] = temp % MOD16;
		cf = temp / MOD16;
	}
	if (cf)
	{
		x->number[x->count] = cf;
		_inc_count_bigint(x);
	}
	_clr_count_bigint(x);
}

extern void sub_bigint_16(BigInt* x, BigInt* y)
{

	/*
		Subtraction in the 16th number system
	*/

	if (cmp_bigint(x, y) == -1)
	{
		if (y->sign == -1)
			y->sign = 1;
		else
			y->sign = -1;
		swap_bigint(x, y);
		_swapped = 1;
		sub_bigint_16(x, y);
		return;
	}

	if (x->sign == -1 || y->sign == -1 || _swapped)
	{
		if (x->sign == -1)
		{
			if (_swapped)
			{
				if (y->sign == -1)
				{
					add_bigint_16(x, y);
					return;
				}
				else
				{
					//continue
				}
			}
			else
			{
				if (y->sign == -1)
				{
					y->sign = 1;
					// continue
				}
				else
				{
					y->sign = -1;
					add_bigint_16(x, y);
					return;
				}
			}

		}
		else if (_swapped)
		{
			if (y->sign == -1)
			{
				//continue
			}
			else
			{
				y->sign = 1;
				add_bigint_16(x, y);
				return;
			}
		}
		else
		{
			if (y->sign == -1)
			{
				y->sign = 1;
				add_bigint_16(x, y);
				return;
			}
			else
			{
				//continue
			}
		}
	}

	_set_count_bigint(x, y);
	int cf = 0;
	for (int i = 0; i < x->count; ++i)
	{
		long long temp = MOD16 + x->number[i] - (cf + y->number[i]);
		x->number[i] = temp % MOD16;
		cf = (temp >= MOD16) ? 0 : 1;
	}
	_clr_count_bigint(x);
	_swapped = 0;
}

extern void mul_bigint_16(BigInt* x, BigInt* y)
{

	/*
		Multiplication in the 16th number system
	*/

	BigInt* c = new_bigint("");
	c->count = x->count + y->count - 1;
	c->num_type = x->num_type;
	_inc_count_bigint(c);
	memset(c->number, 0, c->count * sizeof(long long));
	for (int i = 0; i < x->count; ++i)
	{
		for (int j = 0, cf = 0; j < y->count || cf; ++j)
		{
			long long cur = c->number[i + j] + x->number[i] * 1ll * ((j < y->count) ? y->number[j] : 0) + cf;
			c->number[i + j] = cur % MOD16;
			cf = cur / MOD16;
		}
	}

	if ((x->sign == -1 && y->sign == -1) || (x->sign == 1 && y->sign == 1))
		c->sign = 1;
	else
		c->sign = -1;

	_clr_count_bigint(c);
	swap_bigint(x, c);
	free_bigint(c);
}

//--------------------------------------------------

extern BigInt* new_bigint(unsigned char* str)
{

	BigInt* bigint = (BigInt*)malloc(sizeof(BigInt));
	bigint->size = 10;
	bigint->base_str = str;
	bigint->count = 0;
	bigint->number = (long long*)malloc(bigint->size * sizeof(long long));
	memset(bigint->number, 0, bigint->size * sizeof(long long));

	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '+')
			bigint->sign = 1;
		else
			bigint->sign = -1;
		str++;
	}
	else
		bigint->sign = 1;

	int next = 0;
	int index = 0;
	int len = strlen(str);
	int type = 10;

	for (int i = 0; i < len; ++i)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			type = (type < 16) ? 16 : type;
		else if (str[i] >= 'a' && str[i] <= 'f')
			type = (type < 16) ? 16 : type;
		else if (str[i] >= '0' && str[i] <= '9')
			type = (type < 10) ? 10 : type;
		else {
			printf("\n!ERROR!\nInvalid input\n");
			free_bigint(bigint);
			return;
		}
	}

	bigint->num_type = type;

	if (type == 10)
	{

		unsigned char chunck[9];
		memset(chunck, 0, (9) * sizeof(unsigned char));

		for (int i = len - 1; i != -1; --i)
		{
			chunck[index++] = str[i];
			if (index == 9)
			{
				index = 0;
				_swap(chunck, 9);
				bigint->number[next++] = Atoi(chunck, 9, type);
				_inc_count_bigint(bigint);
			}
		}
		if (index != 0)
		{
			chunck[index] = '\0';
			_swap(chunck, index);
			bigint->number[next++] = Atoi(chunck, index, type);
			_inc_count_bigint(bigint);
		}

	}
	else if (type == 16)
	{
		for (int i = len - 1; i != -1; --i)
		{
			unsigned char chunck[2];
			chunck[0] = str[i];
			chunck[1] = '\0';
			bigint->number[next++] = Atoi(chunck, 1, type);
			_inc_count_bigint(bigint);
		}
	}

	return bigint;
}

extern void free_bigint(BigInt* x)
{
	free(x->number);
	free(x);
}

extern void print_bigint(BigInt* x)
{
	if (x->count == 0)
	{
		printf("null\n");
		return;
	}
	int i = x->count - 1;
	for (; i > 0; --i)
	{
		if (x->number != 0)
		{
			break;
		}
	}
	if (x->sign == -1 && x->number[i] != 0)
		printf("-");
	if (x->num_type == 10)
	{
		printf("%llu", x->number[i]);
	}
	else
	{
		if (x->number[i] >= 10)
			printf("%c", x->number[i] + 'A' - 10);
		else
			printf("%llu", x->number[i]);
		if (!(i % 4))
			printf(" ");
	}
	for (--i; i != -1; --i)
	{
		if (x->num_type == 10)
		{
			printf("%.9llu", x->number[i]);
		}
		else if (x->num_type == 16)
		{
			//printf("%.2llu", x->number[i]);
			if (x->number[i] >= 10)
				printf("%c", x->number[i] + 'A' - 10);
			else
				printf("%llu", x->number[i]);
			if (!(i % 4))
				printf(" ");
		}
	}
	putchar('\n');
	return;
}