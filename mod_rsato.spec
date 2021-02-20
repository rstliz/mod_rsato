%define _unpackaged_files_terminate_build 0
%define	__soversion	1

Summary:	Apache Module For Json Api.
Name:		mod_rsato
Version:	1.0.0
Release:	1
License:	Ryo Sato
Packager:	Ryo Sato
BuildRoot:	%{_tmppath}/%{name}-%{version}-root
Requires:	libapreq2

%description
Apache Module For Json Api.

%install
rm -rf ${RPM_BUILD_ROOT}
mkdir -p ${RPM_BUILD_ROOT}/usr/lib64/httpd/modules
install -m755 mod_rsato.so ${RPM_BUILD_ROOT}/usr/lib64/httpd/modules/mod_rsato.so

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%attr(0755,root,root) /usr/lib64/httpd/modules/mod_rsato.so

%changelog

