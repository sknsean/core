# -*- mode:python; -*-

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "\
  gcc dl stdc++ supc++ resolv util crypt pthread thread_db bfd \
  m rt anl BrokenLocale nsl memusage pcprofile SegFault \
  nss_files nss_dns nss_compat nss_nis nss_nisplus nss_hesiod \
"
AUTO_PACKAGE_LIBS_PKGPREFIX = "sysroot-lib"
AUTO_PACKAGE_LIBS_LIBDIR = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}:lib::.so,.so.*,-*.so: \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}:lib:::.so,.a,_nonshared.a,.la \
"
TARGET_PACKAGES = "${LIBS_AUTO_PACKAGES}"

# We always build all packages, so care must be taken to choose the
# right sysroot packages as there can be multiple builds providing
# (almost) the same
PACKAGES = "${PN}-dbg ${PN}-g++ ${PN} ${PN}-doc ${PN}-locale ${PN}-gdb ${PN}-ldscripts"

PROVIDES_${PN} = "cc"
DEPENDS_${PN} = "target:${PN}-sysroot-dev"
RDEPENDS_${PN} = "target:${PN}-sysroot-dev"
PROVIDES_${PN}-g++ = "c++"
DEPENDS_${PN}-g++ = "target:${PN}-sysroot-c++-dev"

DEPENDS_${PN}-sysroot-libnss-dns	= "${PN}-sysroot-libresolv"
RDEPENDS_${PN}-sysroot-libnss-dns	= "${PN}-sysroot-libresolv"
DEPENDS_${PN}-sysroot-librt-dev		= "${PN}-sysroot-libpthread-dev"
DEPENDS_${PN}-sysroot-librt		= "${PN}-sysroot-libpthread"
RDEPENDS_${PN}-sysroot-librt		= "${PN}-sysroot-libpthread"
DEPENDS_${PN}-sysroot-libstdc++-dev	= "${PN}-sysroot-libgcc-dev ${PN}-sysroot-libm-dev"
DEPENDS_${PN}-sysroot-libstdc++		= "${PN}-sysroot-libgcc ${PN}-sysroot-libm ${PN}-sysroot-c++-dev"
RDEPENDS_${PN}-sysroot-libstdc++	= "${PN}-sysroot-libgcc ${PN}-sysroot-libm"
RDEPENDS_${PN}-sysroot-libdl           += "${PN}-sysroot-libc"

# 1. The install/ dir maintains it's crosstool-ng layout, and all
# FILES_* variables must therefore use crosstool-ng layout paths.

# 2. A fixup function should then be used to move files around inside
# the packages directories to get proper cross and sysroot package
# paths.

FILES_${PN} = "\
${base_bindir} \
${base_libdir}/*.so.* \
${base_libdir}/gcc/${TARGET_ARCH} \
${base_libdir}/*.a \
${base_libexecdir}/gcc/${TARGET_ARCH} \
${base_prefix}/${TARGET_ARCH}/bin \
${base_prefix}/${TARGET_ARCH}/lib \
${base_libdir}64 \
${base_prefix}/${TARGET_ARCH}/lib64 \
"

FILES_${PN}-c++ = "\
${base_bindir}/*++ \
${base_prefix}/${TARGET_ARCH}/bin/*++ \
"

FILES_${PN}-doc += "\
${base_prefix}/build.log* \
"

FILES_${PN}-dbg += "\
${base_prefix}/${TARGET_ARCH}/bin/.debug \
${libexecdir}/gcc/${TARGET_ARCH}/${CT_CC_VERSION}/.debug \
${libexecdir}/gcc/${TARGET_ARCH}/${CT_CC_VERSION}/*/.debug \
"

FILES_${PN}-gdb = "${datadir}/gcc-*/python"

FILES_${PN}-ldscripts = "${base_libdir}/ldscripts"

TARGET_PACKAGES += "${PN}-sysroot-libc"
FILES_${PN}-sysroot-libc = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/libc.so.* \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/libc-*.so \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/ld.so.* \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/ld-*.so \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/ld-*.so.* \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}64 \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}64 \
"
DEPENDS_${PN}-sysroot-libc = "${PN}-sysroot-libc-dev_${PV}"
PROVIDES_${PN}-sysroot-libc = "libc"

TARGET_PACKAGES += "${PN}-sysroot-libc-dev"
# FIXME: the lib64 symlink should be in separate package!
FILES_${PN}-sysroot-libc-dev = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/libc.so \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/libc.a \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/libc_nonshared.a \
"
RDEPENDS_${PN}-sysroot-libc-dev = "${PN}-sysroot-libc_${PV}"
PROVIDES_${PN}-sysroot-libc-dev = "libc-dev"

