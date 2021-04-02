#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.gtk57"), aligned (8)))
#else
# define SECTION
#endif

#ifdef _MSC_VER
static const SECTION union { const guint8 data[865]; const double alignment; void * const ptr;}  gtk57_resource_data = { {
  0107, 0126, 0141, 0162, 0151, 0141, 0156, 0164, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 
  0030, 0000, 0000, 0000, 0164, 0000, 0000, 0000, 0000, 0000, 0000, 0050, 0003, 0000, 0000, 0000, 
  0000, 0000, 0000, 0000, 0001, 0000, 0000, 0000, 0002, 0000, 0000, 0000, 0336, 0314, 0043, 0012, 
  0001, 0000, 0000, 0000, 0164, 0000, 0000, 0000, 0013, 0000, 0166, 0000, 0200, 0000, 0000, 0000, 
  0115, 0003, 0000, 0000, 0125, 0315, 0142, 0036, 0002, 0000, 0000, 0000, 0115, 0003, 0000, 0000, 
  0006, 0000, 0114, 0000, 0124, 0003, 0000, 0000, 0130, 0003, 0000, 0000, 0324, 0265, 0002, 0000, 
  0377, 0377, 0377, 0377, 0130, 0003, 0000, 0000, 0001, 0000, 0114, 0000, 0134, 0003, 0000, 0000, 
  0140, 0003, 0000, 0000, 0155, 0145, 0156, 0165, 0142, 0141, 0162, 0056, 0170, 0155, 0154, 0000, 
  0275, 0002, 0000, 0000, 0000, 0000, 0000, 0000, 0074, 0077, 0170, 0155, 0154, 0040, 0166, 0145, 
  0162, 0163, 0151, 0157, 0156, 0075, 0042, 0061, 0056, 0060, 0042, 0040, 0145, 0156, 0143, 0157, 
  0144, 0151, 0156, 0147, 0075, 0042, 0125, 0124, 0106, 0055, 0070, 0042, 0077, 0076, 0012, 0074, 
  0151, 0156, 0164, 0145, 0162, 0146, 0141, 0143, 0145, 0076, 0074, 0155, 0145, 0156, 0165, 0040, 
  0151, 0144, 0075, 0042, 0141, 0160, 0160, 0055, 0155, 0145, 0156, 0165, 0042, 0076, 0074, 0163, 
  0145, 0143, 0164, 0151, 0157, 0156, 0076, 0074, 0163, 0165, 0142, 0155, 0145, 0156, 0165, 0076, 
  0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 0075, 
  0042, 0154, 0141, 0142, 0145, 0154, 0042, 0076, 0103, 0157, 0156, 0146, 0151, 0147, 0074, 0057, 
  0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0076, 0074, 0151, 0164, 0145, 0155, 0076, 
  0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 0075, 
  0042, 0154, 0141, 0142, 0145, 0154, 0042, 0076, 0103, 0150, 0141, 0156, 0147, 0145, 0040, 0103, 
  0157, 0156, 0146, 0151, 0147, 0061, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 
  0145, 0076, 0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 
  0145, 0075, 0042, 0141, 0143, 0164, 0151, 0157, 0156, 0042, 0076, 0141, 0160, 0160, 0056, 0143, 
  0157, 0156, 0146, 0151, 0147, 0061, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 
  0145, 0076, 0074, 0057, 0151, 0164, 0145, 0155, 0076, 0074, 0151, 0164, 0145, 0155, 0076, 0074, 
  0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 0075, 0042, 
  0154, 0141, 0142, 0145, 0154, 0042, 0076, 0103, 0150, 0141, 0156, 0147, 0145, 0040, 0103, 0157, 
  0156, 0146, 0151, 0147, 0062, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 
  0076, 0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 
  0075, 0042, 0141, 0143, 0164, 0151, 0157, 0156, 0042, 0076, 0141, 0160, 0160, 0056, 0143, 0157, 
  0156, 0146, 0151, 0147, 0062, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 
  0076, 0074, 0057, 0151, 0164, 0145, 0155, 0076, 0074, 0151, 0164, 0145, 0155, 0076, 0074, 0141, 
  0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 0075, 0042, 0154, 
  0141, 0142, 0145, 0154, 0042, 0076, 0103, 0150, 0141, 0156, 0147, 0145, 0040, 0103, 0157, 0156, 
  0146, 0151, 0147, 0063, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0076, 
  0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 0075, 
  0042, 0141, 0143, 0164, 0151, 0157, 0156, 0042, 0076, 0141, 0160, 0160, 0056, 0143, 0157, 0156, 
  0146, 0151, 0147, 0063, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0076, 
  0074, 0057, 0151, 0164, 0145, 0155, 0076, 0074, 0057, 0163, 0165, 0142, 0155, 0145, 0156, 0165, 
  0076, 0074, 0151, 0164, 0145, 0155, 0076, 0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 
  0145, 0040, 0156, 0141, 0155, 0145, 0075, 0042, 0154, 0141, 0142, 0145, 0154, 0042, 0076, 0101, 
  0142, 0157, 0165, 0164, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0076, 
  0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 0075, 
  0042, 0141, 0143, 0164, 0151, 0157, 0156, 0042, 0076, 0141, 0160, 0160, 0056, 0141, 0142, 0157, 
  0165, 0164, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0076, 0074, 0057, 
  0151, 0164, 0145, 0155, 0076, 0074, 0151, 0164, 0145, 0155, 0076, 0074, 0141, 0164, 0164, 0162, 
  0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 0155, 0145, 0075, 0042, 0154, 0141, 0142, 0145, 
  0154, 0042, 0076, 0105, 0170, 0151, 0164, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 
  0164, 0145, 0076, 0074, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0040, 0156, 0141, 
  0155, 0145, 0075, 0042, 0141, 0143, 0164, 0151, 0157, 0156, 0042, 0076, 0141, 0160, 0160, 0056, 
  0161, 0165, 0151, 0164, 0074, 0057, 0141, 0164, 0164, 0162, 0151, 0142, 0165, 0164, 0145, 0076, 
  0074, 0057, 0151, 0164, 0145, 0155, 0076, 0074, 0057, 0163, 0145, 0143, 0164, 0151, 0157, 0156, 
  0076, 0074, 0057, 0155, 0145, 0156, 0165, 0076, 0074, 0057, 0151, 0156, 0164, 0145, 0162, 0146, 
  0141, 0143, 0145, 0076, 0012, 0000, 0000, 0050, 0165, 0165, 0141, 0171, 0051, 0147, 0164, 0153, 
  0065, 0067, 0057, 0000, 0000, 0000, 0000, 0000, 0057, 0000, 0000, 0000, 0001, 0000, 0000, 0000
} };
#else /* _MSC_VER */
static const SECTION union { const guint8 data[865]; const double alignment; void * const ptr;}  gtk57_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\164\000\000\000\000\000\000\050\003\000\000\000"
  "\000\000\000\000\001\000\000\000\002\000\000\000\336\314\043\012"
  "\001\000\000\000\164\000\000\000\013\000\166\000\200\000\000\000"
  "\115\003\000\000\125\315\142\036\002\000\000\000\115\003\000\000"
  "\006\000\114\000\124\003\000\000\130\003\000\000\324\265\002\000"
  "\377\377\377\377\130\003\000\000\001\000\114\000\134\003\000\000"
  "\140\003\000\000\155\145\156\165\142\141\162\056\170\155\154\000"
  "\275\002\000\000\000\000\000\000\074\077\170\155\154\040\166\145"
  "\162\163\151\157\156\075\042\061\056\060\042\040\145\156\143\157"
  "\144\151\156\147\075\042\125\124\106\055\070\042\077\076\012\074"
  "\151\156\164\145\162\146\141\143\145\076\074\155\145\156\165\040"
  "\151\144\075\042\141\160\160\055\155\145\156\165\042\076\074\163"
  "\145\143\164\151\157\156\076\074\163\165\142\155\145\156\165\076"
  "\074\141\164\164\162\151\142\165\164\145\040\156\141\155\145\075"
  "\042\154\141\142\145\154\042\076\103\157\156\146\151\147\074\057"
  "\141\164\164\162\151\142\165\164\145\076\074\151\164\145\155\076"
  "\074\141\164\164\162\151\142\165\164\145\040\156\141\155\145\075"
  "\042\154\141\142\145\154\042\076\103\150\141\156\147\145\040\103"
  "\157\156\146\151\147\061\074\057\141\164\164\162\151\142\165\164"
  "\145\076\074\141\164\164\162\151\142\165\164\145\040\156\141\155"
  "\145\075\042\141\143\164\151\157\156\042\076\141\160\160\056\143"
  "\157\156\146\151\147\061\074\057\141\164\164\162\151\142\165\164"
  "\145\076\074\057\151\164\145\155\076\074\151\164\145\155\076\074"
  "\141\164\164\162\151\142\165\164\145\040\156\141\155\145\075\042"
  "\154\141\142\145\154\042\076\103\150\141\156\147\145\040\103\157"
  "\156\146\151\147\062\074\057\141\164\164\162\151\142\165\164\145"
  "\076\074\141\164\164\162\151\142\165\164\145\040\156\141\155\145"
  "\075\042\141\143\164\151\157\156\042\076\141\160\160\056\143\157"
  "\156\146\151\147\062\074\057\141\164\164\162\151\142\165\164\145"
  "\076\074\057\151\164\145\155\076\074\151\164\145\155\076\074\141"
  "\164\164\162\151\142\165\164\145\040\156\141\155\145\075\042\154"
  "\141\142\145\154\042\076\103\150\141\156\147\145\040\103\157\156"
  "\146\151\147\063\074\057\141\164\164\162\151\142\165\164\145\076"
  "\074\141\164\164\162\151\142\165\164\145\040\156\141\155\145\075"
  "\042\141\143\164\151\157\156\042\076\141\160\160\056\143\157\156"
  "\146\151\147\063\074\057\141\164\164\162\151\142\165\164\145\076"
  "\074\057\151\164\145\155\076\074\057\163\165\142\155\145\156\165"
  "\076\074\151\164\145\155\076\074\141\164\164\162\151\142\165\164"
  "\145\040\156\141\155\145\075\042\154\141\142\145\154\042\076\101"
  "\142\157\165\164\074\057\141\164\164\162\151\142\165\164\145\076"
  "\074\141\164\164\162\151\142\165\164\145\040\156\141\155\145\075"
  "\042\141\143\164\151\157\156\042\076\141\160\160\056\141\142\157"
  "\165\164\074\057\141\164\164\162\151\142\165\164\145\076\074\057"
  "\151\164\145\155\076\074\151\164\145\155\076\074\141\164\164\162"
  "\151\142\165\164\145\040\156\141\155\145\075\042\154\141\142\145"
  "\154\042\076\105\170\151\164\074\057\141\164\164\162\151\142\165"
  "\164\145\076\074\141\164\164\162\151\142\165\164\145\040\156\141"
  "\155\145\075\042\141\143\164\151\157\156\042\076\141\160\160\056"
  "\161\165\151\164\074\057\141\164\164\162\151\142\165\164\145\076"
  "\074\057\151\164\145\155\076\074\057\163\145\143\164\151\157\156"
  "\076\074\057\155\145\156\165\076\074\057\151\156\164\145\162\146"
  "\141\143\145\076\012\000\000\050\165\165\141\171\051\147\164\153"
  "\065\067\057\000\000\000\000\000\057\000\000\000\001\000\000\000"
  "" };
#endif /* !_MSC_VER */

static GStaticResource static_resource = { gtk57_resource_data.data, sizeof (gtk57_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *gtk57_get_resource (void);
GResource *gtk57_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
