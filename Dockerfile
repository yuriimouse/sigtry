FROM rockylinux/rockylinux:latest

# gcc
RUN dnf install gcc -y

# make
RUN dnf install epel-release -y
RUN dnf install make findutils autoconf automake libtool -y
RUN dnf --enablerepo=devel install binutils -y
