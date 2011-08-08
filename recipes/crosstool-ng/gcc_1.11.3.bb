BBCLASSEXTEND="cross sdk-cross canadian-cross"

DEFAULT_CONFIG_toolchain_cc			= "gcc"
DEFAULT_CONFIG_toolchain_cc_version		= "${GCC_VERSION}"

DEFAULT_CONFIG_toolchain_libc			= "glibc"
DEFAULT_CONFIG_toolchain_libc_version		= "2.12.2"

DEFAULT_CONFIG_toolchain_libc_linux-uclibc	= "uclibc"
#DEFAULT_CONFIG_toolchain_libc_version_linux-uclibc = ???

#DEFAULT_CONFIG_toolchain_libc			= "eglibc"
#DEFAULT_CONFIG_toolchain_libc_version		= "2_13"
#DEFAULT_CONFIG_toolchain_libc_eglibc_revision	= "HEAD"

DEFAULT_CONFIG_toolchain_kernel_version_machine	= "2.6.38.4"
DEFAULT_CONFIG_toolchain_kernel_version_sdk	= "2.6.38.4"
DEFAULT_CONFIG_toolchain_kernel_version_build	= "2.6.38.4"

DEFAULT_CONFIG_toolchain_mingwrt_version	= "3.18"
DEFAULT_CONFIG_toolchain_w32api_version		= "3.14"

DEFAULT_CONFIG_toolchain_min_kernel_machine	= "2.6.32"
DEFAULT_CONFIG_toolchain_min_kernel_sdk		= "2.6.27"
DEFAULT_CONFIG_toolchain_min_kernel_build	= "2.6.27"

DEFAULT_CONFIG_toolchain_binutils_version	= "2.20.1"
DEFAULT_CONFIG_toolchain_gdb_version		= "7.2"
DEFAULT_CONFIG_toolchain_gmp_version		= "5.0.1"
DEFAULT_CONFIG_toolchain_mpfr_version		= "3.0.0"
DEFAULT_CONFIG_toolchain_ppl_version		= "0.10.2"
DEFAULT_CONFIG_toolchain_cloog_version		= "0.15.10"
DEFAULT_CONFIG_toolchain_mpc_version		= "0.9"
DEFAULT_CONFIG_toolchain_libelf_version		= "0.8.13"

require toolchain.inc