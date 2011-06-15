# -*- mode:python; -*-

RECIPE_ARCH		= "cross/${MACHINE_ARCH}"
RECIPE_ARCH_MACHINE	= "cross/${MACHINE}"

# Default packages is stage (cross) packages
PACKAGES_append		+= "${SYSROOT_PACKAGES}"
SYSROOT_PACKAGES	?= ""

#DEFAULT_DEPENDS = "cross:toolchain ${TARGET_ARCH}/sysroot-dev"

# Set host=build to get architecture triplet build/build/target
HOST_ARCH		= "${BUILD_ARCH}"
HOST_PREFIX		= "${BUILD_PREFIX}"
HOST_CFLAGS		= "${BUILD_CFLAGS}"
HOST_CPPFLAGS		= "${BUILD_CPPFLAGS}"
HOST_OPTIMIZATION	= "${BUILD_OPTIMIZATION}"
HOST_CFLAGS		= "${BUILD_CFLAGS}"
HOST_CXXFLAGS		= "${BUILD_CXXFLAGS}"
HOST_LDFLAGS		= "${BUILD_LDFLAGS}"

# Arch tuple arguments for configure (oe_runconf in autotools.bbclass)
OECONF_ARCHTUPLE = "--build=${BUILD_ARCH} --host=${HOST_ARCH} --target=${TARGET_ARCH}"

# Use stage_* path variables for host paths
base_prefix		= "${stage_base_prefix}"
prefix			= "${stage_prefix}"
exec_prefix		= "${stage_exec_prefix}"
base_bindir		= "${stage_base_bindir}"
base_sbindir		= "${stage_base_sbindir}"
base_libexecdir		= "${stage_base_libexecdir}"
base_libdir		= "${stage_base_libdir}"
base_includedir		= "${stage_base_includedir}"
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

# Fixup PACKAGE_ARCH_* variables for sysroot packages
def fixup_package_arch(d):
    arch_prefix = bb.data.getVar('RECIPE_TYPE', d, True) + '/'
    arch = bb.data.getVar('RECIPE_ARCH', d, True).partition(arch_prefix)
    if not arch[0] and arch[1]:
        # take part after / of RECIPE_ARCH if it begins with $RECIPE_TYPE/
        arch = arch[2]
    else:
        arch = '${TARGET_ARCH}'
    packages = bb.data.getVar('PACKAGES', d, True).split()
    sysroot_packages = bb.data.getVar('SYSROOT_PACKAGES', d, True).split()
    for pkg in packages:
        if not bb.data.getVar('PACKAGE_ARCH_'+pkg, d, False):
            if pkg in sysroot_packages:
                pkg_arch = 'sysroot/'+arch
            else:
                pkg_arch = 'cross/'+arch
            bb.data.setVar('PACKAGE_ARCH_'+pkg, pkg_arch, d)

def fixup_provides(d):
    pn = bb.data.getVar('PN', d, True) + '-'
    target_arch = bb.data.getVar('TARGET_ARCH', d, True) + '/'
    packages = bb.data.getVar('PACKAGES', d, True).split()
    sysroot_packages = bb.data.getVar('SYSROOT_PACKAGES', d, True).split()

    for pkg in packages:
        provides_changed = False

        provides = (bb.data.getVar('PROVIDES_'+pkg, d, False) or '').split()

        if not pkg in provides:
            provides = [pkg] + provides
            provides_changed = True

	if pkg in sysroot_packages:

            if pkg.endswith("-dev"):
                base_pkg = pkg[:-4]
                if base_pkg in sysroot_packages:
                    cross_provides = base_pkg.replace(pn, target_arch, 1)
                    if not cross_provides in provides:
                        provides += [cross_provides]
                        provides_changed = True
                    depends = (d.getVar("DEPENDS_" + pkg, True) or "").split()
                    if not base_pkg in depends:
                        depends.append(base_pkg)
                    d.setVar("DEPENDS_" + pkg, " ".join(depends))
                else:
                    cross_provides = pkg.replace(pn, target_arch, 1)
                    if not cross_provides in provides:
                        provides += [cross_provides]
                        provides_changed = True

            else:
                cross_provides = pkg.replace(pn, target_arch, 1)
                if not pkg + "-dev" in sysroot_packages:
                    if not cross_provides in provides:
                        provides += [cross_provides]
                        provides_changed = True

        if provides_changed:
            bb.data.setVar('PROVIDES_%s'%pkg, ' '.join(provides), d)

REBUILDALL_SKIP = "1"
RELAXED = "1"