Name:		numcal
Version:	0.1.0
Release:	0%{?dist}
Summary:	Numerical Calculation
Group:		System Environment/Libraries
License:	LGPL v3+
Source0:    %{name}-%{version}.tar.gz

BuildRequires:  cmake, cuba-devel

%description
Numerical Calculation

%prep
%setup -q

%build
mkdir build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
make %{?_smp_mflags}
cd ../

%install
rm -rf %{buildroot}
cd build
make install DESTDIR=%{buildroot}
cd ../

%files
%{_bindir}/numcal

%changelog

