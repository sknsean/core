RECIPE_TYPE			 = "native"
#
RECIPE_ARCH			 = "native/${BUILD_ARCH}"
RECIPE_ARCH_MACHINE		 = "native/${BUILD_ARCH}--${MACHINE}"

# Native packages does not runtime provide anything
RPROVIDES_${PN}		= ""
RDEPENDS_${PN}-dev 	= ""

# No default build dependencies (for now)
DEFAULT_DEPENDS		= ""

# Set host=build
HOST_ARCH		= "${BUILD_ARCH}"
HOST_PREFIX		= "${BUILD_PREFIX}"
HOST_CFLAGS		= "${BUILD_CFLAGS}"
HOST_CPPFLAGS		= "${BUILD_CPPFLAGS}"
HOST_OPTIMIZATION	= "${BUILD_OPTIMIZATION}"
HOST_CFLAGS		= "${BUILD_CFLAGS}"
HOST_CXXFLAGS		= "${BUILD_CXXFLAGS}"
HOST_LDFLAGS		= "${BUILD_LDFLAGS}"

# and target=build for architecture triplet build/build/build
TARGET_ARCH		= "${BUILD_ARCH}"
TARGET_PREFIX		= "${BUILD_PREFIX}"
TARGET_CFLAGS		= "${BUILD_CFLAGS}"
TARGET_CPPFLAGS		= "${BUILD_CPPFLAGS}"
TARGET_OPTIMIZATION	= "${BUILD_OPTIMIZATION}"
TARGET_CFLAGS		= "${BUILD_CFLAGS}"
TARGET_CXXFLAGS		= "${BUILD_CXXFLAGS}"
TARGET_LDFLAGS		= "${BUILD_LDFLAGS}"

TARGET_SYSROOT		= "${STAGE_DIR}/native"

# Arch tuple arguments for configure (oe_runconf in autotools.bbclass)
OECONF_ARCHTUPLE = "--build=${BUILD_ARCH}"

# Use stage_* path variables for host paths
base_prefix		= "${stage_base_prefix}"
prefix			= "${stage_prefix}"
exec_prefix		= "${stage_exec_prefix}"
base_bindir		= "${stage_base_bindir}"
base_sbindir		= "${stage_base_sbindir}"
base_libexecdir		= "${stage_base_libexecdir}"
base_libdir		= "${stage_base_libdir}"
base_includecdir	= "${stage_base_includedir}"
datadir			= "${stage_datadir}"
sysconfdir		= "${stage_sysconfdir}"
servicedir		= "${stage_servicedir}"
sharedstatedir		= "${stage_sharedstatedir}"
localstatedir		= "${stage_localstatedir}"
runitservicedir		= "${stage_runitservicedir}"
infodir			= "${stage_infodir}"
mandir			= "${stage_mandir}"
docdir			= "${stage_docdir}"
bindir			= "${stage_bindir}"
sbindir			= "${stage_sbindir}"
libexecdir		= "${stage_libexecdir}"
libdir			= "${stage_libdir}"
includedir		= "${stage_includedir}"

# Use stage_* path variables for target paths
target_base_prefix	= "${stage_base_prefix}"
target_prefix		= "${stage_prefix}"
target_exec_prefix	= "${stage_exec_prefix}"
target_base_bindir	= "${stage_base_bindir}"
target_base_sbindir	= "${stage_base_sbindir}"
target_base_libexecdir	= "${stage_base_libexecdir}"
target_base_libdir	= "${stage_base_libdir}"
target_base_includecdir	= "${stage_base_includedir}"
target_datadir		= "${stage_datadir}"
target_sysconfdir	= "${stage_sysconfdir}"
target_servicedir	= "${stage_servicedir}"
target_sharedstatedir	= "${stage_sharedstatedir}"
target_localstatedir	= "${stage_localstatedir}"
target_runitservicedir	= "${stage_runitservicedir}"
target_infodir		= "${stage_infodir}"
target_mandir		= "${stage_mandir}"
target_docdir		= "${stage_docdir}"
target_bindir		= "${stage_bindir}"
target_sbindir		= "${stage_sbindir}"
target_libexecdir	= "${stage_libexecdir}"
target_libdir		= "${stage_libdir}"
target_includedir	= "${stage_includedir}"

NATIVE_PKG_CONFIG_PATH = "${STAGE_DIR}/native/share/pkgconfig"
NATIVE_PKG_CONFIG_DIR = "${STAGE_DIR}/native/lib/pkgconfig"
PKG_CONFIG_PATH		= "${NATIVE_PKG_CONFIG_PATH}"
PKG_CONFIG_LIBDIR	= "${NATIVE_PKG_CONFIG_DIR}"

base_do_install() {
    oe_runmake install
}

FIXUP_PACKAGE_ARCH = native_fixup_package_arch
def native_fixup_package_arch(d):
    arch = bb.data.getVar('RECIPE_ARCH', d, True).partition('native/')
    if not arch[0] and arch[1]:
        # take part after / of RECIPE_ARCH if it begins with $RECIPE_TYPE/
        arch = arch[2]
    else:
        arch = '${BUILD_ARCH}'
    for pkg in bb.data.getVar('PACKAGES', d, True).split():
        if not bb.data.getVar('PACKAGE_ARCH_'+pkg, d, False):
            pkg_arch = 'native/'+arch
            bb.data.setVar('PACKAGE_ARCH_'+pkg, pkg_arch, d)

FIXUP_PROVIDES = native_fixup_provides
def native_fixup_provides(d):
    target_arch = bb.data.getVar('TARGET_ARCH', d, True) + '/'
    for pkg in bb.data.getVar('PACKAGES', d, True).split():
    	provides = (bb.data.getVar('PROVIDES_'+pkg, d, True) or '').split()
        if not pkg in provides:
            provides = [pkg] + provides
            bb.data.setVar('PROVIDES_'+pkg, ' '.join(provides), d)
	if bb.data.getVar('RPROVIDES_'+pkg, d, True):
            bb.data.setVar('RPROVIDES_'+pkg, '', d)
	if bb.data.getVar('RDEPENDS_'+pkg, d, True):
            bb.data.setVar('RDEPENDS_'+pkg, '', d)

REBUILDALL_SKIP = "1"
RELAXED = "1"

BLACKLIST_VAR = "BLACKLIST_VAR BLACKLIST_PREFIX"
BLACKLIST_PREFIX = "MACHINE_"