TARGET_PACKAGES += "${PN}-sysroot-gdbserver-dbg"
FILES_${PN}-sysroot-gdbserver-dbg = "\
${base_prefix}/${TARGET_ARCH}/debug-root${target_bindir}/.debug/gdb* \
${base_prefix}/${TARGET_ARCH}/debug-root${target_libdir}/.debug/libgdb* \
"

TARGET_PACKAGES += "${PN}-sysroot-gdbserver"
FILES_${PN}-sysroot-gdbserver = "\
${base_prefix}/${TARGET_ARCH}/debug-root${target_bindir}/gdbserver \
${datadir}/gdb \
"
RDEPENDS_${PN}-sysroot-gdbserver = "${PN}-sysroot-libdl"
PROVIDES_${PN}-sysroot-gdbserver += "target:util/gdbserver"

TARGET_PACKAGES += "${PN}-sysroot-gdbserver-doc"
FILES_${PN}-sysroot-gdbserver-doc = "\
${base_prefix}/${TARGET_ARCH}/debug-root${target_infodir}/gdbserver \
${base_prefix}/${TARGET_ARCH}/debug-root${target_docdir}/gdbserver \
${base_prefix}/${TARGET_ARCH}/debug-root${target_mandir}/man1/gdbserver.1 \
"

TARGET_PACKAGES += "${PN}-sysroot-trace-dbg"
FILES_${PN}-sysroot-trace-dbg = "\
${base_prefix}/${TARGET_ARCH}/debug-root${target_bindir}/.debug/*trace \
${base_prefix}/${TARGET_ARCH}/debug-root${target_libdir}/.debug/*trace* \
"

TARGET_PACKAGES += "${PN}-sysroot-trace"
FILES_${PN}-sysroot-trace = "\
${base_prefix}/${TARGET_ARCH}/debug-root${target_bindir}/strace \
${base_prefix}/${TARGET_ARCH}/debug-root${target_bindir}/ltrace \
${base_prefix}/${TARGET_ARCH}/debug-root${target_bindir}/strace-graph \
${base_prefix}/${TARGET_ARCH}/debug-root${target_libdir}/libinproctrace.so \
${base_prefix}/${TARGET_ARCH}/debug-root${target_sysconfdir}/ltrace.conf \
"
PROVIDES_${PN}-sysroot-trace += "target:util/ltrace target:util/strace"

TARGET_PACKAGES += "${PN}-sysroot-trace-doc"
FILES_${PN}-sysroot-trace-doc = "\
${base_prefix}/${TARGET_ARCH}/debug-root${target_infodir}/*trace \
${base_prefix}/${TARGET_ARCH}/debug-root${target_mandir}/*/*trace.* \
${base_prefix}/${TARGET_ARCH}/debug-root${target_docdir}/*trace \
"

TARGET_PACKAGES += "${PN}-sysroot-dbg"
FILES_${PN}-sysroot-dbg = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_bindir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_bindir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_sbindir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_sbindir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libexecdir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libexecdir}/.debug \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/gconv/.debug \
"

TARGET_PACKAGES += "${PN}-sysroot-c++-dev"
FILES_${PN}-sysroot-c++-dev = "${base_prefix}/${TARGET_ARCH}/include/c++"
DEPENDS_${PN}-sysroot-c++-dev  = "${PN}-sysroot-dev"
RDEPENDS_${PN}-sysroot-c++-dev = "${PN}-sysroot-dev"

TARGET_PACKAGES += "${PN}-sysroot-dev"
FILES_${PN}-sysroot-dev = "\
${base_prefix}/${TARGET_ARCH}/include \
${base_prefix}/${TARGET_ARCH}/sysroot${target_includedir} \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/*.a \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/*.o \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/*.py \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/*.la \
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/ldscripts \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/*.o \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/*.a \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/*.la \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/*.so \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/gconv \
${base_prefix}/${TARGET_ARCH}/sysroot/mingw \
"
DEPENDS_${PN}-sysroot-dev  = "${PN}-sysroot-libc ${PN}-sysroot-libgcc"
RDEPENDS_${PN}-sysroot-dev = "${PN}-sysroot-libc-dev ${PN}-sysroot-libgcc-dev"

