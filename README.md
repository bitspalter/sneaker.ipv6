# sneaker.ipv6 (alpha)

1. compile:
g++ *.cpp -std=c++11 -o sneaker.ipv6 -no-pie -Wall \`pkg-config gtkmm-3.0 --cflags --libs\` -lcap

2. set capabilities for raw socket and promiscuous mode as non root:

   setcap cap_net_raw,cap_net_admin=eip ./sneaker.ipv6

![alt tag](https://github.com/bitspalter/sneaker.ipv6/blob/main/sneaker.v6.png "sneaker.ipv6")
