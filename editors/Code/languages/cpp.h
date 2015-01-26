#define cpp_NAME 		"C++"

#define cpp_EXTENSIONS 	E("cpp") \
						E("cxx") \
						E("c++") \
						E("cc")

#define cpp_SCLEX_ID	SCLEX_CPP

#define cpp_KEYWORDS "if else switch case default break goto return " \
	"for while do continue typedef sizeof NULL new delete throw try " \
	"catch namespace operator this const_cast static_cast dynamic_cast " \
	"reinterpret_cast true false using typeid and and_eq bitand bitor " \
	"compl not not_eq or or_eq xor xor_eq"

#define cpp_TYPES "void struct union enum char " \
	"short int long double float signed unsigned const static extern auto " \
	"register volatile bool class private protected public friend inline " \
	"template virtual asm explicit typename mutable"