FILES_${PN}-sysroot-dev:>TARGET_OS_mingw32 = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_bindir}/*.dll \
"

TARGET_PACKAGES += "${PN}-sysroot-doc"
FILES_${PN}-sysroot-doc = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_infodir} \
${base_prefix}/${TARGET_ARCH}/sysroot${target_mandir} \
${base_prefix}/${TARGET_ARCH}/sysroot${target_docdir} \
"

# Hackeydihack.... should instead get all sysroot doc in target_docdir
FILES_${PN}-sysroot-doc:>TARGET_OS_mingw32 = "\
${base_prefix}/${TARGET_ARCH}/sysroot/doc/runtime \
"

TARGET_PACKAGES += "${PN}-sysroot-locale"
FILES_${PN}-sysroot-locale = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_datadir}/locale \
${base_prefix}/${TARGET_ARCH}/sysroot${target_datadir}/i18n \
"

FILES_${PN}-sysroot-libgcc = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/libgcc_s.so.* \
"
RDEPENDS_${PN}-sysroot-libgcc += "${PN}-sysroot-libc"

FILES_${PN}-sysroot-libgcc-dev = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_libdir}/libgcc_s.so \
"

FILES_${PN}-sysroot-libm-dev = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/libieee.a \
"
RDEPENDS_${PN}-sysroot-libm += "${PN}-sysroot-libc"

FILES_${PN}-sysroot-libbfd = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/libbfd-*.so \
${base_prefix}/${TARGET_ARCH}/sysroot${target_libdir}/libbfd.so"

TARGET_PACKAGES += "${PN}-sysroot-nscd"
FILES_${PN}-sysroot-nscd = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_sbindir}/nscd"
PROVIDES_${PN}-sysroot-nscd = "target:util/rpcgen target:util/nscd"
PROVIDES_${PN}-sysroot-nscd:machine = ""
PROVIDES_${PN}-sysroot-nscd:sdk = ""
PROVIDES_${PN}-sysroot-nscd:canadian-cross = ""

TARGET_PACKAGES += "${PN}-sysroot-rpc"
FILES_${PN}-sysroot-rpc = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_bindir}/rpcgen \
${base_prefix}/${TARGET_ARCH}/sysroot${target_sbindir}/rpcinfo \
${base_prefix}/${TARGET_ARCH}/sysroot${target_sysconfdir}/rpc"
PROVIDES_${PN}-sysroot-rpc = "target:util/rpcgen target:util/rpcinfo"
PROVIDES_${PN}-sysroot-rpc:machine = ""
PROVIDES_${PN}-sysroot-rpc:sdk = ""
PROVIDES_${PN}-sysroot-rpc:canadian-cross = ""

TARGET_PACKAGES += "${PN}-sysroot-ldconfig"
FILES_${PN}-sysroot-ldconfig = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_base_sbindir}/ldconfig"
PROVIDES_${PN}-sysroot-ldconfig = "target:util/ldconfig"
PROVIDES_${PN}-sysroot-ldconfig:machine = ""
PROVIDES_${PN}-sysroot-ldconfig:sdk = ""
PROVIDES_${PN}-sysroot-ldconfig:canadian-cross = ""

TARGET_PACKAGES += "${PN}-sysroot-ldd"
FILES_${PN}-sysroot-ldd = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_bindir}/ldd"
PROVIDES_${PN}-sysroot-ldd = "target:util/ldd"
PROVIDES_${PN}-sysroot-ldd:machine = ""
PROVIDES_${PN}-sysroot-ldd:sdk = ""
PROVIDES_${PN}-sysroot-ldd:canadian-cross = ""

TARGET_PACKAGES += "${PN}-sysroot-catchsegv"
FILES_${PN}-sysroot-catchsegv = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_bindir}/catchsegv"
PROVIDES_${PN}-sysroot-catchsegv = "target:util/catchsegv"
PROVIDES_${PN}-sysroot-catchsegv:machine = ""
PROVIDES_${PN}-sysroot-catchsegv:sdk = ""
PROVIDES_${PN}-sysroot-catchsegv:canadian-cross = ""

TARGET_PACKAGES += "${PN}-sysroot-sprof"
FILES_${PN}-sysroot-sprof = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_bindir}/sprof"
PROVIDES_${PN}-sysroot-sprof = "target:util/sprof"
PROVIDES_${PN}-sysroot-sprof:machine = ""
PROVIDES_${PN}-sysroot-sprof:sdk = ""
PROVIDES_${PN}-sysroot-sprof:canadian-cross = ""

TARGET_PACKAGES += "${PN}-sysroot-timezone-utils"
FILES_${PN}-sysroot-timezone-utils = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_bindir}/tzselect \
${base_prefix}/${TARGET_ARCH}/sysroot${target_sbindir}/zdump \
${base_prefix}/${TARGET_ARCH}/sysroot${target_sbindir}/zic \
${base_prefix}/${TARGET_ARCH}/sysroot${target_datadir}/zoneinfo \
"
PROVIDES_${PN}-sysroot-timezone-utils = "\
    target:util/tzselect target:util/zdump target:util/zic target:util/zoneinfo"
PROVIDES_${PN}-sysroot-timezone-utils:machine = ""
PROVIDES_${PN}-sysroot-timezone-utils:sdk = ""
PROVIDES_${PN}-sysroot-timezone-utils:canadian-cross = ""

TARGET_PACKAGES += "${PN}-sysroot-iconv-utils"
FILES_${PN}-sysroot-iconv-utils = "\
${base_prefix}/${TARGET_ARCH}/sysroot${target_bindir}/iconv \
${base_prefix}/${TARGET_ARCH}/sysroot${target_sbindir}/iconvconfig"
PROVIDES_${PN}-sysroot-iconv-utils = "target:util/iconv target:util/iconvconfig"
PROVIDES_${PN}-sysroot-iconv-utils:machine = ""
PROVIDES_${PN}-sysroot-iconv-utils:sdk = ""
PROVIDES_${PN}-sysroot-iconv-utils:canadian-cross = ""

# throw everything else in this garbage package, which is to be considered a WIP package aimed at being empty
TARGET_PACKAGES += "${PN}-sysroot-garbage"
FILES_${PN}-sysroot-garbage = "\
${base_prefix}/${TARGET_ARCH}/sysroot \
"

# Remaining / ignored files
#/include
#/lib (- /lib/gcc/${TARGET_ARCH})
#/${TARGET_ARCH}/debug-root

SPLIT_FUNCS = "do_split_sysroot_mangle"
SPLIT_FUNCS:>TARGET_OS_mingw32 = " do_split_sysroot_mangle_mingw32"
SPLIT_FUNCS:>cross = " do_split_sysroot_mangle_stage"
SPLIT_FUNCS:>sdk-cross = " do_split_sysroot_mangle_stage"
SPLIT_FUNCS:>native = " do_split_sysroot_mangle_stage"
SPLIT_FUNCS:>machine = " do_split_sysroot_mangle_sdk"
SPLIT_FUNCS:>sdk = " do_split_sysroot_mangle_sdk"
SPLIT_FUNCS:>canadian-cross = " do_split_sysroot_mangle_sdk"
do_split[postfuncs] = "${SPLIT_FUNCS}"

# Move the machine sysroot packages into proper target layout
do_split_sysroot_mangle () {
	cd ${PKGD}
	# Fixup the layout of the sysroot packages
	for pkg in ${TARGET_PACKAGES} ; do
		if [ -d $pkg/${TARGET_ARCH} ] ; then
			(
			cd $pkg/${TARGET_ARCH}
			if [ -d debug-root ] ; then
				mv debug-root/* ../
				rmdir debug-root
			fi
			if [ -d sysroot ] ; then
				mv sysroot/* ../
				rmdir sysroot
			fi
			if [ -L include ] ; then
				rm -f include
			fi
			if [ -d include ] ; then
				mkdir -p ..${target_includedir}
				cp -r include/* ..${target_includedir}
				rm -rf include
			fi
			rm -f lib
			if [ -d lib ] ; then
				mkdir -p ..${target_libdir}
				mv lib/* ..${target_libdir}
				rmdir lib
			fi
			cd ..
			rmdir ${TARGET_ARCH}
			)
		fi
	done
	ln -s ./sysroot/usr/include ${PN}/${TARGET_ARCH}/include
}

do_split_sysroot_mangle_mingw32 () {
	cd ${PKGD}
	# Move object files (*.o) to usr/lib so that ld can find them through
	# the mingw/lib dir (mingw symlinks to /usr)
	for pkg in ${TARGET_PACKAGES} ; do
		if [ -d $pkg/lib ] ; then
			for f in $pkg/lib/*.o ; do
				test -f $f && mv $f $pkg${target_libdir}/
			done
		fi
	done
}

# Add symlinks to get sysroot back on stage for internal cross packages
do_split_sysroot_mangle_stage () {
	cd ${PKGD}
	ln -s ../../${TARGET_TYPE} ${PN}/${TARGET_ARCH}/sysroot
}

# Add empty sysroot dir in sdk packages
do_split_sysroot_mangle_sdk () {
	cd ${PKGD}
	mkdir -p ${PN}/${TARGET_ARCH}/sysroot
}